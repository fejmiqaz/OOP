#include <iostream>
#include <cstring>
using namespace std;

//YOUR CODE HERE:

enum TYPE{
    PERSONAL,
    COMPANY
};

class Account{
private:
    char name[31];
    int id;
    int idd;
    static int ID;
    TYPE type;
    double balance;
    void copy(const Account & a){
        strcpy(this->name, a.name);
        this->id = a.id;
        this->idd = a.idd;
        this->balance = a.balance;
        this->type = a.type;
    }
public:
    Account(){}
    Account(char *name, int id, double balance){
        strcpy(this->name,name);
        ID++;
        this->idd = ID;
        this->balance = balance;
        if(id == 0){
            this->type = PERSONAL;
        }else if(id == 1){
            this->type = COMPANY;
        }
    }
    Account(const Account & other){
        copy(other);
    }

    Account & operator=(const Account & other){
        if(this!=&other){
            copy(other);
        }
        return * this;
    }

    int getIdd() const {
        return idd;
    }

    friend ostream &operator<<(ostream &os, const Account &account) {
        os << account.idd << " - " << account.name << " ";
        if (account.type == PERSONAL){ os << "person";}
        else if(account.type == COMPANY){ os << "company"; }
        os << " " << account.balance << endl;
        return os;
    }

    bool operator==(const Account & acc){
        return (idd == acc.idd);
    }

    double & operator-=(double commission){
        balance -= commission;
        return balance;
    }
};

class Bank{
private:
    char name[21];
    Account * accounts;
    int n;
    void copy(const Bank & b){
        strcpy(this->name, b.name);
        this->n = b.n;
        accounts = new Account[this->n];
        for(int i = 0; i < this->n; i++){
            this->accounts[i] = b.accounts[i];
        }
    }
public:
    Bank(char * name = ""){
        strcpy(this->name, name);
        this->n = 0;
        accounts = new Account[0];
    }

    friend ostream &operator<<(ostream &os, const Bank &bank) {
        os << bank.name << endl;
        for(int i = 0; i < bank.n; i++){
            os << bank.accounts[i];
        }
        return os;
    }

    Bank & operator+=(const Account & acc){
        for(int i = 0; i < n; i++){
            if(accounts[i].getIdd() == acc.getIdd()){
                return * this;
            }
        }

        Account * tmp = new Account[n+1];
        for(int i = 0; i < n; i++){
            tmp[i] = accounts[i];
        }
        tmp[n++] = acc;
        delete[] accounts;
        accounts = tmp;
        return * this;
    }
    bool operator<(const Bank & other){
        for(int i = 0; i < n; i++){
            if (n < other.n){
                return true;
            }
        }
        return false;
    }
    // need to work on this method
    void bankFee(){}
};
// need to work on this method
int leastLiquid(Bank * banks, int n){}

int Account::ID = 111110;

