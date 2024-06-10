#include<iostream>
#include<string>
#include<cstring>
using namespace std;

class Cinema {
protected:
    char name[100];
    int cinemaHallNumber;
    static double studentDiscount;
    double priceMKD;
public:
    Cinema(){}
    Cinema(char * name, int cinemaHallNumber, double price) : cinemaHallNumber(cinemaHallNumber), priceMKD(price) {
        strcpy(this->name,name);
    }

    const char *getname() const {
        return name;
    }

    static double getStudentDiscount() {
        return studentDiscount;
    }

    static void setStudentDiscount(double studentDiscount) {
        Cinema::studentDiscount = studentDiscount;
    }

    virtual double price(bool isStudent){
        if (isStudent){
            return priceMKD * studentDiscount;
        }else{
            return priceMKD;
        }
    }
    friend void cheapestCinema(Cinema ** halls, int n, bool isStudent);
    friend bool searchCinema(Cinema ** c, int n, char * title, bool premiere, bool isStudent);
};

class ThreeDCinema : public Cinema{
protected:
    char * name;
    int duration;
    bool isPremiere;
public:
    ThreeDCinema(char *name, int cinemaHallNumber, double price, char *name1, int duration, bool isPremiere) : Cinema(
            name, cinemaHallNumber, price), name(name1), duration(duration), isPremiere(isPremiere) {
        this->name = new char[strlen(name1)+1];
        strcpy(this->name,name1);
    }

    bool isPremiere1() const {
        return isPremiere;
    }

    char *getName1() const {
        return name;
    }

    double price(bool isStudent) override {
        if(duration > 2.5){
            priceMKD+=50;
        }else if(duration > 3){
            priceMKD+=70;
        }
        if(isPremiere){
            priceMKD+=60;
        }
        return priceMKD;
    }
};

bool searchCinema(Cinema ** c, int n, char * title, bool premiere, bool isStudent){
    bool found = false;
    for(int i = 0; i < n; i++){
        ThreeDCinema * s = dynamic_cast<ThreeDCinema *>(c[i]);
        if(premiere&& strcmp(c[i]->name,title)==0 && s[i].isPremiere1() == true){
            found = true;
            cout << c[i]->name << " " << c[i]->price(isStudent) << endl;
        }else {
            if(strcmp(c[i]->name,title)==0){
                found = true;
                cout << c[i]->name << " " << c[i]->price(isStudent) << endl;
            }
        }
    }
    return found;
}

void cheapestCinema(Cinema ** halls, int n, bool isStudent){
    int threeD = 0;
    double min = halls[0]->price(isStudent);
    int minIDX = 0;
    for(int i = 0; i < n; i++){
        if(halls[i]->price(isStudent) < min){
            min = halls[i]->price(isStudent);
            minIDX = i;
        }
        if(dynamic_cast<ThreeDCinema *>(halls[i])!=0){
            threeD++;
        }
    }
    cout << "Cheapest movie hall: ";
    cout << halls[minIDX]->name << " " << halls[minIDX]->price(isStudent) << endl;
    cout << "3D cinema halls: " << threeD << " from total" << n << endl;
}

double Cinema::studentDiscount = 0.17;

int main(){

    return 0;
}