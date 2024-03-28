/*
 * main.c
 *
 *  Created on: 2024. 3. 27.
 *      Author: jon00
 *  ť ���� ������Ʈ
 *  1�� �Ϸ�
 *  2�� �ʿ�
 *  3�� �ʿ�
 *  4�� �ʿ�
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct{
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;



//���� �Լ�
void error(char *message){
	fprintf(stderr, "%s\n", message);
}

//ť �ʱ�ȭ
void init_queue(QueueType *q){
	q->rear = -1;
	q->front = -1;
	printf("ť �ʱ�ȭ��\nrear : %d | front : %d\n", q->rear, q->front);
}

void queue_print(QueueType *q){
	for(int i=0; i<MAX_QUEUE_SIZE; i++){
		if(i<=q->front || i> q->rear)
			printf("  |");
		else
			printf("%2d|", q->data[i]);
	}
	printf("\n");
}

//���� ã������ ��ȯ (full; return 1 | else; return 0)
int is_full(QueueType *q){
	if(q->rear == MAX_QUEUE_SIZE-1)
		return 1;
	else
		return 0;
}

int is_empty(QueueType *q){
	if(q->front == q->rear)
		return 1;
	else
		return 0;
}

void enqueue(QueueType *q, int item){
	if(is_full(q)){
		error("ť�� ��ȭ�����Դϴ�.");
		return;
	}
	q->data[++(q->rear)] = item;

}

int dequeue(QueueType *q){
	if(is_empty(q)){
		error("ť�� ��������Դϴ�.");
		return -1;
	}
	int item = q->data[++(q->front)];
	printf("dequeue() ~ front : %d\n", q->front);
	return item;
}

void input_element(QueueType *q){
	int element;
	printf("input element: ");
	scanf("%d", &element);
	enqueue(q, element);
	printf("enqueue() ~ element[%d] : %d\n", q->rear, q->data[q->rear]);
}

int main_UI(){
	int sel;
	printf("++++++++++++++++++++++++++ Main Menu ++++++++++++++++++++++++++++++\n");
	printf("1. ť ���� �ֱ� 2. ť ���� 3. ť ����ϱ� 4. ť ��� ���� 5. ����     \n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("�Է�: ");
	scanf("%d", &sel);
	return sel;
}


void main_menu(QueueType *q){
	int num = main_UI();
	int output;
	switch(num){
	case 1:
		input_element(q);
		break;
	case 2:
		output = dequeue(q);
		printf("output : %d\n", output);
		break;
	case 3:
		queue_print(q);
		break;
	case 4:
		init_queue(q);
		break;
	case 5:
		exit(0);
		break;


	}
}

int main(){
	QueueType q;
	init_queue(&q);
	while(1){
		main_menu(&q);
	}



	return 0;
}
