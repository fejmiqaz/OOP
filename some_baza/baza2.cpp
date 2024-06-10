#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord{
private:
    char id[13];
    char name[51];
    double cena;
    double mcena;//Моментална цена на акцијата (реален број)
    int brojnaakcii;
public:
    StockRecord(){
        strcpy(id,"11111");
        strcpy(name,"muli");
        cena=0;
        mcena=0;
        brojnaakcii=0;
    }
    StockRecord(char id[13], char name[51], float cena, float mcena, int brojnaakcii){
        strcpy(this->id,id);
        strcpy(this->name,name);
        this->cena=cena;
        this->mcena=mcena;
        this->brojnaakcii=brojnaakcii;
    }

    StockRecord(char id[13], char name[51], float cena,  int brojnaakcii){
        strcpy(this->id,id);
        strcpy(this->name,name);
        this->cena=cena;

        this->brojnaakcii=brojnaakcii;
    }

    void setNewPrice(double c){
        mcena=c;
    }
    ~StockRecord(){
    }
    double value() const {
        double sum=brojnaakcii*mcena;
        return sum;
    }
    double profit() const {
        double sum=brojnaakcii*(mcena-cena);
        return sum;
    }
    friend ostream &operator<<(ostream & out, const StockRecord &s){
        out<< s.name<<" "<<s.brojnaakcii<<" "<<s.cena<<" "<<s.mcena<<" "<<s.profit()<<endl;

    }
    double getMCENA(){
        return mcena;
    }

};
/*
 * Да се креира класа Client која содржи:

Име и презиме на клиентот (низа од 60 знаци)
ID на сметка (цел број)
Низа од компании кои ги поседува клиентот (динамичка низа од објекти од класата StockRecord)
Број на објекти во низата (цел број)
 */
class Client{
private:
    char name[61];
    int id;
    StockRecord *company;
    int length;

    void copy(const Client &other){
        strcpy(this->name,other.name);
        this->id=other.id;
        company= new StockRecord[length];
        for(int i=0;i<length;i++){
            company[i]=other.company[i];
        }
        this->length=length;
    }
public:
    /*
За класата Client да се дефинираат потребните конструктори, деструктор и метода double totalValue() која ќе ја
 пресметува моменталната вредност на акциите кои ги поседува клиентот. Таа се пресметува како збир од вредноста на
 сите акции од секоја компанија од кои е составено клиентското портфолио (15 поени). Дополнително, за класата да се преоптоварат операторите:
*/
    Client(){
        strcpy(this->name,"muli");
        this->id=1111;
        this->company= new StockRecord[0];
        this->length=length;

    }
    Client(char* name, int id) {
        strcpy(this->name, name);
        this->id = id;
        this->company = new StockRecord[0];
        this->length = 0;
    }
    ~Client(){
        delete [] company;
    }
    Client(const Client &other){
        copy(other);
    }
    Client &operator=(Client &other) {
        if(this!=&other){
            delete [] company;
            copy(other);
        }
        return *this;
    }
    double totalValue() const{
        double sum=0;
        for(int i=0;i<length;i++){
            sum+=company[i].value();
        }
        return sum;
    }
    Client& operator+=(const StockRecord& that) {
        StockRecord* tmp = new StockRecord[length + 1];
        for(int i = 0; i < length; i++) {
            tmp[i] = this->company[i];
        }
        tmp[length++] = that;

        delete [] company;
        this->company = new StockRecord[length];
        for(int i = 0; i < length; i++) {
            this->company[i] = tmp[i];
        }
        delete [] tmp;

        return *this;
    }
    friend ostream& operator<<(ostream& os, const Client& c) {
        os << c.id << " " << c.totalValue() << "\n";
        for(int i = 0; i < c.length; i++) {
            os << c.company[i];
        }
        return os;
    }
};


int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}