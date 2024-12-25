#include <iostream>

#include "defines/node.h"
#include "yacc/parserExport.h"
#include "defines/CodeGen.h"

int eval(Node *node)
{
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

int main()
{
	// bison & flex 扫描分析，生成 AST
	doParse();

	// 后处理
	auto root = getHead();
	CodeGen codeGen;

	// printNode();
	std::cout << "Result: " << eval(root) << std::endl;

	// llvm output
	codeGen.generateIR(root);
	codeGen.printResult();

	// 清理资源
	removeNode(root);
	return 0;
}