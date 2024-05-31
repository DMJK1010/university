#include"Queue.h"

void init(Queue *q)
{
	q->front = q->rear = NULL;
}

int is_empty(Queue *q)
{
	return (q->front == NULL);
}

void enqueue(Queue *q,int data)
{
	Node* temp = (Node *)malloc(sizeof(Node)); // 삽입할 노드 동적 선언
	temp->data = data; // 삽입할 데이터 복사
	temp->link = NULL; // rear부분 즉 큐의 마지막에 들어가므로 새로운 노드의 링크부분은 NULL이여야 한다.
	if(is_empty(q)) // 큐가 비어있는 경우
	{
		q->front = temp;
		q->rear = temp; // front,rear모두 새로운 노드를 가리키도록 함
	}
	else // 큐가 비어있지 않는 경우
	{
		q->rear->link = temp; // rear노드의 링크가 삽입할 노드를 가리키도록 함
		q->rear = temp; // rear포인터를 삽입할 노드를 가리키도록 선언
	}
}

int dequeue(Queue *q)
{
	Node *temp; //삭제할 노드를 위한 임시 노드 선언
	int data;
	if(is_empty(q)) // 큐가 공백상태인지 검사
	{
		printf("error");
	}
	else{
		temp = q->front; // temp가 q->front 노드 가리킴
		data = temp->data;
		q->front = temp->link; // front가 다음 노드를 가리키도록 함( 삭제후 첫번째 노드가 될 노드)
		if(q->front==NULL) // 공백상태를 만들어 주기 위함
			q->rear ==NULL;
		free(temp); // 동적메모리 해제
		return data; // 데이터 반환
	}
}

void print_queue(Queue *q)
{
	Node *p;
	for(p=q->front;p!=NULL;p=p->link)
		printf("%d->",p->data);
	printf("NULL\n");
}
