D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*
FUNCTION		"memcpy"|"printf"|"fprintf"|"exit"|"malloc"|"free"|"calloc"|"realloc"|"assert"|"memset"|"longjmp"|"setjmp"|"strcmp"|"strncmp"|"strcpy"|"strncpy"|"rand"|"srand"|"time"|"strlen"|"NULL"|"stdin"|"stderr"|"EXIT_SUCCESS"|"EXIT_FAILURE"|"main"|"argc"|"argv"|"atoi"|"atof"|"strtol"|"true"|"false"|"bool"|"ssize_t"|"size_t"|"O_RDONLY"|"SEEK_END"|"SEEK_SET"|"O_WRONLY"|"O_TRUNC"|"O_CREAT"|"DEBUG"|"__FILE__"|"__FUNCTION__"|"__LINE__"|"write"|"read"|"close"|"lseek"|"seek"|"perror"|"open"

%{
#include <stdio.h>
#include "cons.h"
#include "list_exist.h"

void count();
void comment();
static list_exist list;
static FILE * currentFile = NULL;
static int isAuto = 1;
static int byPass = 0;
%}

%%
"/*"			{ comment();}

"auto"			{ fprintf(currentFile, "%s", yytext); }
"size_t"		{ fprintf(currentFile, "%s", yytext); }
"off_t"			{ fprintf(currentFile, "%s", yytext); }
"break"			{ fprintf(currentFile, "%s", yytext); }
"case"			{ fprintf(currentFile, "%s", yytext); }
"char"			{ fprintf(currentFile, "%s", yytext); }
"const"			{ fprintf(currentFile, "%s", yytext); }
"continue"		{ fprintf(currentFile, "%s", yytext); }
"default"		{ fprintf(currentFile, "%s", yytext); }
"do"			{ fprintf(currentFile, "%s", yytext); }
"double"		{ fprintf(currentFile, "%s", yytext); }
"else"			{ fprintf(currentFile, "%s", yytext); }
"enum"			{ fprintf(currentFile, "%s", yytext); }
"extern"		{ fprintf(currentFile, "%s", yytext); }
"float"			{ fprintf(currentFile, "%s", yytext); }
"for"			{ fprintf(currentFile, "%s", yytext); }
"goto"			{ fprintf(currentFile, "%s", yytext); }
"if"			{ fprintf(currentFile, "%s", yytext); }
"int"			{ fprintf(currentFile, "%s", yytext); }
"long"			{ fprintf(currentFile, "%s", yytext); }
"register"		{ fprintf(currentFile, "%s", yytext); }
"return"		{ fprintf(currentFile, "%s", yytext); }
"short"			{ fprintf(currentFile, "%s", yytext); }
"signed"		{ fprintf(currentFile, "%s", yytext); }
"sizeof"		{ fprintf(currentFile, "%s", yytext); }
"static"		{ fprintf(currentFile, "%s", yytext); }
"struct"		{ fprintf(currentFile, "%s", yytext); }
"switch"		{ fprintf(currentFile, "%s", yytext); }
"typedef"		{ fprintf(currentFile, "%s", yytext); }
"union"			{ fprintf(currentFile, "%s", yytext); }
"unsigned"		{ fprintf(currentFile, "%s", yytext); }
"void"			{ fprintf(currentFile, "%s", yytext); }
"volatile"		{ fprintf(currentFile, "%s", yytext); }
"while"			{ fprintf(currentFile, "%s", yytext); }
{FUNCTION}		{ fprintf(currentFile, "%s", yytext); }
{L}({L}|{D})*		{ char * reso = malloc(sizeof(char)*(strlen(yytext) + 1)); memcpy(reso, yytext, sizeof(char)*(strlen(yytext) + 1));cons * res = get_from_key(list, reso, isAuto, byPass); fprintf(currentFile, "%s", res->second); if(byPass==1)byPass=0;}
#"define"|"ifdef"|"ifndef" {fprintf(currentFile, "%s", yytext);byPass=1;}
#{L}({L}|{D})* {fprintf(currentFile, "%s", yytext);}
\<{L}({L}|{D}|\/)*".h"\> {fprintf(currentFile, "%s", yytext);}

0[xX]{H}+{IS}?		{ fprintf(currentFile, "%s", yytext); }
0{D}+{IS}?		{ fprintf(currentFile, "%s", yytext); }
{D}+{IS}?		{ fprintf(currentFile, "%s", yytext); }
'(\\.|[^\\'])+'		{ fprintf(currentFile, "%s", yytext); }

{D}+{E}{FS}?		{ fprintf(currentFile, "%s", yytext); }
{D}*"."{D}+({E})?{FS}?	{ fprintf(currentFile, "%s", yytext); }
{D}+"."{D}*({E})?{FS}?	{ fprintf(currentFile, "%s", yytext); }

