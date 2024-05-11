/*
 * CH8_1: ch8_1.cpp
 *
 *  Created on: 2024. 5.11.(16:17) - 완료
 *      Author: Junha Kim
 *
 *
 *  + Person을 상속 받는 Student, Worker 클래스 추가
 *  + MultiManager: 배열 데이타 추가, 멤버 함수 추가
 *  + Inheritance 클래스 추가
 *  + VectorPerson의 메모리 확장 관련 출력문들 주석처리
 */

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

#define AUTOMATIC_ERROR_CHECK true // false: 자동 오류 체크, true: 키보드에서 직접 입력하여 프로그램 실행

/******************************************************************************
 * Person class
 ******************************************************************************/

class Person
{
    string name;       	    // 이름
    string passwd;          // 비번
    int    id;              // Identifier
    double weight;          // 체중
    bool   married;         // 결혼여부
    char*  address;         // 주소:  5_2에서 []에서 *로 변경
    char*  memo_c_str;      // 메모장: 5_2에서 []에서 *로 변경

protected:
    void inputMembers(istream& in);
    void printMembers(ostream& out);
    void copyAddress(const char* address); // 5_2에서 추가
    void copyMemo(const char* c_str);      // 5_2에서 추가

public:
    //Person() : Person("") {}
    //Person(const string name) : Person(name, 0, 0, 0, "") {}
    Person(const string& name={}, int id={}, double weight={}, bool married={}, const char *address ={});
    Person(const Person& p);
    ~Person();

    Person* clone() { return new Person(*this); } // ch7_3에서 추가
    void set(const string& name, int id, double weight, bool married, const char *address);
    void setName(const string& name)       { this->name = name; }
    void setPasswd(const string& passwd)   { this->passwd = passwd; }
    void set(int id)                    { this->id = id; }
    void set(double weight)        { this->weight = weight; }
    void set(bool married)        { this->married = married; }
    void setAddress(const char* address); // 5_2에서 수정
    void setMemo(const char* c_str);      // 5_2에서 수정


    const string&		getName()   const { return name; }
    const string&     getPasswd() const { return passwd; }
    int         getId()     const { return id; }
    double      getWeight() const { return weight; }
    bool        getMarried() const { return married; }
    const char* getAddress() const { return address; }
    const char* getMemo()   const { return memo_c_str; }

    void input(istream& in)  { inputMembers(in); } // ch3_2에서 추가
    void print(ostream& out) { printMembers(out); }
    void println()            { print(cout); cout << endl; }
    void whatAreYouDoing();                          // ch3_2에서 추가
    bool isSame(const string& name, int pid);         // ch3_2에서 추가

    bool operator== (const Person &p);
    Person operator+(double weight);
    friend Person operator+(double weight, Person &p);
    Person& operator = (const Person& p);
    Person& operator++();    // 객체 자신에 대한 참조자 리턴
    Person  operator++(int); // 기존 객체(this)를 복사하여 새로운 지역 객체를 만들고
           // 기존 객체의 체중을 1 증가시킨다. 그리고 새로운 지역 객체(기존 복사본)를 반환한다.
    Person& operator << (const string& name); // setName()과 동일
    Person& operator << (const char* name);   // setName()과 동일
    Person& operator << (int id);             // set(int id)와 동일
    Person& operator >> (string& name); // 멤버 name을 매개변수 name에 저장
    Person& operator >> (int& id);      // 멤버 id을 매개변수 id에 저장
    Person& operator >> (char* name);   // 멤버 name의 C-스트링을 매개변수 name에 복사

    operator string() { return this->name; }
    operator int()    { return this->id; }
};

Person::Person(const string& name, int id, double weight, bool married, const char* address):name(name), id{id}, weight{weight}, married{married}, memo_c_str{} {
    // 생성자 서두에서 memo_c_str{}은 초기 값으로 디폴트 값인 nullptr(실제로는 주소 값 0)로 설정됨
    copyAddress(address);
    cout << "Person::Person(...):"; println();
}

Person::Person(const Person& p):name(p.name), id{p.id}, weight{p.weight}, married{p.married}{
    copyAddress(p.address);
	copyMemo(p.memo_c_str);
    cout << "Person::Person(const Person&):"; println();
}

Person::~Person() {
    cout << "Person::~Person():"; println();

    if(address != nullptr)
    	delete [] address;
    if(memo_c_str != nullptr)
    	delete [] memo_c_str;
}

// 처음 객체가 초기화될 때(생성자 또는 복사생성자) address 멤버를 초기화하고자 할 때 호출된다.
// 즉, 일반 생성자 또는 복사 생성자에서만 호출됨.
// 새로 할당받은 메모리에 매개변수 address 문자열을 복사한다.
void Person::copyAddress(const char* address) {
	if(address == nullptr){
		this->address = nullptr;
		return;
	}
	this->address = new char[strlen(address)+1];
	strcpy(this->address, address);
}

// 복사 생성자에 의해 처음 메모 문자열 memo_c_str을 초기화할 때 호출된다.
// 복사 생성자에서만 호출되고 일반 생성자에서는 nullptr로 설정됨
void Person::copyMemo(const char* c_str)      {
	if(c_str == nullptr){
			memo_c_str = nullptr;
			return;
		}
	memo_c_str = new char[strlen(c_str)+1];
	strcpy(memo_c_str, c_str);
}

void Person::setAddress(const char* address) {
	if(this->address != nullptr){
		delete [] this->address;
	}
    copyAddress(address); // 새로 메모리 할당받은 후 복사한다.
}

void Person::setMemo(const char* c_str)      {
	if(memo_c_str != nullptr){
		delete [] memo_c_str;
	}
    copyMemo(c_str); // 새로 메모리 할당받아 복사한다.
}


void Person::printMembers(ostream& out)   {
	out<<name <<" "<<id<<" "<<weight<<" "<<married<<" :"<<((address == nullptr) ? "" : address)<<": ";
}

void Person::set(const string& name, int id, double weight, bool married, const char *address) {
    this->name = name;
    this->id = id;
    this->weight = weight;
    this->married = married;
    setAddress(address);
}

void Person::inputMembers(istream& in)   {
    in>>name>>id>>weight>>married;
    if (!(in)) return;

    // 지역변수로 미리 큰 주소용 배열을 잡는다.
    char address[40];    // ch5_2에서 추가됨

    in.getline(address, sizeof(address), ':');
    in.getline(address, sizeof(address), ':');


    // 아래 함수를 통해 위 지역변수 address[]에 있는 주소를 멤버 address로 복사한다.
    // 아래 함수에서 address[]의 문자열 길이만큼 메모리를 할당(멤버 address용) 받은 후 복사한다.
    // 멤버 address는 이전에 이미 초기화되었기 때문에 copyAddress()가 아닌 아래 함수를 사용함
    setAddress(address); // ch5_2에서 추가됨
}

void Person::whatAreYouDoing() {
	cout<<name<<" is taking a rest.";
}

bool Person::isSame(const string& name, int pid) {
    if((this->name == name) && (id == pid))
        return true;
    else
        return false;
}

bool Person::operator == (const Person &p){
	return this->isSame(p.name, p.id);
}

Person Person::operator+(double weight){
	Person tmp(*this);
	tmp.weight += weight;
	return tmp;
}

Person operator+(double weight, Person &p){
	Person tmp(p);
	tmp.weight += weight;
	return tmp;
}

Person& Person::operator = (const Person& p){
	this->name = p.name;
	this->passwd = p.passwd;
	this->id = p.id;
	this->weight = p.weight;
	this->married = p.married;
	setAddress(p.address);
	setMemo(p.memo_c_str);
	return *this;
}

Person& Person::operator++(){
	this->weight++;
	return *this;
}
Person Person::operator++(int){
	Person tmp(*this);
	this->weight++;
	return tmp;
}

Person& Person::operator << (const string& name){
	this->name = name;
	return *this;
}

Person& Person::operator << (const char* name){
	this->name = name;
	return *this;
}

Person& Person::operator << (int id){
	this->id = id;
	return *this;
}

Person& Person::operator >> (string& name){
	name = this->name;
	return *this;
}

Person& Person::operator >> (int& id){
	id = this->id;
	return *this;
}

Person& Person::operator >> (char* name){
	strcpy(name, this->name.c_str());
	return *this;
}

/******************************************************************************
 * ch8_1: Student class
 ******************************************************************************/

class Student : public Person {
    string department; // 학과
    double GPA;        // 평균평점
    int    year;       // 학년

protected:
    void inputMembers(istream& in);
    void printMembers(ostream& out);

public:
    Student(const string& name={}, int id={}, double weight={},
            bool married={}, const char* address={},
            const string& department={}, double GPA={}, int year={});
    Student(const Student& s); // copy constructor
    ~Student();
    Person* clone() { return new Student(*this); }  // 자동 업캐스팅

    // Getter and Setter
    int           getYear()       const;
    double        getGPA()        const;
    const string& getDepartment() const;

    void setDepartment(const string& department)	{ this->department = department; }
    void setYear(int year)							{ this->year = year; }
    void setGPA(double GPA)							{ this->GPA = GPA; }

    const string getDepartment()	{ return department; }
    const double getGPA()			{ return GPA; }
    const int getYear()				{ return year; }

    // 부모(기본) 클래스의 멤버 함수 재정의: Redefined member functions
    void input(istream& in);
    void print(ostream& out);
    void println() { print(cout); cout << endl; }

    bool operator==(const Student& s);
    void whatAreYouDoing();

    // 새로 추가된 멤버 함수: Member functions added in Student
    void study();
    void takeClass();
};

Student::Student(const string& name, int id, double weight,
        bool married, const char* address,
        const string& department, double GPA, int year):
    	Person(name, id, weight, married, address),          // 부모 클래스 생성자 호출
		department(department), GPA{GPA}, year{year} {       // 멤버 초기화
    cout << "Student::Student(...):"; printMembers(cout); cout << endl;
}

Student::Student(const Student& s) : Person(s), department(s.department), GPA{s.GPA}, year{s.year} {
    cout << "Student::Student(const Student& s):"; printMembers(cout); cout << endl;
}

Student::~Student() {
    cout << "Student::~Student():"; printMembers(cout); cout << endl;
}

void Student::inputMembers(istream& in){
	cin>>department>>GPA>>year;
}

void Student::printMembers(ostream& out)   {             // 멤버 출력
    out << " " << department << " " << GPA << " " << year;
}

void Student::input(istream& in){
	 Person::inputMembers(in);
	 if(!in) return;
	 Student::inputMembers(in);
}

void Student::print(ostream& out){
	Person::printMembers(cout);
	Student::printMembers(cout);
}

bool Student::operator==(const Student& s){
	if((*(Person*)this == s) && (year==s.year) && (department==s.department))
		return true;
	else
		return false;
}

