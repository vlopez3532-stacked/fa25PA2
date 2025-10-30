//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    MinHeap min_heap_obj;
    // 2. Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; ++i) {
        min_heap_obj.push(i, weightArr);
    }
    // 3. While the heap size is greater than 1:
    while (min_heap_obj.size > 1) {
    //    - Pop two smallest nodes
        int left = min_heap_obj.pop(weightArr);
        int right = min_heap_obj.pop(weightArr);
    //    - Create a new parent node with combined weight
        charArr[nextFree] = ' ';
        weightArr[nextFree] = weightArr[left] + weightArr[right];
    //    - Set left/right pointers
        leftArr[nextFree] = left;
        rightArr[nextFree] = right;
    //    - Push new parent index back into the heap
        min_heap_obj.push(nextFree, weightArr);
        ++nextFree;
    }
    // 4. Return the index of the last remaining node (root)
    return min_heap_obj.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    stack<pair<int, string>> trav_stack;
    trav_stack.push(make_pair(root, ""));
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    while (!trav_stack.empty()) {
        int curr_node = trav_stack.top().first;
        string curr_code = trav_stack.top().second;
        trav_stack.pop();

        // checks if leaf
        if (leftArr[curr_node] == -1 && rightArr[curr_node] == -1) {
            // save the code
            char ch = charArr[curr_node];
            codes[ch - 'a'] = curr_code;
        }
        else {
            // push right dear child append 1
            if (rightArr[curr_node] != -1) {
                trav_stack.push({rightArr[curr_node], curr_code + "1"});
            }
            // push left dear child append 0
            if (leftArr[curr_node] != -1) {
                trav_stack.push({leftArr[curr_node],curr_code + "0"});
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}