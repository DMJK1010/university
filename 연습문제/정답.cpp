#include <iostream>
#include <cstring>
using namespace std;

class Person {
    char* name;
    int age;
    bool married;

public:
    Person() : age{}, married{} { name = nullptr; }
    ~Person() { delete[] name; }


    friend ostream& operator<<(ostream& outs, const Person& p);
    friend istream& operator>>(istream& ins, Person& p);
    Person& operator=(const Person& p);
};


ostream& operator<<(ostream& outs, const Person& p) {
    cout << boolalpha;
    cout << "Person info" << endl;
    cout << "name: " << p.name << ", age: " << p.age << ", married: " << p.married << noboolalpha;
    return outs;
}

istream& operator>>(istream& ins, Person& p) {
    cout << "input info (name, age, married)" << endl;
    char temp[100];
    ins >> boolalpha;
    ins >> temp >> p.age >> p.married;
    if (p.name != nullptr)
        delete[] p.name;
    p.name = new char[strlen(temp) + 1];
    strcpy(p.name, temp);
    return ins;
}

Person& Person::operator=(const Person& p) {
    if (this != &p) {
        if (name != nullptr)
            delete[] name;
        name = new char[strlen(p.name) + 1];
        strcpy(name, p.name);
        age = p.age;
        married = p.married;
    }
    return *this;
}

int main() {
    Person p1, p2;
    cin >> p1 >> p2;
    cout << p1 << endl << p2 << endl;
    cout << "===================================" << endl;
    cout << "p1 = p2 is called()" << endl;
    cout << "===================================" << endl;
    p1 = p2;
    cout << p1 << endl << p2 << endl;
    cout << true << "234" << endl;

    return 0;
}
