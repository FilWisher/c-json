# c-json
json parser in c

parse common json-like structures

## data types

### typedef enum value_t
types of value defined by JSON spec
```
P_STRING
P_NUMBER
P_OBJECT
P_ARRAY
P_BOOLEAN
P_NULL
```

### struct json
an AST node with:
```c
value_t typ;  // represents type of JSON value
int num; // used for numbers, array length, and booleans
union {
  char *str; // string contents
  struct hashtable *obj; // hashtable contents
  struct ls_item *arr; // array contents
} val;
```

### struct hashtable
basic struct and operations for hashtables (for representing objects)
```c
int i; // current count
int cap; // current capacity (dynamically increases when load factor > threshold)
struct ht_item **table; // table contents
```

### struct ht_item
hashtable row item. collisions resolved by linking
```c
const char *k; // key
struct json *v; // value
struct ht_item *next; // next item (for collisions)
```

### struct ls_item
basic struct for linked lists of json (for representing arrays)
```c
struct json *v; // item value
struct ls_item *next; // link to next item
```

## TODO
- enumerate keys and key-value pairs of hashtable
- iterate through arrays
- throw more explicit errors when parsing
- clean up memory after parsing
- write interface functions to access data through ```struct json```
- demo cli function to test parsing .json files
- parse numbers correctly (including floating point and negatives)
- correctly check escape-codes in strings
