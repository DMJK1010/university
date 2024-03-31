#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#define MAX_STACK_SIZE 100
typedef char element;
element stack[MAX_STACK_SIZE];
int top = -1;

int size();
int is_empty();
int is_full();
void push(element item);
element pop();

int main(){
	char input_arr[100] = {};
	char ch;
	scanf("%s", input_arr);
	int len = strlen(input_arr);
	int i;
	for(i=0; i<len; i++){
		if(strcmp(input_arr[len-i-1], ' ') || strcmp(input_arr[len-i-1], ',') || strcmp(input_arr[len-i-1], ',\.') || strcmp(input_arr[len-i-1], '\'')){

		}
		else{
			push(input_arr[len-i-1]);
		}
	}
	for(i=0; i<len; i++){
		if(strcmp(pop(), input_arr[len-i-1]) == 1){
			continue;
		}
		else{
			exit(1);
		}
	}
	printf("\n");
	printf("구두점입니다.");
	system("pause");
	return 0;
}

int is_empty(){
	return (top == -1);
}

int is_full(){
	return (top == (MAX_STACK_SIZE -1));
}

void push(element item){
	if(is_full()){
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++top] = item;
}

element pop(){
	if(is_empty()){
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return stack[top--];
}

int size(){
	return top+1;
}
