#include<iostream>
#include<cstring>
using namespace std;

class UserExistsException {
public:
    void message(){
        cout << "The user already exists in the list" << endl;
    }
};

enum typeC {
    loyal,
    vip,
    standard
};

class Customer {
protected:
    char name[50];
    char email[50];
    typeC buyer;
    static int discount;
    static int additionalDiscount;
    int boughtItems;
public:
    Customer(){}
    Customer(char *name, char *email, typeC buyer, int boughtItems) : boughtItems(boughtItems)
    { strcpy(this->name,name); strcpy(this->email,email);
        if(buyer == 1){
            this->buyer = loyal;
        }else if(buyer == 2){
            this->buyer = vip;
        }else{
            this->buyer = standard;
        }
    }

    static void setDiscount1(int discount) {
        Customer::discount = discount;
    }

    bool operator==(const Customer & c){
        return strcmp(this->email, c.email) != 0;
    }

    friend ostream &operator<<(ostream &os, const Customer &customer) {
        os << customer.name << endl;
        os << customer.email << endl;
        os << customer.boughtItems << endl;
        if(customer.buyer == loyal){
            os << "loyal" << Customer::discount << endl;
        }else if(customer.buyer == vip){
            os << "vip" << Customer::discount+Customer::additionalDiscount << endl;
        }
        return os;
    }

    const char *getEmail() const {
        return email;
    }

};

int Customer::discount = 10;
int Customer::additionalDiscount = 20;

class FINKI_bookstore {
private:
    Customer * customer;
    int n;
public:
    FINKI_bookstore() {
        this->n = 0;
        this->customer = new Customer[n];
    }
    FINKI_bookstore & operator+=(const Customer & c){

        for(int i = 0; i < n; i++){
            if(customer[i].getEmail() == c.getEmail()){
                throw UserExistsException();
            }
        }

        Customer * tmp = new Customer[n+1];
        for(int i = 0; i < n; i++){
            tmp[i] = customer[i];
        }
        tmp[n++] = c;
        delete[] customer;
        customer = tmp;
        return * this;
    }

    void setCustomers(Customer *customer, int n) {
        for(int i = 0; i < n; i++){
            FINKI_bookstore::customer[i] = customer[i];
        }
    }

    friend ostream & operator<<(ostream & os, const FINKI_bookstore & fb){
        for(int i = 0; i < fb.n; i++){
            os << fb.customer[i] << endl;
        }
        return os;
    }

    void update(){}

};

int main(){
    int testCase;
    cin >> testCase;
    int MAX = 9999999;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);

        try{
            fc+=c;
        }catch( UserExistsException & e){
            e.message();
        }

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception!!!) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);

        try {
            fc+=c;
        }catch (UserExistsException & e){
            e.message();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
