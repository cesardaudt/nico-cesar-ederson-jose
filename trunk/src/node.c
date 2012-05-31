#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "node.h"

#define max(x, y) (((x)>(y)) ? (x) : (y))

Node * syntax_tree;

NULL_TERMINATED Node* create_node(int nl, Node_type t, char* lexeme, /* Node* children */ ...) {
	
	Node *new_node;
	
	new_node = (Node*)(malloc(sizeof(Node)));
	
	if(new_node == NULL){
		printf("Alocacao de memoria falhou\n");
		exit(0);
	}
	
	new_node->code = NULL;
	new_node->line_num = nl;
	new_node->deslocamento = NULL;
	new_node->array = NULL;
	new_node->ndim = 0;

    int a = 0;	
	if(lexeme != NULL) {
	    while(lexeme[a] != '\0'){
		    a++;
	    }	
	    new_node->lexeme = (char *)(malloc(sizeof(char)*a+1));

	    if(new_node->lexeme == NULL){
		    printf("Alocacao de memoria falhou\n");
		    exit(0);
	    }

	    memcpy(new_node->lexeme, lexeme, a);
	}

	else {
	    new_node->lexeme = "";
	}
	
	new_node->type = t;
	
	/*attribute; Qualquer coisa por enquanto. */
	
	/* parte que preenche a lista de filhos */

    va_list ap;
    va_start(ap, lexeme);
    int n_children=0;
    Node* arg = va_arg(ap, Node*);
    while (arg != NULL) {	/* conta o tamanho da lista */
        n_children ++;
        arg = va_arg(ap, Node*);
    };
    va_end(ap);
    
    new_node->n_children = n_children;
    
    new_node->children = (Node **)malloc(sizeof(Node *)*(n_children+1));
    
    new_node->children[n_children] = NULL;
	
    int k = 0;
    va_start(ap, lexeme);
    arg = va_arg(ap, Node*);
    while (arg != NULL) {	/* preenche a lista */
        new_node->children[k] = arg;		/*  */
        k++;
        arg = va_arg(ap, Node*);
    };
    va_end(ap);

    return new_node;
}

Node* child(Node* n, int i) {
	if(n == NULL) {
		printf("Tentou acessar um nodo inexistente\n");
		exit(0);
	}
	if((i >= n->n_children) || (i < 0)) {
		printf("Tentou acessar um nodo inexistente\n");
		exit(0);
	}
	else
		return n->children[i];
}

//Na criação do nodo, é setado um atributo da quantidade de filhos. Logo, é necessário fazer esta contagem??
int nb_of_children(Node* n) {
	if(n == NULL){
		printf("Tentou acessar um nodo inexistente\n");
		exit(0);
	}
	int count = 0;
	while(n->children[count]!=NULL)
		count++;
	return count;
}

int height(Node *n) {
	if(n == NULL){
		printf("Tentou acessar um nodo inexistente\n");
		exit(0);
	}
	if(n->n_children == 0)
		return 1;
	else
	{
		int current_height = 0;
		int i;
		for(i = 0; i < n->n_children; i++)		/* nesse laco, a variavel current_height recebe o tamanho do caminho mais longo ate uma folha a partir do nodo atual */
		{
			current_height = max(current_height, height(n->children[i]));		/* recursao */
		}
		return current_height + 1;
	}
}

int deep_free_node(Node* n) {
	if(n->children[0] != NULL)	/* se nao for folha, chama a funcao pra todos os filhos antes de liberar o seu proprio espaco alocado */
	{
		int i;
		for(i = 0;i< n->n_children;i++) {
			deep_free_node(n->children[i]);
		}
	}
	if(n->lexeme != NULL) {
		free(n->lexeme);		/* libera a memoria alocada para o lexema */
		n->lexeme = NULL;
	}
	free(n->children);	/* libera a memoria alocada para a lista de ponteiros */
	free(n);		/* libera a memoria alocada para o nodo */
	n = NULL;
	return 0;
}

int is_leaf(Node* n) {
	if(n == NULL){
		printf("Tentou acessar um nodo inexistente\n");
		exit(0);
	}
	if(n->children[0] == NULL)
		return 1;
	else
		return 0;
}


void uncompile(FILE* outfile, Node *n) {
	//Imprime o valor dos lexemas de todos os nodos folha da esquerda para direita
	if(n==NULL){
		printf("Foi mandado imprimir um nodo nulo!!!\n");
		exit(0);
	}
	if(n->n_children>0) {
		int i;
		for(i=0;i<n->n_children;i++) {
			uncompile(outfile,n->children[i]);
		}
	}
	else {
		fputs(n->lexeme, outfile);
		/*Foi necessario inserir um espaço depois de cada lexema escrito, pois alguns problemas estavam acontecendo.

		  ex1.: "while (true and false) {" ao ser decompilado ficava "while(trueandfalse){", porem, "trueandfalse" 
		  seria interpretado como um idf na recompilacao;

		  ex2.: "end end end end" ao ser decompilado ficava "endendend", que seria identificado como apenas um idf 
		  na recompilacao.
		*/
		fputs(" ", outfile);
		//Caso o lexema seja um dos caracteres ";", "{", "}" ou "then" insere uma quebra de linha
		if( !strcmp(n->lexeme,";") || !strcmp(n->lexeme,"{") || 
		    !strcmp(n->lexeme,"}") || !strcmp(n->lexeme,"then"))
			fputs("\n", outfile);
	}
}
