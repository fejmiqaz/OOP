#include<iostream>
#include<cstring>
using namespace std;

enum tip{
    POP=0,
    RAP=1,
    ROK=2
};

class Pesna{
private:
    char *name;
    int min;
    tip type;

    void copy(Pesna &other){
        this->name = new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->min=other.min;
        this->type=other.type;
    }
public:
    Pesna(){
        name = new char[5];
        strcpy(name,"muli");
        min=0;
        type=ROK;

    }
    Pesna(const char *name, int min,enum tip type){
        this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        this->min=min;
        this->type=type;
    }
    ~Pesna(){
        delete [] name;
    }

    Pesna(Pesna& other){
        copy(other);

    }
    Pesna &operator=(Pesna &other){
        if(this!=&other){
            delete [] name;
            copy(other);
        }
        return *this;
    }

    void pecati(){
        cout << "\"" << name << "\"" << "-" << min<< "min\n";
    }
    int getMin(){
        return min;
    }

    tip getType() {
        return type;
    }


};

class CD{
private:
    Pesna p[10];
    int brojNaPesni;
    int capacity;
    void copy(CD &other){
        this->brojNaPesni=other.brojNaPesni;
        this->capacity=other.capacity;
        for(int i=0;i<other.brojNaPesni;i++){
            p[i]=other.p[i];
        }


    }
public:
    CD(){
        brojNaPesni=0;
    }
    CD(int cap){
        capacity=cap;
    }
    ~CD(){

    }
    CD(CD &other){
        copy(other);
    }
    CD &operator=(CD &other){
        if(this!=&other){
            copy(other);
        }
        return *this;
    }
    void dodadiPesna (Pesna p1){
        int n=0;
        for(int i=0;i<brojNaPesni;i++){
            n+=p[i].getMin();

        }

        n+=p1.getMin();
        if(n<=capacity){
            if(brojNaPesni<10){
                p[brojNaPesni++]=p1;
            }
        }
    }
    void pecatiPesniPoTip(tip t){
        for(int i = 0; i < brojNaPesni; i++) {
            if(p[i].getType() == t) {
                p[i].pecati();
            }
        }
    }
    Pesna getPesna(int idx) {
        return p[idx];
    }
    int getBroj(){
        return brojNaPesni;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}