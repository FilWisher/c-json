#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "hashtable.h"

int hash(const char *k) {
	// TODO: implement fnv hashing
	return (int)*k;
}

struct ht_item *it_make(const char *k, struct json *v, struct ht_item *next) {
	struct ht_item *it = (struct ht_item *)malloc(sizeof(struct ht_item));
	it->k = k;
	it->v = v;
	it->next = next;
	return it;
}

struct hashtable *ht_make() {
	struct hashtable *ht = (struct hashtable *)malloc(sizeof(struct hashtable));
	ht->i = 0;
	ht->cap = 8;
	ht->table = (struct ht_item **)malloc(sizeof(struct ht_item *) * ht->cap);
	return ht;
}

void ht_insert(struct hashtable *ht, const char *k, struct json *v) {
	// TODO: check size constraints
	int i = hash(k) % ht->cap;
	*(ht->table	+ i) = it_make(k, v, *(ht->table + i));
}

struct json *ht_read(struct hashtable *ht, const char *k) {
	int i = hash(k) % ht->cap;
	struct ht_item *cur = *(ht->table+i);
	while (cur && strcmp(cur->k, k) != 0)
		cur = cur->next;
	if (!cur)
		return NULL;
	return cur->v;
}
