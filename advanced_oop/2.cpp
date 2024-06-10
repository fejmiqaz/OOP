#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;

/* Define a structure for Driver with fields for his name (char array of max 100) and time in seconds (integer).
 * Then define a structure Race with fields for location (char array of max 100), number of drivers (integers) and
 * an array of drivers (max 100).

Write a main function that will read the data for N races and for each race will print the top 3 drivers by their time
in increasing order.

For the format of the input data and format of the output, see the sample input and sample output (the time is printed in
two fixed places for minutes and two fixed places with leading zero for seconds, separated with :). */

struct Driver{
    char name[100];
    int time;
    void print(){
        for(int i = 0; i < strlen(name); i++){
            cout << name[i] << " ";
        }
    }
};
struct Race{
    char location[100];
    int n;
    Driver drivers[100];
};

void top3(Race * races, int n){
    Driver tmp;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            if(races[i].drivers[j].time < races[i].drivers[j+1].time){
                tmp = races[i].drivers[j];
                races[i].drivers[j] = races[i].drivers[j+1];
                races[i].drivers[j+1] = tmp;
            }
        }
    }
    for(int i = 0; i < 3 & i < races[i].n; i++){
        for(int j = i; j < 3 & j < races[i].n; j++){
            int mins = races[i].drivers[j].time / 60;
            int secs = races[i].drivers[j].time % 60;
            cout << j+1 << ". " << races[i].drivers[j].name << " " << mins << ":" << secs <<endl;
        }
        cout << endl;
    }

}

int main() {
    int n;
    cin >> n;
    Race races[n];
    for(int i = 0; i < n; ++i) {
        cin >> races[i].location;
        cin >> races[i].n;
        for(int j = 0; j < races[i].n; ++j) {
            cin >> races[i].drivers[j].name;
            cin >> races[i].drivers[j].time;
        }
    }

    for(int i = 0; i < 3; ++i) {
        cout << races[i].location << " (" << races[i].n << " Drivers)" << endl;
        top3(&races[i], n);
    }

    return 0;
}