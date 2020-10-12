#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using namespace std::chrono;

//function prototype to read in full matrices (used in main)
void readMatrix(int& nrows, int& ncols, int& nNZV, int& start_node, int tNZV[], int tIA[], int tJA[]);

//Compressed Spare Row matrix class
class CSR
{

    //overload the '<<' operator
    friend ostream& operator<< (ostream& os, const CSR& csr);

    protected:
        int noRows; //Number of rows of the original matrix
        int noCols; //Number of columns of the original matrix
        int noNonSparseValues; //Number of non-sparse values
        int* valueArray;
        int* IA;
        int* JA;
    public:

        //Constructors and Destructors
        CSR ();
        CSR (int n, int m, int numNZV);
        CSR (const CSR& csr);
        virtual ~CSR();

        //Public methods

        //Setter routines
        void setIA(int ia_array[]);
        void setJA(int ja_array[]);
        void setValueArray(int vv_array[]);

        void setSparseRow (int pos, int r, int c, int v);

        //Getter routines
        int getRows() const;
        int getCols() const;
        int getnumNZV() const;

        int* getJA() const;
        int* getIA() const;
        int* getValueArray() const;

        //Display routines
        void display_valueArray();
        void display_JA();
        void display_IA();

        //overload the '=' sign
        CSR* operator= (CSR& csr0);

};

//Default constructor
CSR::CSR ()
{
    noRows = 0;
    noCols = 0;
    noNonSparseValues = 0;

    //dynamically allocate memory for each of the arrays
    IA = new int[noRows+1];
    JA = new int[noNonSparseValues];
    valueArray = new int[noNonSparseValues];
}

//Constructor with user defined values
CSR::CSR (int n, int m, int numNZV)
{
    noRows = n;
    noCols = m;
    noNonSparseValues = numNZV;

    //dynamically allocate memory for each of the arrays
    IA = new int[noRows+1];
    JA = new int[noNonSparseValues];
    valueArray = new int[noNonSparseValues];
}

//Copy constructor
CSR::CSR (const CSR& csr)
{
    noRows = csr.noRows; //Number of rows of the original matrix
    noCols = csr.noCols; //Number of columns of the original matrix
    noNonSparseValues = csr.noNonSparseValues; //Number of non-sparse values

    //dynamically allocate memory for each of the arrays
    IA = csr.IA;
    JA = csr.JA;
    valueArray = csr.valueArray;
}

//Destructor
CSR::~CSR()
{
    delete [] valueArray;
    delete [] IA;
    delete [] JA;
}

//Public methods
int CSR::getRows() const {return noRows;}
int CSR::getCols() const {return noCols;}
int CSR::getnumNZV() const {return noNonSparseValues;}

int* CSR::getValueArray() const {return valueArray;}
int* CSR::getJA() const {return JA;}
int* CSR::getIA() const {return IA;}

// ---------------------------------------------------------------------------//
void CSR::setIA(int ia_array[])
{
    for (int i=0; i < (noRows+1); i++)
        IA[i] = ia_array[i];
}
// ---------------------------------------------------------------------------//


