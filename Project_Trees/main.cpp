#include <iostream>

//Tree header file
#include "Tree.h"

using namespace std;

int main () {
    Tree* myTree;   
    int numNodes, node, parent, numChildren, child;

    cin >> numNodes;
    myTree = new Tree (numNodes);

    while (!cin.eof()) {
        cin >> parent >> numChildren;
        for (int i=0; i < numChildren; i++) {
            cin >> child;
            (*myTree).setParent (child, parent);
        }
    }

    cout << "The tree that we just read is: " << endl;
    cout << *myTree << endl; //overloading the ostream operator

    Tree* newTree = new Tree (*myTree); //copy constructor

    cout << "The tree that we just copied is: " << endl;
    cout << *newTree << endl;
    cout << "The root of the tree is: " << (*myTree).Root() << endl;

    cout << "The least common ancestor of nodes 3 and 8 is: " << (*newTree).LCA(3,8) << endl;
    cout << "The least common ancestor of nodes 13 and 8 is: " << (*newTree).LCA(13,8) << endl;
    cout << "The least common ancestor of nodes 13 and 11 is: " << (*myTree).LCA(13,11) << endl;

    cout << "The children of node 12 is: "<<endl;
    (*myTree).Children(12);
    cout << endl;

    cout << "The children of node 10 is: "<<endl;
    (*myTree).Children(10);
    cout << endl;

    cout << "The siblings of node 3 is: "<<endl;
    (*myTree).Siblings(3);
    cout << endl;

    cout << "The siblings of node 12 is: "<<endl;
    (*myTree).Siblings(12);
    cout << endl;

    cout << "The nodes at level 3 are: "<<endl;
    (*myTree).nodesAtLevel(3);
    cout << endl;

    cout << "The height of the tree is: " << (*myTree).height() << endl;

    cout << "The level of node 3 in the tree is: " << (*myTree).level(3) << endl;
    cout << "The level of node 12 in the tree is: " << (*myTree).level(12) << endl;

    cout << "The preorder traversal of the tree is: "<<endl;
    (*myTree).Preorder();
    cout << endl;

    cout << "The postorder traversal of the tree is: "<<endl;
    (*myTree).Postorder();
    cout << endl;

    cout << "The inorder traversal of the tree is: "<<endl;
    (*myTree).Inorder();
    cout << endl;

    delete myTree;
    delete newTree;
}