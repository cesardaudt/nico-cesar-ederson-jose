%error-verbose

%{
  /* Aqui, pode-se inserir qualquer codigo C necessario na compilacao
   * final do parser. Sera copiado tal como esta no inicio do y.tab.c
   * gerado por Yacc.
   */
    #include <stdio.h>
    #include <stdlib.h>
    #include "node.h"
    #include "lista.h"
    #include "symbol_table.h"

    #define UNDEFINED_SYMBOL_ERROR -21
    #define CHAR_TYPE   0
    #define INT_TYPE    1
    #define REAL_TYPE   2
    #define DOUBLE_TYPE 3
    #define CHAR_SIZE   1
    #define INT_SIZE    4
    #define REAL_SIZE   4
    #define DOUBLE_SIZE 8   

    typedef struct expr_attr {
            struct node_tac *code;
            char *local;
            int size;
    } EXPR_ATTR;
    
    extern symbol_t symbol_table;
    int tipo_idf = 0;
    int vars_size = 0;
    int temps_size = 0;
    
    char* gera_temp(int type) {
        int size = 0;
        switch (type) {
            case CHAR_TYPE:     size = CHAR_SIZE; break;
            case INT_TYPE:      size = INT_SIZE; break;
            case REAL_TYPE:     size = REAL_SIZE; break;
            case DOUBLE_TYPE:   size = DOUBLE_SIZE; break;
        }
        //uma variável temporária é, essencialmente, o seu deslocamento do registrador Rx.
        //isso gera uma string "ddd(Rx)", que possui tamanho 8 (7+\0) e ddd é o valor da variável temps_size
        char *ret = malloc(sizeof(char)*8);
        sprintf(ret, "%03d(Rx)", temps_size);
        temps_size += size;
        return ret;
    }
    
    void theBookIsOnTheTable(char *lexeme){
    	if(lookup(symbol_table, lexeme)){//testa se já existe uma entrada com esse nome na tabela
					printf("Símbolo %s foi definido múltiplas vezes. \n", lexeme);
					exit(0);

	}
	    else{
		    entry_t* new_entry=(entry_t *) malloc(sizeof(entry_t));
    //		printf("%s %d\n",lexeme,vars_size);
		    new_entry->name = lexeme;
		    new_entry->type = tipo_idf;
		    new_entry->desloc = vars_size;

		    switch(tipo_idf){
		        	case INT_TYPE:		new_entry->size = INT_SIZE;
						    vars_size += INT_SIZE;
    //						printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case DOUBLE_TYPE:	new_entry->size = DOUBLE_SIZE;
						    vars_size += DOUBLE_SIZE;
    //						printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case REAL_TYPE:		new_entry->size = REAL_SIZE;
						    vars_size += REAL_SIZE;
    //						printf("%s %d\n",lexeme,vars_size);
						    break;
		        	case CHAR_TYPE:		new_entry->size = CHAR_SIZE;
						    vars_size += CHAR_SIZE;
    //						printf("%s %d\n",lexeme,vars_size);
		    }
		    if(insert(&symbol_table, new_entry)){
			    printf("Ocorreu um erro ao alocar o simbolo %s na tabela de simbolos.\n",lexeme);
			    exit(0);
		    }
	    }
    }
    
 /*
    Essa funcao consulta a tabela atras de um identificador e retorna o conteudo para 
    a string "local" caso o identificador esteja na tabela, caso contrario retorna o proprio identificador
    */
    char* consulta_tabela(char* identificador) {
        entry_t* entrada;
        entrada = lookup(symbol_table,identificador);
        if(entrada == NULL)
        	return (NULL);
        
        char *ret = malloc(sizeof(char)*8);
        sprintf(ret, "%03d(SP)", entrada->desloc);
        return ret;
    }      
    
%}

%union {
  char* cadeia;
  struct _node * no;
}

%token<cadeia> AND
%token<cadeia> CHAR
%token<cadeia> CONST
%token<cadeia> DOUBLE
%token<cadeia> ELSE
%token<cadeia> END
%token<cadeia> EQ
%token<cadeia> F_LIT
%token<cadeia> FALSE
%token<cadeia> FOR
%token<cadeia> GE
%token<cadeia> IDF
%token<cadeia> IF
%token<cadeia> INT
%token<cadeia> INT_LIT
%token<cadeia> LE
%token<cadeia> NE
%token<cadeia> NEXT
%token<cadeia> NOT
%token<cadeia> OR
%token<cadeia> QUOTE
%token<cadeia> REAL
%token<cadeia> STR_LIT
%token<cadeia> STRING
%token<cadeia> SWAP
%token<cadeia> THEN
%token<cadeia> TRUE
%token<cadeia> WHILE
%token<cadeia> PRINTF