// ---------------------------------------------------------------------------//
void CSR::setJA(int ja_array[])
{
    for (int i=0; i < noNonSparseValues; i++)
        JA[i] = ja_array[i];
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
void CSR::setValueArray(int vv_array[])
{
    for (int i=0; i < noNonSparseValues; i++)
        valueArray[i] = vv_array[i];
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
void CSR::display_valueArray()
{
    for (int i=0; i < noNonSparseValues; i++)
        cout << valueArray[i] << " ";
    cout << endl;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
void CSR::display_JA()
{
    for (int i=0; i < noNonSparseValues; i++)
        cout << JA[i] << " ";
    cout << endl;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
void CSR::display_IA()
{
    for (int i=0; i < noRows; i++)
        cout << IA[i] << " ";
    cout << endl;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
CSR* CSR::operator= (CSR& csr0)
{

    noRows = csr0.noRows; //Number of rows of the original matrix
    noCols = csr0.noCols; //Number of columns of the original matrix
    noNonSparseValues = csr0.noNonSparseValues; //Number of non-sparse values

    IA = csr0.IA;
    JA = csr0.JA;
    valueArray = csr0.valueArray;

    return this;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
ostream& operator<< (ostream& output, const CSR& csr)
{
    int j_index = 0;
    int va_count = 0;

    int* ja;
    int* va;

    ja = csr.getJA();
    va = csr.getValueArray();
    int nr = csr.getRows();
    int nc = csr.getCols();

    //print out matrix in row x col form
    for (int i=0; i < nr; i++){
        for (int j=0; j < nc; j++){

            if (j == *ja){
                output << *va << " " ;
                va++;
                ja++;
            }
            else
                output << "0" << " ";
        }
        output << endl;
    }
    return output;
}
// ---------------------------------------------------------------------------//

//Graph class. Built using a sparse adjacency matrix
class Graph : public CSR
{

    //overload the '<<' operator
    friend ostream& operator<< (ostream& os, const Graph& graph0);

    protected:
        int* parentArray;
        int numVertices;
        int startNode;

    public:
        //Default constructor
        Graph ();

        //2nd constructor
        Graph (int nV, int start_node, int n, int m, int numNZV);

        //Copy constructor
        Graph (const Graph& graph0);

        //Default destructor
        virtual ~Graph();

        //Setter Routines
        void setRoot(int rNode);
        void setParent(int curr_child, int curr_parent);

        //Getter routines
        int getNumVertices() const;
        int getStartNode() const;

        //Graph traversal functions
        void BFS(int start_node);
        void DFS(int start_node);

};

// -------------------------------------------------------------------------------------//
//                      G R A P H    C L A S S    M E T H O D S
// -------------------------------------------------------------------------------------//


//Default constructor
Graph::Graph ()
{
    numVertices = 1;
    startNode = 0;
    parentArray = new int[numVertices];

    //initialize parent array
    for (int i=0; i<getNumVertices(); i++)
        parentArray[i] = i;

}

//Constructor with user defined values
Graph::Graph (int nV, int start_node, int n, int m, int numNZV): CSR (n, m, numNZV)
{
    //initialize number of nodes and root node
    numVertices = nV;
    startNode = start_node;

    parentArray = new int[numVertices];

    //initialize parent array
    for (int i=0; i<getNumVertices(); i++)
        parentArray[i] = i;

}

//Copy constructor
Graph::Graph (const Graph& graph0)
{
    //Number of vertices in graph
    numVertices = graph0.numVertices;

    //copy over the start node
    startNode   = graph0.startNode;

    parentArray = new int[numVertices];

    //set parent array of object to that of the copied object
    for (int i=0; i<getNumVertices(); i++)
        parentArray[i] = graph0.parentArray[i];

}

//Destructor
Graph::~Graph ()
{
    delete[] parentArray;
}

//Get size of the graph (number of vertices)
int Graph::getNumVertices() const {return numVertices;}

//Get starting node of graph
int Graph::getStartNode() const {return startNode;}

// ---------------------------------------------------------------------------//
//Set the root node
void Graph::setRoot(int rNode)
{
    parentArray[rNode] = -1;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Set the parent of a child node
void Graph::setParent(int curr_child, int curr_parent)
{
    //cout << "child: "<< curr_child << ", parent: "<< curr_parent << endl;

    parentArray[curr_child] = curr_parent;
}
// ---------------------------------------------------------------------------//

void Graph::BFS(int start_node)
{
    //USE QUEUE FOR THIS

    //store number of vertices in a separate variable
    int totalVertices = getNumVertices();

	// Mark all the vertices as not visited
	bool *visited = new bool[totalVertices];
	for(int i = 0; i < totalVertices; i++)
		visited[i] = false;

	// Create a queue for BFS
	queue<int> myqueue;

	// Mark the current node as visited and enqueue it
	visited[start_node] = true;
	myqueue.push(start_node);

    //set root node of parentArray;
    setRoot(start_node);

    int number_of_ones=0;

	while(!myqueue.empty())
	{
		// Dequeue a vertex from queue and print it
		start_node = myqueue.front();
		//cout << start_node << " ";
		myqueue.pop();

		// Get all adjacent vertices. If a adjacent has not been visited,
		// then mark it visited and enqueue it

        for (int j=0; j < totalVertices; j++){

            number_of_ones = IA[start_node+1]-IA[start_node];

            for (int t=0; t<=(number_of_ones-1); t++){
                if ((!visited[j]) && (JA[IA[start_node]+t] == j)){

                    visited[j] = true;
                    myqueue.push(j);
                    setParent(j, start_node);
                }
            }
        }
 	}
}

void Graph::DFS(int start_node)
{
    //USE STACK FOR THIS

    //store number of vertices in a separate variable
    int totalVertices = getNumVertices();

	// Mark all the vertices as not visited
	bool *visited = new bool[totalVertices];
	for(int i = 0; i < totalVertices; i++)
		visited[i] = false;

	// Create a stack for BFS
	int mystack[totalVertices];

    // Specify start of stack
    int top_of_stack = 0;
    //int top_of_stack = start_node;
	//cout << top_of_stack << " ";

	// Mark the current node as visited and enqueue it
	visited[start_node] = true;
	mystack[top_of_stack] = start_node;

    //set root node of parentArray;
    setRoot(start_node);

    int number_of_ones=0;

    while(top_of_stack >= 0)
	{

        //boolean to see if any vertex was visited
        bool changed = false;
        bool found = false;

        //get top of stack vertex
        int i = mystack[top_of_stack];

        //loop over all vertices and see if have any visits
        for (int j=0; j < totalVertices; j++){

            number_of_ones = IA[i+1] - IA[i];

            for (int t=0; t<=(number_of_ones-1); t++){

                if ((!visited[j]) && (JA[IA[i]+t] == j)){

                    visited[j] = true;
                    changed = true;
                    found = true;

                    //push vertex onto stack
                    top_of_stack+=1;
                    mystack[top_of_stack] = j;

                    //setParent(child, parent);
                    setParent(j, i);
                    //cout << j << " ";
                    break;
                }

            }
            if (found == true)
                break;
        }
        if (changed == false)
            top_of_stack -= 1;
    }
}

// ---------------------------------------------------------------------------//
//overloaded ostream operator function to print tree contents
ostream& operator<< (ostream& output, const Graph& graph)
{

    for (int i=0; i < graph.getNumVertices(); i++){
        output << i<<": "<< graph.parentArray[i]<<"\t";
    }

    return output;
}
// ---------------------------------------------------------------------------//


// -------------------------------------------------------------------------------------//
//                              M A I N     R O U T I N E
// -------------------------------------------------------------------------------------//

int main()
{
	int startNode;

	int n, m, numNZV;
	cin >> n >> m >> numNZV; //receive the n, m and numNZV for the adjacency matrix
	CSR* adjMat = new CSR(n, m, numNZV);
	//TODO: read in the matrix A from the input file and store it in the given format

    //declare some temporary arrays to store relevant info. Will be transferred to CSR class.
    int ia_a[n+1];
    int ja_a[numNZV];
    int vv_a[numNZV];

    //routine to read in full matrix A and decompose
    readMatrix(n,m,numNZV,startNode,vv_a,ia_a,ja_a);

    //set the 3 1-D arrays for matrix A
    adjMat->setIA(ia_a);
    adjMat->setJA(ja_a);
    adjMat->setValueArray(vv_a);

	cout << "Adjacency Matrix of graph ---- Rows, Cols and number of non common values: " << adjMat->getRows() <<
		", " << adjMat->getCols() << ", " << adjMat->getnumNZV() << endl;

	//Get the startNode for the BFS and DFS implementation
	cin >> startNode;
	cout << "Start node: " << startNode << endl;

	//display the JA array
	cout << "JA array: ";
	adjMat->display_JA();
	//display the IA array
	cout << "IA array: ";
	adjMat->display_IA();
	//display the matrix from the CSr format
	cout << "The adjacency matrix is : " << endl;
    cout << *adjMat ;
	cout << endl;

	//TODO: Get the parentArray of the BFS and DFS trees
	// -- you need to build the trees directly from the CSR format and not store it in a 2D array

    Graph* graph1 = new Graph(n, startNode, n, m, numNZV);

    graph1->setIA(ia_a);
    graph1->setJA(ja_a);
    graph1->setValueArray(vv_a);

    //display the BFS parentArray in the format given in project 2
	cout << "BFS tree: " << endl;
    graph1->BFS(startNode);
    cout << *graph1;

    cout << endl;

	//display the DFS parentArray in the format given in project 2
	cout << "DFS tree: " << endl;
    graph1->DFS(startNode);
    cout << *graph1;

	cout << endl;

    delete graph1;

	return 0;
}

//Routine to read in matrix from input file.
void readMatrix(int& nrows, int& ncols, int& nNZV, int& start_node, int tNZV[], int tIA[], int tJA[])
{

    int matrix[nrows][ncols];
    int value;

    for (int i=0; i<nrows; i++){
        for (int j=0; j<ncols; j++){
            cin >> value;
            matrix[i][j] = value;
        }
    }

    int tcount = 0;

    for (int i=0; i < nrows; i++){
        if (i == 0) {tIA[i] = 0;}
        for (int j=0; j < ncols; j++){
            if (matrix[i][j] != 0){
                tJA[tcount] = j;
                tNZV[tcount] = matrix[i][j];
                tcount++;
            }
        }
        tIA[i+1] = tcount;
    }

    cin >> start_node;
}
