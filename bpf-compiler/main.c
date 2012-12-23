/* 
 * New compiler targeting my old "BPF" VM
 * (could target something cooler one day)
 * by Bl0ckeduser, December 2012
 * Enjoy !
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "tokens.h"
#include "tree.h"
#include "parser.h"
#include "codegen.h"

int main(int argc, char** argv)
{
	char* buf;
	token_t* tokens;
	exp_tree_t tree;
	extern void optimize(exp_tree_t *et);
	extern void run_codegen(exp_tree_t* tree);
	extern void push_line(char *lin);
	extern void print_code(void);
	extern void fail(char*);

	/* Read in at most 1KB of code from stdin */
	if (!(buf = malloc(1024 * 1024)))
		fail("alloc program buffer");
	fread(buf, sizeof(char), 1024 * 1024, stdin);

	setup_tokenizer();
	tokens = tokenize(buf);

#ifdef DEBUG
	/* display the tokens */
	for (int i = 0; tokens[i].start; i++) {
		fprintf(stderr, "%d: %s: ", i, tok_nam[tokens[i].type]);
		tok_display(stderr, tokens[i]);
		fputc('\n', stderr);
	}
#endif

	tree = parse(tokens);
	optimize(&tree);
	
#ifdef DEBUG
	printout_tree(tree);
	fputc('\n', stderr);
#endif

	run_codegen(&tree);

	/* Write out the final compiled assembly */
	print_code();

	free(buf);
	return 0;
}


