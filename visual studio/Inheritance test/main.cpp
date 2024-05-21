#include<iostream>
#include<string>

using namespace std;

/*
* 사람 정보 : 이름(name) / 나이(age) / 결혼(married) / 전화 번호(phone_num)
* 사람 종류 : Student / Worker / StudentWorker(다중상속)
* 각 객체 추가 정보
* Student		:	학과(department), 학년(year), 전공(Major), 학점(grade)
* Worker		:	회사(company), 월급(salary)
* StudentWorker	:	경력(career)
* 
* 구현 해야 할 것
* 1. 각 클래스의 생성자, 소멸자, 복사 생성자
* 2. 각 함수의 set, get, print, whatareyoudoing 구현
* 3. 메인 메뉴 클래스 만들기
* 4. 연산자 오버로딩, 함수 오버라이드
* 
* 진행 상황:
* Person의 기본 함수 구현 완료
*/

class Person {
	string	name;
	int		age;
	bool	married;
	string	phone_num;

protected:
	void inputMembers(istream& in);
	void printMembers(ostream& out);

public:
	Person(string name, int age, bool married, string phone_num);
	Person(const Person& p);
	~Person();

	void input(istream& in)		{ inputMembers(in); }
	void print(ostream& out) { printMembers(out); }

	void setName(string name) { this->name = name; }
	void setAge(int age) { this->age = age; }
	void setMarried(bool married) { this->married = married; }
	void setPhone_num(string phone_num) { this->phone_num = phone_num; }

	const string	getName() { return name; }
	const int		getAge() { return age; }
	const bool		getMarried() { return married; }
	const string	getPhone_num() { return phone_num; }

	void whatareyoudoing();
	void println();
};

Person::Person(string name, int age, bool married, string phone_num) :name(name), age{ age }, married{ married }, phone_num(phone_num) {
	cout << "Person(...):: ";	println();
}

Person::Person(const Person& p) {
	this->name = p.name;
	this->age = p.age;
	this->married = p.married;
	this->phone_num = p.phone_num;
}

Person::~Person() {
	cout << "~Person():: "; println();
}

void Person::inputMembers(istream& in) {
	in >> name >> age >> married >> phone_num;
	if (!(in))
		return;
}

void Person::printMembers(ostream& out) {
	out << name << " " << age << " " << married << " " << phone_num;
}

void Person::println() {
	cout << "name : " << name << ", age : " << age << ", married : " << married << ", phone_num : " << phone_num << endl;
}

void Person::whatareyoudoing() {
	cout << name << "is watching the TV" << endl;
}

/*
class Student: public Person {
	string	department;
	int		year;
	string	Major;
	double	grade;
public:
	Student();
	Student(const Student& s);
	~Student();



	void setDepartment(string department)	{ this->department = department; }
	void setYear(int year)					{ this->year = year; }
	void setMajor(string Major)				{ this->year = year; }
	void setGrade(double grade)				{ this->grade = grade; }

	const string	getDepartmane()	{ return department; }
	const int		getYear()		{ return year; }
	const string	getMajor()		{ return Major; }
	const double	getGrade()		{ return grade; }

	void whatareyoudoing();
	void println();
};
*/





int main() {

	return 0;
}
