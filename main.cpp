#include <iostream>
#include <unistd.h>
#include "RBTree.h"


char showOperations() {
    //Show user the available operations
    std::cout << "Available Red-Black Tree Operations:" << "\n"
              << "1. Display the Red-Black Tree" << "\n"
              << "2. Search for a value in the Red-Black Tree" << "\n"
              << "3. Insert a value into the Red-Black Tree" << "\n"
              << "4. Delete a value from the Red-Black Tree" << "\n"
              << "5. QUIT" << "\n"
              << "Please enter one of the above listed numbers to begin an operation: " << "\n";

    std::string user_input;
    std::cin >> user_input;
    return user_input[0];
}

int main() {
    RBTree Tree;
    NodePtr TNULL = Tree.getTNULL();

    bool hasEnded = false;
    while(!hasEnded){
        char operation_char = showOperations();

        if(!std::isdigit(operation_char)){
            std::cout << "Invalid response. Please try again" << "\n";
        }else{
            int operation_int = operation_char - 48; // Convert character to integer
            if(operation_int < 1 || operation_int > 5){
                std::cout << "Number is not valid. Please try again" << "\n";
            }else{
                switch(operation_int) {
                    case 1: // Display operation
                    {
                        NodePtr root = Tree.getRoot();
                        if(root == TNULL){
                            std::cout << "Cannot compute display operation with an empty tree." << "\n";
                        }else{
                            std::cout << "Current representation of the Red-Black Tree:" << "\n";
                            Tree.rbOutput(root);
                        }
                        break;
                    }
                    case 2: // Search operation
                    {
                        NodePtr root = Tree.getRoot();
                        if(root==TNULL){
                            std::cout << "Cannot compute search operation with an empty tree." << "\n";
                        }else{
                            std::cout << "Please enter in the value you would like to search for: " << "\n";
                            int key;
                            std::cin >> key;
                            NodePtr node = Tree.rbSearch(root, key);
                            if (node != TNULL){
                                if(node == root){
                                    std::cout << "The key was found in the root of the tree." << "\n";
                                }else{
                                    if(node->p->key < node->key){
                                        std::cout << node->key << " is in the right child of node " << node->p->key << "\n";
                                    }else{
                                        std::cout << node->key << " is in the left child of node " << node->p->key << "\n";
                                    }
                                }
                            }else{
                                std::cout << "Could not find a key with a value of "<< key << " in the tree." << "\n";
                            }
                        }
                        break;
                    }
                    case 3: // Insert operation
                    {
                        NodePtr root = Tree.getRoot();
                        std::cout << "Please enter in the value you would like to insert: " << "\n";
                        int key;
                        std::cin >> key;
                        if(root == TNULL){
                            NodePtr new_node = RBTree::create_node('B', key, TNULL, TNULL, TNULL);
                            Tree.setRoot(new_node);
                        }else{
                            NodePtr searched_node = Tree.rbSearch(root, key);
                            if(searched_node != TNULL){
                                std::cout << "Insertion failed because key already exists." << "\n";
                                break;
                            }else{
                                Tree.insert(key);
                            }
                        }
                        std::cout << "Insertion successful! New Red-Black Tree after insertion:" << "\n";
                        Tree.rbOutput(Tree.getRoot());
                        break;
                    }
                    case 4: // Delete operation
                    {
                        if(Tree.getRoot() == TNULL){
                            std::cout << "Cannot compute delete operation with an empty tree." << "\n";
                        }else{
                            std::cout << "Please enter in the value you would like to delete: " << "\n";
                            int key;
                            std::cin >> key;
                            if(Tree.deleteNode(key)){
                                NodePtr root = Tree.getRoot();
                                if(root == TNULL){
                                    std::cout << "Deletion successful. The tree is now empty." << "\n";
                                }else{
                                    std::cout << "Deletion successful. New Red-Black Tree after deletion:" << "\n";
                                    Tree.rbOutput(root);
                                }
                            }else{
                                std::cout << "Deletion failed because key does not exist in tree.";
                            }
                        }
                        break;
                    }
                    case 5: // Quit program
                    {
                        std::cout << "Program has ended, thank you!";
                        hasEnded = true;
                        //Clean tree from memory
                        Tree.rbClear(Tree.getRoot());
                        break;
                    }
                }
            }
        }

        sleep(2); //Wait until showing available operations again for user to read display
    }
}