void Student::whatAreYouDoing() {
    cout << "~~~~~~~~~~~~~~~~ Student::whatAreYouDoing() ~~~~~~~~~~~~~~~~\n";
    study();
    takeClass();
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void Student::study() {
	cout<<Person::getName()<<" is studying as a "<<year<<"-year student in "<<department<<endl;
}

void Student::takeClass() {
	cout<<Person::getName()<<"took several courses and got GPA "<<GPA<<endl;
}

/******************************************************************************
 * ch8_1: Worker class
 ******************************************************************************/

class Worker : public Person {
    string company;    // 회사명
    string position;   // 직급

protected:
    void inputMembers(istream& in);
    void printMembers(ostream& out);

public:
    Worker(const string& name={}, int id={}, double weight={},
            bool married={}, const char* address={},
            const string& company={}, const string& position={});
    Worker(const Worker& w); // copy constructor
    ~Worker();
    Person* clone() { return new Worker(*this); }

    // Getter and Setter
    const string& getCompany()  const	{ return company; }
    const string& getPosition() const	{ return position; }

    void setCompany(const string& company)	{ this->company = company; }
    void setPosition(const string& position)	{ this->position = position; }

    // 부모(기본) 클래스의 멤버 함수 재정의: Redefined member functions
    void input(istream& in);
    void print(ostream& out);
    void println() { print(cout); cout << endl; }

    bool operator==(const Worker& w);
    void whatAreYouDoing();

    // 새로 추가된 멤버 함수: Member functions added in Worker
    void work();
    void goOnVacation();
};

Worker::Worker(const string& name, int id, double weight,
        bool married, const char* address,
        const string& company, const string& position):
        Person(name, id, weight, married, address),
		company(company), position(position){
    cout << "Worker::Worker(...):"; printMembers(cout); cout << endl;
}

Worker::Worker(const Worker& w):Person(w), company(w.company), position(w.position){
	cout << "Worker::Worker(const Worker& w):"; printMembers(cout); cout << endl;
}

Worker::~Worker() {
    cout << "Worker::~Worker():"; printMembers(cout); cout << endl;
}

void Worker::input(istream& in){
	 Person::inputMembers(in);
	 if(!in) return;
	 Worker::inputMembers(in);
}

void Worker::inputMembers(istream& in){
	cin>>company>>position;
}

void Worker::printMembers(ostream& out)   {
    out << " " << company << " " << position;
}

void Worker::print(ostream& out){
	Person::printMembers(cout);
	printMembers(cout);
}

bool Worker::operator==(const Worker& w){
	if(*(Person*)this && (this->company == w.company) && (this->position == w.position))
		return true;
	else
		return false;
}

void Worker::whatAreYouDoing() {
    cout << "!!!!!!!!!!!!!!!! Worker::whatAreYouDoing()!!!!!!!!!!!!!!!!!\n";
    work();
    goOnVacation();
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
}

void Worker::work() {
	cout<<Person::getName()<<" works in "<<company<<" as "<<position<<endl;
}
void Worker::goOnVacation() {
	cout<<Person::getName()<<" is now enjoying his(her) vacation"<<endl;
}

/******************************************************************************
 * User Interface
 ******************************************************************************/
// 기본적인 입력과 관련된 전역 함수들을 UI라는 이름공간 내부에 정의함

class UI {


private:
	static string line, emptyLine;
public:
	static bool echo_input;
	static bool checkInputError(istream& in, const string& msg);
	static bool checkDataFormatError(istream& in);
	static bool inputPerson(Person& p);
	static string& getNext(const string& msg);
	static string& getNextLine(const string& msg);
	static int getInt(const string& msg);
	static int getPositiveInt(const string& msg);
	static int getIndex(const string& msg, int size);
	static int selectMenu(const string& menuStr, int menuItemCount);

};

bool UI::echo_input = false;
string UI::line, UI::emptyLine; // ""로 초기화됨

// 입력에서 정수 대신 일반 문자가 입력되었는지 체크하고 에러 발생시 에러 메시지 출력
bool UI::checkInputError(istream& in, const string& msg) {
    if (!(in)) { // 에러가 발생했다면
        cout << msg;  // 에러 메시지를 출력
        in.clear(); // 에러 발생 상태정보를 리셋함; 그래야 다음 문장에서 읽을 수 있음
        getline(in, emptyLine); // 에러가 발생한 행 전체를 읽어 데이터를 버림
        return true;
    }
    return false;
}

// 정수나 실수를 입력해야 하는 곳에 일반 문자열을 입력한 경우의 에러 체크
bool UI::checkDataFormatError(istream& in) {
    return checkInputError(in, "Input-data format MISMATCHED\n");
}

// 한 사람의 정보 즉, 각 멤버 데이터를 순서적으로 입력 받아 p에 저장하고
// 입력 중 입력 데이터에 오류가 있는지 확인하고 오류가 있을 시 에러 메시지를 출력한다.
bool UI::inputPerson(Person& p) {
    cout << "input person information:" << endl;
    p.input(cin);
    if (checkDataFormatError(cin)) return false;
    if (echo_input) p.println(); // 자동체크에서 사용됨
    return true;
}

// 입력장치에서 하나의 단어로 구성된 문자열을 입력 받음
string& UI::getNext(const string& msg) {
    cout << msg; // 입력용 메시지를 출력
    cin >> line; // 하나의 단어를 읽어 들임
    if (echo_input) cout << line << endl; // 자동체크 시 출력됨
    getline(cin, emptyLine); // 입력받은 한 단어 외 그 행의 나머지 데이타(엔터포함)는 읽어서 버림
    return line;             // 이유는 여기서 [엔터]를 제거하지 않으면
}                            // 다음의 getNextLine()에서 엔터만 읽어 들일 수 있기 때문에

// 입력장치에서 한 행을 입력 받음
string& UI::getNextLine(const string& msg) {
    cout << msg; // 입력용 메시지를 출력
    getline(cin, line); // 한 행을 읽어 들임
    if (echo_input) cout << line << endl; // 자동체크 시 출력됨
    return line;
}

// 하나의 정수를 입력 받음; 정수가 아닌 아닌 문자열 입력시 에러 메시지 출력 후 재입력 받음
int UI::getInt(const string& msg) {
    for (int value; true; ) {
        cout << msg;
        cin >> value;
        if (echo_input) cout << value << endl; // 자동체크 시 출력됨
        if (checkInputError(cin, "Input an INTEGER.\n"))
            continue;
        getline(cin, emptyLine); // skip [enter] after the number
        return value;
    }
}

// 하나의 양의 정수를 입력 받음; 음수 입력시 에러 메시지 출력 후 재입력 받음
int UI::getPositiveInt(const string& msg) {
    int value;
    while ((value = getInt(msg)) < 0)
        cout << "Input a positive INTEGER." << endl;
    return value;
}

// 0~(size-1)사이의 선택된 메뉴 항목 또는 리스트의 항목의 인덱스 값을 리턴함
// 존재하지 않는 메뉴항목을 선택한 경우 에러 출력
int UI::getIndex(const string& msg, int size) {
    while (true) {
        int index = getPositiveInt(msg);
        if (0 <= index  && index < size) return index;
        cout << index << ": OUT of selection range(0 ~ "
             << size-1 << ")" << endl;
    }
}

// 사용자에게 메뉴를 보여주고 사용자가 선택한 메뉴항목의 인덱스를 리턴함
int UI::selectMenu(const string& menuStr, int menuItemCount) {
    cout << endl << menuStr;
    return getIndex("Menu item number? ", menuItemCount);
}


/******************************************************************************
 * ch4_3: string and Memo class
 ******************************************************************************/

class Memo
{
    string mStr; // 메모를 저장해 두는 문자열

    string& get_next_line(size_t& ppos, string& line);
    bool find_line(int line, size_t& start, size_t& next);
    size_t find_last_line();

public:
    Memo(const char* c_str = {} ): mStr{c_str == nullptr ? "" : c_str} { }

    string& getNext(size_t& ppos, string& word);
    void displayMemo();
    void findString();
    void compareWord();
    void dispByLine();
    void deleteLine();
    void replaceLine();
    void scrollUp();
    void scrollDown();
    void inputMemo();
    void run();
    const char *c_str() { return mStr.c_str(); }
    void c_str(const char *c_str){
    	mStr = (c_str == nullptr) ? "" : c_str;
    }

    Memo  operator +  (const Memo& m); // ch7_1 추가
    Memo& operator += (const Memo& m); // ch7_1 추가
};

string& Memo::get_next_line(size_t& ppos, string& line) {
    size_t pos = ppos, end;

    /*
    TODO: string::find()를 이용해 행의 끝('\n') 위치를 찾아서(현재 행의 시작 위치는 pos임) end에 저장
    */
    end = mStr.find('\n', pos);

    // 메모의 끝에 '\n'이 없을 경우: (end == string::npos)
    end = (end == string::npos)? mStr.length() : end+1;
    ppos = end; // 다음 행의 시작 위치를 기록해 둠

    /*
    TODO: 찾은 현재 행을 string::substr()으로 발췌해서 별도의 string으로 구성하여 리턴하라.
          발췌할 단어 길이는 pos와 end로 간단히 계산할 수 있음
    */
    line = mStr.substr(pos, end - pos);
    return line;
}

bool Memo::find_line(int line_num, size_t& pstart, size_t& plen) { // 찾으면 : true 못찾으면 : false 반환
    size_t start = 0;

    for(int i=0; i<line_num; i++){
    	if((start = mStr.find('\n', start)) == string::npos)
    		return false;
    	else
    		start++;
    }

    pstart = start; // line_num 행의 시작 위치를 기록

    if(mStr.find('\n', start) == string::npos){
    	plen = string::npos;
    }
    else{
    	plen = mStr.find('\n', start) - start;
    }
    return true; // line_num 행을 찾았다는 것을 의미함
}

size_t Memo::find_last_line() {
    for (size_t start = 0, pos = 0; true; start = pos) {
    	pos = mStr.find('\n', start);
    	if(pos == string::npos || ++pos == mStr.length()){
    		return start;
    	}

    }
}

void Memo::dispByLine() {
	int i = 0;
    cout << "--- Memo by line ---" << endl;
    for(size_t pos = 0; pos < mStr.length();){
    	string line;
    	get_next_line(pos, line);
    	cout << "[" << i++ << "] "<<line;
        if (mStr.length() > 0 && mStr[mStr.length()-1] != '\n')
            cout << endl; // 메모 끝에 줄바꾸기 문자가 없을 경우 출력
    }
    cout << "--------------------" << endl;
}

void Memo::deleteLine() {
    size_t start, len, line_num = UI::getPositiveInt("Line number to delete? ");
    /*
    TODO: 만약 line_num 행을 찾지 못한 경우
          ( 즉, mStr이 비어 있거나 또는
            find_line(line_num,&start,&len) 호출하여 line_num 행을 못 찾았거나(false) 또는
            찾았지만(true) 행의 시작 위치인 start가 메모 텍스트의 끝인 경우(start == mStr.size()) )
              "Out of line range" 문장 출력
          line_num 행을 찾은 경우 mStr에서 해당 행을 삭제한 후 dispByLine() 호출
          */
    if(mStr.empty() || !(find_line(line_num, start, len)) || start == mStr.size())
    		cout<<"Out of line range";
    else{
    	mStr.erase(start, len+1);
    	dispByLine();
    }

}

void Memo::replaceLine() {
    size_t start, len, line_num = UI::getPositiveInt("Line number to replace? ");

    if(!(find_line(line_num, start, len))){
    	cout<<"Out of line range";
    	return;
    }
    string line = UI::getNextLine("Input a line to replace:\n");
    line += '\n';
    mStr.replace(start, len+1, line);
    dispByLine();
}

void Memo::scrollUp() {
    size_t start, len;

    find_line(0, start, len);

    string line = mStr.substr(start, len+1);
    mStr += line;
    mStr.erase(start, len+1);
    dispByLine();
}

void Memo::scrollDown() {
    size_t last = find_last_line();
    size_t len = mStr.size() - last;
    string line = mStr.substr(last, len+1);
    mStr.erase(last, len+1);
    mStr.insert(0, line);
    dispByLine();
}

void Memo::inputMemo() {
	mStr.clear();
    string line;
    cout << "--- Input memo lines, and then input empty line at the end ---" << endl;
    while (true) {
    	getline(cin, line);
    	if (UI::echo_input) cout << line << endl;
    	if(line == "")
    		return;
    	line += '\n';
    	mStr += line;
    }
}
string& Memo::getNext(size_t& ppos, string& word) {
    size_t pos = ppos, end;
    for ( ; pos < mStr.size() && isspace(mStr[pos]); ++pos) ; // 단어 앞의 공백 문자들 스킵(있을 경우)
    end = pos; // pos는 단어의 시작 위치이고 end는 단어의 끝 다음 위치이다.
    if (end < mStr.size() && ispunct(mStr[end])) // 첫 글자가 구두점일 경우
        ++end;
    else { // 단어의 끝을 찾음
        for ( ; end < mStr.size() && !isspace(mStr[end]) &&
                !ispunct(mStr[end]); ++end) ;
    }
    ppos = end; // 다음 단어의 시작 위치를 기록해 둠

    /*
    TODO: string::substr()을 이용해서 찾은 단어를 발췌해서 별도의 string으로 구성하여 리턴하라.
          mStr의 끝에 도착하여 더 이상 찾을 단어가 없을 경우 "" 문자열을 반환하게 된다.
          발췌할 단어의 길이는 pos와 end의 간단한 계산으로 구할 수 있다.
    */
    word = mStr.substr(pos, end-pos);
    if(pos == mStr.size())
    	word = "";
    return word;
}

void Memo::displayMemo() { // Menu item 1
    cout << "------- Memo -------" << endl;
    cout << mStr;
    if (mStr.length() > 0 && mStr[mStr.length()-1] != '\n')
        cout << endl; // 메모 끝에 줄바꾸기 문자가 없을 경우 출력
    cout << "--------------------" << endl;
}

// 아래 R"( 와 )"는 그 사이에 있는 모든 문자를 하나의 문자열로 취급하라는 의미이다.
// 따라서 행과 행 사이에 있는 줄바꾸기 \n 문자도 문자열에 그대로 포함된다.
// 이런 방식을 사용하지 않으면 여러 행에 걸친 문자열을 만들려면 복잡해진다.

const char* memoData = R"(The Last of the Mohicans
James Fenimore Cooper
Author's Introduction
It is believed that the scene of this tale, and most of the information
necessary to understand its allusions, are rendered sufficiently 
obvious to the reader in the text itself, or in the accompanying notes.
Still there is so much obscurity in the Indian traditions, and so much
confusion in the Indian names, as to render some explanation useful.
Few men exhibit greater diversity, or, if we may so express it, 
greater antithesis of character, 
than the native warrior of North America.
)";

//const char* memoData = "The Last of the Mohicans";

