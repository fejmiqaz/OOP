#include<iostream>
#include<cstring>
#include<stdexcept>
using namespace std;

class ExistinBill : public exception{
public:
    const char* what() const noexcept override {
        return "The bill already exists";
    }
};

class Bill {
private:
    char * billNumber;
    char date[8];
    int expense;
    bool status;
    void copy(const Bill & b){
        this->billNumber = new char[strlen(b.billNumber)+1];
        strcpy(this->billNumber, b.billNumber);
        strcpy(this->date, b.date);
        this->status = b.status;
        this->expense = b.expense;
    }
public:
    Bill(){}
    Bill(char *billNumber, int expense, char *date, bool status){
        this->billNumber = new char[strlen(billNumber)+1];
        strcpy(this->billNumber,billNumber);
        strcpy(this->date,date);
        this->status = status;
        this->expense = expense;
    }
    Bill(const Bill & other){
        copy(other);
    }

    Bill & operator=(const Bill & other){
        if(this!=&other){
            copy(other);
        }
        return * this;
    }

    char *getBillNumber() const {
        return billNumber;
    }

    bool isStatus() const {
        return status;
    }

    ~Bill(){
        delete[] billNumber;
    }

    bool operator==(const Bill & other){
        return (strcmp(this->billNumber, other.billNumber) == 0);
    }

    friend ostream &operator<<(ostream &os, const Bill &bill) {
        return os << bill.billNumber << " ("<< bill.date << ") - " << bill.expense;
    }
};

class UserProfile{
private:
    char name[31];
    Bill * billsArray[30];
    int n;
    void copy(const UserProfile & up){
        strcpy(this->name, up.name);
        this->n = up.n;
        for(int i = 0; i < n; i++){
            this->billsArray[i] = nullptr;
        }
    }
public:
    UserProfile(){}
    UserProfile(char *name){
        strcpy(this->name, name);
        for(int i = 0; i < n; i++){
            billsArray[i] = nullptr;
        }
    }

    UserProfile(const UserProfile & other){
        copy(other);
    }

    ~UserProfile(){
        for(int i = 0; i <n; i++){
            delete[] billsArray[i];
        }
    }

    UserProfile & operator=(const UserProfile & up){
        if(this!=&up){
            for(int i = 0; i < n; i++){
                delete[] billsArray[i];
            }
            copy(up);
        }
        return * this;
    }

    UserProfile & operator+=(const Bill & other){
        for(int i = 0; i < n; i++){
            if((strcmp(this->billsArray[i]->getBillNumber(), other.getBillNumber())==0)){
                throw ExistinBill();
            }
        }
        if(n < 30){
            billsArray[n++] = new Bill(other);
        }
        return * this;
    }

    friend ostream &operator<<(ostream &os, const UserProfile &profile) {
        os << "Pending bills for " << profile.name << " are: " << endl;
        for(int i = 0; i < profile.n; i++){
            if(!profile.billsArray[i]->isStatus()){
                os << profile.billsArray[i] << endl;
            }
        }
        return os;
    }

    int totalDue(int month, int year){}
};

int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator <<-----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += & << -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}
