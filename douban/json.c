#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

char stack[4096];
int tail = 0;
int head = -1;

int ana_arr_json(char *src, int len, struct arr** p_arr)
{
	int i;
	char *p = src;
	struct value* p_v = (*p_arr)->p_v;

	p++;   //first '['
	while(*p)
	{
		switch (*p)
		{
			case ']':	return p - src;
			case ' ':	break;
			case ',':	p_v->p_next = (struct value*)malloc(sizeof(struct value));
						if (p_v->p_next == 0)
						{
							perror("malloc");
							exit(1);
						}
						memset(p_v->p_next, 0, sizeof(struct value));
						p_v = p_v->p_next;
						break;
			default:	p = p - 1 + ana_value_json(p, len, p_v);
		}
		p++;
	}
}


int ana_json(char *src, int len, struct obj **p_obj)
{
	int i;
	int ret;
	char *p = src;			//first {
	struct key* q_key;

#if 1
	while(*p)
	{
		switch (*p)
		{
			case ' ': break;
			case '{': add_obj_json(p_obj);	 q_key = (*p_obj)->p_k; add_json(*p); 
					  break;
			case '}': del_json(*p); 		 return p - src;
			case ':': 
				p++;		 p = p - 1 + ana_value_json(p, len, (q_key->p_v)); 
				break;
			case ',':
				q_key->p_next = (struct key*)malloc(sizeof(struct key));
				if (q_key->p_next == 0)
				{
					perror("malloc");
					exit(1);
				}
				memset(q_key->p_next, 0, sizeof(struct key));
				q_key->p_next->p_v = (struct value*)malloc(sizeof(struct value));
				if (q_key->p_next->p_v == 0)
				{	
					perror("malloc");
					exit(1);
				}
				memset(q_key->p_next->p_v, 0, sizeof (struct value));
				q_key = q_key->p_next;
				break;
			case '"':
				p++;
				i = 0;
				while (*p != '"')
				{
					if (i < STRSIZE - 1)
						sprintf(q_key->key + i, "%c", *p);
					p++ ; i++;
				}
				break;
			default: break;
		}
		p++;
	}
#endif
}

int ana_value_json(char *p, int len,  struct value *const p_v)
{
	int i;
	char *q;
	char *t = p;
	struct value* q_v;

	while (*p != ',' && *p != '}' && *p != ']')
	{
		switch (*p)
		{
			case '{':
				p_v->type = OBJ;
				p = p + ana_json(p, len, (struct obj**)&(p_v->p_data));
				break;
			case ' ':
				break;
			case '[':
				p_v->type = ARR;
				p_v->p_data = (struct arr*)malloc(sizeof(struct arr));
				if (p_v->p_data == 0)
				{
					perror("malloc");
					exit(1);
				}
				memset(p_v->p_data, 0, sizeof(struct arr));
				((struct arr*)(p_v->p_data))->p_v = (struct value*)malloc(sizeof (struct value));
				if (((struct arr*)(p_v->p_data))->p_v == 0)
				{
					perror("malloc");
					exit(1);
				}
				memset(((struct arr*)(p_v->p_data))->p_v, 0, sizeof(struct value));
				p = p + ana_arr_json(p, len, (struct arr**)&(p_v->p_data));
				break;
			case '"':
				p_v->type = STR; 
				p_v->p_data = (char*)malloc(STRSIZE);
				if (p_v->p_data == 0)
				{
					perror("malloc");
					exit(1);
				}
				memset(p_v->p_data, 0, STRSIZE);
				q = p + 1;		 i = 0;
				while (*q != '"')
				{
					if (i < STRSIZE - 1)
						sprintf(p_v->p_data + i, "%c", *q);
					q++; i++;
				}
				p = q;
				break;
			case '0'...'9':
				p_v->type = INT;
				p_v->p_data = (int*)malloc(sizeof(int));
				if (p_v->p_data == 0)
				{
					perror("malloc");
					exit(1);
				}
				if (*p == '0')
					i = 0;
				else
					i = atoi(p);
				*(int*)(p_v)->p_data = i;
				while ( *p <= '9' && *p >= '0')	 p++;
				p--;
				break;
			default:
				break;
		}
		p++;
	}
					
	return p - t;
}

void add_obj_json(struct obj** p_obj)
{
	*p_obj = (struct obj*)malloc(sizeof(struct obj));
	if (p_obj == 0)
	{
		perror("malloc");
		exit(1);
	}
	memset(*p_obj, 0, sizeof(struct obj));
	(*p_obj)->p_k = (struct key*)malloc(sizeof(struct key));
	if ((*p_obj)->p_k == 0)
	{
		perror("malloc");
		exit(1);
	}
	memset((*p_obj)->p_k, 0, sizeof(struct key));
	(*p_obj)->p_k->p_v = (struct value*)malloc(sizeof(struct value));
	if ((*p_obj)->p_k->p_v == 0)
	{
		perror("malloc");
		exit(1);
	}
	memset((*p_obj)->p_k->p_v, 0, sizeof (struct value));
}

void add_json(char c)
{
	stack[++head] = c;
}

void del_json(char c)
{
	if ( (c == ']' && stack[head] != '[') || (c == '}' && stack[head] != '{'))
	{
		printf("del_json error");
		exit(1);
	}
	head--;
}

void clear_json()
{	
	head = -1;
}

int is_empty_json()
{
	if (head == -1)
		return 1;
	else 
		return 0;
}
