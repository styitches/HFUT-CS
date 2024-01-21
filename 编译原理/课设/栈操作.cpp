#include "data.h"

int InitStack(LinkStack* S)
{
	S->base = S->top = (StackPtr)malloc(sizeof(SNode));
	if (!S->base) return 1;
	S->base->data[0] = 0;
	S->base->Next = NULL;
	return 0;
}
int Push(LinkStack* S, char* e)
{
	SNode* Sn = (SNode*)malloc(sizeof(SNode));
	if (!Sn) return 1;
	strcpy(Sn->data, e);
	Sn->Next = S->top;
	S->top = Sn;
	return 0;
}
int Pop(LinkStack* S, char** e)
{
	if (S->top->Next == NULL)return 1;
	strcpy((*e), S->top->data);
	SNode* Sn = S->top;
	S->top = Sn->Next;
	free(Sn);
	return 0;
}
int IsEmpty(LinkStack* S)
{
	if (S->base == S->top) return 1;
	return 0;
}