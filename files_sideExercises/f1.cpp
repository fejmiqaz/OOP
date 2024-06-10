#include<iostream>
#include<fstream>
#include<string>
using namespace std;


int main(){
    ofstream out("C:\\Users\\User\\Desktop\\FINKI\\OOP\\Exercises\\files_sideExercises\\f1.txt");

    if(out.is_open()){
        out << "Fejmi" << endl;
    }
    out.close();


    return 0;
}