%left	OR
%left	AND
%left	NOT
%left	'+' '-'
%left	'*' '/'

%type<no> code 
%type<no> declaracoes
%type<no> acoes
%type<no> declaracao
%type<no> tipo
%type<no> listadeclaracao
%type<no> tipounico
%type<no> tipolista
%type<no> listadupla
%type<no> comando
%type<no> lvalue
%type<no> listaexpr
%type<no> chamaproc
%type<no> fiminstcontrole
%type<no> expbool
%type<no> enunciado
%type<no> expr

%start code

 /* A completar com seus tokens - compilar com 'yacc -d' */

%%
code: declaracoes acoes {   $$ = create_node(@1.first_line, code_node, NULL, $1, $2, NULL);
			                cat_tac(&($$->code), &($2->code));
                            syntax_tree = $$; }
    | acoes             {   $$ = $1;
            			    $$->type = code_node; 
                            syntax_tree = $$; }
    ;

declaracoes: declaracao ';'             {	Node* n = create_node(@1.first_line, semicolon_node, ";", NULL);
						                    $$ = create_node(@1.first_line, declaracoes_node, NULL, $1, n, NULL); }
           | declaracoes declaracao ';' {	Node* n = create_node(@1.first_line, semicolon_node, ";", NULL);
           					                $$ = create_node(@1.first_line, declaracoes_node, NULL, $1, $2, n, NULL); }
           ;

declaracao: tipo ':' listadeclaracao    {	Node* n = create_node(@1.first_line, colon_node, ":", NULL);
			       			                $$ = create_node(@1.first_line, declaracao_node, NULL, $1, n, $3, NULL); }
	      ;

listadeclaracao: IDF				        {	Node* n = create_node(@1.first_line, idf_node, $1, NULL);
							                    theBookIsOnTheTable($1);
							                    $$ = create_node(@1.first_line, listadeclaracao_node, $1, n, NULL);	}
               | IDF ',' listadeclaracao	{	Node* n1 = create_node(@1.first_line, idf_node, $1, NULL);
							                    Node* n2 = create_node(@1.first_line, comma_node, ",", NULL);
							                    theBookIsOnTheTable($1);
							                    $$ = create_node(@1.first_line, listadeclaracao_node, NULL, n1, n2, $3, NULL); }
               ;

tipo: tipounico {   $$ = $1;
			        if(!strcmp($$->lexeme,"int"))
				    tipo_idf = INT_TYPE;
			        if(!strcmp($$->lexeme,"double"))
				    tipo_idf = DOUBLE_TYPE;
			        if(!strcmp($$->lexeme,"real"))
				    tipo_idf = REAL_TYPE;
			        if(!strcmp($$->lexeme,"char"))
				    tipo_idf = CHAR_TYPE;
    			    $$->type = tipo_node; }
    //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
    | tipolista {  $$ = $1; 
			/*$$->type = tipo_node;*/ }
    ;

tipounico: INT      {	Node* n = create_node(@1.first_line, int_node, "int", NULL);
			            $$ = create_node(@1.first_line, tipounico_node, "int", n, NULL); }
         | DOUBLE   {	Node* n = create_node(@1.first_line, double_node, "double", NULL);
			            $$ = create_node(@1.first_line, tipounico_node, "double", n, NULL); }
         | REAL     {	Node* n = create_node(@1.first_line, real_node, "real", NULL);
			            $$ = create_node(@1.first_line, tipounico_node, "real", n, NULL); }
         | CHAR     {	Node* n = create_node(@1.first_line, char_node, "char", NULL);
			            $$ = create_node(@1.first_line, tipounico_node, "char", n, NULL); }
         ;
        //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
