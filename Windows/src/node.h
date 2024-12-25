#pragma once

enum NodeType {
	NUMBER,
	OP
};

struct Node {
	NodeType nodeType;
	int num_val;
	int op_val;

	struct Node *left;
	struct Node* right;
};

Node* getHead();
Node* newNode(NodeType type);
void removeNode(Node* n);
void printNode();
