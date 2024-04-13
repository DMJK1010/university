/*
 * ch2.cpp
 *
 *  Created on: 2024. 4. 13. - 완료
 *      Author: Junha Kim
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
