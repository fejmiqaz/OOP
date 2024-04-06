#include<iostream>
#include<cstring>
using namespace std;

class Patnik{
private:
    static char name[100];
    int number;
    bool hasBicycle;
    void copy(const Patnik & p){
        strcpy(this->name, p.name);
        this->number = p.number;
        this->hasBicycle = hasBicycle;
    }
public:
    Patnik(){}
    Patnik(char *name, int number, bool hasBicycle){
        strcpy(this->name, name);
        this->number = number;
        this->hasBicycle = hasBicycle;
    }
    Patnik(const Patnik & other){
        copy(other);
    }
    friend ostream & operator<<(ostream& out, Patnik & patnik){
        out << "Name: " << patnik.name << endl;
        out << "Carriage class: " << patnik.number << endl;
        out << "Has bicycle: " << (patnik.hasBicycle ? "Yes" : "No") << endl;
        return out;
    }

    const char *getName() const {
        return name;
    }

    int getNumber() const {
        return number;
    }

    bool isHasBicycle() const {
        return hasBicycle;
    }

};

class Voz{
private:
    static char destination[100];
    Patnik * patnik;
    static int n, numOfCyclists;
    void copy(const Voz & p){
        this->n = p.n;
        this->numOfCyclists = p.numOfCyclists;
        patnik = new Patnik[this->n];
        for(int i = 0; i < this->n;i++){
            this->patnik[i] = p.patnik[i];
        }
    }
public:
    Voz(){}
    Voz(char *destination, int n) {
        strcpy(this->destination, destination);
        this->n = n;
        this->numOfCyclists = numOfCyclists;
        patnik = new Patnik[0];
    }
    Voz(const Voz & other){
        copy(other);
    }
    ~Voz(){
        delete [] patnik;
    }
    Voz & operator+=(const Patnik & v){
        Patnik * tmp = new Patnik[n+1];
        for(int i = 0; i < n; i++){
            tmp[i] = patnik[i];
        }
        tmp[n++] = v;
        delete [] patnik;
        patnik = tmp;
        return * this;
    }

    friend ostream & operator<<(ostream & out, const Voz & other){
        for(int i = 0; i < strlen(destination);i++){
            out << other.destination[i];
        }
        out << endl;
        for(int i = 0; i < n; i++){
            out << other.patnik[i];
        }
        return out;
    }
    void patniciNemaMesto() {
        int cyclistsAllowed = n; // Initialize the number of allowed cyclists
        int cyclistsInTrain = 0; // Initialize the number of cyclists already in the train
        int firstClassCyclists = 0; // Initialize the number of cyclists from first class

        for (int i = 0; i < numOfCyclists; i++) {
            if (patnik[i].isHasBicycle()) { // Check if the passenger has a bicycle
                if (patnik[i].getNumber() == 1 && firstClassCyclists < cyclistsAllowed) {
                    firstClassCyclists++; // Increment first class cyclists if space available
                } else if (patnik[i].getNumber() == 2 && cyclistsInTrain < cyclistsAllowed) {
                    cyclistsInTrain++; // Increment cyclists in train if space available
                } else {
                    cout << "Passenger " << patnik[i].getNumber() << " " << patnik[i].isHasBicycle() << " does not have space." << endl;
                }
            }
        }
    }
};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
