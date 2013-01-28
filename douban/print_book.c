#include <stdio.h>
#include "json.h"
#include "print_book.h"

#define FORMAT_NUM 4

void print_arr(struct arr* arr, int num)
{
	int i;
	struct value* p_v = arr->p_v;

	for (i = 0; i < FORMAT_NUM * num; i++)
		printf(" ");

	while(p_v)
	{
		switch (p_v->type)
		{
			case INT:
				printf("%d, ", *(int*)p_v->p_data);
				break;
			case STR:
				printf("%s, ", (char*)p_v->p_data);
				break;
			case ARR:
				print_arr(arr, num + 1);
				break;
			case OBJ:
				printf("\n");
				print_book((struct obj*)p_v->p_data,num + 1);
				break;
			default:
				printf("\n");
				break;
		}
		p_v = p_v->p_next;
	}
}


void print_book(struct obj* obj, int num)
{
	int i;
	struct key* key = obj->p_k;

	while(key)
	{
		for (i = 0; i < FORMAT_NUM * num; i++)
			printf(" ");

		printf("%s:", key->key);

		switch (key->p_v->type)
		{
			case INT:
				printf("%d\n", *(int*)key->p_v->p_data);
				break;
			case STR:
				((char*)key->p_v->p_data)[STRSIZE - 1] = 0;
				printf("%s\n", (char*)key->p_v->p_data);
				break;
			case ARR:
				printf("\n");
				print_arr((struct arr*)key->p_v->p_data, num + 1);
				printf("\n");
				break;
			case OBJ:
				printf("\n");
				print_book((struct obj*)key->p_v->p_data,num + 1);
				break;
			default:
				break;
		}
		key = key->p_next;
	}	
}	

