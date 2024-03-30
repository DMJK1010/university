/*
 * CH4_3: ch4_3.cpp
 *
 *  Created on: 2024. 3.26.(17:25) ������Ʈ ����
 *      Author: Junha Kim
 *
 *
 *  + class Memo �߰�: string Ŭ������ ����Լ� �� operator Ȱ���
 *  + Person::memo_c_str[] ��� �� set, get �Լ� �߰�
 *  + CurrentUser::memo ���, �Լ� �� �޴� �׸� �߰�
 *  + PersonManager::~PersonManager()���� display() ���� ����
 */

#include <iostream>
#include <cstring>

using namespace std;

#define AUTOMATIC_ERROR_CHECK false // false: �ڵ� ���� üũ, true: Ű���忡�� ���� �Է��Ͽ� ���α׷� ����

/******************************************************************************
 * Person class
 ******************************************************************************/

class Person
{
    string name;       	    // �̸�
    string passwd;          // ���
    int    id;              // Identifier
    double weight;          // ü��
    bool   married;         // ��ȥ����
    char   address[40];     // �ּ�

protected:
    void inputMembers(istream* in);
    void printMembers(ostream* out);

public:
    Person() : Person("") {}
    Person(const string name) : Person(name, 0, 0, 0, "") {}
    Person(const string name, int id, double weight, bool married, const char *address);
    ~Person();

    void set(const string name, int id, double weight, bool married, const char *address);
    void setName(const string name)       { this->name = name; }
    void setPasswd(const string passwd)   { this->passwd = passwd; }
    void setId(int id)                    { this->id = id; }
    void setWeight(double weight)        { this->weight = weight; }
    void setMarried(bool married)        { this->married = married; }
    void setAddress(const char* address)  { strcpy(this->address, address); }

    string 		getName()    { return name; }
    string      getPasswd()  { return passwd; }
    int         getId()      { return id; }
    double      getWeight()  { return weight; }  // ���� ��
    bool        getMarried() { return married; }  // ���� ������
    const char* getAddress() { return address; } // �����Ͻÿ�.

    void input(istream* pin)  { inputMembers(pin); } // ch3_2���� �߰�
    void print(ostream* pout) { printMembers(pout); }
    void println()            { print(&cout); cout << endl; }
    void whatAreYouDoing();                          // ch3_2���� �߰�
    bool isSame(const string name, int pid);         // ch3_2���� �߰�
};

Person::Person(const string name, int id, double weight, bool married, const char *address) : name(name), id{id}, weight{weight}, married{married} {
    // ������ �� ����� �ʱ�ȭ�ϴ� {}�� �� �Ű����� ���� ��ü�� �����ϴ� ����� �����ϴ� ���̴�. ��,
    // this->id=id, this->weight=weight, this->married=married�� �����ϴ�.
    // ���⼭ this�� �ش� ��ü�� �������ϴ� ������ �����̸�, (���� �忡�� ����� ������)
    // this->id�� �ش� ��ü�� ��� id�� ��Ī�ϸ� =�� �������� id�� �Լ��� �Ű������̴�.
    // ���� ������ �����ϴ� ���� ��ó�� �ϸ� ������ name[], address[]�� ���� �迭 ���� �Լ�
    // ȣ�� �Ǵ� �ٸ� �Լ��� ȣ���� ���� ������ �Լ��� ��ü { } ������ ȣ���ؾ� �Ѵ�.

	setAddress(address);
    cout << "Person::Person(...):"; println();
}

Person::~Person() {
    cout << "Person::~Person():"; println();
}

void Person::printMembers(ostream* pout)   {
	*pout<<name <<" "<<id<<" "<<weight<<" "<<married<<" :"<<address<<": ";
}

void Person::set(const string name, int id, double weight, bool married, const char *address) {
    this->name = name;
    this->id = id;
    this->weight = weight;
    this->married = married;
    setAddress(address);  //address�� �����ؾ��ϴ���?==================================================?
}

void Person::inputMembers(istream* pin)   {
    *pin>>name>>id>>weight>>married;
    if (!(*pin)) return;
    pin->getline(address, sizeof(address), ':');
    pin->getline(address, sizeof(address), ':');
}

