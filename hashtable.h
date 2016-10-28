struct ht_item {
	const char *k;
	struct json *v;
	struct ht_item *next;
};


struct hashtable {
	int i;
	int cap;
	struct ht_item **table;
};

struct hashtable *ht_make();
void ht_insert(struct hashtable *ht, const char *k, struct json *v);
struct json *ht_read(struct hashtable *ht, const char *k);
