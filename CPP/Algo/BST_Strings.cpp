#include <iostream>
#include <string>
#include <vector>

class Node {
public:
    std::string value;
    Node* left;
    Node* right;
    
    Node(const std::string& val) : value(val), left(nullptr), right(nullptr) {}
};

class StringBST {
private:
    Node* root;
    
    // Helper method for recursive insertion
    void insertRecursive(Node* &node, const std::string& value) {
        if (node == nullptr) {
            node = new Node(value);
            return;
        }
        
        if (value < node->value) {
            insertRecursive(node->left, value);
        } else if (value > node->value) {
            insertRecursive(node->right, value);
        }
        // If values are equal, we don't insert duplicates
    }
    
    // Helper method for recursive search
    Node* searchRecursive(Node* node, const std::string& value) {
        if (node == nullptr || node->value == value) {
            return node;
        }
        
        if (value < node->value) {
            return searchRecursive(node->left, value);
        }
        return searchRecursive(node->right, value);
    }
    
    // Helper method for recursive deletion
    Node* deleteRecursive(Node* node, const std::string& value) {
        // Base case: If tree is empty
        if (node == nullptr) {
            return nullptr;
        }
        
        // Recursively find and delete the node
        if (value < node->value) {
            node->left = deleteRecursive(node->left, value);
        } else if (value > node->value) {
            node->right = deleteRecursive(node->right, value);
        } else {
            // Node with no child or one child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            // Node with two children: Get the inorder successor (smallest in right subtree)
            node->value = minValue(node->right);
            
            // Delete the inorder successor
            node->right = deleteRecursive(node->right, node->value);
        }
        return node;
    }
    
    // Helper method to find minimum value in a subtree
    std::string minValue(Node* node) {
        std::string minVal = node->value;
        while (node->left != nullptr) {
            minVal = node->left->value;
            node = node->left;
        }
        return minVal;
    }
    
    // Helper methods for traversals
    void inorderRecursive(Node* node, std::vector<std::string>& result) {
        if (node != nullptr) {
            inorderRecursive(node->left, result);
            result.push_back(node->value);
            inorderRecursive(node->right, result);
        }
    }
    
    void preorderRecursive(Node* node, std::vector<std::string>& result) {
        if (node != nullptr) {
            result.push_back(node->value);
            preorderRecursive(node->left, result);
            preorderRecursive(node->right, result);
        }
    }
    
    void postorderRecursive(Node* node, std::vector<std::string>& result) {
        if (node != nullptr) {
            postorderRecursive(node->left, result);
            postorderRecursive(node->right, result);
            result.push_back(node->value);
        }
    }
    
    // Helper method for printing tree structure
    void printTreeRecursive(Node* node, int level) {
        if (node != nullptr) {
            printTreeRecursive(node->right, level + 1);
            std::cout << std::string(level * 4, ' ') << node->value << std::endl;
            printTreeRecursive(node->left, level + 1);
        }
    }
    
    // Helper method to recursively free memory
    void destroyRecursive(Node* node) {
        if (node != nullptr) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

public:
    StringBST() : root(nullptr) {}
    
    ~StringBST() {
        destroyRecursive(root);
    }
    
    // Insert a string value into the BST
    void insert(const std::string& value) {
        insertRecursive(root, value);
    }
    
    // Search for a string value in the BST
    bool search(const std::string& value) {
        return searchRecursive(root, value) != nullptr;
    }
    
    // Delete a string value from the BST
    void remove(const std::string& value) {
        root = deleteRecursive(root, value);
    }
    
    // Inorder traversal of the BST
    std::vector<std::string> inorderTraversal() {
        std::vector<std::string> result;
        inorderRecursive(root, result);
        return result;
    }
    
    // Preorder traversal of the BST
    std::vector<std::string> preorderTraversal() {
        std::vector<std::string> result;
        preorderRecursive(root, result);
        return result;
    }
    
    // Postorder traversal of the BST
    std::vector<std::string> postorderTraversal() {
        std::vector<std::string> result;
        postorderRecursive(root, result);
        return result;
    }
    
    // Print a simple visual representation of the tree
    void printTree() {
        if (root == nullptr) {
            std::cout << "Empty tree" << std::endl;
            return;
        }
        printTreeRecursive(root, 0);
    }
};

int main() {
    StringBST bst;
    
    // Insert the provided technical words
    std::vector<std::string> techTerms = {
        "computer", "engineering", "analysis", "networking", 
        "software", "database", "hardware"
    };
    
    std::cout << "Inserting words into BST:" << std::endl;
    for (const auto& term : techTerms) {
        std::cout << "- Inserting: " << term << std::endl;
        bst.insert(term);
    }
    
    std::cout << "\nTree structure (sideways, right is up, left is down):" << std::endl;
    bst.printTree();
    
    // Display traversals
    std::cout << "\nTraversals:" << std::endl;
    
    std::cout << "Inorder (alphabetical): ";
    for (const auto& value : bst.inorderTraversal()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Preorder: ";
    for (const auto& value : bst.preorderTraversal()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Postorder: ";
    for (const auto& value : bst.postorderTraversal()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    // Demonstrate search
    std::string searchTerm = "networking";
    std::cout << "\nSearching for '" << searchTerm << "': " 
              << (bst.search(searchTerm) ? "Found" : "Not found") << std::endl;
    
    // Demonstrate deletion
    std::string deleteTerm = "software";
    std::cout << "\nDeleting '" << deleteTerm << "'" << std::endl;
    bst.remove(deleteTerm);
    
    std::cout << "\nTree after deletion:" << std::endl;
    bst.printTree();
    
    std::cout << "\nFinal inorder traversal: ";
    for (const auto& value : bst.inorderTraversal()) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
