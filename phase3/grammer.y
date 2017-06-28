%{
#include <fstream>
#include <iostream>
#include <map>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <unistd.h>

#define GetCurrentDir getcwd

using namespace std;

string inputFile;
ofstream fout("bytecode.java");	
int varCount = 1; 	
int labelsCount = 0;	
vector<string> codeList;
extern  int yylex();
extern  FILE *yyin;
extern int lineCounter;

typedef enum {INT_T, FLOAT_T, BOOL_T, VOID_T, ERROR_T} type_enum;
map<string, pair<int,type_enum> > symbTab;
map<string,string> inst_list = {
	{"+", "add"},
	{"-", "sub"},
	{"/", "div"},
	{"*", "mul"},
	{"==", "if_icmpeq"},
	{"<=", "if_icmple"},
	{">=", "if_icmpge"},
	{"!=", "if_icmpne"},
	{">",  "if_icmpgt"},
	{"<",  "if_icmplt"}
};

/* helping functions */

void yyerror(const char * s);
void genHeader(void);	
void genFooter(void);	
void cast(int from , int to, string op);
bool checkId(string id);
string getByteCode(string op);
void var(string name, int type);
string genNewLabel();
string getLabel(int n);
void writeLabel(vector<int> *list, int num);
vector<int> * concat (vector<int> *list1, vector<int>* list2);
void printCode(void);
void printLineNumber(int num)
{
	codeList.push_back(".line "+ to_string(num));
}

%}

%start method_body

%code requires {
	#include <vector>
	using namespace std;
}

%union{
	/* values */
	int iVal, boolVal;
	char *idLexVal, *opLexVal;
	float fVal;	

	/* types */
	int sType;
	struct {
		vector<int> *nextList;
	} stmt_type;
	struct {
		int sType;
	} expr_type;
	struct {
		vector<int> *trueList, *falseList;
	} bexpr_type;
}

%token IF ELSE WHILE FOR INT FLOAT BOOLEAN
%token SEMI_COLON ASSIGN LEFT_BRACKET RIGHT_BRACKET LEFT_CURLY_BRACKET RIGHT_CURLY_BRACKET COMMA
%token PRINT

%token <iVal> I_NUM
%token <fVal> F_NUM
%token <boolVal> BOOL
%token <idLexVal> ID
%token <opLexVal> ARITH_OP
%token <opLexVal> RELA_OP
%token <opLexVal> BOOL_OP

%type <sType> primitive_type
%type <expr_type> expression
%type <bexpr_type> boolean_expr
%type <stmt_type> statement
%type <stmt_type> statement_list
%type <stmt_type> if
%type <stmt_type> while
%type <stmt_type> for
%type <iVal> label
%type <iVal> goto

%% 
method_body: 
	{	genHeader();	}
	statement_list
	label
	{
		writeLabel($2.nextList,$3);
		genFooter();
	}
	;
statement_list: 
	statement 
	| 
	statement_list
	label 
	statement
	{
		writeLabel($1.nextList,$2);
		$$.nextList = $3.nextList;
	}
	;
statement: 
	declaration {vector<int> * v = new vector<int>(); $$.nextList =v;}
	|if {$$.nextList = $1.nextList;}
	|while 	{$$.nextList = $1.nextList;}
	|for {$$.nextList = $1.nextList;}
	|assignment {vector<int> * v = new vector<int>(); $$.nextList =v;}
	|system_print {vector<int> * v = new vector<int>(); $$.nextList =v;}
	;
declaration: 
	primitive_type ID SEMI_COLON
	{
		string str($2);
		if($1 == INT_T)
		{
			var(str,INT_T);
		}else if ($1 == FLOAT_T)
		{
			var(str,FLOAT_T);
		}
	}
	;
primitive_type: 
	INT {$$ = INT_T;}
	|FLOAT {$$ = FLOAT_T;}
	|BOOLEAN {$$ = BOOL_T;}
	;
if: 
	IF LEFT_BRACKET boolean_expr RIGHT_BRACKET LEFT_CURLY_BRACKET 
	label statement_list goto RIGHT_CURLY_BRACKET ELSE LEFT_CURLY_BRACKET
	label statement_list RIGHT_CURLY_BRACKET
	{
		writeLabel($3.trueList,$6);
		writeLabel($3.falseList,$12);
		$$.nextList = concat($7.nextList, $13.nextList);
		$$.nextList->push_back($8);
	}
	;
