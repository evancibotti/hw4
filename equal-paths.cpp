#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif
#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool actualtraversal(Node* root, int dep, int& leafdep){
    // base case for recursion
    if(root == nullptr){
        return true;
    }

    // check if node is a leaf node
    if(root->right == nullptr && root->left == nullptr){
        // check if its the first one found and return true if so
        if(leafdep == -1){
            leafdep = dep;
            return true;
        }
        // otherwise return true if the current depth is equal to the leaf depth
        if(leafdep == dep){
            return true;
        } else {
            return false;
        }
    }

    // do other possible recurisve calls
    // initialize booleans to account for not having a child node
    bool right = true;
    bool left = true;

    // do recursive call down subtree if right child node exists
    if(root->right){
        right = actualtraversal(root->right, dep+1, leafdep);
    } 
    // do recursive call down subtree if left child node exists
    if(root->left){
        left = actualtraversal(root->left, dep+1, leafdep);
    } 

    // only return true if all of the children have the correct depth
    if(right && left){
        return true;
    } else {
        return false;
    }
}

bool equalPaths(Node * root)
{
    // Add your code below
    // initialize the original first leaf found to -1
    int leafdep = -1;
    // call the helper function to do the actual traversal down the tree
    return actualtraversal(root, 0, leafdep);
}