tipolista: INT '(' listadupla ')'       {   Node* n1 = create_node(@1.first_line, int_node, "int", NULL);

						                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
						                    $$ = create_node(@1.first_line, tipolista_node, NULL, n1, n2, $3, n4, NULL); }
         | DOUBLE '(' listadupla ')'    {   Node* n1 = create_node(@1.first_line, double_node, "double", NULL);
						                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
						                    $$ = create_node(@1.first_line, tipolista_node, NULL, n1, n2, $3, n4, NULL); }
         | REAL '(' listadupla ')'      {   Node* n1 = create_node(@1.first_line, real_node, "real", NULL);
						                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
						                    $$ = create_node(@1.first_line, tipolista_node, NULL, n1, n2, $3, n4, NULL); }
         | CHAR '(' listadupla ')'      {   Node* n1 = create_node(@1.first_line, char_node, "char", NULL);
						                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
						                    $$ = create_node(@1.first_line, tipolista_node, NULL, n1, n2, $3, n4, NULL); }
         ;

        //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
listadupla: INT_LIT ':' INT_LIT                 {	Node* n1 = create_node(@1.first_line, int_lit_node, $1, NULL);
                              						Node* n2 = create_node(@1.first_line, colon_node, ":", NULL);
                              						Node* n3 = create_node(@1.first_line, int_lit_node, $3, NULL);
                              						$$ = create_node(@1.first_line, listadupla_node, NULL, n1, n2, n3, NULL); }
          | INT_LIT ':' INT_LIT ',' listadupla	{	Node* n1 = create_node(@1.first_line, int_lit_node, $1, NULL);
                              						Node* n2 = create_node(@1.first_line, colon_node, ":", NULL);
                              						Node* n3 = create_node(@1.first_line, int_lit_node, $3, NULL);
                              						Node* n4 = create_node(@1.first_line, comma_node, ",", NULL);
                              						$$ = create_node(@1.first_line, listadupla_node, NULL, n1, n2, n3, n4, $5, NULL); }
          ;

acoes: comando          {   $$ = $1; 
            				$$->type = acoes_node;}
     | comando acoes    {   $$ = create_node(@1.first_line, acoes_node, NULL, $1, $2, NULL); 
             				cat_tac(&($$->code), &($1->code));
             				cat_tac(&($$->code), &($2->code)); }
     ;

comando: lvalue '=' expr ';'    {		Node* n2 = create_node(@1.first_line, attr_node, "=", NULL);
                       					Node* n4 = create_node(@1.first_line, semicolon_node, ";", NULL);
                       					$$ = create_node(@1.first_line, comando_node, NULL, $1, n2, $3, n4, NULL);

	            						struct tac* new_tac = create_inst_tac($1->lexeme,$3->lexeme,"","");
          			        			cat_tac(&($$->code), &($3->code));
			           			        append_inst_tac(&($$->code),new_tac); }
       | lvalue SWAP lvalue ';' {       Node* n2 = create_node(@1.first_line, swap_node, "<=>", NULL);
                       					Node* n4 = create_node(@1.first_line, semicolon_node, ";", NULL);
                       					$$ = create_node(@1.first_line, comando_node, NULL, $1, n2, $3, n4, NULL); 
                   					
                       					char * temp = gera_temp(INT_TYPE);
                       					struct tac* new_tac1 = create_inst_tac(temp,$1->lexeme,"","");
                       					struct tac* new_tac2 = create_inst_tac($1->lexeme,$3->lexeme,"","");
                       					struct tac* new_tac3 = create_inst_tac($3->lexeme,temp,"","");
                       					
           			        			append_inst_tac(&($$->code),new_tac1);
          			        			append_inst_tac(&($$->code),new_tac2);
           			        			append_inst_tac(&($$->code),new_tac3); }
       | expr ';'               /*{   Node* n = create_node(@1.first_line, semicolon_node, ";", NULL);
				                    //$$ = create_node(@1.first_line, comando_node, $1, $1, n, NULL);
				                    $$ = create_node(@1.first_line, comando_node, NULL, $1, n, NULL);  
				                    $$->code = $1->code; }*/
				                {   Node* n = create_node(@1.first_line, semicolon_node, ";", NULL);
				                    $$ = create_node(@1.first_line, comando_node, $1->lexeme, $1, n, NULL);
				                    cat_tac(&($$->code), &($1->code)); }
       | enunciado              {	$$ = $1; 
                   					$$->type=comando_node;}
       | PRINTF expr ';'	    {	Node* n1 = create_node(@1.first_line, print_node, "print", NULL);
                   					Node* n3 = create_node(@1.first_line, semicolon_node, ";", NULL);
                   					$$ = create_node(@1.first_line, comando_node, NULL, n1, $2, n3, NULL);
                 					
                   					struct tac* new_tac = create_inst_tac("",$2->lexeme,"PRINT","");
       			        			cat_tac(&($$->code), &($2->code));
			       			        append_inst_tac(&($$->code),new_tac); }
       ;

