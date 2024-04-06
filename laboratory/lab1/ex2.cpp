#include<iostream>
#include<cstring>
using namespace std;

enum CARD {
    DEBIT,
    CREDIT
};

struct Transactions {
    int ID, comm, paid_amounts, cards;
    CARD card;
    void read(){
        cin >> ID >> paid_amounts >> comm >> cards;
        switch(cards){
            case 0:
                card = DEBIT;
                break;
            case 1:
                card = CREDIT;
                break;
            default:
                cout << "No credit card transaction" << endl;
        }
    }
    void print(bool & flag){
        if (card == CREDIT){
            int result = paid_amounts + comm;
            cout << ID << " " << result << endl;
            flag = true;
        }
    }

};

int main(){
    Transactions transactions[100];
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        transactions[i].read();
    }
    bool flag = false;
    for(int i = 0; i < n; i++){
        transactions[i].print(flag);
    }
    if(!flag){
        cout << "No credit card transaction" << endl;
    }

    return 0;
}