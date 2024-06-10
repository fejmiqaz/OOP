#include<iostream>
#include<cstring>
using namespace std;

class Tickets{
    int ID[12];
    char event[100];
    double price;
public:
    Tickets(int *id, char *event, double price) {
        strcpy(this->event, event);

    }

};


int main(){

    return 0;
}