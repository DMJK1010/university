/*
 * main.c
 *
 *  Created on: 2024. 4. 15.
 *      Author: jon00
 *
 *      이중 연결 리스트 예제
 */

#include<stdio.h>
#include<stdlib.h>
typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode *llink;
	struct DListNode *rlink;
} DListNode;

void init(DListNode *head){
	head->llink = head;
	head->rlink = head;
}

void dinsert(DListNode *before, element data){
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	newnode->data = data;//strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

void ddelete(DListNode* head, DListNode* removed){
	if(removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

void print_dlist(DListNode* head){
	DListNode *p;
	for(p=head->rlink; p != head; p = p->rlink){
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

int main(){
	DListNode *head = (DListNode *)malloc(sizeof(DListNode));
	init(head);
	printf("추가 단계\n");
	for(int i=0; i<5; i++){
		dinsert(head, i);
		print_dlist(head);
	}
	printf("\n삭제 단계\n");
		for (int i = 0; i < 5; i++) {
			print_dlist(head);
			ddelete(head, head->rlink);
		}
		free(head);


	return 0;
}
