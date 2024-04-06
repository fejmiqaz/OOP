#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;

/* Create a structure (in C++ programming language) Film for representing films (movies). The structure should contain: (5 points)

Movie title (array of 100 characters)
Duration (integer)
Price (decimal number)
Is there a student discount (1-yes, 0-no)
Create a structure FilmFestival, that will contain: (10 points)

Name of the festival (array of 100 characters)
Place (where the festival is held) (array of 100 characters)
List of films that will be presented on the festival (array of no more than 100 elements of type Film)
Number of elements in the list (integer)
Write a function print that will print the information for each film in a given film festival (5 points) in the following format:

[Name of the festival] [Place]
[Title1] [Duration1] [Price1]
[Title2] [Duration2] [Price2]

Write a function BestFestival that accepts an array of FilmFestival variables and number of festivals in the array and will
 print the name of the festival that is cheapest for students and the place it is held. For the cheapest festival is considered
 the one that has most films that have student discount. If there is more that one festival with these characteristics than print
 the festival that has the longest duration of all the films. (20 points)
Complete functionality of the whole program */

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