/** @file node.h
 *  @version 1.2
 */

#ifndef _NODE_H_
#define _NODE_H_

#ifdef __GNUC__
    /* If using gcc, warn about missing sentinel NULLs */
    #define NULL_TERMINATED __attribute__((sentinel))
#else
    #define NULL_TERMINATED
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lista.h"


typedef int Node_type;

/* Serie de constantes que servirao para definir tipos de nos (na arvore). 
 * Essa serie pode ser completada ou alterada a vontade.
 */
#define acoes_node		501
#define add_node		502
#define and_node		503
#define attr_node		504
#define chamaproc_node		505
#define char_node		506
#define code_node		507
#define colon_node		508
#define comando_node		509
#define comma_node		510
#define declaracao_node		511
#define declaracoes_node	512
#define div_node		513
#define double_node		514
#define else_node		515
#define end_node		516
#define enunciado_node		517
#define eq_node			518
#define expbool_node		519
#define expr_node		520
#define false_node		521
#define fiminstcontrole_node	522
#define float_node		523
#define ge_node			524
#define gt_node			525
#define idf_node		526
#define if_node			527
#define int_lit_node		528
#define int_node		529
#define l_chaves_node		530
#define l_colchetes_node	531
#define l_parenteses_node	532
#define le_node			533
#define listadeclaracao_node	534
#define listadupla_node		535
#define listaexpr_node		536
#define lt_node			537
#define lvalue_node		538
#define mul_node		539
#define ne_node			540
#define not_node		541
#define or_node			542
#define r_chaves_node		543
#define r_colchetes_node	544
#define r_parenteses_node	545
#define real_node		546
#define semicolon_node		547
#define sub_node		548
#define swap_node		549
#define then_node		550
#define tipo_node		551
#define tipolista_node		552
#define tipounico_node		553
#define true_node		554
#define while_node		555
#define print_node		556




/** Estrutura de dados parcial para o no da arvore. */


typedef struct _node {
   int line_num;   /**< numero de linha. */
   char* lexeme;   /**< o lexema retornado pelo analizador lexical. */
   Node_type type; /**< Um dos valores definidos acima pelos # defines. */
   void* attribute;/**< Qualquer coisa por enquanto. */
   int n_children;	/* numero de filhos do nodo */
   struct _node** children;	/* Lista de ponteiros para os filhos do nodo, dinamicamente alocada na criacao */
   
   struct node_tac * code;
   
   
} Node;

extern Node * syntax_tree;


/**
 *  * Node constructor.
 *
 * @param nl: line number where this token was found in the source code.
 * @param t: node type (one of the values #define'd above). Must abort
 *             the program if the type is not correct.
 * @param lexeme: whatever string you want associated to this node.
 * @param attr: a semantical attribute.
 * @param children: NULL-terminated list of pointers to children Node*'s.
 *     See the extra file 'exemplo_func_var_arg.c' for an example.
 *     Callers are expected to pass *only Node pointers* as arguments.
 *     To create a leaf, use just NULL.
 * @return a pointer to a new Node.
 */
NULL_TERMINATED Node* create_node(int nl, Node_type t, char* lexeme,  /* Node* children */ ...);

/** Accessor to the number of children of a Node.
 *  Must abort the program if 'n' is NULL.
 */
int nb_of_children(Node* n);

/** Tests if a Node is a leaf.
 *  Must abort the program if 'n' is NULL.
 *  @return 1 if n is a leaf, 0 else.
 */
int is_leaf(Node* n);

/** accessor to the i'th child of a Node.
 * @param n : the node to be consulted. Must abort the program if 'n' is NULL.
 * @param i : the number of the child that one wants. Given a node degree d,
 *       valid values for i are: 0 <= i < d.
 *       Must abort the program if i is not correct.
 * @return a pointer to a Node.
 */
Node* child(Node* n, int i) ;

/** Destructor of a Node. Deallocates
 * (recursively) all of the tree rooted at 'n'.
 */
int deep_free_node(Node* n) ;

/** returns the height of the tree rooted by 'n'.
 *  The height of a leaf is 1. 
 */
int height(Node *n) ;

/** Prints into a file the lexemes contained in the node rooted by 'n'.
 *  Lexemes must be printed in a depth-first order.
 *  @param outfile : the file to which the lexemes are printed.
 *  @param n : the root node of the tree. Must abort the program if 'n' is NULL.
 *
 */
void uncompile(FILE* outfile, Node *n);
#endif
