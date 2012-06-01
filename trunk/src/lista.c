#include "lista.h"

int tac_line = 0;


/** \brief  Construtor de Instrucao TAC
 *
 * Para testes, pode-se usar qualquer string em argumentos.
 * @param res um char*.
 * @param arg1 um char*.
 * @param op um char*.
 * @param arg2 um char*.
 * @ return um ponteiro sobre uma 'struct tac'.
 */
struct tac* create_inst_tac(const char* res, const char* arg1, const char* op, const char* arg2){
	struct tac* inst_tac;
	inst_tac=(struct tac *)malloc(sizeof(struct tac));
	if(inst_tac == NULL) {printf("Alocacao de memoria falhou\n");exit(0);}

	inst_tac->op = (char *) malloc(sizeof(char)*(strlen(op)+1));
	if(inst_tac->op == NULL) {printf("Alocacao de memoria falhou\n");exit(0);}
	else {strcpy(inst_tac->op, op);}
	
	inst_tac->res = (char *) malloc(sizeof(char)*(strlen(res)+1));
	if(inst_tac->res == NULL) {printf("Alocacao de memoria falhou\n");exit(0);}
	else {strcpy(inst_tac->res, res);}
	
	inst_tac->arg1 = (char *) malloc(sizeof(char)*(strlen(arg1)+1));
	if(inst_tac->arg1 == NULL) {printf("Alocacao de memoria falhou\n");exit(0);}
	else {strcpy(inst_tac->arg1, arg1);}	
	
	inst_tac->arg2 = (char *) malloc(sizeof(char)*(strlen(arg2)+1));
	if(inst_tac->arg2 == NULL) {printf("Alocacao de memoria falhou\n");exit(0);}
	else {strcpy(inst_tac->arg2, arg2);}	

/*    printf("instrução: %s := %s %s %s\n", inst_tac->res, inst_tac->arg1, inst_tac->op, inst_tac->arg2);*/
	return(inst_tac);
}

/** \brief Funcao que imprime o conteudo de uma instrucao TAC
 *
 * @param out um ponteiro sobre um arquivo (aberto) aonde ira ser escrita a instrucao.
 * @param i a instrucao a ser impressa.
 */
void print_inst_tac(FILE* out, struct tac i){
	
	if(strcmp(i.op,"PRINT") != 0){ //Se o operador não for PRINT
		if(strcmp(i.op,"\0") == 0){ //Se não houver segundo argumento
			fprintf(out, "%s := %s\n", i.res, i.arg1); //A operacao e atribuicao X := Y
		}
		else {
    		fprintf(out, "%s := %s %s %s\n", i.res, i.arg1, i.op, i.arg2); //A operacao e uma operacao X := Y OP Z		
		}
	}
	else{
		fprintf(out, "%s %s\n", i.op, i.arg1); //E uma instrucao print PRINT X
	}
}

/** \brief Imprime no arquivo apontado por 'out' o conteudo da lista apontada
 * por 'code'.
 *
 * @param out um ponteiro sobre um arquivo (aberto) aonde ira ser escrita a lista (uma linha por elemento).
 * @param code o ponteiro para a lista a ser impressa.
 *
 * Obs.: cada linha impressa no arquivo deve comecar por um numero inteiro
 * (3 digitos) seguido de ':'. O numero deve ser o numero da linha.
 * Exemplo:
 *   001:  instrucao_qualquer
 *   002:  outra_instrucao
 *    .....
 *   999:  ultima_instrucao
 *   000:  agora_tem_instrucao_demais
 */
void print_tac(FILE* out, struct node_tac * code){
	
	fprintf(out, "%d\n%d\n", vars_size,temps_size);
	struct node_tac * tac_pointer;
	tac_pointer = code;
	while(tac_pointer){
		fprintf(out, "%03d:   ", tac_pointer->number-1);
		print_inst_tac(out,*(tac_pointer->inst));
		tac_pointer=tac_pointer->next;
	}

}

/** Insere no fim da lista 'code' o elemento 'inst'.
 * @param code lista (possivelmente vazia) inicial, em entrada. Na saida, contem *         a mesma lista, com mais um elemento inserido no fim.
 * @inst  o elemento inserido no fim da lista.
 */
void append_inst_tac(struct node_tac ** code, struct tac * inst){
	struct node_tac * new_inst;
	new_inst = (struct node_tac *) malloc(sizeof(struct node_tac)); 
	if(new_inst == NULL) {
	    printf("Alocacao de memoria falhou\n");exit(0);
    }
	new_inst->inst = inst;
	new_inst->next = NULL;
	new_inst->number = tac_line+1;
	tac_line++;
	if(code[0]==NULL){
		code[0]=new_inst;
		new_inst->prev = NULL;
	}
	else{
	    printf("else_in\n");
		struct node_tac * tac_pointer;
		tac_pointer=code[0];
		while(tac_pointer->next){
		    printf("malocou\n");
			tac_pointer=tac_pointer->next;
		}
		tac_pointer->next = new_inst;
		new_inst->prev =  tac_pointer;
	}
}

/** Concatena a lista 'code_a' com a lista 'code_b'.
 * @param code_a lista (possivelmente vazia) inicial, em entrada. Na saida, contem
 *         a mesma lista concatenada com 'code_b'.
 * @param code_b a lista concatenada com 'code_a'.
 */
void cat_tac(struct node_tac ** code_a, struct node_tac ** code_b){
	if(code_a[0]==NULL){
		code_a[0]=code_b[0];
	}
	else{
		if(code_b[0]){
			struct node_tac * tac_pointer;
			tac_pointer=code_a[0];
			while(tac_pointer->next){
				tac_pointer=tac_pointer->next;
			}
			tac_pointer->next=code_b[0];
			code_b[0]->prev = tac_pointer;
		}
	}
}