while:
	label WHILE LEFT_BRACKET boolean_expr RIGHT_BRACKET LEFT_CURLY_BRACKET
	label statement_list RIGHT_CURLY_BRACKET
	{
		codeList.push_back("goto " + getLabel($1));
		writeLabel($8.nextList,$1);
		writeLabel($4.trueList,$7);
		$$.nextList = $4.falseList;
	}
	;
for:
	FOR LEFT_BRACKET assignment label boolean_expr SEMI_COLON
	label assignment goto RIGHT_BRACKET LEFT_CURLY_BRACKET label
	statement_list goto RIGHT_CURLY_BRACKET
	{
		writeLabel($5.trueList,$12);
		vector<int> * v = new vector<int> ();
		v->push_back($9);
		writeLabel(v,$4);
		v = new vector<int>();
		v->push_back($14);
		writeLabel(v,$7);
		writeLabel($13.nextList,$7);
		$$.nextList = $5.falseList;
	}
	;
assignment: 
	ID ASSIGN expression SEMI_COLON
	{
		string str($1);
		if(checkId(str))
		{
			if($3.sType == INT_T)
			{
				codeList.push_back("istore " + to_string(symbTab[str].first));
			}else if ($3.sType == FLOAT_T)
			{
				codeList.push_back("fstore " + to_string(symbTab[str].first));
			}
		}else{
			string err = "identifier: "+str+" isn't declared in this scope";
			yyerror(err.c_str());
		}
	}
	;
expression: 
	I_NUM 	{$$.sType = INT_T;  codeList.push_back("ldc "+to_string($1));} 
	|F_NUM 	{$$.sType = FLOAT_T; codeList.push_back("ldc "+to_string($1));}
	|expression ARITH_OP expression	{cast($1.sType, $3.sType, string($2));}
	|ID {
		string str($1);
		if(checkId(str))
		{
			$$.sType = symbTab[str].second;
			if(symbTab[str].second == INT_T)
			{
				codeList.push_back("iload " + to_string(symbTab[str].first));
			}else if (symbTab[str].second == FLOAT_T)
			{
				codeList.push_back("fload " + to_string(symbTab[str].first));
			}
		}
		else
		{
			string err = "id: "+str+" isn't declared in this scope";
			yyerror(err.c_str());
			$$.sType = ERROR_T;
		}
	}
	|LEFT_BRACKET expression RIGHT_BRACKET {$$.sType = $2.sType;}
	;
boolean_expr:
	BOOL
	{
		if($1)
		{
			$$.trueList = new vector<int> ();
			$$.trueList->push_back(codeList.size());
			$$.falseList = new vector<int>();
			codeList.push_back("goto ");
		}else
		{
			$$.trueList = new vector<int> ();
			$$.falseList= new vector<int>();
			$$.falseList->push_back(codeList.size());
			codeList.push_back("goto ");
		}
	}
	|boolean_expr BOOL_OP label boolean_expr
	{
		if(!strcmp($2, "&&"))
		{
			writeLabel($1.trueList, $3);
			$$.trueList = $4.trueList;
			$$.falseList = concat($1.falseList,$4.falseList);
		}
		else if (!strcmp($2,"||"))
		{
			writeLabel($1.falseList,$3);
			$$.trueList = concat($1.trueList, $4.trueList);
			$$.falseList = $4.falseList;
		}
	}	
	|expression RELA_OP expression		
	{
		string op ($2);
		$$.trueList = new vector<int>();
		$$.trueList ->push_back (codeList.size());
		$$.falseList = new vector<int>();
		$$.falseList->push_back(codeList.size()+1);
		codeList.push_back(getByteCode(op)+ " ");
		codeList.push_back("goto ");
	}
	;