\"(\\.|[^\\"])*\"	{ fprintf(currentFile, "%s", yytext); }

">>="			{ fprintf(currentFile, "%s", yytext); }
"<<="			{ fprintf(currentFile, "%s", yytext); }
"+="			{ fprintf(currentFile, "%s", yytext); }
"-="			{ fprintf(currentFile, "%s", yytext); }
"*="			{ fprintf(currentFile, "%s", yytext); }
"/="			{ fprintf(currentFile, "%s", yytext); }
"%="			{ fprintf(currentFile, "%s", yytext); }
"&="			{ fprintf(currentFile, "%s", yytext); }
"^="			{ fprintf(currentFile, "%s", yytext); }
"|="			{ fprintf(currentFile, "%s", yytext); }
">>"			{ fprintf(currentFile, "%s", yytext); }
"<<"			{ fprintf(currentFile, "%s", yytext); }
"++"			{ fprintf(currentFile, "%s", yytext); }
"--"			{ fprintf(currentFile, "%s", yytext); }
"->"			{ fprintf(currentFile, "%s", yytext); }
"&&"			{ fprintf(currentFile, "%s", yytext); }
"||"			{ fprintf(currentFile, "%s", yytext); }
"<="			{ fprintf(currentFile, "%s", yytext); }
">="			{ fprintf(currentFile, "%s", yytext); }
"=="			{ fprintf(currentFile, "%s", yytext); }
"!="			{ fprintf(currentFile, "%s", yytext); }
";"			{ fprintf(currentFile, "%s", yytext); }
"{"			{ fprintf(currentFile, "%s", yytext); }
"}"			{ fprintf(currentFile, "%s", yytext); }
","			{ fprintf(currentFile, "%s", yytext); }
":"			{ fprintf(currentFile, "%s", yytext); }
"="			{ fprintf(currentFile, "%s", yytext); }
"("			{ fprintf(currentFile, "%s", yytext); }
")"			{ fprintf(currentFile, "%s", yytext); }
"["			{ fprintf(currentFile, "%s", yytext); }
"]"			{ fprintf(currentFile, "%s", yytext); }
"."			{ fprintf(currentFile, "%s", yytext); }
"&"			{ fprintf(currentFile, "%s", yytext); }
"!"			{ fprintf(currentFile, "%s", yytext); }
"~"			{ fprintf(currentFile, "%s", yytext); }
"-"			{ fprintf(currentFile, "%s", yytext); }
"+"			{ fprintf(currentFile, "%s", yytext); }
"*"			{ fprintf(currentFile, "%s", yytext); }
"/"			{ fprintf(currentFile, "%s", yytext); }
"%"			{ fprintf(currentFile, "%s", yytext); }
"<"			{ fprintf(currentFile, "%s", yytext); }
">"			{ fprintf(currentFile, "%s", yytext); }
"^"			{ fprintf(currentFile, "%s", yytext); }
"|"			{ fprintf(currentFile, "%s", yytext); }
"?"			{ fprintf(currentFile, "%s", yytext); }

[ \t\v\n\f]		{ fprintf(currentFile, "%s", yytext); }
.			{ /* ignore bad characters */ fprintf(currentFile, "%s", yytext); }

%%

int yywrap()
{
 return 1;
}

void comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0)
		;//putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		;//putchar(c1);
}

int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}

static void usage(char * s)
{
  fprintf(stderr, "Usage: %s [-m(manuel)] <fichier a obfusquer>\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  if(argc < 2)
    usage(argv[0]);
  list = create();
  int i = 1;
  if(strlen(argv[1]) == 2 && argv[1][1] == 'm')
  {
    isAuto = 0;
    i = 2;
    printf("is not auto");
  }
  for(; i < argc; i++)
  {
    char tmp[strlen(argv[i]) + 2];
    memcpy(tmp, argv[i], sizeof(char)*(strlen(argv[i])));
    tmp[strlen(argv[i])] = '_';
    tmp[strlen(argv[i]) + 1] = '\0';
    currentFile = fopen(tmp, "w");
    if(currentFile == NULL)
    {
	perror("fopen");
	return 1;
    }
    yyin = fopen(argv[i], "r");
    if(yyin == NULL)
    {
	perror("fopen");
	return 1;
    }
    fprintf(currentFile, "#include \"convert.h\"\n");
    yylex();
    fclose(currentFile);
    fclose(yyin);
    currentFile = NULL;
    yyin = NULL;
  }
  saveToFile(list, "convert.h");
  delete(list);
  return 0;
}
