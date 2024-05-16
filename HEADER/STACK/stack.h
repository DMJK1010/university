/*
 * STACK ADT
 * init(Stack) 초기화
 * is_empty(Stack) 비어있는지 체크
 * push(Stack, item) item을 push
 * pop(Stack) item을 하나 꺼내기
 * print_stack(Stack) 스택에 모든 item을 출력
 */

#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node{
	int data;
	struct Node *link;
}Node;

typedef struct{
	Node *top; // 스택의 top을 나타내는 포인터
}Stack;

void init(Stack *s);
bool is_empty(Stack *s);
void push(Stack *s,int item);
int pop(Stack *s);
void print_stack(Stack *s);

#endif /* SRC_STACK_H_ */