system_print:
	PRINT LEFT_BRACKET expression RIGHT_BRACKET SEMI_COLON
	{
		/* expression is at top of stack now 
		** save it at the predefined temp syso var 
		*/
		if($3.sType == INT_T)
		{			
			codeList.push_back("istore " + to_string(symbTab["1syso_int_var"].first));
			/* call syso */			
			codeList.push_back("getstatic      java/lang/System/out Ljava/io/PrintStream;");
			/*insert param*/
			codeList.push_back("iload " + to_string(symbTab["1syso_int_var"].first ));
			/*invoke syso*/
			codeList.push_back("invokevirtual java/io/PrintStream/println(I)V");

		}else if ($3.sType == FLOAT_T)
		{
			codeList.push_back("fstore " + to_string(symbTab["1syso_float_var"].first));
			/* call syso */			
			codeList.push_back("getstatic      java/lang/System/out Ljava/io/PrintStream;");
			/*insert param*/
			codeList.push_back("fload " + to_string(symbTab["1syso_float_var"].first ));
			/*invoke syso*/
			codeList.push_back("invokevirtual java/io/PrintStream/println(F)V");
		}
	}
	;

label:
{
	$$ = labelsCount;
	codeList.push_back(genNewLabel());
}
;
goto:
{
	$$ = codeList.size();
	codeList.push_back("goto ");
}
;

%%

/*		main function		*/

main (int argv, char * argc[])
{
	FILE *file;
	if(argv == 1) 
	{
		file = fopen("source.txt", "r");
		inputFile = "source.txt";
	}
	else 
	{
		file = fopen(argc[1], "r");
		inputFile = string(argc[1]);
	}
	if (!file) {
		printf("Error: can't open file!\n");
		return -1;
	}
	yyin = file;
	yyparse();
	printCode();
}

/*		helping functions		*/

void yyerror(const char * s)
{
	printf("error@%d: %s\n",lineCounter, s);
}

void genHeader()
{
	codeList.push_back(".source " + inputFile);
	codeList.push_back(".class public test\n.super java/lang/Object\n"); //code for defining class
	codeList.push_back(".method public <init>()V");
	codeList.push_back("aload_0");
	codeList.push_back("invokenonvirtual java/lang/Object/<init>()V");
	codeList.push_back("return");
	codeList.push_back(".end method\n");
	codeList.push_back(".method public static main([Ljava/lang/String;)V");
	codeList.push_back(".limit locals 100\n.limit stack 100");

	/* generate temporal vars for syso*/
	var("1syso_int_var",INT_T);
	var("1syso_float_var",FLOAT_T);

	/*generate line 1*/
	codeList.push_back(".line 1");
}

void genFooter()
{
	codeList.push_back("return");
	codeList.push_back(".end method");
}

bool checkId(string op)
{
	return (symbTab.find(op) != symbTab.end());
}

void var(string name, int type)
{
	if(checkId(name))
	{
		string err = name+" redeclared variable";
		yyerror(err.c_str());
	}else
	{
		if(type == INT_T)
		{
			codeList.push_back("iconst_0\nistore " + to_string(varCount));
		}
		else if ( type == FLOAT_T)
		{
			codeList.push_back("fconst_0\nfstore " + to_string(varCount));
		}
		symbTab[name] = make_pair(varCount++,(type_enum)type);
	}
}

string genNewLabel()
{
	return "l_"+to_string(labelsCount++) + ":";
}

string getLabel(int n)
{
	return "l_"+to_string(n);
}

void writeLabel(vector<int> *lists, int ind)
{
	if(lists)
	for(int i =0 ; i < lists->size() ; i++)
	{
		codeList[(*lists)[i]] = codeList[(*lists)[i]] + getLabel(ind);
	}
}

void printCode(void)
{
	for ( int i = 0 ; i < codeList.size() ; i++){
		fout<<codeList[i]<<endl;
	}
}

string getByteCode(string op)
{
	if(inst_list.find(op) != inst_list.end()){
		return inst_list[op];
	}
	return "";
}

void cast(int from , int to, string op)
{
	if(from == to)
	{
		if(from == INT_T)
		{
			codeList.push_back("i" + getByteCode(op));
		}else if (from == FLOAT_T)
		{
			codeList.push_back("f" + getByteCode(op));
		}
	}
}

vector<int> * concat(vector<int> *list1, vector<int> *list2)
{
	if(list1 && list2){
		vector<int> *list = new vector<int> (*list1);
		list->insert(list->end(), list2->begin(),list2->end());
		return list;
	}else if(list1)
	{
		return list1;
	}else if (list2)
	{
		return list2;
	}else
	{
		return new vector<int>();
	}
}
