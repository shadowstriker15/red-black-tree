#include "RBTree.h"
#include <iostream>
#include <iomanip>


NodePtr RBTree::create_node(char color, int key, NodePtr left, NodePtr right, NodePtr p){
    // Create a tree node
    NodePtr node = new Node;
    node->color = color;
    node->key = key;
    node->left = left;
    node->right = right;
    node->p = p;

    return node;
}

void RBTree::insert(int key){
    // Used to insert a key into a RBT
    NodePtr z = create_node('B', key, TNULL, TNULL, TNULL);
    // Temporary pointers
    NodePtr y = TNULL;
    NodePtr x = root;
    while(x != TNULL){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->p = y;
    if(y == TNULL){
        root = z;
    }else if(z->key < y->key){
        y->left = z;
    }else{
        y->right = z;
    }
    z->left = TNULL;
    z->right = TNULL;
    z->color = 'R';
    insertFixup(z);
}

void RBTree::rbOutput(NodePtr node, int indent){
    // Print right subtree
    if(node->right != nullptr){
        rbOutput( node->right, indent+5);
    }
    // Print node with indent
    if(indent!=0){
        std::cout << std::setw(indent);
    }
    node == TNULL ? std::cout << "nil" << "\n":std::cout << node->key << node->color << "\n"; // Print out nil to represent TNULL
    // Print left subtree
    if(node->left != NULL){
        rbOutput( node->left, indent+5);
    }
}

void RBTree::leftRotate(NodePtr x){
    // Used to rotate a tree to the left for RBT conflicts with insertion and deletion
    NodePtr y = x->right; //Temporary pointer y
    x->right = y->left;
    if(y->left != TNULL){
        y->left->p = x;
    }
    y->p = x->p;
    if(x->p == TNULL){
        root = y;
    }else if(x == x->p->left){
        x->p->left = y;
    }else{
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}

void RBTree::rightRotate(NodePtr y){
    // Used to rotate a tree to the right for RBT conflicts with insertion and deletion
    NodePtr x = y->left;
    y->left = x->right;
    if(x->right != TNULL){
        x->right->p = y;
    }
    x->p = y->p;
    if(y->p == TNULL){
        root = x;
    }else if(y == y->p->right){
        y->p->right = x;
    }else{
        y->p->left = x;
    }
    x->right = y;
    y->p = x;
}

bool RBTree::deleteNode(int key){
    // Used to delete a node in a RBT from a passed key
    NodePtr z = rbSearch(root, key); //Check if key exists in tree first
    if(z != TNULL){
        NodePtr y = z; // Temporary pointer
        char y_org_color = y->color;
        NodePtr x;
        if(z->left==TNULL){
            x = z->right;
            rbTransplant(z, z->right);
        }else if(z->right == TNULL){
            x = z->left;
            rbTransplant(z, z->left);
        }else{
            y = minimum(z->right);
            y_org_color = y->color;
            x = y->right;
            if(y->p == z){
                x->p = y;
            }else{
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
        }
        if(y_org_color == 'B'){
            deleteFixup(x);
        }
        //Deletion successful
        return true;
    }else{
        //Deletion unsuccessful
        return false;
    }
}

void RBTree::setRoot(NodePtr T){
    this->root = T;
}

NodePtr RBTree::getRoot(){
    return this->root;
}

NodePtr RBTree::getTNULL(){
    return this->TNULL;
}

void RBTree::rbClear(NodePtr T) {
    // Clear node from memory
    if(T != TNULL){
        rbClear(T->left);
        rbClear(T->right);
        delete T;
    }
}

NodePtr RBTree::rbSearch(NodePtr T, int key){
    //Used to search for a key in a RBT
    if(T == TNULL){
        //Key was not found
        return T;
    }else if(key < T->key){
        return rbSearch(T->left, key);
    }else if(key > T->key) {
        return rbSearch(T->right, key);
    }else{
        //Key was found
        return T;
    }
}

NodePtr RBTree::minimum(NodePtr x){
    //Find the lowest layer node in the tree
    while(x->left != TNULL){
        x = x->left;
    }
    return x;
}

void RBTree::insertFixup(NodePtr z){
    // Used to fix RBT conflicts with insertion
    while(z != root && z->p->color == 'R'){
        if(z->p == z->p->p->left){
            NodePtr y = z->p->p->right; // Temporary node
            if(y->color == 'R'){
                z->p->color = 'B';
                y->color = 'B';
                z->p->p->color = 'R';
                z = z->p->p;
            }else{
                if(z == z->p->right){
                    z = z->p;
                    leftRotate(z);
                }
                z->p->color = 'B';
                z->p->p->color = 'R';
                rightRotate(z->p->p);
            }
        }else{
            //Same as then clause with 'right' and 'left exchanged
            NodePtr y = z->p->p->left;
            if(y->color == 'R'){
                z->p->color = 'B';
                y->color = 'B';
                z->p->p->color = 'R';
                z = z->p->p;
            }else{
                if(z == z->p->left){
                    z = z->p;
                    rightRotate(z);
                }
                z->p->color = 'B';
                z->p->p->color = 'R';
                leftRotate(z->p->p);
            }
        }
    }
    root->color = 'B';
}

void RBTree::deleteFixup(NodePtr x){
    // Used to fix RBT conflicts with deletion
    while(x != root && x->color == 'B'){
        if(x == x->p->left){
            NodePtr w = x->p->right;
            if(w->color == 'R'){
                w->color = 'B';
                x->p->color = 'R';
                leftRotate(x->p);
                w = x->p->right;
            }
            if(w->left->color == 'B' && w->right->color == 'B'){
                w->color = 'R';
                x = x->p;
            }else{
                if(w->right->color == 'B'){
                    w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = 'B';
                w->right->color = 'B';
                leftRotate(x->p);
                x = root;
            }
        }else{
            // Same as then clause with 'right' and 'left' exchanged
            NodePtr w = x->p->left;
            if (w->color == 'R'){
                w->color = 'B';
                x->p->color = 'R';
                rightRotate(x->p);
                w = x->p->left;
            }
            if(w->right->color == 'B' && w->left->color == 'B'){
                w->color = 'R';
                x = x->p;
            }else{
                if(w->left->color == 'B'){
                    w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = 'B';
                w->left->color = 'B';
                rightRotate(x->p);
                x = root;
            }
        }
    }
    x->color = 'B';
}

void RBTree::rbTransplant(NodePtr u, NodePtr v){
    //Helper function for RBT deletion
    if(u->p == TNULL){
        root = v;
    }else if(u == u->p->left){
        u->p->left = v;
    }else{
        u->p->right = v;
    }
    v->p = u->p;
}
