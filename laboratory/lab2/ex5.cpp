#include<iostream>
#include<cstring>
using namespace std;

/* To create a class BasketballPlayer that will have these:
 * - the name of the player (char array of 20 characters)
 * - surname of the player (char array of 20 characters)
 * - jersey number (int)
 * - points from the first match (int)
 * - points from the second match (int)
 * - points from the third match (int)
 * To write the necessary methods for the class, and a method for printing the data and a method for calculating the average points.
 * On standard input are given name, surname, jersey number and points from 3 matches individually.
 * On standard output to print the data of the player. */

class BasketballPlayer{
private:
    char name[20], surname[20];
    int jNumber, pfm, psm, ptm;
public:
    BasketballPlayer(char *_name = "No information", char * _surname = "No information",
                     int _jNumber = 0, int _pfm = 0, int _psm = 0, int _ptm = 0) {
        strcpy(name,_name);
        strcpy(surname,_surname);
        jNumber = _jNumber;
        pfm = _pfm;
        psm = _psm;
        ptm = _ptm;
    }
     ~BasketballPlayer() {}
    void print(){
        double average = (pfm + psm + ptm);
        cout << "Player: "<< name << " " << surname << " with number: " << jNumber << " has " << average / 3 << " points on average" << endl;
    }
};

int main(){
    BasketballPlayer basketballPlayer[10];
    char name[20], surname[20];
    int jnumber, pfm, psm, ptm;
    int n; cin >> n;
    cin.ignore();
    for(int i = 0; i < n; i++){
        cin.getline(name,20);
        cin.getline(surname,20);
        cin >> jnumber >> pfm >> psm >> ptm;
        basketballPlayer[i] = BasketballPlayer(name, surname, jnumber, pfm, psm, ptm);
        basketballPlayer[i].print();
        cin.ignore();
    }

    return 0;
}