#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN=20;

void showmenu(void);
void makeaccount(void);
void depositmoney(void);
void withdrawmoney(void);
void showallaccinfo(void);

enum {MAKE=1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

typedef struct{
int accID;
int balance;
char cusNAME[NAME_LEN];
} Account;

Account accARR[100];
int accNUM=0;

int main(void){
    int choice;

    while(1){
        showmenu();
        cout<<"���� :";
        cin>>choice;
        cout<<endl;

        switch(choice){
        case MAKE:
            makeaccount();
            break;
        case DEPOSIT:
            depositmoney();
            break;
        case WITHDRAW:
            withdrawmoney();
            break;
        case INQUIRE:
            showallaccinfo();
            break;
        case EXIT:
            return 0;
        default:
            cout<<"�߸��� �����Դϴ�."<<endl;
        }
    }
    return 0;
}

void showmenu(void){
    cout<<"-----Menu------"<<endl;
    cout<<"1. ���°���"<<endl;
    cout<<"2. �Ա�"<<endl;
    cout<<"3. ���"<<endl;
    cout<<"4. �������� ��ü ���"<<endl;
    cout<<"5. ����"<<endl;
}
void makeaccount(void){
    int id;
    char name[NAME_LEN];
    int balance;

    cout<<"[���°���]"<<endl;
    cout<<"����ID: "; cin>>id;
    cout<<"�� �� : "; cin>>name;
    cout<<"�Աݾ�: "; cin>>balance;
    cout<<endl;

    accARR[accNUM].accID=id;
    accARR[accNUM].balance=balance;
    strcpy(accARR[accNUM].cusNAME, name);
    accNUM++;
}
void depositmoney(void){
    int id;
    int money;
    char name[NAME_LEN];

    cout<<"[�� ��]"<<endl;
    cout<<"����ID: "; cin>>id;
    cout<<"�Աݾ�: "; cin>>money;
    for(int i=0; i<accNUM; i++){
        if(accARR[i].accID == id){
            accARR[i].balance += money;
            cout<<"�ԱݿϷ�"<<endl<<endl;
            return;
        }
        cout<<"��ȿ���� ���� ID �Դϴ�."<<endl<<endl;
    }
}

void withdrawmoney(void){
    int money;
    int id;
    cout<<"[�� ��]"<<endl;
    cout<<"����ID: "; cin>>id;
    cout<<"��ݾ�: "; cin>>money;
    for(int i=0; i<accNUM; i++){
        if(accARR[i].accID == id){
            accARR[i].balance -= money;
            cout<<"��ݿϷ�"<<endl<<endl;
            return;
        }
        cout<<"��ȿ���� ���� ID �Դϴ�."<<endl<<endl;
    }
}
void showallaccinfo(void){
    for(int i=0; i<accNUM; i++){
        cout<<"����ID: "<<accARR[i].accID<<endl;
        cout<<"�̸�: "<<accARR[i].cusNAME<<endl;
        cout<<"�ܾ�: "<<accARR[i].balance<<endl<<endl;
    }
}

