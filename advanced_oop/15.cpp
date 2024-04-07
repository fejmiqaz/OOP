#include <iostream>
#include <cstring>
using namespace std;

// your code here

#include<iostream>
#include<cstring>

using namespace std;

class Parcel {
private:
    int ID;
    int processingPrice;
public:
    Parcel(int ID = 1111, int price = 150) {
        this->ID = ID;
        this->processingPrice = price;
    }
    Parcel(const Parcel &other) {
        this->ID = other.ID;
        this->processingPrice = other.processingPrice;
    }

    static void setProcessingPrice(int processingPrice) {
        Parcel::processingPrice = processingPrice;
    }

    int getProcessingPrice() const {
        return processingPrice;
    }

    int getId() const {
        return ID;
    }

    friend ostream& operator<<(ostream && out, Parcel & p){
        out << p.processingPrice << " " << p.ID << endl;
        return out;
    }
};

class Envelope {
private:
    int id;
    char receiver[50];
    int height, width;
public:
    Envelope(){}
    Envelope(char *receiver, int height, int width) {
        strcpy(this->receiver, receiver);
        this->height = height;
        this->width = width;
    }
    Envelope(const Envelope & other){
        id = other.id;
        strcpy(this->receiver, other.receiver);
        height = other.height;
        width = other.width;
    }

    const char *getReceiver() const {
        return receiver;
    }

    double price() const {
        double sum = Parcel::getProcessingPrice() + height * width * 0.3;
        return sum;
    }
    friend ostream& operator<<(ostream & out, Envelope & e){
        out << e.receiver << " " << e.width << " " << e.height << endl;
        return out;
    }

    int getId() const {
        return id;
    }
};

class PostOffice{
private:
    Envelope envelope[100];
    int n;
public:
    PostOffice(){
        this->n = 0;
    }
    void sendEnvelope(int id, char * receiver, int length, int width){
        if(n < 100){
            Envelope newEnvelope(receiver, length, width);
            envelope[n++] = newEnvelope;
        }else{
            cout << "Error" << endl;
        }
    }
    void printEnvelopsTo(char * receiver) const {
        cout << "Envelope addressed to: " << receiver << ":" << endl;
        for(int i = 0; i < n; i++){
            if(strcmp(envelope[i].getReceiver(),receiver)==0){
                cout << "ID: " << i << endl;
            }
        }
    }

    friend ostream& operator<<(ostream & out, PostOffice & p){
        for(int i = 0; i < p.n; i++){
            out << p.envelope[i];
        }
        return out;
    }

};

int main() {

    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) { // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) { // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) { // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) { // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {// Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: " << p2.price() << endl;
        }
    }
    return 0;
}
