#include "defines/node.h"

#include <list>
#include <iostream>

Node* root = nullptr;
std::list <Node*> nodes;

Node* getHead() {
	return root;
}


Node* newNode(NodeType type) {
	auto node = new Node;
	node->nodeType = type;
	node->left = nullptr;
	node->right = nullptr;

	node->num_val = 0;
	node->op_val = 0;

	nodes.push_back(node);

	// root 永远保存最新的节点
	root = node;

	return node;
}

void printNode() {
	for (const auto& node : nodes) {
		std::cout << "NodeType: " << node->nodeType
			<< " NodeVal: " << node->num_val
			<< " OpVal: " << node->op_val
			<< std::endl;
	}
}

void removeNode(Node* n) {
	if (n == nullptr) {
		return;
	}

	removeNode(n->left);
	removeNode(n->right);

	delete n;
}