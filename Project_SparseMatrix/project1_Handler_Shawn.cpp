#include <iostream>

// CSR header file
// #include "CSR.h"
using namespace std;

void readMatrix(int& nrows, int& ncols, int& nNZV, int NZV[], int IA[], int JA[]);

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

        //overload the '+' operator
        CSR* operator+ (const CSR& csr2);

};

//Default constructor
CSR::CSR ()
{
    noRows = 0;
    noCols = 0;
    noNonSparseValues = 0;

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
    for (int i=0; i < (noRows); i++)
        cout << IA[i] << " ";
    cout << endl;
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
CSR* CSR::operator+ (const CSR& csr2)
{
    //create temporary arrays of matrix size (n*m) to store values
    int temp_IA[noRows*noCols];
    int temp_JA[noRows*noCols];
    int temp_NZV[noRows*noCols];
    int temp_nNZV = 0;

    int j_index_A = 0;
    int va_count_A = 0;

    int j_index_B = 0;
    int va_count_B = 0;

    int icount=0;
    for (int i=0; i < noRows; i++){
        temp_IA[0] = 0;
        for (int j=0; j < noCols; j++){

            if ((JA[j_index_A] == csr2.JA[j_index_B]) && ((j == JA[j_index_A]) && (j == csr2.JA[j_index_B])) &&
                ((j_index_A < noNonSparseValues) && (j_index_B < csr2.noNonSparseValues))) {

                temp_NZV[icount] = valueArray[va_count_A] + csr2.valueArray[va_count_B];
                temp_JA[icount] = j;

                va_count_A+=1;
                j_index_A+=1;
                va_count_B+=1;
                j_index_B+=1;
                icount+=1;
            }
            else if ((j == JA[j_index_A]) && (j_index_A < noNonSparseValues)) {

                temp_NZV[icount] = valueArray[va_count_A];
                temp_JA[icount] = j;

                va_count_A+=1;
                j_index_A+=1;
                icount+=1;
            }
            else if ((j == csr2.JA[j_index_B]) && (j_index_B < csr2.noNonSparseValues)) {
                temp_NZV[icount] = csr2.valueArray[va_count_B];
                temp_JA[icount] = j;
                va_count_B+=1;
                j_index_B+=1;
                icount+=1;
            }
            else {
                //continue;
            }
        }
        temp_IA[i+1] = icount;
    }

    temp_nNZV = icount;

    //create CSR object pointer
    CSR* c = new CSR(noRows, noCols, temp_nNZV);

    //set number of non-spare values
    c->noNonSparseValues = temp_nNZV;

    // set the three 1D arrays: IA, JA, and numNZV
    c->setIA(temp_IA);
    c->setJA(temp_JA);
    c->setValueArray(temp_NZV);

    return c;
}
// ---------------------------------------------------------------------------//

int main()
{
    int n, m, numNZV;
    int testValue, count = 0;

    //matrixA
    cin >> n >> m >> numNZV; //receive the n, m and numNZV for matrix A
    CSR* matrixA = new CSR(n, m, numNZV);

    //TODO: read in the matrix A from the input file and store it in the given format

    //declare some temporary arrays to store relevant info. Will be transferred to CSR class.
    int ia_a[n+1];
    int ja_a[numNZV];
    int vv_a[numNZV];

    //routine to read in full matrix and decompose
    readMatrix(n,m,numNZV,vv_a,ia_a,ja_a);

    //set the 3 1-D arrays for matrix A
    matrixA->setIA(ia_a);
    matrixA->setJA(ja_a);
    matrixA->setValueArray(vv_a);

    cout << "MATRIX A ---- Rows, Cols and number of non-common values: " <<
        matrixA->getRows() << ", " << matrixA->getCols() << ", " <<
        matrixA->getnumNZV() << endl;

    cout << "The valuesArray for matrix A are : ";
    matrixA->display_valueArray();
    cout << "The JA for matrix A are : ";
    matrixA->display_JA();
    cout << "The IA for matrix A are : ";
    matrixA->display_IA();
    cout << "The matrix A is : " << endl;
    cout << *matrixA; //overload the ostream operator
    cout << endl;

    // matrixB
    count = 0;
    cin >> n >> m >> numNZV; //receive the n, m and numNZV for matrix B
    CSR* matrixB = new CSR(n, m, numNZV);

    //TODO: read in the matrix B from the input file and store it in the given format

    //declare some temporary arrays to store relevant info. Will be transferred to CSR class.
    int ia_b[n+1];
    int ja_b[numNZV];
    int vv_b[numNZV];

    //routine to read in full matrix and decompose
    readMatrix(n,m,numNZV,vv_b,ia_b,ja_b);

    //set the 3 1-D arrays for matrix B
    matrixB->setIA(ia_b);
    matrixB->setJA(ja_b);
    matrixB->setValueArray(vv_b);

    cout << "MATRIX B ---- Rows, Cols and number of non-common values: " <<
        matrixB->getRows() << ", " << matrixB->getCols() << ", " <<
        matrixB->getnumNZV() << endl;

    cout << "The valuesArray for matrix B are : ";
    matrixB->display_valueArray();
    cout << "The JA for matrix B are : ";
    matrixB->display_JA();
    cout << "The IA for matrix B are : ";
    matrixB->display_IA();
    cout << "The matrix B is : " << endl;
    cout << *matrixB; //overload the ostream operator

    //addition of the two matrices
    //declare third matrix, C, will have same parameters as matrix B.
    CSR* matrixC = new CSR(n, m, numNZV);

    //add matrix A and B to get matrix C
    matrixC = (*matrixA) + (*matrixB); //overloaded ‘+’ operator
    cout << endl;

    cout << "MATRIX C = A + B" << endl;
    cout << "The valuesArray for matrix C are : ";
    matrixC->display_valueArray();
    cout << "The JA for matrix C are : ";
    matrixC->display_JA();
    cout << "The IA for matrix C are : ";
    matrixC->display_IA();
    cout << "The matrix C is : " << endl;
    cout << *matrixC; //overload the ostream operator

    return 0;
}

//Routine to read in matrix from input file.
void readMatrix(int& nrows, int& ncols, int& nNZV, int NZV[], int IA[], int JA[])
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
        if (i == 0) {IA[i] = 0;}
        for (int j=0; j < ncols; j++){
            if (matrix[i][j] != 0){
                JA[tcount] = j;
                NZV[tcount] = matrix[i][j];
                tcount++;
            }
        }
        IA[i+1] = tcount;
    }
}
