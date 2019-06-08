#include <stdio.h>
#include <stdlib.h>
#include <String.h>
// Trabalho de Compiladores
// Analizador Sintatico
// Evandro FErnandes Barreto
// 31/05/2019 - Unesp Bauru




typedef struct no 
{
	char word[50];
	char type[50];
	struct no *next;
}*lexema;

typedef struct p 
{
    char v;
    struct p *next;    
}*stack;





//=====================================================================================================//
//======================================== ESTRUTURAS DE LISTA ========================================//
//=====================================================================================================//

//========================================= INICIA A LISTA ============================================// 
void Init_List(lexema *lex) 
{ 
	*lex = NULL;
}

//==========================================INSERE ELEMENTOS NA LISTA =================================//
int Insert_List(lexema *lex, char tok[20], char typ[50])
{ 
	lexema q = (lexema)malloc(sizeof(struct no));
	lexema p = *lex;
	if (q == NULL)
		return 0;
	strcpy(q->word,tok);
	strcpy(q->type,typ); 		
	q->next = NULL;
	if (*lex == NULL)
		*lex = q;
	else 
    {
		while (p->next)
			p = p->next;
		p->next = q;	
	}
	return 1;
}
//===================================== MOSTRA ELEMENTOS NA LISTA ======================================//

void Show_List(lexema *l)
{
	lexema p = *l;
		while (p) 
        {
			printf("palavra: ");
			printf("%s ",p->word);
			
			printf("tipo: ");
			printf("%s ",p->type);			
			p = p->next;			
		} 
}


//=====================================================================================================//
//=====================================================================================================//
//=====================================================================================================//

//=====================================================================================================//
//======================================== ESTRUTURAS DO TRABALHO======================================//
//=====================================================================================================//


//======================================== FUNÇÃO PARA ERROS  =========================================//
// função para mensagem de erros
int ShowMessageError (int i)
{
 // mostrará o tipo de erro de acordo com a entrada  i                
 if (i == 1)
     printf ("SUCESSO");
 if (i == 2)
     printf ("ERRO SINTATICO");
                 
  return 0;
}
//=====================================================================================================//








//=========================== Função 2. Analizador de BLocos  =========================================//
//Função 2: Analisa todo o resto do bloco da função
// <Bloco> := 1. <rotulos>
//            2. <Variaveis>
//            3. <Sub-Rotinas>
//            4. <Comandos COmpostos> 
int Ana_Bloc(lexema *lex){ 
	*lex = (*lex)->next; // aponta para o prox
	if (!(strcmp((*lex)->type,"PALAVRA RESERVADA USES"))) 
    {
       *lex = (*lex)->next;
       if (!(strcmp((*lex)->type,"IDENTIFICADOR"))) 
       { // compara se é um indentificador
          
          *lex = (*lex)->next;
          if (strcmp((*lex)->type,"PONTO_VIRGULA")) // ponto e virgula
             ShowMessageError(2); // erro sintatico
          *lex = (*lex)->next;
       } 
         else 
             ShowMessageError(2); // erro sintatico
    }    
    do{
	    //Indentificar <Var>
	    // Indentificar o tipo de Variavavel
	    //i indentificar sub-rotinas
	    // indentificar comandos compostos
	
	}while((strcmp((*lex)->type,"PALAVRA RESERVADA BEGIN"))); // VAI ATÉ O FIM DA LISTA
	
	(*lex) = (*lex)->next;
	return 1;
}
//=====================================================================================================//


//=========================== Função 1. Analizador Simbolo Program ====================================//
// FUNÇÃO 1
// INDENTIFICA O PROGRAM <INDENTIFICADOR> <;> <BLOCO DE CODIGO>
int Ana(lexema *lex)
{
	lexema tok = *lex;
	
    if (!(strcmp(tok->type,"PALAVRA PROGRAM"))) // indentifica <Program>
    { 
        tok = tok->next;
        if (!(strcmp(tok->type,"IDENTIFICADOR")))// indentifica o <indentificador>
        { 
            tok = tok->next;// vai para prox palavra
            if (!(strcmp(tok->type,"SMCLN"))) // indentifica o <;>
            { 
                                              
                Ana_Bloc(&tok); // analisa o resto do bloco <bloco>
                if (!(strcmp(tok->type,"PONTO")))
                    if (tok->next == NULL)// chegou ao fim  da lista ?
                        // sim sucesso da primeira parte
                         ShowMessageError(1); // deu certo
                    else
                       ShowMessageError(2); // erro sintatico 
             else
                 ShowMessageError(2);
            }
            else
                ShowMessageError(2);
        }
        else
            ShowMessageError(2);     
    }
    else
        ShowMessageError(2);
}
//================================ Função 3. Indertificador de Vars ===================================//

//Função 3.
// Indentificador de declaração de Variavels