void Person::whatAreYouDoing() {
	cout<<name<<" is taking a rest.";
}

bool Person::isSame(const string name, int pid) {
    if((this->name == name) && (id == pid))
        return true;
    else
        return false;
}

/******************************************************************************
 * User Interface
 ******************************************************************************/
// �⺻���� �Է°� ���õ� ���� �Լ����� UI��� �̸����� ���ο� ������

namespace UI {

bool echo_input = false;
string line, emptyLine;

// �Է¿��� ���� ��� �Ϲ� ���ڰ� �ԷµǾ����� üũ�ϰ� ���� �߻��� ���� �޽��� ���
bool checkInputError(istream* pin, const string msg) {
    if (!(*pin)) { // ������ �߻��ߴٸ�
        cout << msg;  // ���� �޽����� ���
        pin->clear(); // ���� �߻� ���������� ������; �׷��� ���� ���忡�� ���� �� ����
        getline(*pin, emptyLine); // ������ �߻��� �� ��ü�� �о� �����͸� ����
        return true;
    }
    return false;
}

// ������ �Ǽ��� �Է��ؾ� �ϴ� ���� �Ϲ� ���ڿ��� �Է��� ����� ���� üũ
bool checkDataFormatError(istream* pin) {
    return checkInputError(pin, "Input-data format MISMATCHED\n");
}

// �� ����� ���� ��, �� ��� �����͸� ���������� �Է� �޾� p�� �����ϰ�
// �Է� �� �Է� �����Ϳ� ������ �ִ��� Ȯ���ϰ� ������ ���� �� ���� �޽����� ����Ѵ�.
bool inputPerson(Person* p) {
    cout << "input person information:" << endl;
    p->input(&cin);
    if (checkDataFormatError(&cin)) return false;
    if (echo_input) p->println(); // �ڵ�üũ���� ����
    return true;
}

// �Է���ġ���� �ϳ��� �ܾ�� ������ ���ڿ��� �Է� ����
string getNext(const string msg) {
    cout << msg; // �Է¿� �޽����� ���
    cin >> line; // �ϳ��� �ܾ �о� ����
    if (echo_input) cout << line << endl; // �ڵ�üũ �� ��µ�
    getline(cin, emptyLine); // �Է¹��� �� �ܾ� �� �� ���� ������ ����Ÿ(��������)�� �о ����
    return line;             // ������ ���⼭ [����]�� �������� ������
}                            // ������ getNextLine()���� ���͸� �о� ���� �� �ֱ� ������

// �Է���ġ���� �� ���� �Է� ����
string getNextLine(const string msg) {
    cout << msg; // �Է¿� �޽����� ���
    getline(cin, line); // �� ���� �о� ����
    if (echo_input) cout << line << endl; // �ڵ�üũ �� ��µ�
    return line;
}

// �ϳ��� ������ �Է� ����; ������ �ƴ� �ƴ� ���ڿ� �Է½� ���� �޽��� ��� �� ���Է� ����
int getInt(const string msg) {
    for (int value; true; ) {
        cout << msg;
        cin >> value;
        if (echo_input) cout << value << endl; // �ڵ�üũ �� ��µ�
        if (checkInputError(&cin, "Input an INTEGER.\n"))
            continue;
        getline(cin, emptyLine); // skip [enter] after the number
        return value;
    }
}

// �ϳ��� ���� ������ �Է� ����; ���� �Է½� ���� �޽��� ��� �� ���Է� ����
int getPositiveInt(const string msg) {
    int value;
    while ((value = getInt(msg)) < 0)
        cout << "Input a positive INTEGER." << endl;
    return value;
}

// 0~(size-1)������ ���õ� �޴� �׸� �Ǵ� ����Ʈ�� �׸��� �ε��� ���� ������
// �������� �ʴ� �޴��׸��� ������ ��� ���� ���
int getIndex(const string msg, int size) {
    while (true) {
        int index = getPositiveInt(msg);
        if (0 <= index  && index < size) return index;
        cout << index << ": OUT of selection range(0 ~ "
             << size-1 << ")" << endl;
    }
}

// ����ڿ��� �޴��� �����ְ� ����ڰ� ������ �޴��׸��� �ε����� ������
int selectMenu(const string menuStr, int menuItemCount) {
    cout << endl << menuStr;
    return getIndex("Menu item number? ", menuItemCount);
}

} // namespace UI

