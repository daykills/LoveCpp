/*
 449. Serialize and Deserialize BST
 Medium
 
 1060
 
 63
 
 Add to List
 
 Share
 Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.
 
 Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.
 
 The encoded string should be as compact as possible.
 
 Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
 */

#include "Common.h"

namespace SerializeAndDeserializeBST
{
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string data;
        serializePreorderDFS(root, data);
        return data;
    }
    
    void serializePreorderDFS(TreeNode* root, string& data) {
        if (!root) return;
        char buf[sizeof(int)];
        memcpy(buf, &(root->val), sizeof(int)); //burn the int into 4 chars
        for (int i = 0; i< sizeof(int); i++)
            data.push_back(buf[i]);
        serializePreorderDFS(root->left, data);
        serializePreorderDFS(root->right, data);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos = 0;
        return reconstruct(data, pos, INT_MIN, INT_MAX);
    }
    
    TreeNode* reconstruct(const string& buffer, int& pos, int minValue, int maxValue) {
        if (pos >= buffer.size()) return NULL; //using pos to check whether buffer ends is better than using char* directly.
        
        int value;
        memcpy(&value, &buffer[pos], sizeof(int));
        if (value < minValue || value > maxValue) return NULL;
        
        TreeNode* node = new TreeNode(value);
        pos += sizeof(int);
        node->left = reconstruct(buffer, pos, minValue, value);
        node->right = reconstruct(buffer, pos, value, maxValue);
        return node;
    }
};

void Test()
{
    TreeNode *root = makeTree({ 2, 1, 3 });
    TreePrinter::Printer<TreeNode> treePrinter;
    treePrinter.printPretty(root, 1, 1, cout);
    
    Codec codec;
    auto serializedTree = codec.serialize(root);
    cout << "Serialize result: " << serializedTree << endl;
    
    auto deserializedTree = codec.deserialize(serializedTree);
    cout << "Deserialize result: " << endl;
    treePrinter.printPretty(deserializedTree, 1, 1, cout);
}
}
