/*
 * ch5.cpp
 *
 *  Created on: 2024. 4. 13. - 5장 과제 문제 완료
 *      Author: jon00
 */
#include <iostream>
#include <string>
using namespace std;


class MyStack {
private:
	string *element; // 스택의 메모리로 사용할 포인터
	int size;           // 스택의 최대 크기
	int tos;            // 스택의 top을 가리키는 인덱스
public:
	MyStack(int size);    // 생성자 스택의 최대 크기를 입력 받아서 element 객체 배열을 생성해줌.
	MyStack(MyStack& s);  // 깊은 복사 생성자
	~MyStack();           // 소멸자

	bool push(string item); // item을 스택에 삽입
			// 스택이 가득 차 있으면 false를, 아니면 true 리턴
	bool pop(string &item); // 스택의 탑에 있는 값을 item에 반환  그리고 top에 있는 자료 삭제
	bool peek(string &item); // 스택의 탑에 있는 값을 item에 반환
	void print_stack();  // 스택 내용 출력

};

// 위에 코드는 수정 불가

// 여기에 MyStack의 모든 멤버 함수들을 작성하라.
MyStack::MyStack(int size){
	this->size = size;
	tos = 0;
	element = new string[size];
	cout<<"MyStack("<<size<<")"<<endl;
}

MyStack::MyStack(MyStack& s){
	this->size = s.size;
	tos = s.tos;
	element = new string[size];
	for(int i=0; i<size; i++){
		element[i] = s.element[i];
	}
	cout<<"MyStack(MyStack& s): tos+1 = "<<tos<<endl;
}

MyStack::~MyStack(){
	cout<<"~MyStack(): tos+1 = "<<tos<<endl;
}

bool MyStack::push(string item){
	if(tos == size){
		cout<<"stack is full"<<endl;
		return false;
	}
	else{
		element[tos] = item;
		tos++;
		return true;
	}
}

bool MyStack::pop(string &item){
	if(tos == 0){
		cout<<"stack is empty"<<endl;
		return false;
	}
	else{
		item = element[--tos];
		return true;
	}
}

bool MyStack::peek(string &item){
	if(tos == 0)
		return false;
	else{
		item = element[--tos];
		tos++;
		return true;
	}
}

void MyStack::print_stack(){
	for(int i=0; i<tos; i++){
		cout<<element[i]<<" ";
	}
	cout<<endl;
}

// 아래 코드는 수정 불가

int main() {

	int stack_size;

	// 스택이 저장할수 있는 최대 크기를 입력 받는다
	cout << "Enter stack size : ";
	cin >> stack_size;

	// 스택을 생성해 줌
	MyStack first_stack(stack_size);

	// 입력할 데이터의 수를 입력 받는다
	// 데이터를 숫자 만큼 입력 받고 stack에 푸시한다.
	int  input_size;
	string  item;
	cout << "Enter number of input string : " ;
	cin >> input_size;
	for (int i=0; i < input_size; i++ ) {
		cout <<"Enter string : " ;
		cin >> item;
		first_stack.push(item);
	}

	// 스택의 자료를 출력
	cout << "first stack : " ;
	first_stack.print_stack();

	// 스택을 생성해 줌
	MyStack second_stack(first_stack);

	// 스택의 자료를 출력

	cout << "second stack : " ;
	second_stack.print_stack();

	first_stack.pop(item);
	cout << "first stack pop: " << item << endl ;
	second_stack.peek(item);
	cout << "second stack peek: " << item << endl ;

	// 스택의 자료를 출력
	cout << "first stack : " ;
	first_stack.print_stack();

	cout << "second stack : " ;
	second_stack.print_stack();

	cout << "second stack all pop: " << endl;
	while (second_stack.pop(item))
		cout << item << endl;

	return 0;
}
