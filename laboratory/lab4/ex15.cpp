#include<iostream>
#include<cstring>
using namespace std;

class Lekar {
protected:
    int fascimile;
    char name[11], surname[11];
    double startingSalary;
    void copy(const Lekar & l){
        this->fascimile = l.fascimile;
        strcpy(this->name, l.name);
        strcpy(this->surname, l.surname);
        this->startingSalary = l.startingSalary;
    }
public:
    Lekar(){}
    Lekar(int fascimile, char *name, char *surname, double startingSalary){
        this->fascimile = fascimile;
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        this->startingSalary = startingSalary;
    }
    Lekar(const Lekar & other){
        copy(other);
    }

    void pecati(){
        cout << name << " " << surname << endl;
    }
    double plata(){
        return startingSalary;
    }
};

class MaticenLekar : public Lekar {
private:
    int numOfPatients;
    double * kotizacii;
    void copy(const MaticenLekar & ml){
        this->numOfPatients = ml.numOfPatients;
        this->kotizacii = new double[this->numOfPatients+1];
        for(int i = 0; i < this->numOfPatients;i++){
            this->kotizacii[i] = ml.kotizacii[i];
        }
    }
public:
    MaticenLekar(){}
    MaticenLekar(const Lekar &other, int numOfPatients, double *kotizacii) : Lekar(other), numOfPatients(numOfPatients){
        this->kotizacii = new double[this->numOfPatients+1];
        for(int i = 0; i < numOfPatients; i++){
            this->kotizacii[i] = kotizacii[i];
        }
    }
    MaticenLekar(const MaticenLekar & other){
        copy(other);
    }
    void pecati(){
        for(int i = 0; i < numOfPatients; i++){
            pecati();
        }
    }
    double plata(){
        return startingSalary * 0.3;
    }
};

int main() {
    Lekar lekar(233111,"fejmi","qazimi",2500.3);
    lekar.pecati();
    cout << lekar.plata();

    MaticenLekar ml(lekar,5,36563.5);
    ml.pecati();

    return 0;
}