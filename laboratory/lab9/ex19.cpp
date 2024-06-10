#include<iostream>
#include<cstring>
using namespace std;

class InvalidSeatNumberException {
    char c;
public:
    InvalidSeatNumberException(char c): c(c){}

    void message(){
        cout << endl;
        cout << "Invalid Seat Number Exception" << endl;
    }
};

class Flight {
protected:
    char flightCode[40];
    char departureCity[100];
    char arrivalCity[100];
    double flightPrice, baggagePrice;
public:
//    Flight(){}
    Flight(char *flightCode, char *departureCity, char *arrivalCity, double flightPrice, double baggagePrice): flightPrice(flightPrice),baggagePrice(baggagePrice) {
        strcpy(this->flightCode,flightCode);
        strcpy(this->departureCity, departureCity);
        strcpy(this->arrivalCity, arrivalCity);
    }
    virtual double calculateTotalPrice() { return flightPrice + baggagePrice; }
    virtual void displayInfo(){ cout << flightCode << " " << departureCity << "-" << arrivalCity; }
};

class EconomyFlight : public Flight {
private:
    char seatNumber[5];
    static double LOYALTY_DISCOUNT;
public:

    EconomyFlight(const Flight & flight ,char *seatNumber) : Flight(flight) { strcpy(this->seatNumber, seatNumber);}
//
//    EconomyFlight(char *flightCode, char *departureCity, char *arrivalCity, double flightPrice, double baggagePrice)
//            : Flight(flightCode, departureCity, arrivalCity, flightPrice, baggagePrice) { strcpy(this->seatNumber,seatNumber);}


    bool checkSeatNumber(char m){
        return !(m == 'A' || m == 'B' || m == 'C' || m == 'D' || m == 'E' || m == 'F');
    }

    double calculateTotalPrice() override {
        if(checkSeatNumber(seatNumber[0])){
            throw InvalidSeatNumberException(seatNumber[0]);
        }
        double price = Flight::calculateTotalPrice() * LOYALTY_DISCOUNT;
        if(seatNumber[0] == 'C' || seatNumber[0] == 'F' ){
            price *= 1.30;
        }
        return price;
    }

    void displayInfo() override {
        Flight::displayInfo();
        cout << " " << seatNumber << endl;
        cout << "Total Price: $" << calculateTotalPrice() << endl;
    }

    static void setLoyaltyDiscount(double loyaltyDiscount) {
        LOYALTY_DISCOUNT = loyaltyDiscount;
    }
};

double EconomyFlight::LOYALTY_DISCOUNT = 0.80;



int main() {
    int testCase;
    cin>>testCase;
    char code[100];
    char from[100];
    char to[100];
    double price;
    double baggagePrice;
    char seatNumber[4];


        if(testCase == 1){
            cout << "===== Testiranje na klasite ======" << endl;
            int n;
            cin>>n;
            for(int i=0; i<n;i++){
                cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
                Flight f = Flight(code, from, to, price, baggagePrice);
                EconomyFlight ec = EconomyFlight(f,seatNumber);
                ec.displayInfo();
            }
        }

    if(testCase == 2){
        cout << "===== Testiranje na isklucoci ======" << endl;
        int n;
        cin>>n;
        for(int i=0; i<n;i++){
            cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
            try{
                Flight f = Flight(code, from, to, price, baggagePrice);
                EconomyFlight ec = EconomyFlight(f,seatNumber);
                ec.displayInfo();
            }catch(InvalidSeatNumberException & s){
                s.message();
            }
        }
    }


    if(testCase == 3){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>code>>from>>to>>price>>baggagePrice>>seatNumber;
        Flight f = Flight(code, from, to, price, baggagePrice);
        EconomyFlight ec = EconomyFlight(f,seatNumber);
        ec.displayInfo();
        EconomyFlight::setLoyaltyDiscount(50);
        ec.displayInfo();
    }

    return 0;
}
