#include<iostream>
#include<cstring>
#include<string>
using namespace std;

struct Transaction{
    char date[11];
    int amount;
    char currency[4];
    void read(){
        cin.ignore();
        cin.getline(date,11);
        cin >> amount;
        cin.ignore();
        cin.getline(currency,4);
    }
};

int dateSum(char * date){
    int sum = 0;
    for(int i = 0; i < strlen(date); i++){
        if(isdigit(date[i])){
            sum += date[i];
        }
    }
    return sum;
}

void print(Transaction transaction[], int n){
    int total = 0;
    int idx = 1;
    for(int i = 0; i < n ;i++){
        int month = dateSum(transaction[i].date);
        if((strcmp(transaction[i].currency, "MKD") == 0) && (transaction[i].amount > 1000) && (month >= 2015 && month <= 2058)){
            total += transaction[i].amount;
            cout << idx << ". " << transaction[i].date << " " << transaction[i].amount << " " << transaction[i].currency << endl;
        }
    }
    cout << "Total: " << total << "MKD" << endl;
}

int main(){
    Transaction transaction[500];
    int n; cin >> n;
    for(int i = 0; i < n ; i++){
       transaction[i].read();
    }
    print(transaction,n);
    return 0;
}