lvalue: IDF                     {   char *temp = consulta_tabela($1);
				                    if(temp) {
						                Node* n = create_node(@1.first_line, idf_node, $1, NULL);
						                $$ = create_node(@1.first_line, lvalue_node, temp, n, NULL);
				                    }
				                    else {
						                printf("UNDEFINED SYMBOL. A variavel %s nao foi declarada.\n", $1);
							            return( UNDEFINED_SYMBOL_ERROR );
							            //exit(0);
							            //VER ISSO NA ENTREVISTA (PROGRAMA SEGUE EXECUTANDO -> FOI CORRIGIDO NA MAIN ABORTANDO O PROGRAMA CASO O ANALISADOR SINTÁTICO RETORNE ERROR)
				                    } }
        //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
      | IDF '[' listaexpr ']'	{   Node* n1 = create_node(@1.first_line, idf_node, $1, NULL);
					                Node* n2 = create_node(@1.first_line, l_colchetes_node, "[", NULL);
					                Node* n4 = create_node(@1.first_line, r_colchetes_node, "]", NULL);
					                $$ = create_node(@1.first_line, lvalue_node, NULL, n1, n2, $3, n4, NULL); }
      ;

listaexpr: expr                 { 	$$ = $1; }
         | expr ',' listaexpr	{	Node* n = create_node(@1.first_line, comma_node, ",", NULL);
		       		            	$$ = create_node(@1.first_line, listaexpr_node, NULL, $1, n, $3, NULL); }
         ;

expr: expr '+' expr {	Node* n = create_node(@1.first_line, add_node, "+", NULL);
       			        //TODO: INSERIR AQUI UM IF PARA CONSIDERAR O CASO DE FLOAT_TYPE (PRÓX. ETAPA)
       			        $$ = create_node(@1.first_line, expr_node, gera_temp(INT_TYPE), $1, n, $3, NULL);
				
       			        struct tac* new_tac = create_inst_tac($$->lexeme,$1->lexeme,"ADD",$3->lexeme);
       			        cat_tac(&($$->code), &($1->code));
       			        cat_tac(&($$->code), &($3->code));
       			        append_inst_tac(&($$->code),new_tac); }
    | expr '-' expr {	Node* n = create_node(@1.first_line, sub_node, "-", NULL);
       			        //TODO: INSERIR AQUI UM IF PARA CONSIDERAR O CASO DE FLOAT_TYPE (PRÓX. ETAPA)
      			        $$ = create_node(@1.first_line, expr_node, gera_temp(INT_TYPE), $1, n, $3, NULL); 

       			        struct tac* new_tac = create_inst_tac($$->lexeme,$1->lexeme,"SUB",$3->lexeme);
      			        cat_tac(&($$->code), &($1->code));
      			        cat_tac(&($$->code), &($3->code));
       			        append_inst_tac(&($$->code),new_tac); }
    | expr '*' expr {	Node* n = create_node(@1.first_line, mul_node, "*", NULL);
       			        //TODO: INSERIR AQUI UM IF PARA CONSIDERAR O CASO DE FLOAT_TYPE (PRÓX. ETAPA)
       			        $$ = create_node(@1.first_line, expr_node, gera_temp(INT_TYPE), $1, n, $3, NULL); 
				
				        struct tac* new_tac = create_inst_tac($$->lexeme,$1->lexeme,"MUL",$3->lexeme);
       			        cat_tac(&($$->code), &($1->code));
       			        cat_tac(&($$->code), &($3->code));
       			        append_inst_tac(&($$->code),new_tac); }
    | expr '/' expr {	Node* n = create_node(@1.first_line, div_node, "/", NULL);
       			        //TODO: INSERIR AQUI UM IF PARA CONSIDERAR O CASO DE FLOAT_TYPE (PRÓX. ETAPA)
       			        $$ = create_node(@1.first_line, expr_node, gera_temp(INT_TYPE), $1, n, $3, NULL); 
   			        
       			        struct tac* new_tac = create_inst_tac($$->lexeme,$1->lexeme,"DIV",$3->lexeme);
       			        cat_tac(&($$->code), &($1->code));
       			        cat_tac(&($$->code), &($3->code));
       			        append_inst_tac(&($$->code),new_tac); }
    | '(' expr ')'  {   Node* n1 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
               			Node* n3 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
               			$$ = create_node(@1.first_line, expr_node, $2->lexeme, n1, $2, n3, NULL); 
               			cat_tac(&($$->code), &($2->code)); }
    | INT_LIT       {   Node* n = create_node(@1.first_line, int_lit_node, $1, NULL); 
    			        $$ = create_node(@1.first_line, expr_node, $1, n, NULL); }    
    | F_LIT         {   Node* n = create_node(@1.first_line, float_node, $1, NULL); 
    			        $$ = create_node(@1.first_line, expr_node, $1, n, NULL); }    			        
    | lvalue        {   $$ = $1; 
    			        $$->type = expr_node;}
    //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
    | chamaproc     {   $$ = $1; 
    			        /*$$->type = expr_node;*/}
    ;
        
        //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