void Memo::run() {

    // TODO 문제 [1]: func_arr[], menuCount 선언
	using func_t = void (Memo::*)();
	func_t func_arr[] = {
	    nullptr, &Memo::displayMemo, &Memo::findString, &Memo::compareWord, &Memo::dispByLine, &Memo::deleteLine, &Memo::replaceLine, &Memo::scrollUp, &Memo::scrollDown, &Memo::inputMemo
	};
	int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 길이
    string menuStr =
        "++++++++++++++++++++++ Memo Management Menu +++++++++++++++++++++\n"
        "+ 0.Exit 1.DisplayMemo 2.FindString 3.CompareWord 4.DispByLine  +\n"
        "+ 5.DeleteLine 6.RepaceLine 7.ScrollUp 8.ScrollDown 9.InputMemo +\n"
        "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    if (mStr == "") mStr = memoData;// 멤버 mStr이 비었을 경우 위 memoData로 초기화한다.

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}

void Memo::findString() {
    string word = UI::getNext("Word to find? ");
    int count = 0, len = word.length();
    size_t pos = 0;
    for(int i=0; i<(int)mStr.length(); i++){
    	if(mStr.find(word, pos) != string::npos){
    		count++;
    		pos = mStr.find(word, pos) + len;
    	}
    }
    cout << "Found count: " << count << endl;
}

void Memo::compareWord() {
    string next, word = UI::getNext("Word to compare? ");
    int less = 0, same = 0, larger = 0;
    /*
    아래 pos는 getNext(&pos)를 호출할 때 다음 단어를 찾아야 할 시작 위치임
    TODO: for(size_t pos = 0; getNext(&pos)를 호출하여 mStr의 끝까지 반복 수행; )
             위 getNext(&pos)를 호출시 리턴된 다음 단어를 next에 저장한 후
             next가 ""일 경우 mStr의 끝을 의미하므로 for문 종료
             ""가 아닌 경우 찾을 단어인 word와 비교(<, >, ==)하여
             적절한 less, same, larger 변수의 값을 증가시킨다.
    */
    for (size_t pos = 0; !getNext(pos, next).empty(); ) {
    	if(next < word)
    		less++;
    	else if(next == word)
    		same++;
    	else
    		larger++;
    }

    cout << "less: "   << less   << endl;
    cout << "same: "   << same   << endl;
    cout << "larger: " << larger << endl;
}

Memo  Memo::operator +  (const Memo& m){
	Memo tmp;
	tmp.mStr = this->mStr + m.mStr;
	return tmp;
}
Memo& Memo::operator += (const Memo& m){
	mStr = mStr + m.mStr;
	return *this;
}

/******************************************************************************
 * ch3_2: CurrentUser class
 ******************************************************************************/

class CurrentUser
{
    Person& rUser;
    Memo    memo; // ch4_3에서 추가

public:
    CurrentUser(Person& rUser): rUser(rUser) { }
    void display();
    void setter();
    void getter();
    void set();
    void whatAreYouDoing();
    void isSame();
    void inputPerson();
    void changePasswd();
    void manageMemo();
    void defaultParameter();
    void staticMember();
    void run();
};

void CurrentUser::display() { // Menu item 1
    rUser.println();
}

void CurrentUser::getter() { // Menu item 2
    cout << "name:" << rUser.getName() << ", id:" << rUser.getId() << ", weight:" << rUser.getWeight() << ", married:" << rUser.getMarried() << ", address:" << rUser.getAddress() << endl;
}

void CurrentUser::setter() { // Menu item 3
	Person p("rp"), &rp = p; // Person p("rp"); Person& rp = p;와 동일
    rp.setName(rp.getName());
    rp.set(rUser.getId());
    rp.set(rUser.getWeight());
    rp.set(rUser.getMarried());
    rp.setAddress(rUser.getAddress());
    cout << "rp.setMembers():"; rp.println();
}

void CurrentUser::set() { // Menu item 4
	Person p("rp"), &rp = p; // Person p("rp"); Person& rp = p;와 동일
    rp.set(rp.getName(), rUser.getId(), rUser.getWeight(), !rUser.getMarried(), rUser.getAddress());
    cout << "rp.set():"; rp.println();
}

void CurrentUser::whatAreYouDoing() {  // Menu item 5
	rUser.whatAreYouDoing();
}

void CurrentUser::isSame() { // Menu item 6
    rUser.println();
    cout << "isSame(\"user\", 1): " << rUser.isSame("user", 1) << endl;
}

void CurrentUser::inputPerson() { // Menu item 7
    if (UI::inputPerson(rUser)) // GilDong 1 70.5 true :Jongno-gu, Seoul:
        display();              // user 1 71.1 true :Gwangju Nam-ro 21:
}

void CurrentUser::changePasswd() {
	string passwd = UI::getNext("New password: ");
	rUser.setPasswd(passwd);
    cout << "Password changed" << endl;
}

void CurrentUser::manageMemo() { // Menu item 9
    memo.c_str(rUser.getMemo());
    memo.run();
    rUser.setMemo(memo.c_str());
}

void CurrentUser::defaultParameter() { // Menu item 10
    Person ps1;
    Person ps2("ps2");
    Person ps3("ps3", 3);
    Person ps4("ps4", 4, 70.4);
    Person ps5("ps5", 5, 70.5, true);
    Person ps6("ps6", 6, 70.6, true, "ps6 address");

    cout << "\nMemo m1;" << endl;
    Memo m1; // 메모 생성자에게 인자를 넘겨 주지 않은 경우
    m1.displayMemo();

    cout << "\nMemo m2(rUser.getMemo())" << endl;
    Memo m2(rUser.getMemo()); // 메모 생성자에게 인자를 넘겨 준 경우
    m2.displayMemo();
}

void CurrentUser::staticMember() { // Menu item 11
	string word1 = UI::getNext("Input a word: ");
    cout << "UI::getNext(): " << word1 << endl << endl;

    UI ui;
    string word2 = ui.getNext("Input a word: ");
    cout << "ui.getNext() : " << word2 << endl;
}

