D			[0-9]
L			[a-zA-Z]
minus			"-"

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

int lineCounter = 1;
char *str_dup (const char *s);
extern int printLineNumber(int num);

%}

%%
"int"			{ return(INT); }
"boolean"		{ return(BOOLEAN); }
"float"			{ return(FLOAT); }
"while"			{ return(WHILE); }
"for"			{ return(FOR); }
"if"			{ return(IF); }
"else"			{ return(ELSE); }

";" 			{ return SEMI_COLON;}
","			{ return COMMA;}	
"(" 			{ return LEFT_BRACKET;}
")" 			{ return RIGHT_BRACKET;}
("{"|"<%") 		{ return LEFT_CURLY_BRACKET;}
("}"|"%>") 		{ return RIGHT_CURLY_BRACKET;}	


("true"|"false")	{ if(!strcmp(yytext,"true")){ yylval.boolVal = 1;} else { yylval.boolVal = 0;} return BOOL;}

"System.out.println"	{ return PRINT;}

"="			{ return(ASSIGN); }

("+"|"-"|"*"|"/")	{ yylval.opLexVal = str_dup(yytext); return ARITH_OP;}

("&&"|"||")		{ yylval.opLexVal = str_dup(yytext); return BOOL_OP;}
("=="|"!="|">"|">="|"<"|"<=")	{ yylval.opLexVal = str_dup(yytext); return RELA_OP;}

{L}({L}|{D})*		{ yylval.idLexVal = str_dup(yytext);return ID;}

{minus}?{D}+		{ yylval.iVal = atoi(yytext); return I_NUM;}
{minus}?{D}+("."{D}+(E{D}+)?)?	{ yylval.fVal = atof(yytext); return F_NUM;}

[ \t\v\f]
\n			{ ++lineCounter; printLineNumber(lineCounter);}	
.			{ /* ignore bad characters */ }

%%
	
int yywrap() { return 1;}

char *str_dup (const char *s) {
    char *d = (char *) malloc (strlen (s) + 1);
    if (d == NULL) return NULL;          
    strcpy (d,s);                        
    return d;                            
}

