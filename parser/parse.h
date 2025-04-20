#include "../lexer/lexer.h"



 typedef struct word
 {
	char * s;
	int token_type;
 }  word;


 typedef struct node
 {
	struct node* left;
	struct node* right;
	int token_type;
	char *s;
 }  tree;
 

 