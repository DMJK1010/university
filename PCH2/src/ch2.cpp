/*
 * ch2.cpp
 *
 *  Created on: 2024. 4. 13. - 2장 실습 문제 완료
 *      Author: Junha Kim
 */
/*
===============================================================================
== 문제
===============================================================================
 이름, id, 몸무게(실수값), 결혼여부(true or false)를 각각 입력 받아 출력한다.
 그리고 마지막에 찾을 이름을 입력 받아 앞전에 입력한 이름과 같은 이름이 입력되면
 입력 받은 모든 값을 하나의 행에 출력하고, 이름이 다르면 "not found"를 출력한다.
*/

#include<iostream>
#include<string>
using namespace std;


int main(){
	cin >> boolalpha;
	cout << boolalpha;
	bool married;
	string name, findname;
	int id;
	double weight;

	cout<<"Hello world!!"<<endl;

	cout<<"name? ";
	getline(cin, name, '\n');
	cout<<"name: "<<name<<endl;

	cout<<"id? ";
	cin>>id;
	cout<<"id: "<<id<<endl;

	cout<<"weight? ";
	cin>>weight;
	cout<<"weight: "<<weight<<endl;

	cout<<"married? ";
	cin>>married;
	cout<<"married: "<<married<<endl;

	cout<<"name to find? ";
	getline(cin, findname, '\n');
	getline(cin, findname, '\n');
	if(findname == name)
		cout<<"name:"<<name<<", id:"<<id<<", weight:"<<weight<<", married:"<<married<<endl;
	else
		cout<<findname<<": not found"<<endl;

	return 0;
}
