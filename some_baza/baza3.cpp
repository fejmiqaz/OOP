#include<iostream>
#include<cstring>
using namespace std;

class Patnik {
private:
    char ime[101];
    int klasa;
    bool bicecycle;

    void copy_p(const Patnik &other) {
        strcpy(this->ime,other.ime);
        this->klasa = other.klasa;
        this->bicecycle = other.bicecycle;
    }

public:
    Patnik(const char* ime = "muli", int klasa = 1, bool bicecycle = true) {
        strcpy(this->ime, ime);
        this->klasa = klasa;
        this->bicecycle = bicecycle;
    }
    Patnik(const Patnik &other) {
        copy_p(other);
    }
    Patnik &operator=(const Patnik &other) {
        if (this != &other) {
            copy_p(other);
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Patnik& p) {
        out << p.ime << endl << p.klasa << endl << p.bicecycle << endl << endl;
        return out;
    }

    bool getBicecycle() const {
        return bicecycle;
    }

    int getKlasa() const {
        return klasa;
    }
    ~Patnik(){

    }
};


class Voz{

private:
    char destination[100];
    Patnik *patnici;
    int numOfElements;
    int capacity;
    void copy(Voz &other){
        strcpy(this->destination,other.destination);
        this->patnici=new Patnik[other.numOfElements];
        this->numOfElements=other.numOfElements;
        for(int i=0;i<numOfElements;i++){
            this->patnici[i]=other.patnici[i];
        }
        this->capacity=other.capacity;

    }
public:
    Voz() {
        strcpy(this->destination, "destinacija");
        this->patnici = nullptr;
        this->numOfElements = 0;
        this->capacity=0;
    }

    Voz(char *destination, int capacity){
        strcpy(this->destination,destination);
        this->capacity=capacity;
        this->numOfElements=0;
        this->patnici=nullptr;
    }
//copy constructor
    Voz(Voz &other){
        copy(other);
    }
    Voz &operator=(Voz &other){
        if(this!=&other) {
            delete [] patnici;
            copy(other);
        }
        return *this;

    }

    Voz &operator+=(const Patnik& p) {
        if(p.getBicecycle() && capacity==0) {
            return *this;
        }

        Patnik* tmp = new Patnik[numOfElements + 1];
        for(int i = 0; i < this->numOfElements; i++) {
            tmp[i] = patnici[i];
        }
        tmp[numOfElements++] = p;

        delete [] patnici;
        patnici = tmp;


        return *this;
    }
    friend ostream &operator<<(ostream &out,const Voz &v){
        out<< v.destination<<endl;
        if(v.capacity==0) {
            for (int i = 0; i < v.numOfElements; i++) {
                if (!v.patnici[i].getBicecycle()) {
                    out << v.patnici[i];
                }
            }
            return out;
        }

        for(int i = 0; i < v.numOfElements; i++) {
            out << v.patnici[i];
        }

        return out;

    }
    void patniciNemaMesto() {
        int count_bikes = 0, no_room1 = 0, no_room2 = 0;
        for (int i = 0; i < numOfElements; i++) {
            if (patnici[i].getBicecycle()&& patnici[i].getKlasa()==1) {
                count_bikes++;
            }
            if ((patnici[i].getBicecycle() && patnici[i].getKlasa()==1) && (count_bikes > capacity)) {
                no_room1++;
            }
        }
        for (int i = 0; i < numOfElements; i++) {
            if (patnici[i].getBicecycle() && patnici[i].getKlasa()==2) {
                count_bikes++;
            }
            if ((patnici[i].getBicecycle() && patnici[i].getKlasa()==2) && (count_bikes > capacity)) {
                no_room2++;
            }
        }
        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << no_room1 << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << no_room2 << endl;
    }
    ~Voz(){
        delete [] patnici;
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