/******************************************************************************
 * ch4_3: string and Memo class
 ******************************************************************************/

class Memo
{
    string mStr; // �޸� ������ �δ� ���ڿ�

    string get_next_line(size_t* ppos);
    bool find_line(int line, size_t* start, size_t* next);
    size_t find_last_line();

public:
    string getNext(size_t* ppos);
    void displayMemo();
    const char *get_c_str();
    void set_c_str(const char *c_str);
    void findString();
    void compareWord();
    void dispByLine();
    void deleteLine();
    void replaceLine();
    void scrollUp();
    void scrollDown();
    void inputMemo();
    void run();
};

void Memo::displayMemo() { // Menu item 1
    cout << "------- Memo -------" << endl;
    cout << mStr;
    if (mStr.length() > 0 && mStr[mStr.length()-1] != '\n')
        cout << endl; // �޸� ���� �ٹٲٱ� ���ڰ� ���� ��� ���
    cout << "--------------------" << endl;
}

// �Ʒ� R"( �� )"�� �� ���̿� �ִ� ��� ���ڸ� �ϳ��� ���ڿ��� ����϶�� �ǹ��̴�.
// ���� ��� �� ���̿� �ִ� �ٹٲٱ� \n ���ڵ� ���ڿ��� �״�� ���Եȴ�.
// �̷� ����� ������� ������ ���� �࿡ ��ģ ���ڿ��� ������� ����������.
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

void Memo::run() {

    // TODO ���� [1]: func_arr[], menuCount ����
	using func_t = void (Memo::*)();
	func_t func_arr[] = {
	    nullptr, &Memo::displayMemo, &Memo::findString
	};
	int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] ����
    string menuStr =
        "++++++++++++++++++++++ Memo Management Menu +++++++++++++++++++++\n"
        "+ 0.Exit 1.DisplayMemo 2.FindString 3.CompareWord 4.DispByLine  +\n"
        "+ 5.DeleteLine 6.RepaceLine 7.ScrollUp 8.ScrollDown 9.InputMemo +\n"
        "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    if (mStr == "") mStr = memoData;// ��� mStr�� ����� ��� �� memoData�� �ʱ�ȭ�Ѵ�.

    // TODO ���� [1]: while ���� �����Ͽ� ���õ� �޴��׸� �����ϴ� �Լ� ȣ��
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
    string Data(memoData);

    /*
    TODO: for ���� ����Ͽ� �ݺ������� string::find() �Լ��� ȣ���Ͽ� ã�� �ܾ���
          ���� ȸ��(count)�� �����. find()�� ���� ã�� ��ġ���� len�� ���ϸ�
          ã�� �ܾ��� �� ��ġ�� �Ǵµ� �̰��� ���� ���� ã�� ������ ��ġ�̴�.
          string::find()�� ���� ���� string::npos�� ������
          �ܾ ã�� ���ߴٴ� ���� �ǹ��Ѵ�. �� ã�� ������ �ݺ� �����ϸ� ��.
          ã�� ���� ��ġ �Ǵ� ���� ���� Ÿ���� size_t�� ����϶�.
    */
    for(int i=0; i<(int)Data.length(); i++){
    	if(Data.find(word, pos) != string::npos){
    		count++;
    		pos = Data.find(word, pos) + len;
    	}
    }
    cout << "Found count: " << count << endl;
}

/******************************************************************************
 * ch3_2: CurrentUser class
 ******************************************************************************/

class CurrentUser
{
    Person* pUser;
    Memo    memo; // ch4_3���� �߰�

public:
    CurrentUser(Person* pUser): pUser(pUser) { }
    void display();
    void setter();
    void getter();
    void set();
    void whatAreYouDoing();
    void isSame();
    void inputPerson();
    void changePasswd();
    void manageMemo();
    void run();
};

