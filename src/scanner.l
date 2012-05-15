    /* Secao das declaracoes */
    
%option yylineno 

%{
    #define YY_USER_ACTION yylloc.first_line = yylineno;
    #define YY_USER_INIT yylineno = 1;
%}


%option noyywrap
    /* Sera copiado no .c final */
%{
    /**
     * \file scanner.l
     * \brief Definicao das RegExp necessarias para o analisador lexico do nico
     * \author Cesar Garcia Daudt
     * \author Ederson de Vargas Vieira
     * \author Jose Luis Damaren Junior
     * \date 2012
     * 
     * 
     */
    #include <stdlib.h>
    #include <string.h>
    /** tokens do nico */
    #include "tokens.h"
    
    /** global que armazena um token do tipo int*/
    int     VAL_INT;
    /** global que armazena um token do tipo float*/
    double  VAL_DOUBLE;
  
%}

    /** Definicoes regulares */

digito      [0-9]
maiuscula   [A-Z]
minuscula   [a-z]
enter       (\n)
branco      ([ \t])+
sinal       "+"|"-"
expoente    (("e"|"E"){sinal}?{digito}+)
str_lit      \"({minuscula}|{maiuscula}|{digito}|{branco})+\"
idf         ({minuscula}|(_))+({maiuscula}|{minuscula}|_|{digito})*
const       ({maiuscula})+(_|{maiuscula}|{digito})*
int_lit     {digito}+
f_lit       {digito}*"."{digito}+{expoente}?

%%

    /** Secao das Regras de traducao */
int         { return(INT); }
double      { return(DOUBLE); }
real        { return(REAL); }
char        { return(CHAR); }
string      { return(STRING); }
"*"         { return('*'); }
"+"         { return('+'); }
"-"         { return('-'); }
"/"         { return('/'); }
","         { return(','); }
";"         { return(';'); }
":"         { return(':'); }
"'"         { return(QUOTE); }
"("         { return('('); }
")"         { return(')'); }
"["         { return('['); }
"]"         { return(']'); }
"{"         { return('{'); }
"}"         { return('}'); }
"<=>"       { return(SWAP); }
"<"         { return('<'); }
">"         { return('>'); }
"="         { return('='); }
"<="        { return(LE); }
">="        { return(GE); }
"=="        { return(EQ); }
"<>"        { return(NE); }
and         { return(AND); }
or          { return(OR); }
not         { return(NOT); }
if          { return(IF); }
then        { return(THEN); }
else        { return(ELSE); }
for         { return(FOR); }
next        { return(NEXT); }
while       { return(WHILE); }
end         { return(END); }
true        { return(TRUE); }
false       { return(FALSE); }
print	    { return(PRINTF); }
{branco}    { /*printf("SPACE\n");*/ }
{enter}     { yylineno++; }
{idf}       { /*printf("%s\n", yytext); */
              yylval.cadeia = (char*) malloc((strlen(yytext)+1)*sizeof(char));
              strcpy(yylval.cadeia, yytext);          
              return(IDF); }
              
{const}     { /*printf("%s\n", yytext);*/ 
              yylval.cadeia = (char*) malloc((strlen(yytext)+1)*sizeof(char));
              strcpy(yylval.cadeia, yytext);
              return(CONST); }
              
{str_lit}   { //printf("%s\n", yytext); 
              yylval.cadeia = (char*) malloc((strlen(yytext)+1)*sizeof(char));
              strcpy(yylval.cadeia, yytext);  
              return(STR_LIT); }
              
{int_lit}   {   //uncomment for debug
                //printf("%s\n", yytext);
              yylval.cadeia = (char*) malloc((strlen(yytext)+1)*sizeof(char));
              strcpy(yylval.cadeia, yytext);
              VAL_INT = atoi(yytext);
              return(INT_LIT); }
              
{f_lit}     {   //uncomment for debug
                //printf("%s\n", yytext);
              yylval.cadeia = (char*) malloc((strlen(yytext)+1)*sizeof(char));
              strcpy(yylval.cadeia, yytext);             
              VAL_DOUBLE = atof(yytext);
              return(F_LIT); }

    /** Tratamento dos erros lexicos: a regra seguinte pega tudo o que nao
    * fechou com uma Regexp anterior.
    */
.           { 
              printf("Erro lexico - caractere nao reconhecido: %c.\n", yytext[0]);
              exit(-1); }
%%

    /** Secao dos  Procedimentos auxiliares  */

    /** Para redefinir a entrada padrao do LEX. 
    * Redefinir a variavel 'yyin' para ler de um arquivo. Por exemplo:
     yyin = fopen("Meu_programa.c", "r");
    * ira mandar ler o programa a ser compilado pelo analisador lexical
    * em 'Meu_programa.c'.
    * O default eh ler da entrada standard (o teclado).
    */

extern FILE *yyin;

    /** main
    * \brief funcao principal do analisador lexico
    * \author Cesar Garcia Daudt
    * \author Ederson de Vargas Vieira
    * \author Jose Luis Damaren Junior
    * \date 2012
    * \param[in] argc Numero de argumentos passados (nao fornecido pelo usuario)
    * \param[in] argv Argumentos passados ao programa (uso: nico <input_file>) 
    */
int old_main(int argc, char* argv[]) {
    int token;
    
    if (argc != 2) {
        printf("uso: %s <input_file>. Try again!\n", argv[0]);
        exit(-1);
    }

    yyin = fopen(argv[1], "r");

    if (!yyin) {
        printf("Uso: %s <input_file>. Could not find %s. Try again!\n", argv[0], argv[1]);
        exit(-1);
    }
    
    /** agora a entrada padrao e o arquivo especificado como 1o argumento ao
    * executavel (argv[1]).
    * Chama o analisador lexico default fornecido pelo output do Flex:
    */
    
    while ((token=yylex())) { 
    /** neste laco, obtem-se "palavra por palavra" os tokens reconhecidos
    * pelo scanner fornecido pelo Lex. Poderia ser feita a analise
    * sintatica... Sera feito depois!
    */
        printf("Meu analisador lexico reconheceu o token %d\n", token);
    }

    return(0);
}
