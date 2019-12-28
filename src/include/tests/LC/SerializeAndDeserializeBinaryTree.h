/*
297. Serialize and Deserialize Binary Tree My Submissions QuestionEditorial Solution
Total Accepted: 16672 Total Submissions: 60556 Difficulty: Hard
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

For example, you may serialize the following tree

1
/ \
2   3
/ \
4   5
as "[1,2,3,null,null,4,5]", just the same as how LeetCode OJ serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.
Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

Credits:
Special thanks to @Louis1992 for adding this problem and creating all test cases.
*/

#include <iostream>
#include "Common.h"

namespace SerializeAndDeserializeBinaryTree
{
	// Definition for a binary tree node.
	struct TreeNode {
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	class Codec {
	public:

		string serialize(TreeNode* root) {
			ostringstream out;
			serializeIterative(root, out);
			return out.str();
		}

		TreeNode* deserialize(string data) {
			istringstream in(data);
			return deserialize(in);
		}

	private:
		// Encodes a tree to a string.
		void serializeIterative(TreeNode* root, ostringstream& out) {
			
			stack<TreeNode*> hist;
			auto cur = root;
			while (!hist.empty() || cur)
			{
				// if cur is nullptr, set the right child of the top of hist as cur
				if (cur == nullptr)
				{
					// record that this child is empty
					out << "# ";
					cur = hist.top()->right;
					hist.pop();
					continue;
				}
				// add cur node to output vector whenever it's pushed into hist
				out << cur->val << " ";
				hist.push(cur);
				cur = cur->left;
			}
			out << "#";
		}

        void serializeRecursive(TreeNode* root, ostringstream& os) {
            if (root == nullptr) os << "# ";
            else {
                os << root->val << " ";
                serializeToStream(root->left, os);
                serializeToStream(root->right, os);
            }
        }
        
        TreeNode* deserializeFromStream(istringstream& is) {
            string read;
            is >> read;
            if (read == "#")
                return nullptr;
            TreeNode* root = new TreeNode(stoi(read));
            root->left = deserializeFromStream(is);
            root->right = deserializeFromStream(is);
            return root;
        }
	};

	void Test()
	{
		//[1, 2, 2, 3, 3, null, null, 4, 4]
		const int n = 7;
		TreeNode* nodes[n];
		for (int i = 0; i < n; i++)
		{
			nodes[i] = new TreeNode(i);
		}
		nodes[0]->left = nodes[1];
		nodes[0]->right = nodes[2];
		nodes[1]->left = nodes[3];
		nodes[1]->right = nodes[4];
		//nodes[3]->left = nodes[5];
		nodes[3]->right = nodes[6];

		TreePrinter::Printer<TreeNode> treePrinter;
		treePrinter.printPretty(nodes[0], 1, 1, cout);

		Codec codec;

		auto serializedTree = codec.serialize(nodes[0]);
		cout << "Serialize result: " << serializedTree << endl;

		auto deserializedTree = codec.deserialize(serializedTree);
		cout << "Deserialize result: " << endl;
		treePrinter.printPretty(deserializedTree, 1, 1, cout);
	}
}
