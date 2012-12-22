/* Token helper routines */

#include "tokens.h"
#include <string.h>
#include <stdio.h>

/* Print out a token's raw string */
void tok_display(FILE *f, token_t t)
{
	char buf[1024];
	strncpy(buf, t.start, t.len);
	buf[t.len] = 0;
	fprintf(f, "%s", buf);
}

int is_add_op(char type)
{
	return type == TOK_PLUS || type == TOK_MINUS;
}

int is_asg_op(char type)
{
	return type == TOK_PLUSEQ
 		|| type == TOK_MINUSEQ
		|| type == TOK_DIVEQ
		|| type == TOK_MULEQ
		|| type == TOK_ASGN;
}

int is_mul_op(char type)
{
	return type == TOK_MUL || type == TOK_DIV;
}

int is_comp_op(char type)
{
	return type == TOK_GT 
		|| type == TOK_LT
		|| type == TOK_GTE
		|| type == TOK_LTE
		|| type == TOK_NEQ
		|| type == TOK_EQ;
}

int is_instr(char type)
{
	return type == TOK_ECHO 
		|| type == TOK_DRAW
		|| type == TOK_WAIT
	 	|| type == TOK_CMX
		|| type == TOK_CMY
		|| type == TOK_MX
		|| type == TOK_MY
		|| type == TOK_OD;
}

