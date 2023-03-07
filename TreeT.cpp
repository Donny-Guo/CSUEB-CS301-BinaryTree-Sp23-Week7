#include "TreeT.h"

template<class T>
TreeT<T>::TreeT() {
    root = nullptr;
    numNodes = 0;
}

template<class T>
TreeT<T>::~TreeT() {
    DestroyTree(root);
}

template<class T>
TreeT<T> & TreeT<T>::operator=(const TreeT &otherTree) {
    TreeT<T> copy;
    copy.numNodes = otherTree.numNodes;
    copy.iterArr.operator=(otherTree.iterArr);
    CopyHelper(copy.root, otherTree.root);
    return copy;
}

template<class T>
void TreeT<T>::Add(T value) {
    Node * currNode = root;
    Node * newNode = new Node;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    if (root == nullptr) { // empty case
        root = newNode;
        ++numNodes;
        return;
    }

    while (currNode != nullptr) {
        // if current value is greater than input value, check the left leaf
        if (currNode->value > value) {
            if (currNode->left != nullptr) { // if there is a child, go to that child
                currNode = currNode->left;
            } else {
                currNode->left = newNode; // if no children, add node
                break;
            }
        } else if (currNode->value < value){ // if current value is less than input value, check the right leaf
            if (currNode->right != nullptr) { // if there is a child, go to that child
                currNode = currNode->right;
            } else {
                currNode->right = newNode; // if no children, add node
                break;
            }
        } else { // if it is the same value
            return;
        }
    }
    ++numNodes;

}

template<class T>
void TreeT<T>::Remove(T value) {
    if (Contains(value)) {
        RemoveHelper(root, value);
        --numNodes;
    }
}

template<class T>
bool TreeT<T>::Contains(T value) {
    Node * currNode = root;
    while (currNode != nullptr) {
        // if current value is greater than input value, check the left leaf
        if (currNode->value > value) {
            if (currNode->left != nullptr) { // if there is a child, go to that child
                currNode = currNode->left;
            } else {
                break;
            }
        } else if (currNode->value < value){ // if current value is less than input value, check the right leaf
            if (currNode->right != nullptr) { // if there is a child, go to that child
                currNode = currNode->right;
            } else {
                break;
            }
        } else { // if it is the same value
            return true;
        }
    }
    return false;
}

template<class T>
int TreeT<T>::Size() {
    return numNodes;
}

template<class T>
void TreeT<T>::ResetIterator(Order traverseOrder) {
    // remove all the items in iterArr
    while (!iterArr.empty()) {
        iterArr.pop();
    }

    if (traverseOrder == POST_ORDER){
        PlacePostOrder(root);
    }
    else if (traverseOrder == IN_ORDER){
        PlaceInOrder(root);
    }
    else if (traverseOrder == PRE_ORDER){
        PlacePreOrder(root);
    }
}

template<class T>
T TreeT<T>::GetNextItem() {
    if (iterArr.empty()) {
        throw EmptyTreeError();
    }
    T itemToReturn = iterArr.front();
    iterArr.pop();
    return itemToReturn;
}


template<class T>
void TreeT<T>::DestroyTree(TreeT::Node *&node) {
    if (node == nullptr){
        return;
    }
    if (node->left != nullptr){
        DestroyTree(node->left);
    }
    if (node->right != nullptr){
        DestroyTree(node->right);
    }
    delete node;
    node = nullptr;
}


template<class T>
void TreeT<T>::RemoveHelper(TreeT::Node *&subtree, T value) {
    if (value < subtree->value){
        RemoveHelper(subtree->left, value);
    } else if (subtree->value < value){
        RemoveHelper(subtree->right, value);
    } else {
        DeleteNode(subtree); // node found
    }
}

template<class T>
void TreeT<T>::DeleteNode(TreeT::Node *&subtree) {

    Node * temp = subtree;
    // no children
    if (subtree->left == nullptr && subtree->right == nullptr){
        delete subtree;
        subtree = nullptr; ///////important
    }
    // one child
    else if (subtree->left == nullptr) {
        subtree = subtree->right;
        delete temp;
    }
    else if (subtree->right == nullptr) {
        subtree = subtree->left;
        delete temp;
    }

    // two children
    else {
        T data;
        GetPredecessor(subtree->left, data);
        subtree->value = data;
        RemoveHelper(subtree->left, data);

    }
}

template<class T>
void TreeT<T>::GetPredecessor(TreeT::Node *curr, T &value) {
    while (curr->right != nullptr) {
        curr = curr->right;
    }
    value = curr->value;
}

template<class T>
void TreeT<T>::CopyHelper(TreeT::Node *&thisTree, TreeT::Node *otherTree) {
    if (otherTree == nullptr){
        thisTree = nullptr;
        return;
    }
    thisTree = new Node;
    thisTree->value = otherTree->value;
    CopyHelper(thisTree->left, otherTree->left);
    CopyHelper(thisTree->right, otherTree->right);
}

template<class T>
void TreeT<T>::PlacePreOrder(TreeT::Node *node) {
    if (node == nullptr){
        return;
    }
    iterArr.push(node->value);
    PlacePreOrder(node->left);
    PlacePreOrder(node->right);
}

template<class T>
void TreeT<T>::PlacePostOrder(TreeT::Node *node) {
    if (node == nullptr){
        return;
    }
    PlacePostOrder(node->left);
    PlacePostOrder(node->right);
    iterArr.push(node->value);
}

template<class T>
void TreeT<T>::PlaceInOrder(TreeT::Node *node) {
    if (node == nullptr){
        return;
    }
    PlaceInOrder(node->left);
    iterArr.push(node->value);
    PlaceInOrder(node->right);
}

template<class T>
void TreeT<T>::MakeEmpty() {
    DestroyTree(root);
    numNodes = 0;
}


