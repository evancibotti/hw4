#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{
}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{
}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static Node<Key, Value>* successor(Node<Key, Value>* current);
    void actualclear(Node<Key, Value>* current);
    bool actualbalanced(Node<Key, Value>* root, int& height) const;


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    // set current to passed in ptr
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    // set current to null
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    // return true or false depending on statement
    if(current_ == rhs.current_){
        return true;
    } else {
        return false;
    }
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    // return true or false depending on statement
    if(current_ != rhs.current_){
        return true;
    } else {
        return false;
    }
}

/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    // set current to the successor node
    current_ = successor(current_);

    // return a reference to the iterator object
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    // set root to null
    root_ = NULL;

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    // call clear function that we will implement
    clear();
    
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    // create a new node to be used
    Node<Key, Value>* insertion = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);

    // if the tree is empty then create a new node, set it to root, and return
    if(root_ == nullptr){
        root_ = insertion;
        return;
    }

    // create pointers for traversal and start at root
    Node<Key, Value>* currentnode = root_;

    while(currentnode != nullptr){
        // check if the key is already in the tree
        if(keyValuePair.first == currentnode->getKey()){
            // if so set value, delete the create node because it is useless, and return
            currentnode->setValue(keyValuePair.second);
            delete insertion;
            return;

        // check if key is more than the current
        } else if(keyValuePair.first > currentnode->getKey()){
            // insert if theres no child on right
            if(currentnode->getRight() == nullptr){ 
                // attach new node through parent and child and return
                insertion->setParent(currentnode);
                currentnode->setRight(insertion);
                return;
            } else {
                // continue to traverse
                currentnode = currentnode->getRight();
            }

        // check if the key is less than the current
        } else if(keyValuePair.first < currentnode->getKey()){
            // insert if theres no child on left
            if(currentnode->getLeft() == nullptr){
                // attach new node through parent and child and return
                insertion->setParent(currentnode);
                currentnode->setLeft(insertion);
                return;
            } else {
                // continue to traverse
                currentnode = currentnode->getLeft();
            }
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // Find the node to delete
    Node<Key, Value>* tbd = internalFind(key);

    // do nothing if theres nothing in tree
    if(tbd == nullptr){
      return;
    }

    // If the node has two children then swap because it will always have 1 child after
    if(tbd->getRight() != nullptr && tbd->getLeft() != nullptr){
      Node<Key, Value>* predecess = predecessor(tbd);
      nodeSwap(tbd, predecess);
    }

    // save the pointer to the child now and initialize with nullptr
    Node<Key, Value>* tbdchild = nullptr;

    // save the child depending on which one it is if they have one
    if(tbd->getRight() != nullptr){
      tbdchild = tbd->getRight();
    } else if(tbd->getLeft() != nullptr){
      tbdchild = tbd->getLeft();
    }

    // connect child and parent branching
    if(tbd->getParent() != nullptr){
      // create pointer for parent
      Node<Key, Value>* tbdparent = tbd->getParent();

      // connect parent to child if they have one
      if(tbdparent->getRight() == tbd){
        tbdparent->setRight(tbdchild);
      } else if(tbdparent->getLeft() == tbd){
        tbdparent->setLeft(tbdchild);
      }

      // connect child to parent if child isn't still null
      if(tbdchild != nullptr){
        tbdchild->setParent(tbdparent);
      }
    } else {
      // set root equal to child because tbd was the root
      root_ = tbdchild;
      // make childs parent null if it exists because its new root
      if(tbdchild != nullptr){
        tbdchild->setParent(nullptr);
      }
    }
  // finally delete the node to be deleted
  delete tbd;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // return NULL if the node is null because there is no predecessor
    if(current == nullptr){
        return nullptr;
    }

    // create variable to store the predecessor and initialize it to the current
    Node<Key, Value>* predecessor = current;
    // store the parent pointer for later and initialize to null
    Node<Key, Value>* predparent = predecessor->getParent();

    // return the right most node in the left subtree if its exists
    // as the predecessor
    if(predecessor->getLeft()!= nullptr){
        // set it to the left child
        predecessor = predecessor->getLeft();
        // continue to move right until you cant anymore
        while(predecessor->getRight() != nullptr){
            predecessor = predecessor->getRight();
        }
        // finally return once you get the right most child(largest)
        return predecessor;
    
    // return the first node that carries a right child traversing 
    // upward if the left subtree doesn't exist as the predecessor
    } else {
      // continue upward until you reach the root
      while(predparent != nullptr){
        if(predecessor == predparent->getRight()){
          return predparent;
        } else {
          predecessor = predparent;
          predparent = predecessor->getParent();
        }
      }
    }
    // return null if it is the smallest node in tree
    return nullptr;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    // call the recursive helper and start at root
    actualclear(root_);
    // clear the root data member to finish clearing everything
    root_ = nullptr;
}

// recursive helper function for the clear function
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::actualclear(Node<Key, Value>* current)
{
    // base case
    if(current == nullptr){
        return;
    }

    // recursive call for right subtree
    actualclear(current->getRight());
    // recursive call for left subtree
    actualclear(current->getLeft());

    // delete the current node
    delete current;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // create a node to return and initialize it to the root
    Node<Key, Value>* smallest = root_;

    // if the root is null then just return null because its empty
    if(root_ == nullptr){
        return nullptr;
    }

    // traverse down and left until you reach the smallest node
    while(smallest->getLeft() != nullptr){
        smallest = smallest->getLeft();
    }

    // finally return the smallest node
    return smallest;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    // create a node to return and initialize it to root
    Node<Key, Value>* keyintree = root_;

    // traverse down the tree until its key is equal to the key and return it
    while(keyintree != nullptr){
      if(keyintree->getKey() == key){
        return keyintree;
      } else if(keyintree->getKey() > key){
        keyintree = keyintree->getLeft();
      } else if(keyintree->getKey() < key){
        keyintree = keyintree->getRight();
      }
    }

    // only reached when key isnt in tree, then return null
    return nullptr;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    // call the helper function with root_ data member and initialized height
    int height = 0;
    return actualbalanced(root_, height);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::actualbalanced(Node<Key, Value>* root, int& height) const
{
    // TODO
    // base case for when subtrees are empty or original tree is empty 
    if(root == nullptr){
      // empty means balanced
      return true;
    }

    // create variables for both subtrees height
    int rheight = 0;
    int lheight = 0;

    // recursively call and store booleans for each side
    bool rbalanced = actualbalanced(root->getRight(), rheight);
    bool lbalanced = actualbalanced(root->getLeft(), lheight);

    // update the height 
    if(rheight >= lheight){
      height = rheight + 1;
    } else {
      height = lheight + 1;
    }

    // return the answer
    if(rbalanced == true && lbalanced == true && std::abs(rheight - lheight) <= 1){
      return true;
    } else {
      return false;
    }
}

// created successor function needed
template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    // return NULL if the node is null because there is no successor
    if(current == nullptr){
        return nullptr;
    }

    // create variable to store the successor and initialize it to the current
    Node<Key, Value>* successor = current;
    // store the parent pointer for later and initialize to null
    Node<Key, Value>* sucparent = nullptr;

    // return the left most node in the right subtree if its exists
    // as the successor
    if(successor->getRight()!= nullptr){
        // set it to the right child
        successor = successor->getRight();
        // continue to move left until you cant anymore
        while(successor->getLeft() != nullptr){
            successor = successor->getLeft();
        }
        // finally return once you get the left most child
        return successor;
    
    // return the first node that carries a left child traversing 
    // upward if the right subtree doesn't exist as the successor
    } else {
        // continue upward until you reach the root
        while(successor != nullptr){
            // update the parent pointer
            sucparent = successor->getParent();
            // check if the current successor is the parents left child 
            if(sucparent != nullptr && sucparent->getLeft() == successor){
                // if so then the successor to return is the parent
                // so set them equal and return
                successor = sucparent;
                return successor;
            }
            // if not just increment while loop by changing current successor
            // to parent without returning
            successor = sucparent;
        }
    }
    // return null if it is the largest node in tree
    return nullptr;  
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
