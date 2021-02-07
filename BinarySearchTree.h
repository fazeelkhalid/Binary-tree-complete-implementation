#define BST_H

#include<iostream>
#include<cmath>
#include"linked_list.h"
#include<stack>
using namespace std;

class BST{
private:
	/***********************************/
	//DATA MEMBER
	/***********************************/

	struct Node {
		int data;
		Node * leftChild = NULL;
		Node * rightChild = NULL;
	};
	Node * root;

	/***********************************/
	//RECURSIVE FUNCTIONS
	/***********************************/

	void insert(Node*& parent, int data) {//insert child in tree by recursively
		if (parent == NULL) {// if parent become NULL
			parent = new Node;
			parent->data = data;
			return;
		}
		else {
			if (data > parent->data) {
				insert(parent->rightChild, data); //check right child
			}
			else if (data < parent->data) {
				insert(parent->leftChild, data);//check left child
			}
			else {
				cout << "\nData already present";
				return;
			}
		}
	}
	int height(Node* parent) { //find height of tree by recursively
		if (parent == NULL) {
			return 0;
		}
		else if(parent!=NULL) {
			int rightDepth = height(parent->rightChild);
			int leftDepth = height(parent->leftChild);
			
			//return the greates height
			int Height;
			if (leftDepth > rightDepth) {
				 Height = leftDepth + 1;
			}
			else {
				Height = rightDepth + 1;
			}
			return Height;
		}
		
	}
	void printLeftToRight(Node* root, int currentLevel, int level) {// print left to right child data of same level	
		if (root != NULL) { // check is parent NULL
			if (currentLevel == level) {// is level came or not
				cout << root->data << " ";
				return;
			}
		}
		else {
			return;
		}

		printLeftToRight(root->leftChild, currentLevel + 1, level);
		printLeftToRight(root->rightChild, currentLevel + 1, level);
	}
	void printRightToLeft(Node* root, int currentLevel, int level) { // print right to left child data of same level
		if (root != NULL) { // check is parent NULL
			if (currentLevel == level) {// is level came or not
				cout << root->data << " ";
				return;
			}
		}
		else {
			return;
		}
		printRightToLeft(root->rightChild, currentLevel + 1, level);
		printRightToLeft(root->leftChild, currentLevel + 1, level);
	}
	void BinaryMirrorTree(Node* MirrorParent) {
		if (MirrorParent != NULL) {
			//swap left child with right child of the poarent
			Node*temp = MirrorParent->rightChild;
			MirrorParent->rightChild = MirrorParent->leftChild;
			MirrorParent->leftChild = temp;

			BinaryMirrorTree(MirrorParent->leftChild);
			BinaryMirrorTree(MirrorParent->rightChild);
		}
		else {
			return;
		}
	}
	void deleteTree(Node * parent) {
		if (parent == NULL) {
			return;
		}
		else { // post order
			deleteTree(parent->leftChild); // delte left leef nodes
			deleteTree(parent->rightChild);//delete right leef Nodes
			delete parent;
		}
	}
	void flattenedTree(Node *parent, linkedList<int>&  flattened) { // receive Node and linked List for flattened tree
		if (parent == NULL) { // if parent Null then return 
			return;
		}
		flattened.insertAtEnd(parent->data);
		flattenedTree(parent->leftChild, flattened); // check left sub tree
		flattenedTree(parent->rightChild, flattened);// check right sub tree
	}
	
	void printNodesAtLevel(Node* root, int currentLevel, int level, int tempspaces) {
		int spaces = tempspaces + tempspaces - 1;

		if (root == NULL) {
			cout << " ";
			for (int k = 0; k < spaces; k++) {
				cout << " ";
			}
			return;
		}
		if (currentLevel == level) {
			cout << root->data;
			for (int k = 0; k < spaces; k++) {
				cout << " ";
			}
			return;
		}

		printNodesAtLevel(root->leftChild, currentLevel + 1, level, tempspaces);
		printNodesAtLevel(root->rightChild, currentLevel + 1, level, tempspaces);
	}
	void print(Node*parent, int height) {
		Node * temp = parent;
		for (int i = 0; i < height; i++) {
			int element = pow(2, i);
			int tempspaces = pow(2, height - (i + 1));

			for (int j = 0; j < tempspaces; j++) { // print first spaces
				cout << " ";
			}
			printNodesAtLevel(parent, 0, i, tempspaces);
			cout << endl;
		}
	}

	void copyData(Node *parent, BST& copy) { // receive parents and BST tree for copy data 
		if (parent == NULL) { // if parent Null then return 
			return;
		}
		copy.insert(parent->data);
		copyData(parent->leftChild, copy); // check left sub tree
		copyData(parent->rightChild, copy);// check right sub tree
	}

