using namespace std;

class Tree
{

    //overload the '<<' operator
    friend ostream& operator<< (ostream& os, const Tree& tree0);

    protected:
        int* data;
        int numNodes;
        int root_node;

       // int child;
       // int parent;

    public:
        //Default constructor
        Tree ();

        //2nd constructor
        Tree (int nNodes);

        //Copy constructor
        Tree (const Tree& tree0);

        //Default destructor
        virtual ~Tree();

        //Setter Routines
        void setRoot(int rNode);
        void setParent(int curr_child, int curr_parent);

        //Getter routines
        int getSize() const;
        int Parent(int curr_node);
        void Children(int curr_node);
        void Siblings(int curr_node);

        int Root() const;
        int LCA(int node1, int node2);

        void nodesAtLevel(int level_we_want);
        int height() const;
        int level(int curr_node);

        //Helper tree traversal functions (recursive)
        void RecPreOrder(int node);
        void RecPostOrder(int node);
        void RecInOrder(int node);

        //Tree traversal functions
        void Preorder();
        void Postorder();
        void Inorder();

        //overload the '=' sign
        Tree* operator= (Tree* tree0);

        //overload the '+' operator
        Tree* operator+ (const Tree& tree2);
};
