#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Define a structure to represent nodes in the Huffman tree
struct Node {
    char data;            // Stores the character data of the node
    int frequency;        // Keeps track of the frequency of the character
    Node* left, *right;   // Pointers to the left and right children

    Node(char d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}
};

// Custom comparator for the priority queue
struct CompareNodes {
    bool operator()(Node* const& a, Node* const& b) {
        return a->frequency > b->frequency; // Defines a min heap based on character frequency
    }
};

// Function to build the Huffman tree
Node* buildHuffmanTree(string characters, int frequencies[], int n) {
    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;

    // Create a node for each character and add it to the priority queue
    for (int i = 0; i < n; ++i) {
        minHeap.push(new Node(characters[i], frequencies[i]));
    }

    // Build the Huffman tree by merging nodes with the lowest frequencies
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        // Create a combined node with '$' as data (internal node)
        Node* combined = new Node('$', left->frequency + right->frequency);
        combined->left = left;
        combined->right = right;

        minHeap.push(combined);
    }

    return minHeap.top(); // Return the root of the Huffman tree
}

// Function to traverse the Huffman tree and generate codes
void generateHuffmanCodes(Node* root, string code, vector<string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    // If the node is a leaf, add its code to the vector
    if (root->data != '$') {
        // Find the index of the character in the characters string
        size_t index = root->data - 'a';
        huffmanCodes[index] = code;
        return; // Avoid further traversal for leaf nodes
    }

    // Traverse left and append '0' to the code
    generateHuffmanCodes(root->left, code + '0', huffmanCodes);

    // Traverse right and append '1' to the code
    generateHuffmanCodes(root->right, code + '1', huffmanCodes);
}

// Function to delete the Huffman tree nodes after use
void deleteHuffmanTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    deleteHuffmanTree(root->left);
    deleteHuffmanTree(root->right);
    delete root;
}

// Function to print Huffman codes
void printHuffmanCodes(string characters, vector<string>& huffmanCodes) {
    cout << "Huffman codes will be:" << endl;
    for (int i = 0; i < characters.size(); ++i) {
        cout << characters[i] << ": " << huffmanCodes[i] << endl;
    }
}

int main() {
    // Input data
    string characters = "abcdef";
    int frequencies[] = {5, 9, 12, 13, 16, 45};
    int n = sizeof(frequencies) / sizeof(frequencies[0]);

    // Build the Huffman tree
    Node* root = buildHuffmanTree(characters, frequencies, n);

    vector<string> huffmanCodes(n);  // Assuming lowercase letters

    // Generate Huffman codes
    generateHuffmanCodes(root, "", huffmanCodes);

    // Print Huffman codes
    printHuffmanCodes(characters, huffmanCodes);

    // Delete the Huffman tree to free memory
    deleteHuffmanTree(root);

    return 0;
}