void CurrentUser::display() { // Menu item 1
    pUser->println();
}

void CurrentUser::getter() { // Menu item 2
    cout << "name:" << pUser->getName() << ", id:" << pUser->getId() << ", weight:" << pUser->getWeight() << ", married:" << pUser->getMarried() << ", address:" << pUser->getAddress() << endl;
}

void CurrentUser::setter() { // Menu item 3
	Person* pp = new Person("pp"); // pp ���� �Ҵ�
    pp->setName(pp->getName());
    pp->setId(pUser->getId());
    pp->setWeight(pUser->getWeight());
    pp->setMarried(pUser->getMarried());
    pp->setAddress(pUser->getAddress());
    cout << "pp->setMembers():"; pp->println();
    delete pp; // pp�� ������ �ϴ� ��ü�� �޸𸮸� ��ȯ
}

void CurrentUser::set() { // Menu item 4
	Person* pp = new Person("pp"); // pp ���� �Ҵ�
    pp->set(pp->getName(), pUser->getId(), pUser->getWeight(), !pUser->getMarried(), pUser->getAddress());
    cout << "pp->set():"; pp->println();
    delete pp; // pp ��ȯ
}

void CurrentUser::whatAreYouDoing() {  // Menu item 5
	pUser->whatAreYouDoing();
}

void CurrentUser::isSame() { // Menu item 6
    pUser->println();
    cout << "isSame(\"user\", 1): " << pUser->isSame("user", 1) << endl;
}

void CurrentUser::inputPerson() { // Menu item 7
    if (UI::inputPerson(pUser)) // GilDong 1 70.5 true :Jongno-gu, Seoul:
        display();              // user 1 71.1 true :Gwangju Nam-ro 21:
}

void CurrentUser::changePasswd() {
	string passwd = UI::getNext("New password: ");
	pUser->setPasswd(passwd);
    cout << "Password changed" << endl;
}

void CurrentUser::manageMemo() { // Menu item 9
    memo.run();
}

void CurrentUser::run() {
    using func_t = void (CurrentUser::*)();
    using CU = CurrentUser;
    func_t func_arr[] = {
        nullptr, &CU::display, &CU::getter, &CU::setter, &CU::set, &CU::whatAreYouDoing, &CU::isSame, &CU::inputPerson, &CU::changePasswd, &CU::manageMemo
    };

    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] �迭�� ����
    string menuStr =
            "+++++++++++++++++++++ Current User Menu ++++++++++++++++++++++++\n"
            "+ 0.Logout 1.Display 2.Getter 3.Setter 4.Set 5.WhatAreYouDoing +\n"
            "+ 6.IsSame 7.InputPerson 8.ChangePasswd(4_2)                   +\n"
    		"+ 6.IsSame 7.InputPerson 8.ChangePasswd(4_2) 9.ManageMemo(4_3) +\n"
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
// VectorPerson�� n���� Person * �����͸� pVector[] �迭�� ��� �����ϴ� Ŭ�����̴�.
// �ʿ信 ���� �����͸� ����, ����, �߰� ���� �� �� �ִ�.
// �����ϴ� ������ ������ ���� �������� pVector[] �迭�� ���� �޸𸮸� �ڵ� Ȯ���ϱ⵵ �Ѵ�.

class VectorPerson
{
    static const int DEFAULT_SIZE = 10; // pVector�� ����Ʈ �迭 ���� ����

    Person **pVector; // Person *pVector[]; Person�� ���� �����͵��� �迭, �迭�� ����� ���� Person *�̴�.
    int count;        // pVector �迭�� ���� ���Ե� ��ü �������� ����
    int allocSize;    // �Ҵ� ���� pVector�� �� �迭 ������ ����

    void extend_capacity(); /* TODO ���� [7] */

public:
    VectorPerson() : VectorPerson(DEFAULT_SIZE) {}
    VectorPerson(int capacity);
    ~VectorPerson();

