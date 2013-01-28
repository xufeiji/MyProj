#ifndef JSON_H
#define JSON_H

#define INT 1
#define STR 2
#define ARR	3
#define OBJ 4

#if 0
#define STRSIZE 64
#else 
#define STRSIZE (100)
#endif

struct value
{
	void *p_data;		//point to value
	int type;
	struct value* p_next;  //when arr, point to next value; when key, is NULL
};

struct key
{
	char key[STRSIZE];
	struct value *p_v;
	struct key * p_next;
};

struct arr
{
	struct value *p_v;
};

struct obj
{
	struct key * p_k;
};

void add_obj_json(struct obj**);
void add_json(char);
void del_json(char);
void clear_json();
int is_empty_json();


int ana_value_json(char *p, int len, struct value* const p_v);
int ana_json(char *, int, struct obj**);
int ana_arr_json(char *, int , struct arr**);
	
#endif
