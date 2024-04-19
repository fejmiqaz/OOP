#include<iostream>
#include<cstring>
using namespace std;

class Vehicle{
private:
    char registration[9];
    char * name;
    int location;
    int maxPassengers;
    int kms;
    void copy(const Vehicle & v){
        strcpy(this->registration, v.registration);
        this->location = v.location;
        this->maxPassengers = v.maxPassengers;
        this->kms = v.kms;
        this->name = new char[strlen(v.name)+1];
        strcpy(this->name, v.name);
    }
public:
    Vehicle(char *registration="", char *name="", int location = 1, int maxPassengers = 3) {
        strcpy(this->registration, registration);
        this->location = location;
        this->maxPassengers = maxPassengers;
        this->kms = 0;
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
    }
    Vehicle(const Vehicle & other){
        copy(other);
    }

    Vehicle & operator=(const Vehicle & v){
        if(this!=&v){
            delete[] name;
            copy(v);
        }
        return * this;
    }

    friend ostream & operator << (ostream & out, Vehicle & v){
        return out << v.name << " " << v.location << " " << v.registration << " " << v.kms << endl;
    }

    bool operator==(const Vehicle & rhs) const{
        return strcmp(registration, rhs.registration) == 0;
    }

    bool operator!=(const Vehicle & rhs) const {
        return !(rhs == * this);
    }

    Vehicle& operator+=(int kms){
        this->kms += kms;
        return *this;
    }

    ~Vehicle(){
        delete[] name;
    }
};

class RideApp{
private:
    char name[21];
    Vehicle * vehicles;
    int n;
    void copy(const RideApp & ra){
        strcpy(this->name, ra.name);
        this->n = ra.n;
        this->vehicles = new Vehicle[this->n];
        for(int i = 0; i < this->n; i++){
            this->vehicles[i] = ra.vehicles[i];
        }
    }
public:
    RideApp(char *name = "") {
        strcpy(this->name,name);
        this->n = 0;
        this->vehicles = new Vehicle[n];
    }
    RideApp(const RideApp & other){
        copy(other);
    }

    RideApp & operator+=(const Vehicle & other){
        for(int i = 0; i < n; i++){
            if(vehicles[i] == other){
                return * this;
            }
        }

        Vehicle * tmp = new Vehicle[n + 1];
        for(int i = 0; i < n; i++){
            tmp[i] = vehicles[i];
        }
        tmp[n++] = other;
        delete[] vehicles;
        vehicles = tmp;
        return * this;
    }

    friend ostream & operator<<(ostream & out, RideApp & other){
        out << other.name << endl;
        if(other.n == 0){
            out << "Empty" << endl;
        }
        for(int i = 0; i < other.n;i++){
            out << other.vehicles[i] << endl;
        }
        return out;
    }

};

int main(){

    return 0;
}