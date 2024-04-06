#include<iostream>
#include<cstring>
using namespace std;

struct Engine{
    int horsepower;
    int torque;
};

struct Car{
    char manufacturer[100];
    int year;
    Engine engine;

    void print(){
        cout << "Manufacturer: "<< manufacturer << endl;
        cout << "Horsepower: " << engine.horsepower << endl;
        cout << "Torque: " << engine.torque << endl;
    }
};
void read(int n, Car * car){
    for(int i = 0; i < n; i++){
        cin >> car[i].manufacturer;
        cin >> car[i].year;
        cin >> car[i].engine.horsepower;
        cin >> car[i].engine.torque;
    }
}

void printCar (int n, Car * car){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(car[i].engine.horsepower < car[j].engine.horsepower){
                swap(car[i], car[j]);
            }
        }
    }
    if(car[0].engine.torque > car[1].engine.torque){
        car[0].print();
    }else{
        car[1].print();
    }
}

int main(){
    Car cars[100];
    int n; cin >> n;
    read(n,cars);
    printCar(n,cars);


    return 0;
}