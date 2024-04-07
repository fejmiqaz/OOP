#include<iostream>
#include<cstring>
using namespace std;

class Bill{
private:
    char * billNumber;
    int expense;
    char date[10];
    bool status;
    void copy(const Bill & b) {
        billNumber = new char[strlen(b.billNumber) + 1];
        strcpy(this->billNumber, billNumber);
        expense = b.expense;
        strcpy(date, b.date);
        status = b.status;
    }
public:
    Bill(){}
    Bill(char *billNumber, int expense, char *date, bool status){
        billNumber = new char[strlen(billNumber)+1];
        strcpy(this->billNumber, billNumber);
        this->expense = expense;
        strcpy(this->date, date);
        this->status = status;
    }
    Bill(const Bill & other){
        copy(other);
    }
    ~Bill(){
        delete[] billNumber;
    }

    bool isStatus() const {
        return status;
    }

    bool isInMonthYear(int month, int year) const {
        int billMonth, billYear;
        sscanf(date, "%*d-%d-&d", &billYear, &billMonth);
        return billMonth == month && billYear == year;
    }

    int getExpense() const {
        return expense;
    }

    bool operator==(const Bill & b){
        return billNumber == b.billNumber;
    }
    friend ostream& operator<<(ostream & out, Bill & b){
        out << b.billNumber << " (" << b.date << ") - " << b.expense << endl;
        return out;
    }
};

class UserProfile{
private:
    char name[30];
    Bill * bills[30];
    int n;
    void copy(const UserProfile & up){
        strcpy(name, up.name);
        n = up.n;
        for(int i = 0; i < n; i++){
            bills[i]= new Bill(*(up.bills[i]));
        }
    }
public:
    UserProfile(char *name) {
        strcpy(this->name, name);
        for(int i = 0; i <n; i++){
            this->bills[i] = nullptr;
        }
    }
    UserProfile(const UserProfile & other){
        copy(other);
    }

    ~UserProfile(){
        delete[] bills;
    }


    UserProfile& operator=(const UserProfile & up){
        if(this!=&up){

            for(int i = 0; i < n; i++){
                delete[] bills[i];
            }
            strcpy(name, up.name);
            n = up.n;
            for(int i =0; i < n; i++){
                bills[i] = new Bill(*(up.bills[i]));
            }
        }
        return *this;
    }

    UserProfile & operator+=(const Bill & b){
        if(n < 30){
            bills[n++] = new Bill(b);
        }
        return * this;
    }

    int totalDue(int month, int year) const {
        int total = 0;
        for(int i = 0; i < n; i++){
            if(bills[i]->isInMonthYear(month,year)){
                total += bills[i]->getExpense();
            }
        }
        return total;
    }

    friend ostream& operator<<(ostream& out, const UserProfile& up) {
        out << "Name: " << up.name << endl;
        for (int i = 0; i < up.n; i++) {
            if(up.bills[i]->isStatus() == false){
                out << "Pending bills for " << up.name << " are: " << up.bills[i];
            }
            out << endl;
        }
        return out;
    }

};

class ExistingBill{

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
