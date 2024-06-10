#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Shape {
protected:
    int side;
public:
    Shape(){}
    explicit Shape(int side) : side(side) {}
    virtual double plot() = 0;
    virtual void pecati() = 0;
    virtual int getType() = 0;
};

class Square : public Shape {
public:
    explicit Square(int side) : Shape(side) {}

    double plot() override {
        return side * side;
    }

    void pecati() override {
        cout << "Kvadrat so plostina = " << plot() << endl;
    }

    int getType() override {
        return 1;
    }
};
class Circle : public Shape {
public:
    explicit Circle(int side) : Shape(side) {}

    double plot() override {
        return 3.14 * side * side;
    }

    void pecati() override {
        cout << "Krug so plostina = " << plot() << endl;
    }

    int getType() override {
        return 2;
    }
};
class Triangle : public Shape {
public:
    explicit Triangle(int side) : Shape(side) {}

    double plot() override {
        return (sqrt(3)/4) * side * side;
    }

    void pecati() override {
        cout << "Triagolnik so plostina = " << plot() << endl;
    }

    int getType() override {
        return 3;
    }
};

void checkNumTypes(Shape ** array, int n){
    int cnt = 0, cnt1 = 0, cnt2 = 0;
    for(int i = 0; i < n; i++){
        if(array[i]->getType() == 1){
            cnt++;
        }else if(array[i]->getType() == 2){
            cnt1++;
        }else if(array[i]->getType() == 3){
            cnt2++;
        }
    }
    cout << "Broj na kvadrati vo nizata = " << cnt << endl;
    cout << "Broj na krugovi vo nizata = " << cnt1 << endl;
    cout << "Broj na triagolnici vo nizata = " << cnt2 << endl;
}

int main(){


    int n;
    cin >> n;

    //TODO: inicijaliziraj niza od pokazuvachi kon klasata Shape


    Shape ** niza = new Shape *[n];

    //TODO: alociraj memorija so golemina n za prethodno navedenata niza

    int classType;
    int side;

    //TODO: konstruiraj for ciklus so chija pomosh ke ja popolnish nizata
    for(int i = 0; i < n; ++i){

        cin >> classType;
        cin >> side;

        if (classType == 1){
            niza[i] = new Square(side);
        }else if (classType == 2){
            niza[i] = new Circle(side);
        }else if (classType == 3) {
            niza[i] = new Triangle(side);
        }

    }


    for(int i = 0; i < n; ++i){

        niza[i]->pecati();
    }

    checkNumTypes(niza, n);


    return 0;
}