%{
#include <stdio.h>
#include "node.h"
#include "parserExport.h"
extern int yylex();
void yyerror(const char*);

%}

%union {
	int NUMBER;
	char OP;
	struct Node* NODE;
}


%token<NUMBER> EOL number
%token<OP> op

%type<NODE> factor exp

%%

exp: exp EOL
	| factor
	| '+' exp exp {
		Node* node = newNode(NodeType::OP);
		node->num_val = 0;  
		node->op_val = 1;
		node->left = $2;
		node->right = $3;

		$$ = node;
	}
	| '-' exp exp  {
		Node* node = newNode(NodeType::OP);
		node->num_val = 0;  
		node->op_val = 2;
		node->left = $2;
		node->right = $3;

		$$ = node;
	}

factor: number { 
		Node* node = newNode(NodeType::NUMBER); 
		node->num_val = $1;  
		node->op_val = 0;
		node->left = nullptr;
		node->right = nullptr;

		$$ = node;
	}

%%

void doParse() {
	yyparse();
}

void yyerror(const char* msg) {
	printf("%s\n", msg);
}
