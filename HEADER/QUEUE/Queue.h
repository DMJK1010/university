/*
 * Queue ADT
 * init(Q) 초기화 함수
 * is_empty(Q) 큐가 비어있는지
 * enqueue(Q, data) 큐 넣기
 * dequeue(Q) 큐 빼기
 * print_queue(Q) 큐 내용 출력
 */

#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node *link;
}Node; // 연결 리스트의 형태를 갖추기 위한 구조체

typedef struct{
	Node *front, *rear;
}Queue; // 큐의 형태를 갖추기 위한 구조체

void init(Queue *q);
int is_empty(Queue *q);
void enqueue(Queue *q,int data);
int dequeue(Queue *q);
void print_queue(Queue *q);

#endif /* SRC_QUEUE_H_ */