chamaproc: IDF '(' listaexpr ')'    {	Node* n1 = create_node(@1.first_line, idf_node, $1, NULL);
					                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
                       					Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
					                    $$ = create_node(@1.first_line, chamaproc_node, NULL, n1, n2, $3, n4, NULL); }
         ;

        //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
enunciado: IF '(' expbool ')' THEN acoes fiminstcontrole	{   Node* n1 = create_node(@1.first_line, if_node, "if", NULL);
									                            Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
                               									Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
                               									Node* n5 = create_node(@1.first_line, then_node, "then", NULL);
				                               					$$ = create_node(@1.first_line, enunciado_node, NULL, n1, n2, $3, n4, n5, $6, $7, NULL); }
         | WHILE '(' expbool ')' '{' acoes '}'              {	Node* n1 = create_node(@1.first_line, while_node, "while", NULL);
									                            Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
                               									Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
                               									Node* n5 = create_node(@1.first_line, l_chaves_node, "{", NULL);
                               									Node* n7 = create_node(@1.first_line, r_chaves_node, "}", NULL);
                                 								$$ = create_node(@1.first_line, enunciado_node, NULL, n1, n2, $3, n4, n5, $6, n7, NULL); }
         ;

            //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
fiminstcontrole: END            {   Node* n = create_node(@1.first_line, end_node, "end", NULL);
					                $$ = create_node(@1.first_line, fiminstcontrole_node, NULL, n, NULL); }
               | ELSE acoes END {   Node* n1 = create_node(@1.first_line, else_node, "else", NULL);
                       				Node* n3 = create_node(@1.first_line, end_node, "end", NULL);
                       				$$ = create_node(@1.first_line, fiminstcontrole_node, NULL, n1, $2, n3, NULL); }
               ;

        //TODO: REGRAS SEMANTICAS NAO CRIADAS NESSA ETAPA
expbool: TRUE                   {  	Node* n = create_node(@1.first_line, true_node, "true", NULL);
					                $$ = create_node(@1.first_line, expbool_node, NULL, n, NULL); }
       | FALSE                  {  	Node* n = create_node(@1.first_line, false_node, "false", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, n, NULL); }
       | '(' expbool ')'        {   Node* n1 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
                   					Node* n3 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
                   					$$ = create_node(@1.first_line, expbool_node, NULL, n1, $2, n3, NULL); }
       | expbool AND expbool    {   Node* n = create_node(@1.first_line, and_node, "and", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, $1, n, $3, NULL); }
       | expbool OR expbool     {   Node* n = create_node(@1.first_line, or_node, "or", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, $1, n, $3, NULL); }
       | NOT expbool            {   Node* n = create_node(@1.first_line, not_node, $1, NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, n, $2, NULL); }
       | expr '>' expr          {   Node* n = create_node(@1.first_line, gt_node, ">", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, $1, n, $3, NULL); }
       | expr '<' expr          {   Node* n = create_node(@1.first_line, lt_node, "<", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, $1, n, $3, NULL); }
       | expr LE expr           {   Node* n = create_node(@1.first_line, le_node, "<=", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, $1, n, $3, NULL); }
       | expr GE expr           {   Node* n = create_node(@1.first_line, ge_node, ">=", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, $1, n, $3, NULL); }
       | expr EQ expr           {   Node* n = create_node(@1.first_line, eq_node, "==", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, $1, n, $3, NULL); }
       | expr NE expr           {   Node* n = create_node(@1.first_line, ne_node, "<>", NULL);
       					            $$ = create_node(@1.first_line, expbool_node, NULL, $1, n, $3, NULL); }
       ;
%%
