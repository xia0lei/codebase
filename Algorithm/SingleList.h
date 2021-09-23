#ifndef _SINGLE_LIST_H
#define _SINGLE_LIST_H

typedef struct ListElmt_
{
	void *data;
	struct ListELmt_* next;
}ListElmt;

typedef struct List_
{
	int size;
	int (*match)(const void *key1, const void* key2);
	void (*destory)(void * data);
	ListElmt* head;
	ListElmt* tail;
} List;

void list_init(List *list, void(*destory)(void* data));
void list_destory(List* list);
int list_ins_next(List* list, ListElmt* element, const void* data);
int list_rem_next(List* list, ListElmt* element, void **data);
int list_size(const List* list);
ListElmt* list_head(const List* list);
ListElmt* list_tail(const List* list);
int List_is_head(const ListElmt *element);
int list_is_tail(const ListElmt *element);
void* list_data(const ListElmt* element);
ListElmt* list_next(const ListElmt* element);

#endif