#include<iostream>
#include<cstring>
using namespace std;

class AlcoholicDrink{
private:
    char name[100];
    char country[100];
    float alcPercent, basePrice;
    void copy(const AlcoholicDrink & ad){
        strcpy(name, ad.name);
        strcpy(country, ad.country);
        alcPercent = ad.alcPercent;
        basePrice = ad.basePrice;
    }
public:
    AlcoholicDrink(){}
    AlcoholicDrink(char *name, char *country, float alcPercent, float basePrice) {
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->alcPercent = alcPercent;
        this->basePrice = basePrice;
    }

    AlcoholicDrink(const AlcoholicDrink & other){
        copy(other);
    }

    AlcoholicDrink & operator = (const AlcoholicDrink & other){
        if(this!=&other){
            copy(other);
        }
        return * this;
    }

    friend ostream & operator<<(ostream & out, const AlcoholicDrink & ac){
        out << ac.name << " " << ac.country << " " << ac.basePrice << endl;
        return out;
    }

};

class Beer{
private:
    AlcoholicDrink * alcoholicDrink;
    int n;
    bool mainIngredient;
    void copy(const Beer & b){
        mainIngredient = b.mainIngredient;
        this->n = b.n;
        alcoholicDrink = new AlcoholicDrink[this->n];
        for(int i = 0; i < this->n; i++){
            this->alcoholicDrink[i] = b.alcoholicDrink[i];
        }

    }
public:
    Beer(){}
    Beer(float p, char * name, char * country, float price,bool mainIngredient){
        alcoholicDrink = new AlcoholicDrink[0];
        this->mainIngredient = mainIngredient;
    }

    Beer(const Beer & other){
        copy(other);
    }

    Beer & operator=(const Beer & other){
        if(this!=&other){
            delete[] alcoholicDrink;
            copy(other);
        }
        return * this;
    }

    ~Beer(){
        delete[] alcoholicDrink;
    }

    friend ostream& operator<<(ostream & out, Beer & b){
        out << b.mainIngredient << endl;
        return out;
    }
};
class Wine{
private:
    int year;
    char grapeType[20];
public:
    Wine(){}
    Wine(float p, char * name, char * country, float price, int year, char *grapeType) {
        this->year = year;
        strcpy(this->grapeType, grapeType);
    }
    friend ostream& operator<<(ostream& out, Wine & w){
        out << w.year << " " << w.grapeType << endl;
        return out;
    }
};

int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape [20];
    if(testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if(testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    } else if(testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }

}