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
    
    extern symbol_t symbol_table;
    int tipo_idf = 0;   //indicates the type of the current idf being analyzed (helps when we have multiple idfs)
    int elems_idf = 1;  //indicates how many elems are being declared in the current idf (helps when we have n-dimensional arrays)
    void* extra_info;
    int extra_info_pos = 1; //starts at second position because the first position stores the number of array dimensions
    int vars_size = 0;  //size of all nico program vars
    int temps_size = 0; //size of all nico program temps
    
    //returns a temp var
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
    
    //checks wether the var "lexeme" is in the symbols table. If not, add it.
    void theBookIsOnTheTable(char *lexeme) {
        if(lookup(symbol_table, lexeme)){//testa se já existe uma entrada com esse nome na tabela
			printf("Símbolo %s foi definido múltiplas vezes. \n", lexeme);
			exit(0);

	}
	    else {
		    entry_t* new_entry=(entry_t *) malloc(sizeof(entry_t));
		    new_entry->name = lexeme;
		    new_entry->type = tipo_idf;
		    new_entry->desloc = vars_size;

            //this code is just used in multi-dimensional arrays		    
		    if(extra_info != NULL) {
		        if(new_entry->extra = malloc(sizeof(int)*(extra_info_pos+1))) {
		            int i;
		            //Copy all extra_info content to new_entry->extra
		            for(i=0; i <= *((int*)new_entry->extra)+1; i++) {
		                *(((int*)new_entry->extra)+i) = *(((int*)extra_info)+i);
		            }
		            //clear extra_info, extra_info_pos vars
                    	free(extra_info);
                    	extra_info = NULL;
                    	extra_info_pos = 1;
		        }
		        
		        else
		            exit(0);
		    }

		    switch(tipo_idf){
            	case INT_TYPE:		
            	    new_entry->size = INT_SIZE * elems_idf;
		            vars_size += INT_SIZE * elems_idf;
		            break;
            	case DOUBLE_TYPE:	
            	    new_entry->size = DOUBLE_SIZE * elems_idf;
			        vars_size += DOUBLE_SIZE * elems_idf;
			        break;
            	case REAL_TYPE:		
            	    new_entry->size = REAL_SIZE * elems_idf;
			        vars_size += REAL_SIZE * elems_idf;
			        break;
            	case CHAR_TYPE:		
            	    new_entry->size = CHAR_SIZE * elems_idf;
			        vars_size += CHAR_SIZE * elems_idf;
		    }
		    //clear elems_idf var
		    elems_idf = 1;
		    if(insert(&symbol_table, new_entry)) {
			    printf("Ocorreu um erro ao alocar o simbolo %s na tabela de simbolos.\n",lexeme);
			    exit(0);
		    }
	    }
    }
    
    /*
    returns where "identificador" is allocated
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
    
    //returns "array" c constant to calc one element position
    int foo_c(char* array) {
        entry_t* entrada;
        entrada = lookup(symbol_table, array);
        if(entrada!=NULL) {
            //first position of extra field contains the number of dimensions
            int k = *((int*) (entrada->extra)); 
            //in extra field, the (k-d+1)ith position contais the number of elements in the dth dimension
            //the last position has the c value
            return *(((int *)entrada->extra)+k+1);
        }
        else
            exit(0);
    }
    
    //returns "array" sizeof(one element)
    //now we just have INT_TYPE arrays
    int foo_largura(char* array) {
        return INT_SIZE;
        //TODO: implement with lookup
    }
    
    //returns "array" number of elements in "dim" dimension
    int foo_limite(char* array, int dim) {
        entry_t* entrada;
        entrada = lookup(symbol_table, array);
        if(entrada!=NULL) {
            //first position of extra field contains the number of dimensions
            int k = *((int*) (entrada->extra)); 
            //in extra field, the (k-d+1)ith position contais the number of elements in the dth dimension
            return *(((int *)(entrada->extra))+k-dim+1);
        }
        else
            exit(0);
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
    | tipolista {   $$ = $1; 
                    if(!strcmp($$->lexeme,"int"))
			            tipo_idf = INT_TYPE;
		            if(!strcmp($$->lexeme,"double"))
			            tipo_idf = DOUBLE_TYPE;
		            if(!strcmp($$->lexeme,"real"))
			            tipo_idf = REAL_TYPE;
		            if(!strcmp($$->lexeme,"char"))
			            tipo_idf = CHAR_TYPE;
			        $$->type = tipo_node; }
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
        
tipolista: INT '(' listadupla ')'       {   Node* n1 = create_node(@1.first_line, int_node, "int", NULL);
						                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
						                    $$ = create_node(@1.first_line, tipolista_node, "int", n1, n2, $3, n4, NULL); 

						                    int base = vars_size;
						                    $$->c = base - ($3->c * INT_SIZE);
						                    extra_info = realloc(extra_info, sizeof(int)*(extra_info_pos+1));
								  *(((int*)extra_info) + extra_info_pos+1) = $$->c; }
       
       
         | DOUBLE '(' listadupla ')'    {   Node* n1 = create_node(@1.first_line, double_node, "double", NULL);
						                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
						                    $$ = create_node(@1.first_line, tipolista_node, "double", n1, n2, $3, n4, NULL); }
         | REAL '(' listadupla ')'      {   Node* n1 = create_node(@1.first_line, real_node, "real", NULL);
						                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
						                    $$ = create_node(@1.first_line, tipolista_node, "real", n1, n2, $3, n4, NULL); }
         | CHAR '(' listadupla ')'      {   Node* n1 = create_node(@1.first_line, char_node, "char", NULL);
						                    Node* n2 = create_node(@1.first_line, l_parenteses_node, "(", NULL);
						                    Node* n4 = create_node(@1.first_line, r_parenteses_node, ")", NULL);
						                    $$ = create_node(@1.first_line, tipolista_node, "char", n1, n2, $3, n4, NULL); }
         ;

listadupla: INT_LIT ':' INT_LIT                 {	//TODO: check wether up_limit >= low_limit and both > 0
                                                    Node* n1 = create_node(@1.first_line, int_lit_node, $1, NULL);
                              						Node* n2 = create_node(@1.first_line, colon_node, ":", NULL);
                              						Node* n3 = create_node(@1.first_line, int_lit_node, $3, NULL);
                              						$$ = create_node(@1.first_line, listadupla_node, NULL, n1, n2, n3, NULL); 
                              						elems_idf = elems_idf * (atoi($3) - atoi($1) + 1);
                                                    $$->linf = atoi($1);
                                                    $$->n = atoi($3) - atoi($1) + 1;
                                                    $$->c = $$->linf;
                                                    
                                                    //extra_info will be copied to array->extra (array is the var name in the symbols table)
                              						extra_info = malloc(sizeof(int)*2);
                              						*((int*)extra_info) = 1;                    //#dimensions is, at least, 1
                              						*(((int*)extra_info)+extra_info_pos) = $$->n; //#elements at last dimension
                              						extra_info_pos++; }
          | INT_LIT ':' INT_LIT ',' listadupla	{	//TODO: check wether up_limit >= low_limit and both > 0
                                                    Node* n1 = create_node(@1.first_line, int_lit_node, $1, NULL);
                              						Node* n2 = create_node(@1.first_line, colon_node, ":", NULL);
                              						Node* n3 = create_node(@1.first_line, int_lit_node, $3, NULL);
                              						Node* n4 = create_node(@1.first_line, comma_node, ",", NULL);
                              						$$ = create_node(@1.first_line, listadupla_node, NULL, n1, n2, n3, n4, $5, NULL);
                              						elems_idf = elems_idf * (atoi($3) - atoi($1) + 1); 
                                                    $$->c = ($5->n * atoi($1))+ $5->c;
                              						$$->n = (atoi($3) - atoi($1)+1) * $5->n;
                              						
                              						//inserts info in the next available position
                              						extra_info = realloc(extra_info, sizeof(int)*(extra_info_pos+1));
                              						*((int*)extra_info) += 1;                    //inc #dimensions
                              						*(((int*)extra_info)+extra_info_pos) = atoi($3) - atoi($1) + 1; //#elements at last dimension
                              						 extra_info_pos++; }
          ;

acoes: comando          {   $$ = $1; 
            				$$->type = acoes_node;}
     | comando acoes    {   $$ = create_node(@1.first_line, acoes_node, NULL, $1, $2, NULL); 
             				cat_tac(&($$->code), &($1->code));
             				cat_tac(&($$->code), &($2->code)); }
     ;

comando: lvalue '=' expr ';'    {   Node* n2 = create_node(@1.first_line, attr_node, "=", NULL);
                   					Node* n4 = create_node(@1.first_line, semicolon_node, ";", NULL);
                   					$$ = create_node(@1.first_line, comando_node, NULL, $1, n2, $3, n4, NULL);

		           			        if($1->deslocamento == NULL) {
                                        struct tac* new_tac = create_inst_tac($1->lexeme,$3->lexeme,"","");
      			        			    cat_tac(&($$->code), &($3->code));
		           			            append_inst_tac(&($$->code),new_tac); 
		           			        }
		           			        else {
		           			            char* op1 = (char*) malloc(sizeof(int)*27);
		           			            op1[0]='\0';
		           			            strcat(op1, $1->lexeme);
                                        strcat(op1, "(");
		           			            strcat(op1, $1->deslocamento);
		           			            strcat(op1, ")");
                                        struct tac* new_tac = create_inst_tac(op1,$3->lexeme,"","");
      			        			    cat_tac(&($1->code), &($3->code));
		           			            append_inst_tac(&($1->code),new_tac);
		           			            cat_tac(&($$->code), &($1->code)); 
		           			        } }
       | lvalue SWAP lvalue ';' {   Node* n2 = create_node(@1.first_line, swap_node, "<=>", NULL);
                   					Node* n4 = create_node(@1.first_line, semicolon_node, ";", NULL);
                   					$$ = create_node(@1.first_line, comando_node, NULL, $1, n2, $3, n4, NULL); 
               					
                   					char * temp = gera_temp(INT_TYPE);
                   					struct tac* new_tac1 = create_inst_tac(temp,$1->lexeme,"","");
                   					struct tac* new_tac2 = create_inst_tac($1->lexeme,$3->lexeme,"","");
                   					struct tac* new_tac3 = create_inst_tac($3->lexeme,temp,"","");
                       					
       			        			append_inst_tac(&($$->code),new_tac1);
      			        			append_inst_tac(&($$->code),new_tac2);
       			        			append_inst_tac(&($$->code),new_tac3); }
       | expr ';'               {   Node* n = create_node(@1.first_line, semicolon_node, ";", NULL);
				                    $$ = create_node(@1.first_line, comando_node, $1->lexeme, $1, n, NULL);
				                    cat_tac(&($$->code), &($1->code)); }
       | enunciado              {	$$ = $1; 
                   					$$->type=comando_node;}
       | PRINTF expr ';'	    {	Node* n1 = create_node(@1.first_line, print_node, "print", NULL);
                   					Node* n3 = create_node(@1.first_line, semicolon_node, ";", NULL);
                   					$$ = create_node(@1.first_line, comando_node, NULL, n1, $2, n3, NULL);
                 					
                   					struct tac* new_tac = create_inst_tac("",$2->lexeme,"PRINT","");
       			        			//cat_tac(&($$->code), &($2->code));
			       			        append_inst_tac(&($$->code),new_tac); }
       ;

lvalue: IDF                     {   char *temp = consulta_tabela($1);
				                    if(temp) {
						                Node* n = create_node(@1.first_line, idf_node, $1, NULL);
						                $$ = create_node(@1.first_line, lvalue_node, temp, n, NULL);
						                $$->deslocamento = NULL;
				                    }
				                    else {
						                printf("UNDEFINED SYMBOL. A variavel %s nao foi declarada.\n", $1);
							            return( UNDEFINED_SYMBOL_ERROR );
				                    } }
        | listaexpr ']'         {   Node* n2 = create_node(@1.first_line, r_colchetes_node, "]", NULL);
                                    $$ = create_node(@1.first_line, lvalue_node, NULL, $1, n2, NULL);

                                    
                                    $$->lexeme = gera_temp(INT_TYPE);
                                    $$->deslocamento = gera_temp(INT_TYPE);
                                    int c = foo_c($1->array);
                                    //sprintf(str,"%d",value) converts to decimal base.
                                    char c_str[100];
                                    sprintf(c_str, "%d", c);
                                    struct tac* new_tac1 = create_inst_tac($$->lexeme,c_str,"","");

                                    int largura = foo_largura($1->array);
                                    //sprintf(str,"%d",value) converts to decimal base.
                                    char largura_str[100];
                                    sprintf(largura_str, "%d", largura);
                                    struct tac* new_tac2 = create_inst_tac($$->deslocamento,$1->lexeme,"MUL",largura_str);
                                    cat_tac(&($$->code), &($1->code));
			       			        append_inst_tac(&($$->code),new_tac1);
			       			        append_inst_tac(&($$->code),new_tac2); }
      ;

listaexpr: IDF '[' expr {   char *temp = consulta_tabela($1);
		                    if(temp) {
		                    		Node* n1 = create_node(@1.first_line, idf_node, $1, NULL);
				                Node* n2 = create_node(@1.first_line, l_colchetes_node, "[", NULL);
                                $$ = create_node(@1.first_line, listaexpr_node, NULL, n1, n2, $3, NULL);
                                

                                $$->array = $1;
                                $$->lexeme = $3->lexeme;
                                $$->ndim = 1;
//                                cat_tac(&($$->code), &($3->code));
                                $$->code = $3->code;
		                    }
		                    else {
				                printf("UNDEFINED SYMBOL. A variavel %s nao foi declarada.\n", $1);
					            return( UNDEFINED_SYMBOL_ERROR );
		                    } 
		         }
         | listaexpr ',' expr	{	Node* n = create_node(@1.first_line, comma_node, ",", NULL);
		       		            	$$ = create_node(@1.first_line, listaexpr_node, NULL, $1, n, $3, NULL); 
		       		            	
		       		            	char* t = gera_temp(INT_TYPE);
		       		            	int m = $1->ndim + 1;
		       		            	int limite = foo_limite($1->array, m);
		       		            	//sprintf(str,"%d",value) converts to decimal base.
		       		            	char limite_str[100];
		       		            	sprintf(limite_str, "%d", limite);
		       		            	struct tac* new_tac1 = create_inst_tac(t,$1->lexeme,"MUL",limite_str);
		       		            	struct tac* new_tac2 = create_inst_tac(t,t,"ADD",$3->lexeme);
		       		            	$$->array = $1->array;
		       		            	$$->lexeme = t;
		       		            	$$->ndim = m;
		       		            	cat_tac(&($$->code),&($3->code));
		       		            	cat_tac(&($$->code),&($1->code));
		       		            	append_inst_tac(&($$->code),new_tac1);
		       		            	append_inst_tac(&($$->code),new_tac2); }
         ;

expr: expr '+' expr {	Node* n = create_node(@1.first_line, add_node, "+", NULL);
       			        $$ = create_node(@1.first_line, expr_node, gera_temp(INT_TYPE), $1, n, $3, NULL);
				
       			        struct tac* new_tac = create_inst_tac($$->lexeme,$1->lexeme,"ADD",$3->lexeme);
       			        cat_tac(&($$->code), &($1->code));
       			        cat_tac(&($$->code), &($3->code));
       			        append_inst_tac(&($$->code),new_tac); }
    | expr '-' expr {	Node* n = create_node(@1.first_line, sub_node, "-", NULL);
      			        $$ = create_node(@1.first_line, expr_node, gera_temp(INT_TYPE), $1, n, $3, NULL); 

       			        struct tac* new_tac = create_inst_tac($$->lexeme,$1->lexeme,"SUB",$3->lexeme);
      			        cat_tac(&($$->code), &($1->code));
      			        cat_tac(&($$->code), &($3->code));
       			        append_inst_tac(&($$->code),new_tac); }
    | expr '*' expr {	Node* n = create_node(@1.first_line, mul_node, "*", NULL);
       			        $$ = create_node(@1.first_line, expr_node, gera_temp(INT_TYPE), $1, n, $3, NULL); 
				
				        struct tac* new_tac = create_inst_tac($$->lexeme,$1->lexeme,"MUL",$3->lexeme);
       			        cat_tac(&($$->code), &($1->code));
       			        cat_tac(&($$->code), &($3->code));
       			        append_inst_tac(&($$->code),new_tac); }
    | expr '/' expr {	Node* n = create_node(@1.first_line, div_node, "/", NULL);
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
    
    | lvalue        {   if($1->deslocamento != NULL) {
				char* op2=(char*) malloc(sizeof(int)*27);
				op2[0]='\0';
       			        strcat(op2, $1->lexeme);
//       			        printf("l.local: %s\n", $1->lexeme);
                            	strcat(op2, "(");
       			        strcat(op2, $1->deslocamento);
//       			        printf("l.deslocamento: %s\n", $1->deslocamento);
       			        strcat(op2, ")");
//       			        printf("op2: %s\n", op2);
       			        $1->lexeme = gera_temp(INT_TYPE);
       			        struct tac* new_tac = create_inst_tac($1->lexeme,op2, "", "");
       			        free(op2);
       			        append_inst_tac(&($1->code),new_tac);
//       			        printf("apendou\n");
    			        }
    			 $$ = $1; 
    			 $$->type = expr_node; }
    			        
    
    			            			        
    			        
    			        
    			        
    			        
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