	void copyData(BST & tree) {// copy data of caller tree
		tree.root = NULL;
		this->copyData(this->root, tree);
	}
	void insertinMirror(Node*& parent, int data) {//insert child in tree by recursively with reverse property
		//reverse property means small number enter at left side and larger at right side
		if (parent == NULL) {// if parent become NULL
			parent = new Node;
			parent->data = data;
			return;
		}
		else {
			if (data < parent->data) {
				insertinMirror(parent->rightChild, data); //check left child
			}
			if (data > parent->data) {
				insertinMirror(parent->leftChild, data);//check right child
			}
		}
	}
	void printLevelWise(Node* root, int currentLevel, int level) {// print left to right child data of same level	
		if (root != NULL) { // check is parent NULL
			if (currentLevel == level) {// is level came or not
				cout << "\nThis node Address " << root;
				cout << "\nLeft Child Address : " << root->leftChild;
				cout << "\nRight Child Address : " << root->rightChild;
				cout << "\nData : " << root->data;
				cout << "\n.........................................\n";
				return;
			}
		}
		else {
			return;
		}
		printLevelWise(root->leftChild, currentLevel + 1, level);
		printLevelWise(root->rightChild, currentLevel + 1, level);
	}
public:
	BST() {
		root = NULL;
	}

	/***********************************/
	//Helper functions
	/***********************************/
	Node* getRoot() {
		return this->root;
	}
	void insert(int data) {
		if (root == NULL) { //if root Null put Node on root and put data in it;
			root = new Node;
			root->data = data;
		}
		else {
			insert(root, data);
		}
	}
	int height() {
		return height(root);
	}
	void SpiralOrderTraversal() { // print tree in spiral Form
		cout << "\nData printing in spiral order : ";
		int Height = this->height();
		for (int i = 0; i < Height; i++) {// change level of tree
			if (i % 2 == 0) {
				printRightToLeft(root, 0, i);
			}
			else {
				printLeftToRight(root, 0, i);
			}
		}
	}

	int DiameterOfBinaryTree(Node*Parent) {
		if (Parent == NULL) {
			return 0;
		}
		//check height
		int leftHeight = this->height(Parent->leftChild);// height of left sub tree 
		int rightHeight = this->height(Parent->rightChild);// height of right sub tree
		//Now check Diameter
		int rightDiameter = this->DiameterOfBinaryTree(Parent->rightChild);// check the diameter of left child
		int leftDiameter = this->DiameterOfBinaryTree(Parent->leftChild);// check the diameter of left child

		if (leftDiameter > rightDiameter) { // check which diameter greater
			if ((leftHeight + rightHeight) > leftDiameter) {// compare height and diamter and return dreater value
				return (leftHeight + rightHeight);
			}
			else {
				return leftDiameter;
			}
		}
		else {
			if ((leftHeight + rightHeight) > rightDiameter) {// compare height and diamter and return dreater value
				return (leftHeight + rightHeight);
			}
			else {
				return rightDiameter;
			}
		}
	}
	
	void BinaryMirrorTree(BST& mirror) {
		this->ItrativePreorder(mirror);
	}
	void ItrativePreorder(BST & mirror) {
		//operation = root , right child, left child push into stack
		mirror.root = NULL;
		if (this->root == NULL)
			return;
		Node*tempRoot = this->root;
		stack<Node*> s;
		s.push(tempRoot);
		while (!s.empty()) {
			tempRoot = s.top(); //point last root enter in stak
			s.pop();
			mirror.insertinMirror(mirror.root,tempRoot->data);//enter data in mirror tree
			
			if (tempRoot->rightChild != NULL) {
				s.push(tempRoot->rightChild);
			}
			if (tempRoot->leftChild != NULL) {
				s.push(tempRoot->leftChild);
			}
		}
	}

	void flattenedTree(linkedList<int>& flattened) {
		flattened.deleteList(); // if list already consist of any data
		flattenedTree(root, flattened); // call recursive function
	}
	void print() {//print data of tree in simple form;
		int Height = height(this->root);
		for (int i = 0; i < Height; i++) {
			cout << "\n________________________________________\n";
			cout << "				  LEVEL " << i << endl;
			printLevelWise(this->root, 0, i);
		}
	}

	void Printintreeform() {
		if (root != NULL) {
			cout << "It's not good way but you can observe many thisngs in this way :(\n";
			print(root, height(root));
			cout << "\n\n\t\t for more clerefication : ";
			this->print();
		}
		else {
			cout << "\nEmpty :( ";
		}
	}

	~BST() {
		this->deleteTree(this->root);
	}
};