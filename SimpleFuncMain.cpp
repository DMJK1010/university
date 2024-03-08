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
        cout<<"선택 :";
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
            cout<<"잘못된 선택입니다."<<endl;
        }
    }
    return 0;
}

void showmenu(void){
    cout<<"-----Menu------"<<endl;
    cout<<"1. 개좌개설"<<endl;
    cout<<"2. 입금"<<endl;
    cout<<"3. 출금"<<endl;
    cout<<"4. 계좌정보 전체 출력"<<endl;
    cout<<"5. 종료"<<endl;
}
void makeaccount(void){
    int id;
    char name[NAME_LEN];
    int balance;

    cout<<"[계좌개설]"<<endl;
    cout<<"계좌ID: "; cin>>id;
    cout<<"이 름 : "; cin>>name;
    cout<<"입금액: "; cin>>balance;
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

    cout<<"[입 금]"<<endl;
    cout<<"계좌ID: "; cin>>id;
    cout<<"입금액: "; cin>>money;
    for(int i=0; i<accNUM; i++){
        if(accARR[i].accID == id){
            accARR[i].balance += money;
            cout<<"입금완료"<<endl<<endl;
            return;
        }
        cout<<"유효하지 않은 ID 입니다."<<endl<<endl;
    }
}

void withdrawmoney(void){
    int money;
    int id;
    cout<<"[출 금]"<<endl;
    cout<<"계좌ID: "; cin>>id;
    cout<<"출금액: "; cin>>money;
    for(int i=0; i<accNUM; i++){
        if(accARR[i].accID == id){
            accARR[i].balance -= money;
            cout<<"출금완료"<<endl<<endl;
            return;
        }
        cout<<"유효하지 않은 ID 입니다."<<endl<<endl;
    }
}
void showallaccinfo(void){
    for(int i=0; i<accNUM; i++){
        cout<<"계좌ID: "<<accARR[i].accID<<endl;
        cout<<"이름: "<<accARR[i].cusNAME<<endl;
        cout<<"잔액: "<<accARR[i].balance<<endl<<endl;
    }
}

