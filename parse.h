struct hashtable;
struct json;

struct parser {
	struct token **tks;
	struct token **pos;
	struct json *root;
};

typedef enum {
	P_STRING,
	P_NUMBER,
	P_OBJECT,
	P_ARRAY,
	P_BOOLEAN,
	P_NULL
} value_t;


struct ls_item {
	struct json *v;
	struct ls_item *next;
};

struct json {
	value_t typ;
	int num;	
	union {
		char *str;
		struct hashtable *obj;
		struct ls_item *arr;
	} val;
}; 

struct json *parse(char *str);
void print_json(struct json *j);
