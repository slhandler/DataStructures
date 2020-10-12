#include <iostream>

//Tree header file
#include "Tree.h"

using namespace std;

//Default constructor
Tree::Tree ()
{
    numNodes = 1;

    data = new int[numNodes];  
}
        
//Constructor with user defined values
Tree::Tree (int nNodes)
{
    numNodes = nNodes;

    data = new int[numNodes];
    
    //initialize parent array
    for (int i=0; i<getSize(); i++)
        data[i] = i;
}

//Copy constructor
Tree::Tree (const Tree& tree0)
{
    numNodes = tree0.numNodes; //Number of nodes of tree to copy

    data = new int[numNodes];
    
    //set parent array of object to that of the copied object
    for (int i=0; i<getSize(); i++)
        data[i] = tree0.data[i];
}

//Destructor
Tree::~Tree ()
{
    delete[] data;
}

//Get size of the tree
int Tree::getSize() const {return numNodes;}

//Get the parent node for a given child
int Tree::Parent(int curr_node) {return data[curr_node];}

//Print out the children of given node
void Tree::Children(int curr_node)
{
    int child;

    for (int i=0; i < numNodes; i++){
        if (data[i] == curr_node){
            child = i;
            cout << child << " ";
        }
    }
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Print the siblings for a given node
void Tree::Siblings(int curr_node)
{
    int sibling;

    // get parent node for current node
    int parent = Parent(curr_node);

    for (int i=0; i < numNodes; i++){
        if ((data[i] == parent) && (i != curr_node)){
            sibling = i;
            cout << sibling << " ";
        }
    }
}
// ---------------------------------------------------------------------------//

//Get the root node
int Tree::Root() const {return root_node;}

// ---------------------------------------------------------------------------//
//Perform least common ancestor calculation and return the node
int Tree::LCA(int node1, int node2) 
{
    
    //create a visited array of size numNodes. Will store which nodes we have
    //traversed along a path
    int visited[numNodes];
    
    visited[node1] = 1;

    //move from node1 to root and mark all nodes visited.
    while (data[node1] != -1){
        visited[node1] = 1;
        node1 = data[node1];
    }
    
    visited[node1] = 1;
    
    //move from node2 to root but stopping once we hit the first common node.
    while (visited[node2] != 1)
        node2 = data[node2];
    
    return node2;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Set the root node
void Tree::setRoot(int rNode)
{
    data[rNode] = -1;
    root_node = rNode;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Set the parent of a child node
void Tree::setParent(int curr_child, int curr_parent)
{
    data[curr_child] = curr_parent;
    
    //set root node based on current parent and if it's the same as initialized data array.
    if (data[curr_parent] == curr_parent)
        setRoot(curr_parent);
} 
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Print the nodes at a certain level (or depth of a tree)    
void Tree::nodesAtLevel(int level_we_want)
{
    
    //loop over each node, and traverse to the root. Keep track of height along the way.
    for (int node=0; node<numNodes; node++) {
        int p = node, current_level = 1;
        while (data[p] != -1){
            current_level++;
            p = data[p];
        }
        if (current_level == level_we_want)
            cout << node << " ";
    }
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Determine the height/depth of the tree
int Tree::height() const
{
    int tallness = 0;
    
    //loop over each node, and traverse to the root. Keep track of height along the way.
    for (int i=0; i<numNodes; i++) {
        int p = i, current = 1;
        while (data[p] != -1){
            current++;
            p = data[p];
        }
        
        tallness = (tallness < current)?current:tallness;
    }

    return tallness;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//For a given node, get its height (or level) in the tree 
int Tree::level(int curr_node) 
{
    int counter = 0;
    int temp=curr_node;

    while (temp != -1) {
        counter++;
        temp = data[curr_node];
        curr_node = temp;
    }
    
    return counter;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Recursion function for preorder traversal
void Tree::RecPreOrder(int node)
{
    int child_node=0;
    cout << node << " ";

    //find children and call recursively on child
    for (int i=0; i < numNodes; i++){
        if (data[i] == node){
            child_node = i;
            RecPreOrder(child_node);
        }
    }
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Recursion function for postorder traversal
void Tree::RecPostOrder(int node)
{
    int child_node=0;

    //find children and call recursively on child
    for (int i=0; i < numNodes; i++){
        if (data[i] == node){
            child_node = i;
            RecPostOrder(child_node);
        }
    }
    cout << node << " ";
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//Recursion function for inorder traversal
void Tree::RecInOrder(int node)
{

    int child_node=0;
    int tmp_count = 0;

    //find children and call recursively on child
    for (int i=0; i < numNodes; i++){
        if (data[i] == node){
            child_node = i;
            RecInOrder(child_node);
            if (tmp_count == 0){
                cout << node << " ";
            }
            tmp_count++;
        }    
    }    
    if (tmp_count == 0)
        cout << node << " ";

}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//run preorder traversal
void Tree::Preorder()
{
    RecPreOrder(Root());
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//run postorder traversal
void Tree::Postorder() 
{
    RecPostOrder(Root());
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//run inorder traversal
void Tree::Inorder()
{
    RecInOrder(Root());
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//overloaded ostream operator function to print tree contents
ostream& operator<< (ostream& output, const Tree& Tree)
{

    for (int i=0; i < Tree.getSize(); i++){
        output << i<<": "<< Tree.data[i]<<"\t";
    }    
    return output;
}
// ---------------------------------------------------------------------------//

// ---------------------------------------------------------------------------//
//overloaded assignment operator
Tree* Tree::operator= (Tree* Tree0)
{
    
    numNodes = Tree0->numNodes; //Number of nodes of tree to copy
    data = Tree0->data;
    
    return this;
}
// ---------------------------------------------------------------------------//
