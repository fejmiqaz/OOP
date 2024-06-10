#include<iostream>
#include<cstring>
using namespace std;

struct SkiLift{
    char name[15];
    int n;
    bool doesFunction;
    void read(){
        cin.ignore();
        cin.getline(name,15);
        cin >> n;
        cin >> doesFunction;
    }
    void print(){
        cout << name << " " << n << " " << doesFunction;
    }
};

struct SkiCenter{
    char name[20];
    char country[20];
    SkiLift skiLift[20];
    int n;
    void read(){
        cin.getline(name,20);
        cin.getline(country,20);
        cin >> n;
        for(int i = 0; i < n; i++){
            skiLift[i].read();
        }
    }
    void print(){
        cout << name << " " << country << endl;
        for(int i = 0; i < n; i++){
            skiLift[i].print();
        }
    }
};

void biggestCapacity(SkiCenter * sc, int n){
    SkiCenter * maxCapacity = nullptr;
    int max = 0;
    int maxSkiLifts = 0;
    for(int i = 0; i < n; i++){
        int functionalLifts = 0;
        for(int j = 0; j < sc[i].n; j++){
            if(sc[i].skiLift[j].doesFunction == true){
                functionalLifts++;
            }
        }

        if(functionalLifts > 0 && sc[i].n > max){
            maxCapacity = &sc[i];
            max = sc[i].n;
            maxSkiLifts = functionalLifts;
        }else if(functionalLifts > 0 && sc[i].n == max && functionalLifts > maxSkiLifts){
            maxCapacity = &sc[i];
            max = sc[i].n;
            maxSkiLifts = functionalLifts;
        }
    }
    if(maxCapacity != nullptr){
        cout << "Name: " << maxCapacity->name << endl;
        cout << "Country: " << maxCapacity->country << endl;
        cout << "Capacity: " << maxCapacity->n << endl;
    }else{
        cout << "Error" << endl;
    }
}

int main(){
    int n; cin >> n; cin.ignore();
    SkiCenter skiCenter[n];
    for(int i = 0; i < n; i++){
        skiCenter[i].read();
    }

    biggestCapacity(skiCenter, n);

    return 0;
}