int main() {
    int testCase;
    cin>>testCase;
    if(testCase==0)
    {
        cout<<"TESTING ACCOUNT CONSTRUCTOR"<<endl;
        Account account1("Paul",0,32000);
        Account account2("Globex",1,500000);
        Account account3("Anna",0,8700);
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==1)
    {
        cout<<"TESTING ACCOUNT OPERATOR <<"<<endl;
        Account account1("Paul",0,32000);
        Account account2("Globex",1,500000);
        Account account3("Anna",0,8700);
        cout<<account1;
        cout<<account2;
        cout<<account3;
        cout<<"TEST PASSED"<<endl;
    } else if(testCase==2)
    {
        cout<<"TESTING ACCOUNT OPERATOR -="<<endl;
        Account account1("Paul",0,32000);
        Account account2("Globex Industries",1,500000);
        Account account3("Anna",0,8700);
        cout<<account1;
        cout<<account2;
        cout<<account3;
        account1-=350;
        account2-=20000;
        account3-=500;
        cout<<"===== DECREASE ====="<<endl;
        cout<<account1;
        cout<<account2;
        cout<<account3;
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==3)
    {
        cout<<"TESTING BANK CONSTRUCTOR and <<"<<endl;
        Bank bank1("Capital One Bank");
        cout<<bank1;
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==4)
    {
        cout<<"TESTING BANK OPERATOR += and <<"<<endl;
        Account account1("Paul",0,32000);
        Account account2("Globex Industries",1,500000);
        Account account3("Anna",0,8700);
        Bank bank1("Capital One Bank");
        bank1+=account1;
        bank1+=account2;
        bank1+=account3;
        cout<<bank1;
        cout<<"TEST PASSED"<<endl;
    }
    else if(testCase==5)
    {
        cout<<"TESTING BANK OPERATOR += and <<"<<endl;
        Account account1("Paul",0,32000);
        Account account2("Globex Industries",1,500000);
        Account account3("Anna",0,8700);
        Bank bank1("Capital One Bank");
        bank1+=account1;
        bank1+=account2;
        bank1+=account3;
        bank1+=account1;
        cout<<bank1;
        cout<<"TEST PASSED"<<endl;
    }
    else if(testCase==6)
    {
        cout<<"TESTING BANK COPY-CONSTRUCTOR and OPERATOR ="<<endl;
        Account account1("Paul",0,32000);
        Account account2("Globex Industries",1,500000);
        Account account3("Anna",0,8700);
        Account account4("Umbrella Corporation",1,300000);
        Account account5("Theo",0,15500);
        Bank bank1("Capital One Bank");
        bank1+=account1;
        bank1+=account2;
        bank1+=account3;
        Bank bank2(bank1);
        Bank bank4;
        {
            Bank bank3("First National Bank");
            bank3+=account4;
            bank3+=account5;
            bank4=bank3;
        }
        cout<<bank2;
        cout<<bank4;
        cout<<"TEST PASSED"<<endl;
    }else if(testCase==7)
    {
        cout<<"TESTING BANK OPERATOR < "<<endl;
        Account account1("Paul",0,32000);
        Account account2("Globex Industries",1,500000);
        Account account3("Anna",0,8700);
        Account account4("Umbrella Corporation",1,300000);
        Account account5("Theo",0,15500);
        Bank bank1("Capital One Bank");
        bank1+=account1;
        bank1+=account2;
        bank1+=account3;
        Bank bank3("First National Bank");
        bank3+=account4;
        bank3+=account5;
        if(bank1<bank3)
        {
            cout<<"TEST FAILED"<<endl;
        }
        else
        {
            cout<<"TEST PASSED"<<endl;
        }
    }else if(testCase==8)
    {
        cout<<"TESTING METHOD bankFee()"<<endl;
        char name[30],name1[30];
        int type, numberOfBanks, numberOfAccounts;
        float money;
        cin>>numberOfBanks;
        cin.ignore();
        Bank banks[10];
        for(int i=0;i<numberOfBanks;i++)
        {
            cin.getline(name,20);
            banks[i]=Bank(name);
            cin>>numberOfAccounts;
            cin.ignore();
            Account accounts[10];
            for(int j=0;j<numberOfAccounts;j++)
            {
                cin >> name1 >> type >> money;
                cin.ignore();
                accounts[j]=Account(name1,type,money);
                banks[i]+=accounts[j];
            }
        }
        for(int i=0;i<numberOfBanks;i++)
        {
            cout<<banks[i];
            cout<<"FEE-PAID"<<endl;
            banks[i].bankFee();
            cout<<banks[i];
        }
    }else if(testCase==9)
    {
        cout<<"TESTING METHOD leastLiquid()"<<endl;
        char name[30],name1[30];
        int type, numberOfBanks, numberOfAccounts;
        float money;
        cin>>numberOfBanks;
        cin.ignore();
        Bank banks[10];
        for(int i=0;i<numberOfBanks;i++)
        {
            cin.getline(name,20);
            banks[i]=Bank(name);
            cin>>numberOfAccounts;
            cin.ignore();
            Account accounts[10];
            for(int j=0;j<numberOfAccounts;j++)
            {
                cin >> name1 >> type >> money;
                cin.ignore();
                accounts[j]=Account(name1,type,money);
                banks[i]+=accounts[j];
            }
        }
        cout<<leastLiquid(banks,numberOfBanks);
    }
    return 0;
}