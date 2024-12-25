%{
#include <stdlib.h>
#include "parser.tab.h"
%}

%%
[0-9]+			{ yylval.NUMBER = atoi(yytext);  return number; }

"+"	| 
"-"				{ return yytext[0]; }

\n				{ return EOL; }
.				{ /* ignore other character. */ }


%%
int yywrap() {
	return 1;
}