    // �Ʒ� �� �Լ��̸� ���� const�� �� �Լ��� Ŭ���� ��� �������� �������� �ʰ� �б⸸ �Ѵٴ� �ǹ���
    // pVector[index]�� ������ ���� ��ȯ
    Person* at(int index) const { return pVector[index]; }

    // �Ҵ� ���� pVector�� �� �迭 ������ ������ ��ȯ
    int     capacity()    const { return allocSize; }

    // pVector �迭�� ���� ���Ե� ��ü �������� ������ 0���� ����
    void    clear()             { count = 0; }

    // ���� ���Ե� ��ü �����Ͱ� �ϳ��� ������ true, ������ false
    bool    empty()       const { return count == 0; }

    // ���� ���Ե� ��ü �������� ������ ��ȯ
    int     size()        const { return count; }

    // pVector �迭�� ������ ���Ե� ���� �ڿ� ���ο� ���� p�� �����ϰ� ���� ���Ե� ��ü ������ ����
    void    push_back(Person* p); /* TODO ���� [4, 7] */
};

// capacity�� �Ҵ��ؾ� �� �迭 ������ ����
VectorPerson::VectorPerson(int capacity) : count{}, allocSize{ capacity } {
    // allocSize = capacity, count = 0; �ʱ�ȭ�� �� �Լ� ����(�� /* */ �ּ� ����)���� �� ��
    // �Լ� ���ο��� �ʱ�ȭ�ϴ� ����� Person Ŭ���� ������ ��
    cout << "VectorPerson::VectorPerson(" << allocSize << ")" << endl;
    pVector = new Person*[allocSize]; // Person* ���� �迭�� ���� ���� �޸� �Ҵ�
}

VectorPerson::~VectorPerson() {
	delete [] pVector;
    cout << "VectorPerson::~VectorPerson(): pVector deleted" << endl;
}

void VectorPerson::push_back(Person* p){
	if(count >= allocSize){
		extend_capacity();
	}
	pVector[count++] = p;
}

void VectorPerson::extend_capacity(){
	Person **saved_persons = pVector;
	allocSize *= 2;
	pVector = new Person*[allocSize];

	for(int i=0; i<count; i++){
		pVector[i] = saved_persons[i];
	}

	delete [] saved_persons;
	cout << "VectorPerson: capacity extended to " << allocSize << endl;
}

/******************************************************************************
 * ch4_2: Factory class
 ******************************************************************************/

class Factory
{
public:
    // �������� Person ��ü�� �Ҵ� ���� �� Ű����κ��� ���� �߰��ϰ��� �ϴ� �����
    // ���������� �о� �鿩 �ش� ��ü�� ������ �� �� ��ü�� �����͸� ��ȯ�Ѵ�.
    Person* inputPerson(istream* in) {
        Person* p = new Person();
        p->input(in);  // ������� �Է� ����
        if (UI::checkDataFormatError(in)) { // �����Է��� ���� �Ϲ� ���� �Է��� ���
            delete p;         // �Ҵ��� �޸� �ݳ�
            return nullptr;   // nullptr ��ȯ�� ������ �߻��ߴٴ� �ǹ���
        }
        if (UI::echo_input) p->println(); // �ڵ�üũ���� ����
        return p;
    }
};

/******************************************************************************
 * ch4_2: PersonManager class
 ******************************************************************************/

class PersonManager
{
    VectorPerson persons;
    Factory factory;

    void deleteElemets();
    void printNotice(const string preMessage, const string postMessage);
    Person* findByName(const string name);

public:
    PersonManager(Person* array[], int len); // 6�忡�� default �Ű����� ����
    ~PersonManager();
    void display();
    void append();
    void clear();
    void login();
    void run();
};

PersonManager::PersonManager(Person* array[], int len) {
    cout << "PersonManager::PersonManager(array[], len)" << endl;
    for(int i=0; i<len; i++){
    	Person* s = array[i];
    	Person *n_person = new Person(s->getName(), s->getId(), s->getWeight(), s->getMarried(), s->getAddress());
    	persons.push_back(n_person);
    }
    display();
}

PersonManager::~PersonManager() {
    deleteElemets();
}