void CurrentUser::run() {
    using func_t = void (CurrentUser::*)();
    using CU = CurrentUser;
    func_t func_arr[] = {
        nullptr, &CU::display, &CU::getter, &CU::setter, &CU::set, &CU::whatAreYouDoing, &CU::isSame, &CU::inputPerson, &CU::changePasswd, &CU::manageMemo, &CU::defaultParameter, &CU::staticMember
    };

    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 배열의 길이
    string menuStr =
            "+++++++++++++++++++++ Current User Menu ++++++++++++++++++++++++\n"
            "+ 0.Logout 1.Display 2.Getter 3.Setter 4.Set 5.WhatAreYouDoing +\n"
    		"+ 6.IsSame 7.InputPerson 8.ChangePasswd(4_2) 9.ManageMemo(4_3) +\n"
    		"+ 10.DefaultParameter(6_1) 11.StaticMember(6_1)                +\n"
            "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}


// ch3_2: CurrentUser class

/******************************************************************************
 * ch4_2: VectorPerson class
 ******************************************************************************/
// VectorPerson는 n개의 Person * 포인터를 pVector[] 배열에 담아 관리하는 클래스이다.
// 필요에 따라 포인터를 삽입, 삭제, 추가 등을 할 수 있다.
// 삽입하는 포인터 개수가 점점 많아지면 pVector[] 배열을 위한 메모리를 자동 확장하기도 한다.

class VectorPerson
{
    static const int DEFAULT_SIZE = 10; // pVector의 디폴트 배열 원소 개수

    Person **pVector; // Person *pVector[]; Person에 대한 포인터들의 배열, 배열에 저장될 값이 Person *이다.
    int count;        // pVector 배열에 현재 삽입된 객체 포인터의 개수
    int allocSize;    // 할당 받의 pVector의 총 배열 원소의 개수

    void extend_capacity(int capacity);

public:
    //VectorPerson() : VectorPerson(DEFAULT_SIZE) {}
    VectorPerson(int capacity = DEFAULT_SIZE);
    VectorPerson(const VectorPerson& vp);
    ~VectorPerson();

    // 아래 긱 함수이름 뒤의 const는 그 함수가 클래스 멤버 변수들을 수정하지 않고 읽기만 한다는 의미임
    // pVector[index]의 포인터 값을 반환
    Person* at(int index) const { return pVector[index]; }

    // 할당 받의 pVector의 총 배열 원소의 개수를 반환
    int     capacity()    const { return allocSize; }

    // pVector 배열에 현재 삽입된 객체 포인터의 개수를 0으로 설정
    void    clear()             { count = 0; }

    // 현재 삽입된 객체 포인터가 하나도 없으면 true, 있으면 false
    bool    empty()       const { return count == 0; }

    // 현재 삽입된 객체 포인터의 개수를 반환
    int     size()        const { return count; }

    // pVector 배열에 마지막 삽입된 원소 뒤에 새로운 원소 p를 삽입하고 현재 삽입된 객체 개수를 증가
    void    push_back(Person* p); /* TODO 문제 [4, 7] */
    void erase(int index);
    void insert(int index, Person* p);

    Person* operator [] (int index)const;
    bool operator ! ();
    operator bool ();
    VectorPerson& operator = (const VectorPerson& vp);
    VectorPerson  operator + (const VectorPerson& vp);
    VectorPerson& operator += (const VectorPerson& vp);
};

// capacity는 할당해야 할 배열 원소의 개수
VectorPerson::VectorPerson(int capacity) : count{}, allocSize{ capacity } {
    // allocSize = capacity, count = 0; 초기화를 위 함수 서두(위 /* */ 주석 사이)에서 할 것
    // 함수 서두에서 초기화하는 방법은 Person 클래스 참고할 것
    //cout << "VectorPerson::VectorPerson(" << allocSize << ")" << endl;
    pVector = new Person*[allocSize]; // Person* 들의 배열을 위한 동적 메모리 할당
}

VectorPerson::VectorPerson(const VectorPerson& vp){
	cout << "VectorPerson::VectorPerson(const VectorPerson& vp)" << endl;
	this->allocSize = vp.allocSize;
	this->count = vp.count;

	pVector = new Person*[allocSize];

	for(int i=0; i<count; i++){
		pVector[i] = vp.pVector[i];
	}
}

VectorPerson::~VectorPerson() {
	delete [] pVector;
    //cout << "VectorPerson::~VectorPerson(): pVector deleted" << endl;
}

void VectorPerson::push_back(Person* p){
	if(count >= allocSize){
		extend_capacity(allocSize*2);
	}
	pVector[count++] = p;
}

void VectorPerson::extend_capacity(int capacity){
	Person **saved_persons = pVector;
	allocSize = capacity;
	pVector = new Person*[allocSize];

	for(int i=0; i<count; i++){
		pVector[i] = saved_persons[i];
	}

	delete [] saved_persons;
	//cout << "VectorPerson: capacity extended to " << allocSize << endl;
}

void VectorPerson::erase(int index) {
	if(index < 0 || index > count)
		return;
	for(int i=0; i<count; i++){
		pVector[index+i] = pVector[index+i+1];
	}
	count--;
}
void VectorPerson::insert(int index, Person* p) {
	if(count >= allocSize){
			extend_capacity(allocSize*2);
	}
	for(int i=count-1; i>=index; i--){
		pVector[i+1] = pVector[i];
	}
	pVector[index] = p;
	count++;
}

Person* VectorPerson::operator [] (int index)const{
	return pVector[index];
}

bool VectorPerson::operator ! (){
	return this->empty();
}

VectorPerson::operator bool (){
	return !(this->empty());
}

VectorPerson& VectorPerson::operator = (const VectorPerson& vp){
	if(vp.count > this->allocSize){
		delete [] pVector;
		this->allocSize = vp.allocSize;
		pVector = new Person*[allocSize];
		//cout << "VectorPerson::operator = : capacity extended to " << allocSize << endl;
	}
	this->count = vp.count;
	for(int i=0; i<count; i++){
		pVector[i] = vp.pVector[i];
	}
	return *this;
}

VectorPerson  VectorPerson::operator + (const VectorPerson& vp){
	VectorPerson tmp(this->count + vp.count);
	for(int i=0; i<this->count; i++){
		tmp.pVector[i] = this->pVector[i];
	}
	for(int i=0; i<vp.count; i++){
		tmp.pVector[this->count + i] = vp.pVector[i];
	}
	tmp.count = this->count + vp.count;
	return tmp;
}

VectorPerson& VectorPerson::operator += (const VectorPerson& vp){

	if(count + vp.count > allocSize){
		extend_capacity(this->allocSize+vp.allocSize);
	}
	for(int i=0; i<vp.count; i++){
		this->pVector[i+count] = vp.pVector[i];
	}
	count += vp.count;
	return *this;
}

/******************************************************************************
 * ch4_2: Factory class
 ******************************************************************************/

class Factory
{
public:
    // 동적으로 Person 객체를 할당 받은 후 키보드로부터 새로 추가하고자 하는 사람의
    // 인적정보를 읽어 들여 해당 객체에 저장한 후 그 객체의 포인터를 반환한다.
    static Person* inputPerson(istream& in) {
        Person* p = new Person();
        p->input(in);  // 멤버들을 입력 받음
        if (UI::checkDataFormatError(in)) { // 정수입력할 곳에 일반 문자 입력한 경우
            delete p;         // 할당한 메모리 반납
            return nullptr;   // nullptr 반환은 에러가 발생했다는 의미임
        }
        if (UI::echo_input) p->println(); // 자동체크에서 사용됨
        return p;
    }
};

/******************************************************************************
 * ch4_2: PersonManager class
 ******************************************************************************/

class PersonManager
{
    VectorPerson persons;
    //Factory factory;

    Person** array;     // ch7_3 추가
    int arrLen;         // ch7_3 추가
    int cpCount;        // ch7_3 추가

    void pushArray();   // ch7_3 추가
    void deleteElemets();
    void printNotice(const string& preMessage, const string& postMessage);
    Person* findByName(const string& name);

public:
    PersonManager(Person* array[], int len); // 6장에서 default 매개변수 설정
    ~PersonManager();
    void display();
    void append();
    void clear();
    void login();
    void run();
    void insert();
    void remove();
    void copyPersons();
    void reset();
};

PersonManager::PersonManager(Person* array[], int len):array{array}, arrLen{len}, cpCount{} {
    //cout << "PersonManager::PersonManager(array[], len)" << endl;
	pushArray();
	display();
}

PersonManager::~PersonManager() {
    deleteElemets();
}

void PersonManager::pushArray(){
    for(int i=0; i<arrLen; i++){
    	Person *n_person = new Person(*array[i]);
    	persons.push_back(array[i]->clone());
    }
}

void PersonManager::deleteElemets() {
    /* TODO 문제 [5] */
	for(int i=0; i<persons.size(); i++){
		delete persons[i];
	}
	persons.clear();
	cpCount = 0;
}

void PersonManager::display() { // Menu item 1
    int count = persons.size();
    cout << "display(): count " << count << endl;

    for (int i = 0; i < count; ++i) {
        cout << "[" << i << "] ";
        persons[i]->println();
    }

    //cout << "empty():" << persons.empty() << ", size():" << persons.size()<< ", capacity():" << persons.capacity() << endl;
}

void PersonManager::append() { // Menu item 2
	int count = UI::getPositiveInt("The number of persons to append? ");
	// to_string(10) 함수: 정수 10을 문자열 "10"으로 변환
	// stoi("10") 함수: 문자열 "10"을 정수 10으로 변환
	printNotice("Input "+to_string(count), ":");
	for (int i = 0; i < count; ++i) {
	    Person* p = Factory::inputPerson(cin); // 한 사람 정보 입력 받음
	    if (p) persons.push_back(p); // if (p != nullptr) 와 동일;
	    // 만약 p가 nullptr이면 이는 입력 시 에러가 발생한 것임
	    // (즉, 정수를 입력해야 하는 곳에 일반 문자를 입력한 경우)
	}
	display();
}

void PersonManager::clear() { // Menu item 3
    deleteElemets();
    display();
}
void PersonManager::login() { // Menu item 4
	string name = UI::getNext("user name: ");
	Person* p = findByName(name); // 해당 사람을 VectorPerson에서 찾는다.
	if (p == nullptr) return;     // 해당 사람 존재하지 않음
		string passwd = UI::getNextLine("password: ");
	if (passwd != p->getPasswd()) // 비번 불일치
	    cout << "WRONG password!!" << endl;
	else
	    CurrentUser(*p).run();
}

void PersonManager::run() {
    using func_t = void (PersonManager::*)();
    using PM = PersonManager; // 코딩 길이를 줄이기 위해
    func_t func_arr[] = {
        nullptr, &PM::display, &PM::append, &PM::clear, &PM::login, &PM::insert, &PM::remove
		,&PM::copyPersons, &PM::reset
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 길이
    string menuStr =
        "====================== Person Management Menu ===================\n"
        "= 0.Exit 1.Display 2.Append 3.Clear 4.Login(CurrentUser, ch6)   =\n"
        "= 5.Insert(6_2) 6.Delete(6_2) 7.CopyPersons(7_3) 8.Reset(7_3)   =\n"
        "=================================================================\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}

void PersonManager::printNotice(const string& preMessage, const string& postMessage) {
    cout << preMessage;
    cout << " [person information] ";
    cout << postMessage << endl;
}

Person* PersonManager::findByName(const string& name) {
    for(int i=0; i<persons.size(); i++){
    	if(name == persons[i]->getName()){
    		return persons[i];
    	}

    }
    cout << name + ": NOT found" << endl;
    return nullptr;
}

void PersonManager::insert() { // Menu item 5
	int index;
	if(persons.empty())
		index = 0;
	else
		index = UI::getIndex("Index to insert in front? ", persons.size() + 1);
	printNotice("Input", "to insert:");
	Person* p = Factory::inputPerson(cin);
	if (p == nullptr) return;
	persons.insert(index, p);
	display();
}

void PersonManager::remove() { // Menu item 6
	if(persons.empty()){
		cout << "No entry to remove" << endl;
		return;
	}
	int index = UI::getIndex("Index to delete? ", persons.size());
	delete persons[index];
	persons.erase(index);
	display();
}

void PersonManager::copyPersons() { // Menu item 7
    cpCount++;
    for (unsigned i = 0, size = persons.size(); i < size; ++i) {
        Person *p = persons[i]->clone();
        string name = p->getName();
        for (int j = 0; j < cpCount; ++j)
            name = name[0] + name;  // 이름 변경
        p->setName(name);
        p->set(p->getId()+(20*cpCount));
        p->set(p->getWeight()+cpCount);
        if(cpCount %2)
        	p->set((!p->getMarried()));
        persons.push_back(p);
    }
    display();
}

void PersonManager::reset() { // Menu item 8
	deleteElemets();
	pushArray();
	display();
}

/******************************************************************************
 * ch3_2, 4_1, 4_2: MultiManager class
 ******************************************************************************/
class MultiManager
{
    static const int personCount = 5;
    Person persons[personCount] = {
        Person("p0", 10, 70.0, false, "Gwangju Nam-gu Bongseon-dong 21"),
        Person("p1", 11, 61.1, true,  "Jong-ro 1-gil, Jongno-gu, Seoul"),
        Person("p2", 12, 52.2, false, "1001, Jungang-daero, Yeonje-gu, Busan"),
        Person("p3", 13, 83.3, true,  "100 Dunsan-ro Seo-gu Daejeon"),
        Person("p4", 14, 64.4, false, "88 Gongpyeong-ro, Jung-gu, Daegu"),
    };
    // new를 이용해 동적으로 할당할 경우 소멸자 함수를 만들어 거기서 delete 해 주어야 함

    static const int allPersonCount = personCount;
    Person* allPersons[allPersonCount] = {
        &persons[0], &persons[1], &persons[2], &persons[3], &persons[4],
    };

    PersonManager personMng { allPersons, allPersonCount };
    // 위 문장은 PersonManager personMng(allPersons, allPersonCount);와 동일함

public:
    void run() {
        cout << "PersonManager::run() starts" << endl;
        personMng.run();
        cout << "PersonManager::run() returned" << endl;
    }
}; // ch3_2, 4_1, 4_2: MultiManager class

/******************************************************************************
 * ch3_1: Class And Object
 ******************************************************************************/

//Person gps("gps", 1000, 100, true, "gps adress");

class ClassAndObject
{
    void defualConstructor() { // Menu item 1
    	Person ps;    // Person::Person() 기본 생성자 및 소멸자 실행
    }

    void constructor() { // Menu item 2: 지역객체의 다양한 생성자 및 소멸자 실행
        Person ps1;
        Person ps2("ps2");
        Person ps3("ps3", 3, 70.3, true, "ps3 address");
    }

    void construcor_destructor_inner_inner() {
        cout << "\n--- construcor_destructor_inner_inner() begins ---" << endl;
        Person ps3("ps3");
        cout << "\n- if begins -" << endl;
        if (true) {
            Person ps4("ps4");
        }
        cout << "- if ends -\n" << endl;
        cout << "- temporary object begins -" << endl;
        Person("temp_ps_1"); // 임시객체(이름 없는 객체) 성성 및 소멸
        cout << endl;
        Person("temp_ps_2").setName("TEMP_PS_2"); // 임시객체 생성,
                                                  // setName() 호출, 임시객체 소멸
        cout << "- temporary object ends -\n" << endl;
        Person ps5("ps5");
    }

    void construcor_destructor_inner() {
        cout << "\n--- construcor_destructor_inner() begins ---" << endl;
        Person ps2("ps2");
        construcor_destructor_inner_inner();
        cout << "--- construcor_destructor_inner_inner() returned ---\n" << endl;
        Person ps6("ps6");
    }

    void construcorDestructor() { // Menu item 3
        Person ps1("ps1");
        construcor_destructor_inner();
        cout << "--- construcor_destructor_inner() returned ---\n" << endl;
    }

    void global_static_local_objects_inner() {
        cout << "\n--- global_static_local_objects_inner() begins ---" << endl;
        //static Person sps("sps", 2000, 200, false, "sps adress");
    }

    void globalStaticLocalObjects() { // Menu item 4
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
        global_static_local_objects_inner();
        cout << "--- global_static_local_objects_inner() returned ---" << endl;
    }

    class Init1 { // ch6_2 추가
        Person p;
        int i, j;
        double d;
        char name[5];
    public:
        void print() {
            // d = i = j = 0;
            cout << "Init1 i: " << i << ", j: " << j <<
                    ", d: " << d << ", name: " << name << endl;
        }
    };

    // 기본 생성자가 있지만 아무것도 실행하지 않는다.
    // 이럴 경우 객체 멤버들(여기선 p)은 자동으로 기본 생성자가 실행되어 초기화된다.
    // 하지만 기본 데이타 타입 변수(i, j, d)들은 자동으로 초기화되지 않는다.
    // 따라서 필요한 경우 기본 데이타 타입 변수들은 생성자 내에서 반드시 초기화 해 주어야 한다.
    class Init2 {
        Person p;
        int i, j;
        double d;
    public:
        Init2() { i = 6; j = 6; }
        void print() {
            cout << "Init2 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    // 기본 생성자가 있지만 아무것도 실행하지 않는다.
    // 그러나 멤버 변수 선언 시에 멤버 p와 i처럼 선언과 동시에 초기화를 할 수 있다.
    // 멤버를 초기화하는 한 방법이지만 추천하고 싶은 방법은 아니다.
    // (일부 컴파일러는 이를 지원하지 않을 수 있는데 그럴경우 class Init4처럼 수정하라.)
    class Init3 {
        Person p { "p-Init3" };
        // Person p("p-Init3");와 동일한 기능이나 이렇게 표현하면 컴파일 에러가 발생할 것이다.
        // 즉, 함수 리턴 타입이 Person이고 함수 이름 p, 매개변수가 "p-Init3"인 새로운
        // [함수 선언]으로 컴파일러가 오해하여 에러 메시지(매개변수가 잘못되었다는)를 출력한다.
        // 컴파일러는 함수 선언인지 객체변수 선언인지 구분할 수 없기 때문이다.
        // 그래서 { }를 사용한다. { }는 객체 변수 선언이며 생성자 함수 인자를 의미한다.
        int i {3}, j;  // i {3}는 i = 3으로 표현해도 됨; 그러나 i(3)은 에러
        double d;      // i는 초기화되지만 j, d는 초기화되지 않음
    public:
        Init3() { j = 6; d = 0; }
        void print() {
            cout << "Init3 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    // 생성자의 서두에서 멤버 초기화(p{"p-Init4-head"})가 있을 경우 멤버 변수 선언 때 즉,
    // Person p는 초기화(생성자 실행 X)하지 않고 생성자의 서두에서 멤버 p와 i를 초기화 한다.
    // 이처럼 생성자 서두에서 멤버를 초기화하는 것이 일반적인 방법이다.
    class Init4 {
        Person p;
        int i, j;
        double d;
    public:
        Init4(): p{"p-Init4-head"}, i{4} { j = 6; d = 0; }
         // 위 함수 서두에서는 p("p-Init4-head") 로 초기화해도 됨; 그러나 i = 4는 안됨
        void print() {
            cout << "Init4 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    // 멤버 선언 때도 초기화하고, 생성자 서두에서도 초기화를 하면 생성자가 두번 실행될까?
    // 정답은 생성자 서두에 있는 멤버 초기화만 한번 실행된다. 멤버 선언 때의 초기화는 무시된다.
    class Init5 {
        Person p { "p-Init5" };
        int i{4}, j;
        double d;
    public:
        Init5(): p{ "p-Init5-head" }, i{5} { j = 6; d = 0; }
        void print() {
            cout << "Init5 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    // 멤버 선언과 생성자 서두에서 객체를 초기화 하지 않으면 객체 p의 기본 생성자가 자동으로 무조건 실행된다.
    // 생성자 함수 본체에서는 객체 p의 생성자를 호출할 수는 없고 set() 함수를 호출하여 초기화해야 한다.
    // 그래서 생성자 Init6()의 셍성자 본체 { } 에서 p.set()을 호출하면 객체 p는 두번 초기화되는 것이다.
    //----------------------------------------------------------------------------
    // 중요: 결국 객체 멤버(p)는 생성자의 서두에서 초기화하는 것이 가장 좋으며,
    //      기본 데이타 타입(int, double 등)의 경우 생성자 본체 또는 서두에서 초기화해도 상관없다.
    //      어차피 멤버 변수 선언 때 자동으로 초기화되지 않으니까.
    class Init6 {
        Person p;
        int i, j;
        double d;
    public:
        // 여기서는 p.set(...) 대신 편의상 p.setName(...)을 호출했다.
        Init6() { i = j = 6; d = 0; p.setName("p-Init6-body"); p.println(); }
        void print() {
            cout << "Init6 i: " << i << ", j: " << j << ", d: " << d << endl;
        }
    };

    void memberInitialization() { // Menu item 5
        int i = 0, i2 = i; i = i2; // 의미 없는 문장이지만, 삭제하지 말 것

        // 임시객체 생성 후 print()를 호출하고 바로 소멸된다.
        Init1().print(); cout << endl;
        Init2().print(); cout << endl;
        Init3().print(); cout << endl;
        Init4().print(); cout << endl;
        Init5().print(); cout << endl;
        Init6().print();
    }

    class Parameter {
    public:
        // 아래 각 함수 선언에서 const가 있는 매개변수는 해당 함수에서 객체 p를 수정하지 않는다는 의미이고,
        // const가 없는 매개변수는 해당 함수에서 객체 p를 수정할 수 있다는 의미임
        // 함수 호출한 곳에서 함수의 실행 결과를 매개변수를 통해 넘겨 받아야 하는 경우는 const가 없어야 함
        void normalValue(Person p)           { cout << "normalValue(Person p)" << endl; }
        void constValue(const Person p)      { cout << "constValue(const Person p)" << endl; }
        void normalReference(Person& p)      { cout << "normalReference(Person& p)" << endl; }
        void constReference(const Person& p) { cout << "constReference(const Person& p)" << endl; }

        void printStr(string& s)             { cout << "printStr(string& s): " << s << endl; }
        void printConstStr(const string& s)  { cout << "printConstStr(const string& s): " << s << endl; }
        void printPerson(const Person& p) { // const Person p로 선언해도 동일한 결과가 나옴
            cout << "printPerson(const Person& p)" << endl;
            // 위 const Person& p 선언의 의미: 이 함수에서 객체 p를 수정하지 않겠다는 의미임
            // 따라서 아래의 p.setName("const-value")처럼 p의 멤버함수를 호출하면 에러로 처리함;
            // 이유는 이 함수가 const 객체인 p의 멤버 name를 수정하기기 때문에.

            /* p.setName("const-value"); */ // 명백히 이름을 수정하는 것이므로 컴파일 에러 발생
            cout << p.getName() << " " << p.getId() << " " << p.getWeight() << " " <<p.getMarried() << " :" << ((p.getAddress()==nullptr)?"":p.getAddress()) <<":" << endl;

            // 주석을 풀 경우 발생하는 컴파일 에러는 매개변수가 const로 선언되었기 때문에
            // 발생하는 것이다. 컴파일러 입장에서는 위 멤버함수들이 p의 멤버를 수정하는지 아니면
            // 읽기만하는지 알 수 없기 때문에 컴파일 시 에러로 처리함;
        }
    };

    Parameter cp;

    void normalParameter() {
        cout << "normalParameter()" << endl;
        cout << "Person p1(\"p1-name\")" << endl;

        // 요점: 아래 Person p1처럼 p1이 일반적인 객체일 경우
        //      함수의 매개변수 타입에 상관없이 이 객체를 함수 인자로 넘겨 줄 수 있다.
        Person p1("p1-name");

        cp.normalValue(p1);     // 복사생성자 통해 매개변수 p에 p1을 복사해서 넘겨 줌
        cp.constValue(p1);      // 복사생성자 통해 매개변수 p에 p1을 복사해서 넘겨 줌
        cp.normalReference(p1); // 매개변수 p에 단순히 p1의 참조만 넘겨 줌
        cp.constReference(p1);  // 매개변수 p에 단순히 p1의 참조만 넘겨 줌
    }

    void constParameter() {
        cout << "constParameter()" << endl;
        cout << "const Person p2(\"const-p2-name\")" << endl;

        // 요점: p2처럼 상수(const) 객체일 경우
        //      매개변수 타입 선언에 따라 인자로 넘겨 줄 수 없는 함수가 있다.
        const Person p2("const-p2-name"); // p2는 상수이므로 수정되어서는 안된다.

        // 아래 인자 p2가 일반 매개변수 p에 복사되므로
        // 매개변수 p는 수정될지언정 원래 인자 p2는 수정되지 않는다. OK
        cp.normalValue(p2);
        // 아래 인자 p2가 상수 매개변수 p에 복사되므로 원래 인자 p2는 수정되지 않는다. OK
        cp.constValue(p2);
        //cp.normalReference(p2);
        // 위 함수의 일반 참조 매개변수 p는 p2와 메모리를 공유하므로 해당 함수에서 상수인 p2를
        // 수정할 가능성이 있다.(const로 선언되지 않았으므로)
        // 이런 경우 상수 객체 p2을 normalReference()의 인자로 줄 수 없다. 컴파일 에러.
        cp.constReference(p2); // 상수 참조 매개변수 p는 p2와 메모리를 공유하지만 p가 상수
        // 객체의 참조로 선언되어 있으므로 해당 함수에서 p2를 수정하지 않는다는 것을 보장한다. OK
    }

    void temporaryParameter() {
        cout << "temporaryParameter()" << endl;

        // 요점: 아래의 Person("Person-name")는 임시객체가 생성되며,
        //      이 임시객체는 컴파일러에 의해 const로 취급된다.
        //      따라서 이 임시객체는 위 [문제 10]의 const p2와 동일하게 취급된다.

        cp.normalValue(Person("Person-name"));       // 불필요한 객체 복사 일어남
        cp.constValue(Person("Person-name"));        // 불필요한 객체 복사 일어남
        //cp.normalReference(Person("Person-name")); // 컴파일 에러 발생
        cp.constReference(Person("Person-name"));    // 임시 객체 참조만 넘어감

        // 결론: 일반적으로 객체는 함수의 매개변수로 value로 복사해서 넘기지 않고 객체의 참조를 넘긴다.
        //      이유는 객체의 크기가 커지면 복사 오버헤드가 발생하기 때문이다.
        //      그런데 함수의 매개변수가 const가 아닌 일반 참조 변수로 선언된 경우
        //      그 함수에서 이 참조변수를 통해 원본 객체를 수정할 수 있기 때문에
        //      const p2 또는 위 임시객체(const 취급)와 같은 객체들을 함수 인자로 넘길 수 없다.
        //      따라서 [만약 함수 내에서 매개변수인 객체를 수정하지 않는다면]
        //      일반 & 매개변수로 선언하기 보다는 const &로 습관적으로 선언하는 것이 유리하다.
        //      (이렇게 선언하면 위 cp.constReference()처럼
        //       임시객체의 참조를 함수의 매개변수로 바로 넘길 수 있다.)
    }

    void stringParameter() {
        cout << "stringParameter()" << endl;

        string s("name1"); // string s = "name1"; 과 동일

        cp.printStr(s);
        cp.printConstStr(s);
        // 아래는 임시 string 객체 생성 (임시객체는 항상 const): 컴파일 에러
        //cp.printStr(string("name"));
        cp.printConstStr(string("name2")); // const 임시 객체 생성
        // 아래 "name"은 자동으로 임시 string("name") 객체 생성: 컴파일 에러
        //cp.printStr("name");
        cp.printConstStr("name3"); // const 임시 객체 생성
        // 결론: 함수의 매개변수로 "name3"처럼 문자열을 직접 넘겨 주고 싶으면
        //      함수 매개변수를 const string& 으로 선언해야 한다. string&로 선언시 에러.
        //      함수 내에서 매개변수 객체를 수정하지 않을 경우 습관적으로 항상 이렇게 선언하라.
        // 매개변수를 const string으로 선언해도 되지만 이 경우 문자열 전체가 복사되므로 비효율적임
    }

    void parameters() { // Menu item 6
        normalParameter();
        constParameter(); cout << endl;
        temporaryParameter(); cout << endl;
        stringParameter(); cout << endl;
        cp.printPerson(Person("name", 10, 77.7, true, "address"));
        // 임시 Person 객체의 참조 전달 (임시 객체는 항상 const)
    }


public:
    // 사용자가 선택한 메뉴 항목을 실행하는 멤버 함수(func_arr[menuItem]에 등록된 함수)를 호출
    void run() {
    	using CO = ClassAndObject;
        // ClassAndObject의 멤버 함수에 대한 포인터 타입인 새로운 데이타 타입 func_t를 정의함
        using func_t = void (ClassAndObject::*)();
        // 위 using 문은 ClassAndObject 클래스의 멤버 함수(리턴 타입이 void 이면서 매개변수가 없는)에
        // 대한 포인터 타입을 앞으로는 간단히 func_t로 사용하겠다는 의미이다.

        // ClassAndObject의 멤버 함수 포인터들의 배열
        // 나중에 호출하기 위해 멤버 함수의 이름을 미리 배열에 저장(등록)
        //     함수 이름이 곧 함수에 대한 포인터임: 즉, 함수의 첫번째 명령어의 주소를 저장함
        // 등록된 이 멤버 함수들은 나중에 run()에서 호출됨
        //     (즉, 함수 주소로 jump 해 가서 함수를 실행함)

        func_t func_arr[] = { // 메뉴항목을 실행하는 멤버 함수를 배열에 미리 저장(등록)해 둠
            nullptr, &CO::defualConstructor, &CO::constructor,
            &CO::construcorDestructor, &CO::globalStaticLocalObjects, &CO::memberInitialization,
			&CO::parameters
        };
        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
        // func_arr[]의 원소의 개수 = 배열 전체 크기 / 한 배열 원소의 크기

        // 화면에 보여 줄 메뉴
        string menuStr =
            "+++++++++++ Person Class And Object Menu ++++++++++++\n"
            "+ 0.Exit 1.DefualConstructor 2.Constructor          +\n"
            "+ 3.ConstrucorDestructor 4.GlobalStaticLocalObjects +\n"
            "+ 5.MemberInitialization 6.constParameter           +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount); // 메뉴 번호 입력 받음
            if (menuItem == 0) return;
            (this->*func_arr[menuItem])(); // 선택된 메뉴 항목을 실행할 멤버 함수를 호출함
            /* 위 문장은 다음을 간단히 한 것이다. 앞으로 계속 나올테니 잘 이해하기 바란다.
               func_t f = func_arr[menuItem];// 배열에 저장된 멤버 함수 포인터
               (this->*f)();                 // 멤버함수 포인터를 이용하여 해당 함수를 호출함
            */
        }
    }
}; // ch3_1: class ClassAndObject

/******************************************************************************
 * ch5_1: Reference and CopyConstructor
 ******************************************************************************/
class CopyConstructor
{
    Person u;
    Person backup;

public:
    // u는 일반 생성자, backup은 복사생성자를 이용하여 멤버를 초기화
    CopyConstructor(): u("u", 1, 70, true, "Gwangju"), backup(u) { }

    void explicitCopyConstructor() { // Menu item 1
        cout << "u: "; u.println();

        //TODO: Person형의 객체 p를 선언하되 복사생성자를 사용하여 u을 복사하여 초기화하라.
        Person p(u);
        //TODO: 실행결과를 참고하여 지역 객체 p의 멤버 값들을 변경하라.
        p.set("p", 2, 80, false, "Seoul");
        cout << "u: "; u.println();
        cout << "p: "; p.println();
        // 함수 리턴 시 객체 p의 소멸자가 실행됨
    }

    void referenceVariable() { // Menu item 2
    	cout << "p: ";
    	Person p(u);

    	//TODO: 지역 변수 p와 객체를 공유하는 Person형의 참조 변수 r을 선언하고 초기화하라.
    	Person &r = p;
    	cout << "p: "; p.println();         // r은 참조이고 u와 동일한 객체를 공유하므로
    	cout << "r: "; r.println();         // 두 출력물은 동일한 객체를 출력함

    	//TODO: 실행결과를 참고하여 참조 변수 r의 멤버 값들을 변경하라.
    	r.set("r", 2, 80, false, "Seoul");
    	cout << "p: "; p.println();
    	cout << "r: "; r.println();

    	//TODO: 실행결과를 참고하여 지역 객체 p의 멤버 값들을 변경하라.
    	p.set("p", 1, 70, true, "Gwangju");
    	cout << "p: "; p.println();
    	cout << "r: "; r.println();
    // r은 객체 p를 공유하는 참조이므로 함수 리턴 시 소멸자가 실행되지 않음
    }

    // 매개변수 a는 함수호출시 복사 생성자에 의해 복사되어 초기화됨; call by value로 매개변수를 선언하라.
    void function_argument( Person a/* TODO: 매개변수 a 선언; [교재 예제 5-12] 참조 */ ) { // Menu item 3-1
        cout << "a: "; a.println();
        cout << "a.setName(a)" << endl;
        a.setName("a");
        cout << "a: "; a.println();
    }

    Person return_member_object() { // Menu item 3-2
        //TODO: u 객체를 반환함 (여기서는 임식 객체에 복사됨); [교재 예제 5-12] 참조
    	return u;
    }

    void implicitCopyConstructor() { // Menu item 3
        cout << "u: "; u.println();
        cout << "\nimplicit copy constructor 1: operator =" << endl;
        cout << "Person p = u" << endl;
        cout << "p: ";

        //TODO: 새로운 Person 객체 p를 선언하고 객체 u를 p에 대입하여 초기화하라.(묵시적 복사생성자를 호출) [교재 예제 5-12] 참조
        Person p = u;
        cout << "p.setName(p)" << endl;
        p.setName("p");
        cout << "p: "; p.println();

        cout << "\nimplicit copy constructor 2: function argument" << endl;
        cout << "call function_argument(u)" << endl;

        // 묵시적으로 복사 생성자를 호출하여 함수 인자를 복사하여 함수의 매개변수 a에 넘김
        function_argument(u);
        cout << "function_argument(u) returned" << endl;

        cout << "\nimplicit copy constructor 3: return object" << endl;
        cout << "call return_member_object().println()" << endl;
        return_member_object().println();
          // return_member_object()의 리턴 값을 복사생성자에 의해 임시객체(이름 없는 지역변수)에 복사하고
          // 그 임시 객체의 println()을 호출하여 객체를 출력한다.
          // 출력 후 더 이상 그 임시 객체가 필요 없기 때문에 소멸자를 호출하여 바로 임시 객체를 소멸시킴
        cout << "return_member_object() returned" << endl;
    }

    Person return_local_object() { // Menu item 4-1
        Person pL("pL", 0, 70, true, "Gwangju Nam-gu");
        cout << "return_local_object() returns pL" << endl;
        return pL;
        // 정석대로 하면 리턴하기 전에 복사생성자를 호출하여 지역 객체 pL를 복사해 준 후
        // 리턴 직전에 pL를 소멸해야 한다.
        // 그러나 컴파일러는 효율적인 실행을 위해 복사생성자와 소멸자를 호출하지 않고
        // 함수가 리턴한 후 return_local_object().println() 호출 시
        // 함수의 지역 객체 pL의 메모리를 그대로 재사용한다. (소멸되지 않았으므로)
        // println() 실행 후 더 이상 객체가 필요 없으면 그제서야 소멸자를 호출하여 소멸시킴
    }

    Person return_temporary_object() { // Menu item 4-2
        cout << "return_temporary_object() returns Person(pT, 0, 70, true, Gwangju Nam-gu)" << endl;
        return Person("pT", 0, 70, true, "Gwangju Nam-gu"); // 임시 객체를 리턴함
        // return {"p", 0, 70, true, "Gwangju Nam-gu"}; // 위 문장과 동일한 기능임
        // 위 문장은 컴파일러가 함수의 리턴 타입을 참고하여
        //   Person("p", 0, 70, true, "Gwangju Nam-gu")으로 자동 처리함
    }

    void temporaryObject() { // Menu item 4
        cout << "temporary object 1: Person(p0, 10, 70, true, Gwangju)" << endl;
        // 임시객체 생성 방법: 클래스이름(생성자 인자들)
        // 생성자 호출된 후 아래 문장이 끝나면 바로 소멸자가 호출됨
        // 주요: 임시 객체가 포함된 해당 문장의 실행이 종료되면 임시 객체는 소멸됨
        Person("p0", 10, 70, true, "Gwangju");

        cout << "\ntemporary object 2: Person(p1, 11, 60, false, Seoul).println()" << endl;
        // 임시객체: 생성자 호출, println() 호출, 소멸자 호출
        Person("p1", 11, 60, false, "Seoul").println();

        cout << "\nreturn_member_object().println()" << endl;
        return_member_object().println(); // 복사 생성자 활용
        cout << "return_member_object() returned" << endl;

        cout << "\nreturn_local_object().println()" << endl;
        return_local_object().println(); // 복사 생성자 사용하지 않음
        cout << "return_local_object() returned" << endl;

        cout << "\nPerson pL = return_local_object()" << endl;
        Person pL = return_local_object(); // 복사 생성자 활용
        cout << "return_local_object() returned" << endl;
        pL.println();

        cout << "\nreturn_temporary_object().println()" << endl;
        return_temporary_object().println();  // 생성자 활용
        cout << "return_temporary_object() returned" << endl;

        cout << "\nPerson pT = return_temporary_object()" << endl;
        Person pT = return_temporary_object();  // 생성자 활용
        cout << "return_temporary_object() returned" << endl;
        pT.println();
    }

    // TODO: 아래 함수 매개변수를 call by value가 되게 Person의 객체 p로 선언하라.
    void call_by_value( Person p ) { // Menu item 5-1: call by value: 복사생성자에 의해 복사됨
        cout << "p: "; p.println();
        cout << "u: "; u.println();
        cout << "p.set(p, 2, 80, false, Seoul)" << endl;
        p.set("p", 2, 80, false, "Seoul");
        cout << "p: "; p.println();      // p는 u과 다른 메모리를 사용하는 객체임
        cout << "u: "; u.println(); // u은 영향을 받지 않음
        // 함수 리턴 시 매개변수 p 객체의 소멸자 함수가 호출됨
    }

        // TODO: 아래 함수 매개변수를 call by reference가 되게 Person의 참조변수 p로 선언하라.
    void call_by_reference( Person &p ) { // Menu item 5-2: call by reference
        cout << "p: "; p.println();   // p는 u의 참조이므로 u와 동일한 객체 메모리를 공유함
        cout << "u: "; u.println();
        cout << "p.set(p, 2, 80, false, Seoul)" << endl;
        p.set("p", 2, 80, false, "Seoul");
        cout << "p: "; p.println();   // p와 u은 동일한 객체 메모리를 공유하므로 항상 내용이 동일함
        cout << "u: "; u.println();
        //u = backup;       // u 값을 원래 값으로 복구
        u = backup;
        // 매개변수 p는 참조이므로 함수 리턴 시 소멸자가 호출되지 않음
    }

    // TODO: 아래 함수 매개변수를 call by address가 되게 Person에 대한 포인터 변수 p로 선언하라.
    void call_by_address( Person *p ) { // Menu item 5-3: call by address
        cout << "p: "; p->println();   // p는 u 메모리를 포인터하므로 동일한 내용이 출력됨
        cout << "u: "; u.println();
        cout << "p->set(p, 2, 80, false, Seoul)" << endl;
        p->set("p", 2, 80, false, "Seoul");
        cout << "p: "; p->println();   // p는 u 메모리를 포인터하므로 항상 동일한 내용이 출력됨
        cout << "u: "; u.println();
        //u = backup;       // u 값을 원래 값으로 복구
        u = backup;
        // 매개변수 p는 포인터이므로 함수 리턴 시 소멸자가 호출되지 않음
    }

    void functionParameterType() { // Menu item 5
        cout << "call_by_value" << endl;
        // 함수 호출 시 복사생성자를 통해 u 객체를 매개변수 p에 복사
        //TODO: call_by_value()을 호출하되 멤버 객체 u을 인자로 넘겨 주어라.
        call_by_value(u);
        cout << endl;

        cout << "call_by_reference" << endl;
        //TODO: call_by_reference()을 호출하되 멤버 객체 u을 인자로 넘겨 주어라.
        call_by_reference(u);
        cout << endl; // 단순히 u의 참조만 전달됨

        cout << "call_by_address" << endl;
        //TODO: call_by_address()을 호출하되 멤버 객체 u의 주소를 인자로 넘겨 주어라.
        call_by_address(&u);
        cout << endl; // 단순히 u의 주소값, 즉 포인터가 전달됨
    }
    // TODO: 아래 주석(/* */)을 지우고 Person 객체를 리턴하도록 함수의 리턴 타입을 선언하라.
    Person return_value() {                   // return value
        return u;
    }

    void return_value_test() { // Menu item 6-1
        cout << "--- return_value_test() ---" << endl;
        cout << "call return_value()" << endl;
        cout << "p: ";

        //TODO: Person형 객체 변수 p를 선언하고 return_value()의 리턴 값으로 초기화하라.
        Person p = return_value();
        cout << "return_value() returned" << endl;
        cout << "p: "; p.println();
        cout << "p.set(p, 2, 80, false, Seoul)" << endl;
        p.set("p", 2, 80, false, "Seoul");
        cout << "p: "; p.println();        // 두 객체의 name은 다른 값임
        cout << "u: "; u.println();
        // 함수 리턴 시 지역변수 p 객체의 소멸자 함수가 호출됨
    }

   // TODO: 아래 주석(/* */)을 지우고
   //       Person 객체의 참조를 리턴하도록 함수의 리턴 데이타 타입을 선언하라.
    Person& return_reference() {                  // return reference
        return u;
    }

    void return_reference_test() { // Menu item 6-2
        cout << "--- return_reference_test() ---" << endl;
        cout << "call return_reference()" << endl;
        cout << "p: ";

        //TODO: Person형 객체 변수 p를 선언하고 return_reference()의 리턴 값으로 초기화하라.
        Person p = return_reference();
        cout << "return_reference() returned" << endl;
        cout << "p.set(p, 2, 80, false, Seoul)" << endl;
        p.set("p", 2, 80, false, "Seoul");
        cout << "p: "; p.println();
        cout << "u: "; u.println();
        cout << endl;

        cout << "call return_reference()" << endl;

        //TODO: Person형 참조 변수 r를 선언하고 return_reference()의 리턴 값으로 초기화하라.

        Person& r = return_reference(); // r는 리턴된 u의 참조를 저장하고 있는 참조변수임
        cout << "return_reference() returned" << endl;
        cout << "u: "; u.println();
        cout << "r.set(p, 2, 80, false, Seoul)" << endl;
        r.set("r", 2, 80, false, "Seoul");
        cout << "r: "; r.println();
        cout << "u: "; u.println();
        //u = backup;
        u = backup;
        // 함수 리턴 시 지역 객체 p의 경우 소멸자 함수가 호출되지만
        //           참조 변수 r는 소멸자가 호출되지 않음
    }

    // TODO: 아래 주석을 지우고 함수의 리턴 값을 참조하여 함수의 리턴 데이타 타입을 적절히 선언하라.
    Person* return_address() {                  // return address
        return &u;
    }

    void return_address_test() { // Menu item 6-3
        cout << "--- return_address_test() ---" << endl;
        cout << "call return_address()" << endl;

        //TODO: Person형 포인터 변수 p를 선언하고 return_address()의 리턴 값으로 초기화하라.
        Person* p = return_address();
        cout << "return_address() returned" << endl;
        cout << "p: "; p->println();
        cout << "u: "; u.println();
        cout << "p.set(p, 2, 80, false, Seoul)" << endl;
        p->set("p", 2, 80, false, "Seoul"); // p는 u 객체를 포인터하므로 u과 동일한 메모리를 공유함
        cout << "p: "; p->println();
        cout << "u: "; u.println();
        //u = backup;
        u = backup;
        // 함수 리턴 시 p는 포인터 변수이므로 소멸자가 호출되지 않음
    }

    void returnDataType() { // Menu item 6
        return_value_test();        cout << endl;
        return_reference_test();    cout << endl;
        return_address_test();
    }
    void inputPerson() { // Menu item 7
        cout << "u: "; u.println();
        while (!UI::inputPerson(u)) ;  // USER 11 88 false :DONG-GU, DAEGU:
        //backup = u;
        backup = u;
        cout << "u: "; u.println();
    }


    void run() {
        using CC = CopyConstructor;
    	using func_t = void (CopyConstructor::*)();
    	func_t func_arr[] = {
    	        nullptr, &CC::explicitCopyConstructor, &CC::referenceVariable, &CC::implicitCopyConstructor, &CC::temporaryObject, &CC::functionParameterType, &CC::returnDataType, &CC::inputPerson
    	};
    	int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 길이
        string menuStr =
            "+++++++++ Reference And Copy Constructor Menu ++++++++++\n"
            "+ 0.Exit 1.ExplicitCopyConstructor 2.ReferenceVariable +\n"
            "+ 3.ImplicitCopyConstructor 4.TemporaryObject          +\n"
            "+ 5.FunctionParameterType 6.FunctionReturnType         +\n"
            "+ 7.inputPerson                                        +\n"
            "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        // TODO 문제 [3]: while 문장 삽입하여 선택된 메뉴항목 실행하는 함수를 호출하라.
        while (true) {
        	int menuItem = UI::selectMenu(menuStr, menuCount);
        	if (menuItem == 0) return;
        	(this->*func_arr[menuItem])();
        }
  }
}; // ch5_1: Reference and CopyConstructor

/******************************************************************************
 * ch5_2: AllocatedMember, new을 이용한 동적 메모리 할당한 멤버 취급
 ******************************************************************************/
class AllocatedMember
{
    Person  u;
    Memo    memo;
    void set_print_address(Person& p, const char* address) {
        cout << "p.setAddress(" << (address? address : "") << ")" << endl;
        p.setAddress(address);
        p.println();
        cout << endl;
    }

    void changeAddress() { // Menu Item 1
        Person p("p", 1, 70, true, "Gwangju");
        set_print_address(p, "short address");
        set_print_address(p, "middle length Address, Seoul");
        set_print_address(p, "long length Address Seoul Mapo-gu Korea");
        set_print_address(p, u.getAddress());
    }

    void print_memo(Person& p) { // 객체 p의 메모 출력
        cout << "------ " << p.getName() << " memo ------" << endl;
        const char *pmemo = p.getMemo();
        cout << (pmemo? pmemo : ""); // 메모 출력; nullptr이면 "" 출력
        cout << "--------------------" << endl << endl;
    }

    void set_print_memo(Person& p, const char* memo) { // 객체 p에 메모 복사하고 출력
        cout << "p.setMemo(memo)" << endl;
        p.setMemo(memo);
        print_memo(p);
    }

    void changeMemo() { // Menu Item 2
        Person p("p", 1, 70, true, "Gwangju");
        set_print_memo(p, "short memo\n");
        set_print_memo(p, "middle long memo: The Last of the Mohicans\n");
        set_print_memo(p, u.getMemo());
    }

    void manageMemo() { // Menu item 3
        memo.c_str(u.getMemo());
        memo.run();
        cout << "\nmemo.run() returned" << endl;
        u.setMemo(memo.c_str());   // 메모 메뉴에서 새로 삽입한 메모를 u에 저장
        print_memo(u);
    }

    Person call_by_value_and_return_value(Person p) { // 복사생성자로 p 초기화
        cout << "p.setName(p)" << endl;
        p.setName("p");
        // 함수 리턴 전에 p를 p2에 복사해서 초기화(복사생성자)
        cout << "p2: ";
        return p; // 함수 리턴 시 p 소멸자 실행
    }

    void copyConstructor() { // Menu Item 4
        cout << "u: ";    u.println();
        print_memo(u);

        cout << "Person p1(u)" << endl;
        cout << "p1: ";
        Person p1(u); // 명시적 복사생성자로 p1 초기화
        p1.setName("p1");
        p1.println();
        print_memo(p1);

        cout << "Person p2 = call_by_value_and_return_value(p1)" << endl;
        // 묵시적으로 두번의 복사생성자 실행: 함수 인자를 넘길 때, 함수 리턴 값을 p2에 복사할 때
        cout << "p: ";
        Person p2 = call_by_value_and_return_value(p1);
        cout << "call_by_value_and_return_value(p1) returned\n" << endl;
        cout << "p2.setName(p2)" << endl;
        p2.setName("p2");
        p2.println();
        print_memo(p2);
        cout << "copyConstructor() returns" << endl;
        // 함수 리턴 시 지역객체 p1, p2 소멸자 실행됨
    }

    void nullptrMember() { // Menu Item 5
        u.println();
        print_memo(u);
        cout << "set address = memo_c_str = nullptr" << endl;
        u.setAddress(nullptr);
        u.setMemo(nullptr);
        u.println();
        print_memo(u);

        cout << "memo.c_str(u.getMemo())" << endl;
        memo.c_str(u.getMemo()); // u.getMemo() == nullptr이므로 memo의 mStr은 ""이다.
        memo.displayMemo();

        cout << endl << "u.setMemo(memo.c_str())" << endl;
        u.setMemo(memo.c_str()); // memo.get_c_str() == nullptr 이므로
                                      // u의 memo_c_str은 nullptr로 설정
        print_memo(u);
    }

    void inputPerson() { // Menu item 6
        cout << "u: "; u.println();
        while (!UI::inputPerson(u)) ;  // USER 11 88 false :DONG-GU, DAEGU:
        cout << "u: "; u.println();
    }

public:
    AllocatedMember():
        u("u", 1, 70, true, "NAMDAEMUN-RO 123, JONGNO-GU, SEOUL, KOREA") {
        u.setMemo("It is believed that the Aborigines of the American continent\n");
    }

    void run() {
        using AM = AllocatedMember;

    	using func_t = void (AllocatedMember::*)();
    	func_t func_arr[] = {
    		nullptr, &AM::changeAddress, &AM::changeMemo, &AM::manageMemo, &AM::copyConstructor, &AM::nullptrMember, &AM::inputPerson
    	};
    	int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 길이
        string menuStr =
            "++++++++++++++++ Allocated Member Menu ++++++++++++++++\n"
            "+ 0.Exit 1.ChangeAddress 2.ChangeMemo 3.UsingMemoMenu +\n"
            "+ 4.CopyConstructor 5.NullptrMember 6.inputPerson     +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
        while (true) {
        	int menuItem = UI::selectMenu(menuStr, menuCount);
        	if (menuItem == 0) return;
        	(this->*func_arr[menuItem])();
        }
  }
}; // ch5_2: AllocatedMember

/******************************************************************************
 * ch7_2: VectorOperator class
 ******************************************************************************/
class VectorOperator
{
    Person pa[5] = {
        Person("Hong ", 0, 72.1, true, nullptr),
        Person("Mong ", 1, 65.4, true, nullptr),
        Person("Choon", 3, 56.7, true, nullptr),
        Person("Soon ", 2, 87.6, true, nullptr),
        Person("Chung", 4, 67.8, true, nullptr),
    };
    int pa_len = sizeof(pa) / sizeof(pa[0]);

    VectorPerson pv1, pv2;

    void disp_vector(const VectorPerson& pv) {
        int count = pv.size();
        cout << "count " << count << endl;
        for (int i = 0; i < count; ++i) {
            cout << "[" << i << "] "; pv.at(i)->println();
        }
        cout << endl;
    }

    void operatorIndex() { // Memu item 1
        MultiManager().run();
        // display(), remove(), clear(), login()에서 [index] 연산자 사용
    }

    void operatorNot() { // Memu item 2
        VectorPerson pv;
        disp_vector(pv);

        // operator bool() 호출
        if (pv) cout << "if(pv): true" << endl;
        else    cout << "if(pv): false" << endl;
        cout << "operator bool(): " << (bool)pv << endl;

        // operator !() 호출
        if (!pv) cout << "if(!pv): true" << endl;
        else     cout << "if(!pv): false" << endl;
        cout << "operator !(): " << !pv << endl;

        pv.push_back(pa);
        disp_vector(pv);
        cout << "(pv? true: false) " << (pv? true: false) << endl;// operator bool() 호출
        pv.push_back(new Person("Chung", 2, 67.8, true,  nullptr));
        disp_vector(pv);

        // operator []
        cout << "pv[0]: "; pv[0]->println();
        cout << "delete pv[1];" << endl;
        delete pv[1];
        // pv[0]는 동적으로 할당받은 주소가 아니므로, 즉 배열 원소 pa[0]의 주소이므로 반납하지 않아도 됨
    }

    VectorPerson call_return_value(VectorPerson pv) {
        cout << "pv: "; disp_vector(pv);
        cout << "return pv1 " << endl;
        return pv1;
    }

    void copyConstructor() { // Memu item 3
        cout << "VectorPerson pv3 = pv2" << endl;
        VectorPerson pv3 = pv2;  // 묵시적 복사생성자 호출; VectorPerson pv3(pv2)와 동일
        cout << "pv3: "; disp_vector(pv3);
        pv3.erase(0);
        cout << "pv3.erase(0)" << endl;
        cout << "pv3: "; disp_vector(pv3);
        cout << "pv2: "; disp_vector(pv2);
        cout << "disp_vector(call_return_value(vp2))" << endl;
        // 아래 함수 호출에서 pv2 인자를 복사생성자를 이용하여 call_return_value()의
        // 매개변수 pv에 복사하고 함수에서 리턴되는 pv1 또한 복사생성자를 통해 임시객체에 복사된다.
        // 그 후 disp_vector()를 호출하여 리턴된 임시객체를 보여줌
        disp_vector(call_return_value(pv2)); // 임시객체와 아래 pv1의 출력이 같아야 함
        cout << "pv1: "; disp_vector(pv1);
    }

    void operatorAssign() { // Memu item 4
        cout << "VectorPerson pv3 = pv2" << endl;
        VectorPerson pv3 = pv2;
        cout << "pv3: "; disp_vector(pv3);
        cout << "pv3 = pv1" << endl;
        pv3 = pv1; // 대입 연산자
        cout << "pv3: "; disp_vector(pv3);
        cout << "repeat 9 times: pv3.push_back(pa+2)" << endl;
        for (int i = 0; i < 9; ++i) // 원소개수가 11개 이상이면 pv3 메모리가 확장되어야 함
            pv3.push_back(pa+2);
        cout << "pv3: "; disp_vector(pv3);
        VectorPerson pv4;
        cout << "pv4 = pv3" << endl;
        pv4 = pv3; // 대입 연산자: 원소개수가 11개 이상이면 pv4의 메모리가 확장되어야 함
        cout << "pv4: "; disp_vector(pv4);
    }

    void operatorAdd() { // Memu item 5
        VectorPerson pv3;
        cout << "pv3 = pv1 + pv2" << endl;
        pv3 = pv1 + pv2;
        cout << "pv3: "; disp_vector(pv3);
        cout << "pv3 = pv2 + pv2 + pv3" << endl;
        pv3 = pv2 + pv2 + pv3; // + 연산자: pv3의 메모리가 확장
        cout << "pv3: "; disp_vector(pv3);
    }

    void operatorAddAssign() { // Memu item 6
        cout << "VectorPerson pv4 = pv1: " << endl;
        VectorPerson pv4 = pv1;   // 묵시적 복사생성자 호출
        cout << "pv4: "; disp_vector(pv4);
        cout << "pv4 += pv2" << endl;
        pv4 += pv2; // += 연산자
        cout << "pv4: "; disp_vector(pv4);
        cout << "pv4 += pv2 + pv2" << endl;
        pv4 += pv2 + pv2;       // 원소개수가 11개 이상이면 메모리 확장해야 함
        cout << "pv4: "; disp_vector(pv4);
    }

public:
    VectorOperator() {
        int i;
        for (i = 0; i < 2; ++i)
            pv1.push_back(&pa[i]); // &pa[i] == &(pa[i])
        cout << "pv1: "; disp_vector(pv1);

        for ( ; i < pa_len; ++i)
            pv2.push_back(pa+i);     // pa+i == &pa[i]
        cout << "pv2: "; disp_vector(pv2);
    }

    void run() {
        using VO = VectorOperator;
    	using func_t = void (VectorOperator::*)();
    	func_t func_arr[] = {
    		nullptr, &VO::operatorIndex, &VO::operatorNot, &VO::copyConstructor, &VO::operatorAssign
			,&VO::operatorAdd, &VO::operatorAddAssign
    	};
    	int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 길이
        string menuStr =
            "+++++++++++++ Vector Operator Overload ++++++++++++++\n"
            "+ 0.Exit 1.operator[] 2.operator! 3.CopyConstructor +\n"
            "+ 4.operator= 5.operator+ 6.operator=+              +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
        	int menuItem = UI::selectMenu(menuStr, menuCount);
        	if (menuItem == 0) return;
        	(this->*func_arr[menuItem])();
        }
    }

}; // ch7_2: VectorOperator class

/******************************************************************************
 * ch7_1: OperatorOverload class
 ******************************************************************************/
class OperatorOverload
{
    Person p;
    Memo   m;

    void disp_memo(const string& name, Memo& m) {
        cout << name << endl; m.displayMemo(); cout << endl;
    }

    void memoAdd() { // Memu item 1
        Memo m1(m);
        Memo m2("James Fenimore Cooper\n");
        disp_memo("m1", m1);
        disp_memo("m2", m2);
        // operator +
        Memo m3 = m1 + m2;
        disp_memo("m3 = m1 + m2", m3);
        // operator +=
        m3 += Memo("1st const added memo line.\n");
        disp_memo("m3 += Memo(...)", m3);
        // operator +
        m3 = m3 + m2 + Memo("2nd const added memo line.\n");
        disp_memo("m3 = m3 + m2 + Memo(...)", m3);
    }

    void personEqual() { // Memu item 2
        Person p1(p), p2(p);
        cout << "p1: "; p1.println();
        cout << "p2: "; p2.println();
        cout << "p1 == p2 : " << (p1 == p2) << endl;
        p2.set(2);  // p2는 p1과 비교해 이름은 같고 id는 다름
        cout << "p2: "; p2.println();
        cout << "p1 == p2 : " << (p1 == p2) << endl;
        p2.set(1); p2.setName("user"); // p2는 p1과 비교해 이름은 다르고 id는 동일
        cout << "p2: "; p2.println();
        cout << "p1 == p2 : " << (p1 == p2) << endl;
    }

    void personAdd() { // Memu item 3
        Person p1(p); p1.setAddress("");
        cout << "p1:  "; p1.println();
        cout << "p2 = p1 + 5.0" << endl;
        Person p2 = p1 + 5.0;
        cout << "p2:  "; p2.println();
        cout << "(p2 + 10.0).println()" << endl;
        cout << "tmp: "; (p2 + 10.0).println();
        cout << "p2:  "; p2.println();
        cout << "p3 = 15.0 + p1" << endl;
        Person p3 = 15.0 + p1;
        cout << "p3:  "; p3.println();
        cout << "(20.0 + p3).println()" << endl;
        cout << "tmp: "; (20.0 + p3).println();
        cout << "p3:  "; p3.println();
    }

    void personAssign() { // Memu item 4
        cout << "p:  "; p.println();
        Person p2; // 기본 생성자에 의해 초기화
        cout << "p2 = p" << endl;
        p2 = p;
        cout << "p2: "; p2.println();
        Person p3("Hong",  0, 72.1, false, "Gwangju Nam-gu Bongseon-dong 21");
        cout << "p3: "; p3.println();
        cout << "p3 = 20.0 + p2 + 30.5" << endl;
        p3 = 20.0 + p2 + 30.5;
        cout << "p3: "; p3.println();
        cout << "p == p3 : " << (p == p3) << endl;
    }

    void personIncrement() { // Memu item 5
        Person p1(p); p1.setAddress("");
        cout << "p1  : "; p1.println();
        cout << "++p1: "; (++p1).println(); // operator ++()
        cout << "p1++: "; (p1++).println(); // operator ++(int)
        cout << "p1  : "; p1.println();
        cout << "p2 = p1++" << endl;
        Person p2 = p1++; // copy constructor
        cout << "p2  : "; p2.println();
        cout << "p1  : "; p1.println();
        cout << "p2 = (++p1)++" << endl;
        p2 = (++p1)++;
        cout << "p2  : "; p2.println();
        cout << "p1  : "; p1.println();
        cout << "p2 = ++(p1++)" << endl;
        p2 = ++(p1++);
        cout << "p2  : "; p2.println();
        cout << "p1  : "; p1.println();
        cout << "p2 = ++p1++" << endl;
        p2 = ++p1++;
        cout << "p2  : "; p2.println();
        cout << "p1  : "; p1.println();
        cout << "(p2 = 2.0 + ++p1++ + 3.0) == p : "
             << ((p2 = 2.0 + ++p1++ + 3.0) == p) << endl;
        cout << "p2  : "; p2.println();
        cout << "p1  : "; p1.println();
    }

    void personShift() { // Memu item 6
        Person p1(p); p1.setAddress("");
        cout << "p1: "; p1.println();
        cout << "p1 << \"p1\" << 11" << endl;
        // operator << (const char *), operator << (int)
        p1 << "p1";
        p1 << 11;
        cout << "p1: "; p1.println();

        cout << "p1 << name << 12" << endl;
        string name("p1-12");
        // operator << (const string&), operator << (int)
        p1 << name << 12;
        cout << "p1: "; p1.println();

        cout << "p1 >> name >> id >> c_name" << endl;
        int id;
        char c_name[40];
        name = "";
        // operator >> (string), operator >> (int), operator >> (char *)
        p1 >> name >> id >> c_name;
        cout << "name:" << name << ", id:" << id << ", c_name:" << c_name << endl;

        cout << "(p1 << \"p\" << 1) == p : " << ((p1 << "p" << 1) == p) << endl;
        cout << "p1: "; p1.println();
        cout << "p : "; p.println();
    }

    void print_name_id(string name, int id) {
        cout << "print_name_id() name:" << name << ", id:" << id << endl;
    }

    void typeConversion() { // Memu item 7
        Person p1(p), p2(p);
        p1 << "Hong" << 1; // 이름과 id를 객체 p1에 설정함
        p2 << "Dong" << 2;
        cout << "p1: "; p1.println();
        cout << "p2: "; p2.println();

        // 아래 문장은 int id = (int)p1; 과 동일; 컴파일러가 id와 동일한 타입인 int로
        // 타입을 변경하는 operator int()를 자동으로 호출하여 리턴 값을 id에 저장
        int id = p1;

        // 아래 문장은 (string)p1 와 동일; 컴파일러가 name과 동일한 타입인 string로
        // 타입을 변경하는 operator string()를 자동으로 호출하여 리턴 값을 name에 저장
        string name = p1;

        cout << "p1 name:" << name << ", id:" << id << endl;
        p2 >> id >> name; // 객체 p2로부터 id와 이름을 얻어옴
        cout << "p2 name:" << name << ", id:" << id << endl;

        // 아래 함수호출 시 컴파일러가 알아서 자동으로 함수 매개변수와 동일한 타입으로 변환해 주는
        // operator string()과  operator int()를 호출하여 리턴 값을 함수인자로 넘겨 줌
        print_name_id(p1, p1);
        print_name_id(p2, p2);

        // 아래 문장은 사용자가 출력할 데이타 타입을 정확히 지정해 주면
        // 컴파일러가 상응하는 operator string()과  operator int()를 호출한다.
        cout << "p2 name:" << (string)p2 << ", id:" << (int)p2 << endl;
        cout << "p1+p2 name:" << (string)p1+name << ", id:" << (int)p1+id << endl;
    }

    void currentUser() { // Memu item 8
        CurrentUser(p).run();
        m.c_str(p.getMemo());
        cout << "p: "; p.println();
        m.displayMemo();
    }

    void vectorOOL() { // Memu item 9
        VectorOperator().run();
    }

public:
    OperatorOverload():
        p("p",  1, 65.4, true,  "Jong-ro 1-gil, Jongno-gu, Seoul"),
        m("The Last of the Mohicans\n") {
    }

    void run() {
        using OOL = OperatorOverload;

        // TODO: func_t, func_arr[], menuCount 선언
    	using func_t = void (OperatorOverload::*)();
    	func_t func_arr[] = {
    			nullptr, &OOL::memoAdd, &OOL::personEqual, &OOL::personAdd, &OOL::personAssign
				,&OOL::personIncrement, &OOL::personShift, &OOL::typeConversion, &OOL::currentUser
				,&OOL::vectorOOL
    	};
    	int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 길이

        string menuStr =
            "+++++++++++++++++++ Operator Overload +++++++++++++++++\n"
            "+ 0.Exit 1.MemoAdd 2.Equal 3.Add 4.Assign 5.Increment +\n"
            "+ 6.Shift 7.TypeConversion 8.CurrentUser 9.VectorOOL  +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
        	int menuItem = UI::selectMenu(menuStr, menuCount);
        	if (menuItem == 0) return;
        	(this->*func_arr[menuItem])();
        }
    }

}; // ch7_1: OperatorOverload class

/******************************************************************************
 * ch8_1, ch8_2: Inheritance class
 ******************************************************************************/
class Inheritance
{
    Student s { "s1", 1, 65.4, true,  "Jongno-gu Seoul", "Physics", 3.8, 1 };
    Worker  w { "w1", 3, 33.3, false, "Kangnam-gu Seoul",  "Samsung", "Director" };

    void student() {
        Student s1(s); // 복사생성자 호출
        cout << "s1: "; s1.println();
        Student s2 = s1; // 묵시적 복사생성자 호출
        cout << "s2: "; s2.println();
        cout << "s1 == s2 : " << (s1 == s2) << endl;
        s2.setName("s2");
        s2.set(s1.getId()+1);
        s2.set(s1.getWeight() * 1.1);
        s2.set(!s1.getMarried());
        s2.setDepartment(s1.getDepartment()+"-Electronics");
        s2.setGPA(s1.getGPA()+1);
        s2.setYear(s1.getYear()+1);
        cout << "s2: "; s2.println();;
        cout << "s1 == s2 : " << (s1 == s2) << endl;
        s2.whatAreYouDoing();
        Student *s3 = (Student *)s1.clone();  // 다운 캐스팅
        cout << "s3: "; s3->println();
        cout << "s1: "; s1.println();;
        cout << "s3 == s1 : " << (*s3 == s1) << endl;
        delete s3;
        cout << "input student: ";
        s2.input(cin); // s1 1 66.6 false :Kangnam-gu Seoul: Physics 3.0 1
        if (UI::echo_input) s2.println(); // 자동체크에서 사용됨
        cout << "s2: "; s2.println();
        cout << "s1: "; s1.println();;
        cout << "s2 == s1 : " << (s2 == s1) << endl;
    }

    void worker() {
        Worker w1(w); // 복사생성자
        cout << "w1: "; w1.println();
        Worker w2 = w1;
        cout << "w2: "; w2.println();
        cout << "w1 == w2 : " << (w1 == w2) << endl;

        w2.setName("w2");
        w2.set(w1.getId()+1);
        w2.set(w1.getWeight() * 1.1);
        w2.set(!w1.getMarried());
        w2.setCompany(w1.getCompany()+"-Hyundai");
        w2.setPosition(w1.getPosition()+"-Manager");
        cout << "w2: "; w2.println();;
        cout << "w1 == w2 : " << (w1 == w2) << endl;

        w2.whatAreYouDoing();

        Worker *w3 = (Worker *)w1.clone();
        cout << "w3: "; w3->println();
        cout << "w1: "; w1.println();;
        cout << "w3 == w1 : " << (*w3 == w1) << endl;
        delete w3;

        cout << "input worker: ";
        w2.input(cin); // w1 3 44.4 true :Jongno-gu Seoul: Samsung Director
        if (UI::echo_input) w2.println(); // 자동체크에서 사용됨
        cout << "w2: "; w2.println();
        cout << "w1: "; w1.println();;
        cout << "w2 == w1 : " << (w2 == w1) << endl;
    }

public:
    void run() {
        using func_t = void (Inheritance::*)();
        func_t func_arr[] = {
            nullptr, &Inheritance::student, &Inheritance::worker,
        };
        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] 길이
        string menuStr =
            "+++++++++++++ Inheritance Menu ++++++++++++++\n"
            "+ 0.Exit 1.Student 2.Worker                 +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) return;
            (this->*func_arr[menuItem])();
        }
    }

};
// ch8_1, ch8_2: Inheritance class

/******************************************************************************
 * Main Menu
 ******************************************************************************/

class MainMenu
{
public:
    void run() {
        int menuCount = 7; // 상수 정의
        string menuStr =
        		"******************************* Main Menu *********************************\n"
        		"* 0.Exit 1.PersonManager(ch3_2, 4, 6, 7_2, 8)                             *\n"
        		"* 2.Class:Object(ch3_1) 3.CopyConstructor(ch5_1) 4.AllocatedMember(ch5_2) *\n"
        		"* 5.OperatorOverload(ch7_1) 6.Inheritance(ch8)                            *\n"
        		"***************************************************************************\n";
        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;

            switch(menuItem) {
            case 1: MultiManager().run();             break;
            case 2: ClassAndObject().run();           break;
            case 3: CopyConstructor().run();		  break;
            case 4: AllocatedMember().run();		  break;
            case 5: OperatorOverload().run();		  break;
            case 6: Inheritance().run();			  break;
            }
        }
        cout << "Good bye!!" << endl;
    }
}; // class MainMenu

/******************************************************************************
 * run() 함수: 메인 메뉴를 시작함
 ******************************************************************************/
void run() {
    MainMenu().run();
    // MainMenu 타입의 이름 없는 임시객체를 생성한 후
    // 그 객체의 run() 멤버함수를 호출함; run()에서 리턴한 후에는 임시객체가 자동 소멸됨
    // 즉, 위 문장은 아래 두 문장과 동일한 기능임
    // MainMenu mm;
    // mm.run();
}

/******************************************************************************
 * Program Test: Automatic Error Check
 ******************************************************************************/
#if AUTOMATIC_ERROR_CHECK
#include "check_error.h"
#endif

/******************************************************************************
 * main() 함수
 ******************************************************************************/
int main() {
    cout << boolalpha;  // 11장에서 배움; bool 타입 값을 0, 1 대신 true, false로 출력하도록 설정
    cin >> boolalpha;   // bool 타입 값을 0, 1 대신 true, false로 입력 받도록 설정

#if AUTOMATIC_ERROR_CHECK
    evaluate(true);   // 각 문제에 대해 단순히 O, X만 확인하고자 할 때는 false
#else
    run();
#endif
}
