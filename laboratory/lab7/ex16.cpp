#include<iostream>
#include<string>
using namespace std;

class ZicanInstrument {
protected:
    string name;
    int numOfWires;
    double price;
public:
    ZicanInstrument(){}
    ZicanInstrument(string name, int numOfWires, double price) : name(name), numOfWires(numOfWires), price(price) {
    }
    virtual double cena() = 0;

    bool operator==(const ZicanInstrument & zi) const{
        return numOfWires == zi.numOfWires;
    }

    friend ostream &operator<<(ostream &os, const ZicanInstrument &instrument) {
        os << instrument.name << " " << instrument.numOfWires << " " << instrument.price;
        return os;
    }

    friend void pecatiInstrumenti(ZicanInstrument & zi, ZicanInstrument **i, int n);
    };

class Mandolina : public ZicanInstrument {
private:
    string form;
public:
    Mandolina(string name, int numOfWires, double price, string form) : ZicanInstrument(name, numOfWires, price), form(form){}

    double cena() override {
        if(form.find("Neapolitan") != string::npos){
            return price + price * 0.15;
        }else{
            return price;
        }
    }
};

class Violina : public ZicanInstrument {
private:
    double size;
public:
    Violina(string name, int numOfWires, double price, double size) : ZicanInstrument(name, numOfWires, price),size(size) {}

    double cena() override {
        if(size == 0.25){
            return price + price * 0.10;
        }else if(size == 1.00){
            return price + price * 0.20;
        } else{
            return price;
        }
    }
};

void pecatiInstrumenti(ZicanInstrument & zi, ZicanInstrument **i, int n){
    for(int j = 0; j < n; j++){
        if(i[j]->numOfWires == zi.numOfWires){
            cout << i[j]->cena() << endl;
        }
    }
}



//Vasiot kod ovde:

int main() {
    char ime[20];
    int brojZici;
    float cena;
    char forma[20];
    cin >> ime >> brojZici >> cena >> forma;
    Mandolina m(ime, brojZici, cena, forma);
    int n;
    cin >> n;
    ZicanInstrument **zi = new ZicanInstrument*[2 * n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> brojZici >> cena >> forma;
        zi[i] = new Mandolina(ime, brojZici, cena, forma);
    }
    for(int i = 0; i < n; ++i) {
        float golemina;
        cin >> ime >> brojZici >> cena >> golemina;
        zi[n + i] = new Violina(ime, brojZici, cena, golemina);
    }
    pecatiInstrumenti(m, zi, 2 * n);
    for(int i = 0; i < 2 * n; ++i) {
        delete zi[i];
    }
    delete [] zi;
    return 0;
}