void PersonManager::deleteElemets() {
    /* TODO ���� [5] */
	for(int i=0; i<persons.size(); i++){
		delete persons.at(i);
	}
	persons.clear();
}

void PersonManager::display() { // Menu item 1
    int count = persons.size();
    cout << "display(): count " << count << endl;
    for (int i = 0; i < count; ++i) {
        cout << "[" << i << "] ";
        persons.at(i)->println();
    }
    cout << "empty():" << persons.empty() << ", size():" << persons.size()
         << ", capacity():" << persons.capacity() << endl;
}

void PersonManager::append() { // Menu item 2
	int count = UI::getPositiveInt("The number of persons to append? ");
	// to_string(10) �Լ�: ���� 10�� ���ڿ� "10"���� ��ȯ
	// stoi("10") �Լ�: ���ڿ� "10"�� ���� 10���� ��ȯ
	printNotice("Input "+to_string(count), ":");
	for (int i = 0; i < count; ++i) {
	    Person* p = factory.inputPerson(&cin); // �� ��� ���� �Է� ����
	    if (p) persons.push_back(p); // if (p != nullptr) �� ����;
	    // ���� p�� nullptr�̸� �̴� �Է� �� ������ �߻��� ����
	    // (��, ������ �Է��ؾ� �ϴ� ���� �Ϲ� ���ڸ� �Է��� ���)
	}
	display();
}

void PersonManager::clear() { // Menu item 3
    deleteElemets();
    display();
}
void PersonManager::login() { // Menu item 4
	string name = UI::getNext("user name: ");
	Person* p = findByName(name); // �ش� ����� VectorPerson���� ã�´�.
	if (p == nullptr) return;     // �ش� ��� �������� ����
		string passwd = UI::getNextLine("password: ");
	if (passwd != p->getPasswd()) // ��� ����ġ
	    cout << "WRONG password!!" << endl;
	else
	    CurrentUser(p).run();
}

void PersonManager::run() {
    using func_t = void (PersonManager::*)();
    using PM = PersonManager; // �ڵ� ���̸� ���̱� ����
    func_t func_arr[] = {
        nullptr, &PM::display, &PM::append, &PM::clear, &PM::login,
    };
    int menuCount = sizeof(func_arr) / sizeof(func_arr[0]); // func_arr[] ����
    string menuStr =
        "====================== Person Management Menu ===================\n"
        "= 0.Exit 1.Display 2.Append 3.Clear 4.Login(CurrentUser, ch4_2) =\n"
        "=================================================================\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) return;
        (this->*func_arr[menuItem])();
    }
}

void PersonManager::printNotice(const string preMessage, const string postMessage) {
    cout << preMessage;
    cout << " [person information] ";
    cout << postMessage << endl;
}

