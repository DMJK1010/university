/*
 * ch3.cpp
 *
 *  Created on: 2024. 4. 13. - 3장 과제 문제 완료
 *      Author: jon00
 *      (OOP-2023) 3장 과제 문제
 */

#include <iostream>
using namespace std;

//여기에 클래스 코드 작성할 것
class alu {
public:
	unsigned int r1, r2;
	char oper;

	alu();

	int calc();
};

alu::alu(){
	r1 = 1;
	r2 = 3;
	oper = '*';
}

int alu::calc(){
	if(oper == '+')
		return r1+r2;
	else if(oper == '-')
		return r1-r2;
	else if(oper == '*')
		return r1*r2;
}

//아래 main 함수는 수정 불가

int main() {
    alu machine; //생성자 구현하여 아래 출력 결과 1*3처럼 출력되게 각 멤버를 초기화 시킬 것
    cout << machine.r1 << machine.oper << machine.r2 << endl; // 출력 결과:1*3
    cin  >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:7 + 7
    cout << machine.calc() << endl;                           // 출력 예시:14
    cin  >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:25 - 8
    cout << machine.calc() << endl;                           // 출력 예시:17
    cin  >> machine.r1 >> machine.oper >> machine.r2;         // 입력 예시:9 * 25
    cout << machine.calc() << endl;                           // 출력 예시:225
}
