#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;

struct Film{
    char name[100];
    int time;
    double price;
    bool discount;
    void print(){
        for(int i = 0; i < strlen(name); i++){
            cout << name[i] << " " << time << " " << fixed << setprecision(2) << price << endl;
        }
    }
};
struct FilmFestival{
    char name[100];
    char place[100];
    Film films[100];
    int no;
    void print(){
        for(int i = 0; i < strlen(name);i++){
            cout << name[i] << " ";
        }
        for(int i = 0; i < strlen(place); i++){
            cout << place[i] << endl;
        }
        for(int i = 0; i < no; i++){
            films[i].print();
        }
    }
};

void bestFestival(FilmFestival * filmFestival, int n){
    int cheapestIndex = -1;
    int maxDiscountFilms = 0;
    int maxDuration;

    for(int i = 0; i <n ; i++){
        int discountFilmsCount = 0;
        int totalDuration = 0;
        for(int j = 0; i < filmFestival[i].no; j++){
            if(filmFestival[i].films[j].discount){
                discountFilmsCount++;
            }
            totalDuration += filmFestival[i].films[j].time;
        }
        if(discountFilmsCount > maxDiscountFilms || (discountFilmsCount == maxDiscountFilms && totalDuration > maxDuration)){
            cheapestIndex = i;
            maxDiscountFilms = discountFilmsCount;
            maxDuration = totalDuration;
        }
    }
    if(cheapestIndex != -1){
        cout << filmFestival[cheapestIndex].name << endl;
        cout << filmFestival[cheapestIndex].place << endl;
    }else{
        cout << "No festival found" << endl;
    }
}


int main() {
    int i, j, n;
    FilmFestival ff[50];
    cin >> n;

    for (i = 0; i < n; i++) {
        cin >> ff[i].name;
        cin >> ff[i].place;
        cin >> ff[i].no;

        for (j = 0; j < ff[i].no; j++) {
            cin >> ff[i].films[j].name;
            cin >> ff[i].films[j].time;
            cin >> ff[i].films[j].price;
            cin >> ff[i].films[j].discount;
        }
    }

    for (i = 0; i < n; ++i) {
        ff[i].print();
    }

    bestFestival(ff, n);

    return 0;
}