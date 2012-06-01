#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "lista.h"
#include "symbol_table.h"

/* Programa principal do nico. */
char* progname;
int lineno;
extern FILE* yyin;
symbol_t symbol_table;
FILE* outfile;

void yyerror(char* s) {
    fprintf(stderr, "%s: %s", progname, s);
    fprintf(stderr, "line %d\n", lineno);
}



int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("uso: %s -o <output.tac>  <src.nico>. Try again!\n", argv[0]);
        exit(-1);
    }
    

    if(init_table(&symbol_table)){
		printf("Falha na criacao da tabela de simbolos\n");
		exit(0);
	}
	
    
    yyin = fopen(argv[3], "r");
    
    if (!yyin) {
        printf("uso: %s -o <output.tac> <src.nico>. Could not find %s.\n", 
        argv[0], argv[3]);
        exit(-1);
    }

    progname = argv[0];
    if (!yyparse()) 
        printf("OKAY.\n");
    else {
        printf("ERROR.\n");
        exit(0);
    }
    fclose(yyin);

    outfile = fopen(argv[2],"w");
	//print_table(symbol_table);
	print_tac(outfile,syntax_tree->code);

/*    uncompile(outfile,syntax_tree);*/
    
    fclose(outfile);
    //deep_free_node(syntax_tree);
  
    return(0);
}
