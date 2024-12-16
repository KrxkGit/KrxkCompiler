#include <iostream>

#include "node.h"
#include "parserExport.h"

int eval(Node* node) {
	switch (node->nodeType)
	{
	case NodeType::OP:
		switch (node->op_val)
		{
		case 1: // +
			node->num_val = eval(node->left) + eval(node->right);
			break;
		case 2: // -
			node->num_val = eval(node->left) - eval(node->right);
			break;
		default:
			std::cerr << "Unknown operator" << std::endl;
			return -1;
		}

		return node->num_val;

	case NodeType::NUMBER:
		return node->num_val;
		break;
	default:
		std::cerr << "Unknown node type" << std::endl;
		return -1;
	}
}

int main() {
	doParse();

	//printNode();
	auto root = getHead();
	std::cout << "Result: " << eval(root) << std::endl;
	removeNode(root);
	return 0;
}