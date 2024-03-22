/*
 * CH3_1: ch3_1.cpp
 *
 *  Created on: 2024. 3.17.
 *      Author: Junha Kim
 *
 *  + struct Person�� class Person���� ����
 *  + Person�� ��� �Լ��� ����
 *  + UI::inputPerson() ����
 *  + ClassAndObject Ŭ���� �߰�:
 *     ��ü�� ���� �� �Ҹ�,
 *     ������ü, static ��ü, ������ü�� ���� �� �Ҹ� �ñ�
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
    char   name[20];        // �̸�
    int    id;              // Identifier
    double weight;          // ü��
    bool   married;         // ��ȥ����
    char   address[40];     // �ּ�

protected:
    void printMembers(ostream* out);

public:
    Person();
    Person(const char *name);
    Person(const char *name, int id, double weight, bool married, const char *address);
    ~Person();

    void setName(const char* pname)       { strcpy(name, pname); }
    void setAddress(const char* paddress) { strcpy(address, paddress); }

    void input(istream* pin)  {  }
    void print(ostream* pout) { printMembers(pout); }
    void println()            { print(&cout); cout << endl; }
};

Person::Person(): name{}, id{}, weight{}, married{}, address{} {
    // �� �Լ� ����(:�� �Լ� ��ü ����)���� �� ����� �ʱ�ȭ�ϴµ� �̴� �Լ� �����ϱ� ����
    // �� ����� ���� �ʱ�ȭ�ϴ� ���̴�. {}�� �� ����Ÿ Ÿ�Ժ��� ����Ʈ ������ �ʱ�ȭ�϶�� �ǹ���.
    // ��, name[]={'\0'}="", id=0, weight=0.0, married=false, address[]={'\0'}=""
    cout << "Person::Person():"; println();
}

Person::Person(const char *name) : id{}, weight{}, married{}, address{} {
    setName(name);
    cout << "Person::Person(\"" << name << "\"):"; println();
}

Person::Person(const char *name, int id, double weight, bool married, const char *address) : id{id}, weight{weight}, married{married} {
    // ������ �� ����� �ʱ�ȭ�ϴ� {}�� �� �Ű����� ���� ��ü�� �����ϴ� ����� �����ϴ� ���̴�. ��,
    // this->id=id, this->weight=weight, this->married=married�� �����ϴ�.
    // ���⼭ this�� �ش� ��ü�� �������ϴ� ������ �����̸�, (���� �忡�� ����� ������)
    // this->id�� �ش� ��ü�� ��� id�� ��Ī�ϸ� =�� �������� id�� �Լ��� �Ű������̴�.
    // ���� ������ �����ϴ� ���� ��ó�� �ϸ� ������ name[], address[]�� ���� �迭 ���� �Լ�
    // ȣ�� �Ǵ� �ٸ� �Լ��� ȣ���� ���� ������ �Լ��� ��ü { } ������ ȣ���ؾ� �Ѵ�.

    // TODO: [���� 2]
	setName(name);
	setAddress(address);
    cout << "Person::Person(...):"; println();
}

Person::~Person() {
    cout << "Person::~Person():"; println();
}

void Person::printMembers(ostream* pout)   {
    // TODO: [���� 1]
	*pout<<name <<" "<<id<<" "<<weight<<" "<<married<<" :"<<address<<": ";
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
        int menuCount = 2; // ��� ����
        string menuStr =
"******************************* Main Menu *********************************\n"
"* 0.Exit 1.Class:Object(ch3_1)                                            *\n"
"***************************************************************************\n";

        while (true) {
            int menuItem = UI::selectMenu(menuStr, menuCount);
            if (menuItem == 0) break;

            switch(menuItem) {
            case 1: ClassAndObject().run();           break;
            // �� ClassAndObject()�� �ӽð�ü(�̸����� ��ü)�� �������ϴ� �ڵ��̰�
            // ���� �ٷ� �ش� ��ü�� ��� run()�� ȣ���ϰ� run()���� ���ϵ� �Ŀ��� ��ü �ڵ� �Ҹ��
            // ���� ������ ����. ClassAndObject tmp; tmp.run();
            }
        }
        cout << "Good bye!!" << endl;
    }
}; // class MainMenu

/******************************************************************************
 * run() �Լ�: ���� �޴��� ������
 ******************************************************************************/
void run() {
    MainMenu().run();
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
