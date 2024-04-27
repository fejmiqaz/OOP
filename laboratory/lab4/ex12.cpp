#include<iostream>
#include<cstring>
using namespace std;

class Vehicle {
protected:
    char * brand;
    char * model;
    int yearOfProduction;
    int price;
    void copy(const Vehicle & other){
        this->brand = new char[strlen(other.brand) + 1]; strcpy(this->brand,other.brand);
        this->model = new char[strlen(other.model) + 1]; strcpy(this->model, other.model);
        this->yearOfProduction = other.yearOfProduction;
        this->price = other.price;
    }
public:
    Vehicle(char *brand = "", char *model = "", int yearOfProduction = 0, int price = 0){
         this->brand = new char[strlen(brand)+1]; strcpy(this->brand,brand);
         this->model = new char[strlen(model) + 1]; strcpy(this->model, model);
         this->yearOfProduction = yearOfProduction;
         this->price = price;
    }

    Vehicle & operator=(const Vehicle & other){
        if(this!=&other){
            delete[] brand;
            delete[] model;
            copy(other);
        }
        return * this;
    }

    double getRentPricePerHour() const {}
    void print() {
         cout << brand << " " << model << endl;
    }

};

class PassengerVehicle : public Vehicle {
    int numSeats, numDoors;
public:
    PassengerVehicle(const Vehicle & other, int numSeats = 0, int numDoors = 0) : Vehicle(other){
        this->numDoors = numDoors;
        this->numSeats = numSeats;
    }
    double getRentalPricePerHour(){
        return price + price * 0.1;
    }
    void print() {
        Vehicle::print();
        cout << numSeats << " " << getRentalPricePerHour() << " euros." << endl;
    }
};

class FreightVehicle : public Vehicle {
    int cargoCapacity, horsepower;
public:
    FreightVehicle(const Vehicle & other,int cargoCapacity = 0, int horsepower = 0) : Vehicle(other) {
        this->cargoCapacity = cargoCapacity;
        this->horsepower = horsepower;
    }

    double getRentPricePerHour() {
        return price + price * 0.5;
    }
    void print(){
        Vehicle::print();
        cout << cargoCapacity << " - " << getRentPricePerHour() << " euros" << endl;
    }
};


// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int n;
    cin >> n;
    char manufacturer[100];
    char model[100];
    int productionYear;
    int rentalPricePerHour;

    for (int i = 0; i < n; i++) {
        cin >> manufacturer;
        cin >> model;
        cin >> productionYear;
        cin >> rentalPricePerHour;

        Vehicle v = Vehicle(manufacturer, model, productionYear, rentalPricePerHour);

        if (i % 2) {
            int cargoCapacity;
            int horsePower;
            cin >> cargoCapacity;
            cin >> horsePower;
            FreightVehicle fv = FreightVehicle(v, cargoCapacity, horsePower);
            fv.print();
        } else {
            int numSeats;
            int numDoors;
            cin >> numSeats;
            cin >> numDoors;
            PassengerVehicle pv = PassengerVehicle(v, numSeats, numDoors);
            pv.print();
        }
    }


    return 0;
}