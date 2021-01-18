#ifndef CSC232_RBTREE_H__
#define CSC232_RBTREE_H__


// Node structure in Red-Black Tree
struct Node {
    int key;
    Node *p; // Pointer to the parent
    Node *left; // Pointer to left child node
    Node *right; // Pointer to right child node
    char color; // Starting character of node's color
};

typedef Node *NodePtr;

class RBTree {
    private:
        NodePtr root;
        NodePtr TNULL;

    public:
        RBTree() {
            TNULL = new Node;
            TNULL->color = 'B';
            TNULL->left = nullptr;
            TNULL->right = nullptr;
            root = TNULL;
        }

        static NodePtr create_node(char color, int key, NodePtr left, NodePtr right, NodePtr p);

        void insert(int key);
        void rbOutput(NodePtr node, int indent=0);
        void leftRotate(NodePtr x);
        void rightRotate(NodePtr y);
        bool deleteNode(int key);

        void setRoot(NodePtr T);
        NodePtr getRoot();
        NodePtr getTNULL();
        void rbClear(NodePtr T);

        NodePtr rbSearch(NodePtr T, int key);

        // Helper functions
        NodePtr minimum(NodePtr x);
        void insertFixup(NodePtr z);
        void deleteFixup(NodePtr x);
        void rbTransplant(NodePtr u, NodePtr v);
};

#endif //CSC232_RBTREE_H__
