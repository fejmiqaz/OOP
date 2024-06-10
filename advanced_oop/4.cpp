#include<iostream>
#include<cstring>
using namespace std;

struct Transaction{
    string date;
    int amount;
    char currency[4];
};
void print(Transaction transaction[500], int n){
    int total = 0;
    int idx = 1;
    for(int i = 0; i < n; i++){
        string monthStr = transaction[i].date.substr(3,2);
        int month = stoi(monthStr);
        if((transaction[i].amount < 5000) && (strcmp(transaction[i].currency, "USD") == 0) && (month <= 3)) {
            total += transaction[i].amount;
            cout << idx << ". " << transaction[i].date << " " << transaction[i].amount << " " << transaction[i].currency << endl;
            idx++;
        }
    }
    cout << "Total:" << total << " USD";
}

int main(){
    Transaction transactions[500];
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> transactions[i].currency;
        cin >> transactions[i].amount;
        cin >> transactions[i].date;
    }
    print(transactions,n);
    return 0;
}