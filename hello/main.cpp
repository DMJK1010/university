#include <iostream>
#include <cstring>

using namespace std;

class Account{
private:
	char name[20];
	int id;
	double balance;
public:
	Account();
	Account(char *name);
	void setName(char *pname){ strcpy(name, pname); }
};

Account::Account(): name{}, id{}, balance{}{
}
Account::Account(char *name): id{}, balance{}{
	setName(name);
}

class


int main(){
	run();





	return 0;
}