Person* PersonManager::findByName(const string name) {
    for(int i=0; i<persons.size(); i++){
    	if(name == persons.at(i)->getName()){
    		return persons.at(i);
    	}

    }
    cout << name + ": NOT found" << endl;
    return nullptr;
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
    // new�� �̿��� �������� �Ҵ��� ��� �Ҹ��� �Լ��� ����� �ű⼭ delete �� �־�� ��

    static const int allPersonCount = personCount;
    Person* allPersons[allPersonCount] = {
        &persons[0], &persons[1], &persons[2], &persons[3], &persons[4],
    };

    PersonManager personMng { allPersons, allPersonCount };
    // �� ������ PersonManager personMng(allPersons, allPersonCount);�� ������

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
    	Person ps;    // Person::Person() �⺻ ������ �� �Ҹ��� ����
    }

    void constructor() { // Menu item 2: ������ü�� �پ��� ������ �� �Ҹ��� ����
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
        Person("temp_ps_1"); // �ӽð�ü(�̸� ���� ��ü) ���� �� �Ҹ�
        cout << endl;
        Person("temp_ps_2").setName("TEMP_PS_2"); // �ӽð�ü ����,
                                                  // setName() ȣ��, �ӽð�ü �Ҹ�
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

public:
    // ����ڰ� ������ �޴� �׸��� �����ϴ� ��� �Լ�(func_arr[menuItem]�� ��ϵ� �Լ�)�� ȣ��
    void run() {
        // ClassAndObject�� ��� �Լ��� ���� ������ Ÿ���� ���ο� ����Ÿ Ÿ�� func_t�� ������
        using func_t = void (ClassAndObject::*)();
        // �� using ���� ClassAndObject Ŭ������ ��� �Լ�(���� Ÿ���� void �̸鼭 �Ű������� ����)��
        // ���� ������ Ÿ���� �����δ� ������ func_t�� ����ϰڴٴ� �ǹ��̴�.

        // ClassAndObject�� ��� �Լ� �����͵��� �迭
        // ���߿� ȣ���ϱ� ���� ��� �Լ��� �̸��� �̸� �迭�� ����(���)
        //     �Լ� �̸��� �� �Լ��� ���� ��������: ��, �Լ��� ù��° ��ɾ��� �ּҸ� ������
        // ��ϵ� �� ��� �Լ����� ���߿� run()���� ȣ���
        //     (��, �Լ� �ּҷ� jump �� ���� �Լ��� ������)

        func_t func_arr[] = { // �޴��׸��� �����ϴ� ��� �Լ��� �迭�� �̸� ����(���)�� ��
            nullptr, &ClassAndObject::defualConstructor, &ClassAndObject::constructor,
            &ClassAndObject::construcorDestructor, &ClassAndObject::globalStaticLocalObjects,
        };
        int menuCount = sizeof(func_arr) / sizeof(func_arr[0]);
        // func_arr[]�� ������ ���� = �迭 ��ü ũ�� / �� �迭 ������ ũ��

        // ȭ�鿡 ���� �� �޴�
        string menuStr =
            "+++++++++++ Person Class And Object Menu ++++++++++++\n"
            "+ 0.Exit 1.DefualConstructor 2.Constructor          +\n"
            "+ 3.ConstrucorDestructor 4.GlobalStaticLocalObjects +\n"
            "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount); // �޴� ��ȣ �Է� ����
            if (menuItem == 0) return;
            (this->*func_arr[menuItem])(); // ���õ� �޴� �׸��� ������ ��� �Լ��� ȣ����
            /* �� ������ ������ ������ �� ���̴�. ������ ��� �����״� �� �����ϱ� �ٶ���.
               func_t f = func_arr[menuItem];// �迭�� ����� ��� �Լ� ������
               (this->*f)();                 // ����Լ� �����͸� �̿��Ͽ� �ش� �Լ��� ȣ����
            */
        }
    }
}; // ch3_1: class ClassAndObject


/******************************************************************************
 * Main Menu
 ******************************************************************************/

class MainMenu
{
public:
    void run() {
        int menuCount = 3; // ��� ����
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.PersonManager(ch3_2, 4)                                        *\n"
"* 2.Class:Object(ch3_1)                                                   *\n"
"***************************************************************************\n";
        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;

            switch(menuItem) {
            case 1: MultiManager().run();             break;
            case 2: ClassAndObject().run();           break;
            }
        }
        cout << "Good bye!!" << endl;
    }
}; // class MainMenu

/******************************************************************************
 * run() �Լ�: ���� �޴��� ������
 ******************************************************************************/
void run() {
    //MainMenu().run();
	Memo().run();
    // MainMenu Ÿ���� �̸� ���� �ӽð�ü�� ������ ��
    // �� ��ü�� run() ����Լ��� ȣ����; run()���� ������ �Ŀ��� �ӽð�ü�� �ڵ� �Ҹ��
    // ��, �� ������ �Ʒ� �� ����� ������ �����
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
 * main() �Լ�
 ******************************************************************************/
int main() {
    cout << boolalpha;  // 11�忡�� ���; bool Ÿ�� ���� 0, 1 ��� true, false�� ����ϵ��� ����
    cin >> boolalpha;   // bool Ÿ�� ���� 0, 1 ��� true, false�� �Է� �޵��� ����

#if AUTOMATIC_ERROR_CHECK
    evaluate(true);   // �� ������ ���� �ܼ��� O, X�� Ȯ���ϰ��� �� ���� false
#else
    run();
#endif
}
