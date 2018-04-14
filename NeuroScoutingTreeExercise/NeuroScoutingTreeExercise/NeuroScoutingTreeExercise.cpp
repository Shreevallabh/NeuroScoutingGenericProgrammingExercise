/*
Title: NeuroScouting Generic Programming Exercise about Tree Data Structure
Notes: Compiled and tested using Microsoft Visual Studio 2015 C++ compiler. Read companion ReadMe file for explaination of logic.
Programmer: Shreevallabh Kulkarni
Email: shreevallabh29@gmail.com
*/

// Header files section
using namespace std;
#include <iostream>


// Variable Declerations
int levelDepth;
int counter=1;
int totalNodes;
bool searchingNewLevel = true;
bool flag_fillingData=true;
bool calculate_values = false;


// Tree node structure
struct Node
{
	int data;
	struct Node *left, *right;
	struct Node *parent;
	struct Node *neighborLeft, *neighborRight;
}*tempNeighbor;



// Helper function that allocates a new node with the given data and sets NULL to all pointers.
struct Node *newNode(int k)
{
	struct Node *node = new Node;
	node->data = k;
	node->right = node->left = node->parent = node->neighborLeft = node->neighborRight = NULL;
	return node;
}



// Main Logic part where node values are calculated as per given rules and node values are printed on console.
void printGivenLevel(struct Node* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
	{
		if (flag_fillingData)
		{
			root->data = counter++;

			if (root->parent != NULL)
			{
				if (searchingNewLevel)
				{
					tempNeighbor = root;
					searchingNewLevel = false;
					root->data = root->parent->data;
				}
				else
				{
					tempNeighbor->neighborRight = root;
					root->neighborLeft = tempNeighbor;
					tempNeighbor = root;	
					root->data = root->parent->data;
					if (root->parent->left == root)
					{
						if (root->parent->neighborLeft != NULL)
						{
							root->data += root->parent->neighborLeft->data;
						}
					}
					if (root->parent->right == root)
					{
						if (root->parent->neighborRight != NULL)
						{
							root->data += root->parent->neighborRight->data;
						}
					}
				}			
			}
		}
		else
		{
			cout << root->data << " ";
		}
	
	}
	
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}


// Function to print level order traversal a tree
void printLevelOrder(struct Node* root)
{
	int h = levelDepth;
	int i;
	for (i = 1; i <= h; i++)
	{
		searchingNewLevel = true;
		printGivenLevel(root, i);
		cout << endl;
	}
}



// This recursive function creates a framework of a perfect binary tree. This tree contains dummy values in nodes.
// This tree is later used by differnt function to find actual values of nodesry tree is perfect
bool buildTheTree(struct Node* root, int d, int level = 0)
{

	if (level  == levelDepth -1)
	{
		return true;
	}

	struct Node* tempRootLeft = NULL;
	tempRootLeft = newNode(counter++);
	root->left = tempRootLeft;
	tempRootLeft->parent = root;


	struct Node* tempRootRight = NULL;
	tempRootRight = newNode(counter++);
	root->right = tempRootRight;
	tempRootRight->parent = root;

	return buildTheTree(root->left, d, level + 1) &&
		   buildTheTree(root->right, d, level + 1);
}


// Wrapper over buildTheTree(). Just sets the maximum depth needed for the tree.
bool setTreeDepth(Node *root)
{
	int d = levelDepth;
	return buildTheTree(root, d);
}



// Prints Preorder traversal of tree
void printPreorder(struct Node* node)
{
	if (node == NULL)
		return;

	cout<< node->data << " ";
	printPreorder(node->left);
	printPreorder(node->right);
}

// Prints Postorder traversal of tree
void printPostorder(struct Node* node)
{
	if (node == NULL)
		return;

	printPostorder(node->left);
	printPostorder(node->right);
	cout<< node->data << " ";
}

// Prints Inorder traversal of tree
void printInorder(struct Node* node)
{
	if (node == NULL)
		return;

	printInorder(node->left);
	cout << node->data << " ";
	printInorder(node->right);
}



// Main Function
int main()
{
	cout << "*NeuroScouting Generic Programming Exercise*" << endl << endl;
	cout << "Enter Depth/Level of the tree: ";
	cin >> levelDepth;
	totalNodes = pow(2, levelDepth) - 1;


	struct Node* root = NULL;
	root = newNode(counter++);
	cout << "Total Nodes the tree has: " << totalNodes << endl;


	//Creating the Tree
	setTreeDepth(root);
	counter = 1;


	// Printing the Tree in Breadth First order
	cout << endl << endl << "Output Tree (Breadth First Traversal)" << endl <<"(Apologies for not properly showing it in a actual TREE form) " << endl;
	printLevelOrder(root);
	flag_fillingData = false;
	printLevelOrder(root);


	// Printing the Tree in Pre-In-Post Order traversal
	cout << endl << "Preorder traversal of nodes:  ";
	printPreorder(root);
	cout << endl << "Inorder traversal of nodes:   ";
	printInorder(root);
	cout << endl << "Postorder traversal of nodes: ";
	printPostorder(root);
	cout << endl << endl;
	system("pause");



    return 0;

}

