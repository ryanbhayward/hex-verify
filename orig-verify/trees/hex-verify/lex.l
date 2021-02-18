%{

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "verifier.h"
#include "y.tab.h"

int num_errors, num_warnings;

int line_number;
int col_number;

int lex_tabwidth = 8;

char current_line[1024];

void flush()
{
}

void newline()
{
        flush();
        line_number++;
        col_number = 1;
        current_line[0] = 0;
}

void addtoken()
{
        strcat(current_line, yytext);
        col_number += yyleng;
}

void error(char *str, ...)
{
	char out[128];
	va_list args;
	va_start(args, str);
	vsnprintf(out, 128, str, args);
	va_end(args);

        num_errors++;
	printf("error:%d.%d: %s\n", line_number,col_number,out);
}

void warning(char *str, ...)
{
	char out[128];
	va_list args;
	va_start(args, str);
	vsnprintf(out, 128, str, args);
	va_end(args);

        num_warnings++;
	printf("warning:%d.%d: %s\n", line_number,col_number,out);
}

void lex_init()
{
        num_errors = num_warnings = 0;
        line_number = 1;
        col_number = 1;
        current_line[0] = 0;
}

void lex_shutdown()
{
        if (!num_warnings && !num_errors) return;
        printf("%d warning%s; %d error%s\n", 
	       num_warnings, (num_warnings == 1)?"":"s", 
	       num_errors, (num_errors == 1)?"":"s");
}


%}

%x single
%x comment

%%
"("                       { addtoken(); return(yytext[0]); }
")"                       { addtoken(); return(yytext[0]); }
"["                       { addtoken(); return(yytext[0]); }
"]"                       { addtoken(); return(yytext[0]); }
"all"                     { addtoken(); return(ALL); }
"boardsize"               { addtoken(); return(BOARDSIZE); }

[0-9]+                    { addtoken();
                            sscanf(yytext, "%d", &yylval.ival);
                            return(DIGIT); }

[a-zA-Z0-9_]+             { addtoken(); 
                            strncpy(yylval.str, yytext, 63);
                            return(ID); }

"/"+"/"                   { addtoken(); BEGIN(single); }
<single>[^\n]*            { addtoken(); }
<single>\n                { newline(); BEGIN(INITIAL); }

"{"                       { addtoken(); BEGIN(comment); }
<comment><<EOF>>          { error("lex: unterminated comment"); 
                            yyterminate(); }
<comment>\n               { newline(); }
<comment>[^}]             { addtoken(); }
<comment>"}"              { addtoken(); BEGIN(INITIAL); }

[ ]+                      { addtoken(); }
[\t]                      { col_number += lex_tabwidth; 
                            // FIXME: handle tabs properly
                          }
[\n]                      { newline(); }
.                         { error("lex: unknown symbol '%s'", yytext);
                            addtoken(); }
%%
