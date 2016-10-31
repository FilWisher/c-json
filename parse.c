#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <assert.h>

#include "lex.h"
#include "parse.h"
#include "hashtable.h"

struct parser *parser_make(char *str);
struct json *parse_token(struct parser *p);
struct json *parse_array(struct parser *p);
struct json *parse_object(struct parser *p);

char *strndup(char *src, size_t len) {
	char *dst = (char *)malloc((sizeof(char)*len)+1);
	char *sp = src, *dp = dst;
	unsigned int i;
	for (i = 0; i < len; i++)
		*(dp++) = *(sp++);
	*dp = '\0';
	return dst;
}

struct parser *parser_make(char *str) {
	struct lexer *l = lex_make();
	if (lex(l, str) != 0) {
		lex_delete(l);
		return NULL;
	}
	struct parser *p = (struct parser *)malloc(sizeof(struct parser));
	p->pos = l->tks;
	p->root = NULL;
	return p;
}

struct json *parse(char *str) {
	struct parser *p = parser_make(str);
	p->root = parse_token(p);
	return p->root;
}

struct json *json_make() {
	return (struct json *)malloc(sizeof(struct json));
}

struct json *number_make(int i) {
	struct json *j = json_make();
	j->typ = P_NUMBER;
	j->num = i;
	return j;
}

struct json *string_make(char *str, int len) {
	struct json *j = json_make();
	j->typ = P_STRING;
	j->val.str = strndup(str, len);
	return j;
}

struct json *boolean_make(int i) {
	struct json *j = json_make();
	j->typ = P_BOOLEAN;
	j->num = i;
	return j;
}

struct json *hashtable_make() {
	// TODO: make hashtable
	struct json *j = json_make();
	j->typ = P_OBJECT;
	j->val.obj = ht_make();
	return j;
}

int expect(struct parser *p, tt typ) {
	struct token *cur = *p->pos;
	if (cur->typ == typ) {
		p->pos++;
		return 0;
	}
	return -1;
}

struct json *parse_token(struct parser *p) {
	struct token *tk = *p->pos;
	struct json *j;
	char *tmp;
	int i;
	switch (tk->typ) {
	case TT_STR:
		j = string_make(tk->st, tk->len);
		p->pos++;
		break;
	case TT_NUM:
		// NOTE: temporary hack while number parsing not implemented
		tmp = strndup(tk->st, tk->len);
		i = atoi(tmp);
		j = number_make(i);
		free(tmp);
		p->pos++;
		break;
	case TT_AOPEN:
		j = parse_array(p);
		break;
	case TT_OOPEN:
		j = parse_object(p);
		break;	
	case TT_TRUE: 
	case TT_FALSE:
		j = boolean_make(tk->typ == TT_TRUE);
		p->pos++;
		break;
	default:
		j = NULL;
	}
	return j;
}

struct json *parse_object(struct parser *p) {
	
	struct json *ht = hashtable_make();
	struct token *cur;
	for (cur = *p->pos; cur->typ != TT_ACLOSE && cur->typ != TT_END; cur = *p->pos) {
		char *k = strndup(cur->st, cur->len);
		if(expect(p, TT_COLON) != 0)
			return NULL;
		struct json *v = parse_token(p);
		if (!v)
			return NULL;
		ht_insert(ht->val.obj, k, v);
		p->pos++;
	}
	return ht;
}

struct json *array_make() {
	struct json *j = json_make();
	j->typ = P_ARRAY;
	j->val.arr = NULL;
	j->num = 0;
	return j;
}

struct ls_item *item_make(struct json *j) {
	struct ls_item *it = (struct ls_item *)malloc(sizeof(struct ls_item));
	it->v = j;
	it->next = NULL;
	return it;
}

// TODO: construct correct string and return (don't print in func)
void print_json(struct json *j) {
	struct ls_item *cur;
	switch (j->typ) {
	case P_STRING:
		printf("%s", j->val.str);
		break;
	case P_NUMBER:
		printf("%d", j->num);
		break;
	case P_BOOLEAN:
		//printf("%s", j->num == 0 ? "true" : "false");
		printf("%s", j->num == 0 ? "true" : "false");
		break;
	case P_ARRAY:
		printf("[ ");
		cur = j->val.arr;
		for (int i = 0; cur != NULL && i < j->num; cur = cur->next, i++) {
			print_json(cur->v);
			if (i < j->num-1)
				printf(", ");
		}
		printf(" ]");
		break;
	default:
		printf("wat");
	}
}

struct json *parse_array(struct parser *p) {
	struct json *v, *j = array_make();
	struct ls_item **end = &j->val.arr;
	struct token *cur;
	if (expect(p, TT_AOPEN) != 0)
		return NULL;
	for (cur = *p->pos; cur->typ != TT_ACLOSE && cur->typ != TT_END; cur = *p->pos) {
		
		if ((v = parse_token(p)) == NULL)
			return NULL;

		// fill end and point it at next position to be filled
		*end = item_make(v);
		end = &((*end)->next);
		
		j->num++;
		
		if (expect(p, TT_ACLOSE) != 0 && expect(p, TT_COMMA) != 0)
			return NULL;
	}
	return j;
}
