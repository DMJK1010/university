/*
 * CH2: ch2.cpp
 *
 *  Created on: 2024. 1.14.
 *      Author: Junha Kim
 *
 *  1) struct Person �߰�
 *  2) namespace UI�� �⺻���� �Է� �Լ� �߰�
 *  3) Person ��ü�� �����ϴ� �پ��� test �Լ���
 *
 */

#include <iostream>
#include <cstring>

using namespace std;

#define AUTOMATIC_ERROR_CHECK false // false: �ڵ� ���� üũ, true: Ű���忡�� ���� �Է��Ͽ� ���α׷� ����

struct Person {
    char   name[20];        // �̸�
    int    id;              // Identifier
    double weight;          // ü��
    bool   married;         // ��ȥ����
    char   address[50];     // �ּ�
};

void print(Person* p) {
    cout<<p->name <<" "<<p->id<<" "<<p->weight<<" "<<p->married<<" :"<<p->address<<": ";
}

void println(Person* p) {
    print(p);
    cout<<endl;
}

void input(Person* p) {
    cin>>p->name>>p->id>>p->weight>>p->married;
    if (!cin) return;
    cin.getline(p->address, sizeof(p->address), ':');
    cin.getline(p->address, sizeof(p->address), ':');
}

bool isSame(const Person* p, const char* pname, int pid) {
    if(strcmp(p->name, pname)==0 && (p->id == pid))
        return true;
    else
        return false;
}

void whatAreYouDoing(Person* p) {
    cout<<p->name<<" is taking a rest.";
}

void init(Person* p, const char *pname, int pid, double pweight, bool pmarried, const char *paddress) {
    strcpy(p->name,  pname);
    p->id = pid;
    p->weight = pweight;
    p->married = pmarried;
    strcpy(p->address, paddress);
    cout << "init("; print(p); cout << ")" << endl;
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
    input(p); // p-name 100 65 true :426 hakdong-ro, Gangnam-gu, Seoul:
    if (checkDataFormatError(&cin)) return false;
    if (echo_input) println(p); // �ڵ�üũ���� ����
    return true;
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
 * simple test
 ******************************************************************************/

Person p = { "Hong", 1, 61.1, true, "Seoul Jongno-gu Nam-ro 123" };

void printlnTest() { // Menu item 1
    Person p1 = {};
    println(&p1);
    Person p2 = { "LeeSoonShin", 0, 70.1, true, "Gangnam Seoul" };
    println(&p2);
    Person p3{ "Hong,gildong", 1, 60.2, false, "Jongno-gu, Busan" };
    println(&p3);
    println(&p);
}
void initTest() { // Menu item 2
    Person u1;
    init(&u1, "u1", 10, 60.0, false, "Jongno-gu, Seoul");
    Person u2;
    init(&u2, "u2", p.id, p.weight, p.married, p.address);
    println(&p);
}
void getter() { // Menu item 3
    cout<<"name:"<<p.name<<", id:"<<p.id<<", weight:"<<p.weight<<", married:"<<p.married<<", address:"<<p.address;
}
void setter() { // Menu item 4
    Person u;
    strcpy(u.name, "u");
    u.id = p.id;
    u.weight = p.weight;
    u.married = p.married;
    strcpy(u.address, p.address);
    //TODO: p�� weight, married, address ������ u�� �����ϴ� ����� �����϶�.

    println(&u);
}
void isSameTest() { // Menu item 5
    println(&p);
    Person u = { "Hong", 1, };
    cout << "p.isSame(): " << isSame(&p, u.name, u.id) << endl;
}
void whatAreYouDoingTest() {  // Menu item 6
    whatAreYouDoing(&p);
}
void noBoolAlphaOutput() { // Menu item 7
     // married ��� �� �Ǵ� bool ���� 1, 0�� ��µ�
    printlnTest();
    initTest();
    getter();
    setter();
    isSameTest();
    whatAreYouDoingTest();
}
void   boolAlphaOutput() { // Menu item 8
    cout << boolalpha;    // married ��� �� �Ǵ� bool ���� true, false�� ��µǵ��� ����
    noBoolAlphaOutput();
    cout << noboolalpha;  // ���� ���·� ������
}
void noBoolAlphaInputPerson() { // Menu item 9
    // married ��� �� �Ǵ� bool ���� 0 �Ǵ� 1�� �Է�
    // HongGilDong 0 71.5 1 :Gwangju Nam-gu Bongseon-dong 21:
    if (UI::inputPerson(&p)) // �Է½� ���� �Ǵ� �Ǽ� ���� �Ϲ� ���ڷ� �߸� �Է����� ���� ���
        println(&p);

}
void   boolAlphaInputPerson() { // Menu item 10
    cout << boolalpha;
    // �Ʒ��� married ��� �� �Ǵ� bool ���� true �Ǵ� false�� �Է¹޵��� ����
    cin  >> boolalpha;
    // �Ʒ� �Է� ������������ married ��� ���� 1�� �ƴ� true��
    // Hong 1 71.5 true :Gwangju Nam-gu Bongseon-dong 21:
    if (UI::inputPerson(&p))  // �Է½� ���� �Ǵ� �Ǽ� ���� �Ϲ� ���ڷ� �߸� �Է����� ���� ���
        println(&p);
    cin  >> noboolalpha; // ���� ���·� ������
    cout << noboolalpha; // ���� ���·� ������
}
void dataTypeSize() { // Menu item 11
     cout << "bool   size: " << sizeof(bool)   << endl;
    cout << "char   size: " << sizeof(char)   << endl;
    cout << "short  size: " << sizeof(short)  << endl;
    cout << "int    size: " << sizeof(int)    << endl;
    cout << "long   size: " << sizeof(long)   << endl;
    cout << "float  size: " << sizeof(float)  << endl;
    cout << "double size: " << sizeof(double) << endl;
    cout << "int*   size: " << sizeof(int*)   << endl;
}

/******************************************************************************
 * run() �Լ�
 ******************************************************************************/

void run() {
    int menuCount = 12; // ��� ����
    // ȭ�鿡 ���� �� �޴�
    string menuStr =
    "+++++++++++++++++++++ Person Structure Test Menu +++++++++++++++++++++\n"
    "+ 0.Exit 1.printlnTest 2.initTest 3.getter 4.setter 5.isSameTest     +\n"
    "+ 6.whatAreYouDoingTest 7.NoBoolAlphaOutput 8.BoolAlphaOutput        +\n"
    "+ 9.NoBoolAlphaInputPerson 10.BoolAlphaInputPerson 11.DataTypeSize() +\n"
    "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    while (true) {
        int menuItem = UI::selectMenu(menuStr, menuCount);
        if (menuItem == 0) break;

        switch(menuItem) {
        case 1: printlnTest();            break;
        case 2: initTest();               break;
        case 3: getter();                 break;
        case 4: setter();                 break;
        case 5: isSameTest();             break;
        case 6: whatAreYouDoingTest();    break;
        case 7: noBoolAlphaOutput();      break;
        case 8:   boolAlphaOutput();      break;
        case 9: noBoolAlphaInputPerson(); break;
        case 10:  boolAlphaInputPerson(); break;
        case 11: dataTypeSize();          break;
        }
    }
    cout << "Good bye!!" << endl;
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
#if AUTOMATIC_ERROR_CHECK
    evaluate(true);            // �Լ� ȣ��
#else
    run();
#endif
}
