/*
 * Stack.h
 *
 *  Created on: 18/06/2018
 *      Author: administrador
 */

#ifndef STACK_H_
#define STACK_H_

typedef enum {false, true} bool;

typedef void * Type;

typedef struct strStack *Stack;

Stack createStack();

void destroyStack(Stack);

bool push(Stack, Type);

Type pop(Stack);

Type top(Stack);

bool isEmpty(Stack);

#endif /* STACK_H_ */





/*
 * useStack.c
 *
 *  Created on: 19/06/2018
 *      Author: administrador
 */
//#include "Stack.h"
//#include <string.h>
//
//int main(){
//	int n1=1, n2=2, n3=3;
//	Stack s1;
//	s1=createStack();
//	int i;
//
//	push(s1, (void *)&n1);
//	push(s1, &n2);
//	push(s1, &n3);
//
//	int *r=pop(s1);
//	printf("%d", *r);
//
//	Stack s2;
//	s2=createStack();(
//	char t1[]="Hola ";
//	char t2[]="ITESO";
//	push(s2, t1);
//	push(s2, t2);
//
//	strcpy(t2, "tieso");
//
//	char *rt=pop(s2);
//	printf("\n%s", rt);
//
//	return 0;
//}