// declaração de variaveis
int Decla_Var(lexema *lex)
{
  // indentificar a palavra Var          
  /* <parte de declaração de variavel> := < var> <declaração de variavel>
                                                 {;<declaração de variavel>};*/   
                                                      
  if (!(strcmp((*lex)->type,"PALAVRA RESERVADA VAR"))) // procura a palavrar <VAR>
  {     
	
  	 
  // quando achar, vai para a proxima palavra       
  (*lex) = (*lex)->next;    
  
   while (!(strcmp((*lex)->type,"DEC_VAR")))// fica no while até encontrar um :
   // ou seja < variavel> : <tipo>  ;
   {
       if (!(strcmp((*lex)->type,"IDENTIFICADOR")))//verifica o nome da variavel
       {
          (*lex) = (*lex)->next;     
          // analisa se existe mais indentificadores    
          if(!(strcmp((*lex)->type,"VIRGULA"))) // verifica se existe mais variavels
          {
            //existe mais variaveis
            // temos   <variavel> <,>                                  
            (*lex) = (*lex)->next;    
                                          
          }
          // se não é uma v irgula , tem que ser um final (:)
          else 
               if((strcmp((*lex)->type,"DEC_VAR")))
		          ShowMessageError (2); // mostra erro se n for um fina                                                
       }       
        else        
            ShowMessageError(2);  // se não for um <indentificador> aponta erro
            
   }
}
   // quando achar um : 
   (*lex) = (*lex)->next;
   //analisa o tipo da VAR
  //Analisa o tipo de variavel
  
  if (!(strcmp((*lex)->type,"PALAVRA RESERVADA INTEGER")))// inteira
  {
     (*lex) = (*lex)->next;                                  
  }       
  else
     if (!(strcmp((*lex)->type,"PALAVRA RESERVADA BOOLEAN"))) // Boolean
     {
        (*lex) = (*lex)->next;                                  
     }
  else      
      ShowMessageError(2); // se o tipo de variavel não for INT ou BOOLEAN MOSTRA ERRO
      
  return 1;   
}
//=====================================================================================================//
//===================================== Analisador de Procedures ======================================//
// Função 7. Procredure
/* <declaração de procedimento> ::=  <procedure> <indentificador> 
                                     {<parametros formais>} ; <bloco>*/

int Ana_Procedure (lexema *lex)
{
   if (!(strcmp((*lex)->type,"PALAVRA RESERVADA PROCEDURE"))) // verifica se existe a palavra proc 
   {
		(*lex) = (*lex)->next; // passa pra prox
		//<indentificador>
		if(!(strcmp((*lex)->type,"IDENTIFICADOR")))
        {
			(*lex) = (*lex)->next; // se a syntaxe estiver certa passa pra prox
			if (!(strcmp((*lex)->type,"PALAVRA RESERVADA VAR"))) // verifica se é uma var
			{
                (*lex) = (*lex)->next;         
            }
            else
                ShowMessageError(2); // se n for uma var, indica ERRO
                
			// analisa agora se as variaveis foram declaradas certas
			Decla_Var(lex);
			
			// verifica se existe begin 
			if (!(strcmp ((*lex)->type ,"PALAVRA RESERVADA BEGIN")))
			   (*lex) = (*lex)->next;
			else   
               ShowMessageError(2);// mostra erro se não tiver begin
		}   
     // analisa o bloco 
   }
   
   
   return 1;
}

//=====================================================================================================//




//================================= Função 8. Analisa Funções =========================================//
//função 8. declaração de função
/* <declaração de função> ::= <function>  <indentificador>
                              {<parametros formais>}: <indentificador>;
                              <bloco>*/

int Ana_Func (lexema *lex)
{        // acha a palavra function
         if (!(strcmp((*lex)->type,"PALAVRA RESERVADA FUNCTION")))
         {
		    (*lex) = (*lex)->next; // segue pro prox 
		    // verifica se há <indentificador> 
            if(!(strcmp((*lex)->type,"IDENTIFICADOR")))
            {
                (*lex) = (*lex)->next;
			    // {parametros formais}
			     (*lex) = (*lex)->next;
		        // verifica se há <indentificador> 
			    if(!(strcmp((*lex)->type,"IDENTIFICADOR")))
			      (*lex) = (*lex)->next;
                else
                    ShowMessageError(2); //se não há indentificador mostra um erro 
               
               //Analisa o bloco, função para analisar a validade do bloco                                           
			    
			 }			
				else
		
                 ShowMessageError(2);
         }				  
		
        return 1;	
}
//=====================================================================================================//
//============================= Função 9. Analisa Parametros Formais ==================================//
//Função 9. Analisa Parametros Formais
/*    (<seção de Parametros formais>) {(seção de parametros formais)})*/
int Ana_Para_Form(lexema *lex)
{
    while (!(strcmp((*lex)->type,"PALAVRA RESERVADA END")))// vai até i final da seção
    {
                                        
      /* precisa ser implementada a função 10. */                                 
     }
	(*lex) = (*lex)->next;
}

/*Função 10. Seção de Parametros FOrmais
[var] <lista de indentificadores>: <indentificador> */
int Secao_Para_Form(lexema *lex) 
{
     // verifica para var no inicio
     if (!(strcmp((*lex)->type,"PALAVRA RESERVADA VAR")))
     {
             // lista de indentificadores             
             (*lex) = (*lex)->next;
             //verifica se o prox é um ':'
             if (!(strcmp((*lex)->type,"DEC_VAR")))
             {
                 (*lex) = (*lex)->next;                                                                                    
                 if (!(strcmp((*lex)->type,"INDENTIFICADOR")))
                 {
                     (*lex) = (*lex)->next;
                 } 
                 // caso nenhum dos IFS for validos uma messagem de erro sera mostrada 
                  else
                      ShowMessageError(2);                                   
              }
              else
                   ShowMessageError(2);                                     
       }
        else 
             ShowMessageError(2);
 
  return 1;                      
}
//=====================================================================================================//
/*Função 11. Comando Composto
<Begin> <comando> {;<comando>} end*/

int Cmd_Comp (lexema *lex)
{
         
}









int main ()
{
    
 system ("Pause");   
}
