#include<iostream>
#include<cstring>
using namespace std;

class Parcel {
protected:
    static int id;
    static int processingPrice;
    int idd;
    void copy(const Parcel & other){
        this->id = other.id;
        this->processingPrice = other.processingPrice;
    }
public:
    Parcel(int id = 1111, int price = 150) {
        id++;
        this->idd = id;
        this->processingPrice = price;
    }
    Parcel(const Parcel & other){
        copy(other);
    }


    static void setProcessingPrice(int price) {
        Parcel::processingPrice = price;
    }

    int getId() const {
        return id;
    }

    void print(){
        cout << id;
    }
    double price(){}
};
class Envelope : public Parcel {
protected:
    int W, L;
    char receiver[50];
    void copy(const Envelope & other){
        this->W = other.W;
        this->L = other.L;
        strcpy(this->receiver, other.receiver);
    }
public:
    Envelope(){}
    Envelope(int id,char *receiver,int w, int l) : W(w), L(l) {
        strcpy(this->receiver,receiver);
    }
    Envelope(const Envelope & other){
        copy(other);
    }
    double price() {
        return processingPrice + L * W * 0.3;
    }
    void print(){
        cout << receiver << " are envelops with ids: " << id << " ";
    }

    const char *getReceiver() const {
        return receiver;
    }
};

class PostOffice{
protected:
    Envelope * envelope;
    int n;
    void copy(const PostOffice & po){
        this->envelope = new Envelope[this->n];
        for(int i = 0; i < this->n; i++){
            this->envelope[i] = po.envelope[i];
        }
    }
public:
    PostOffice(){}
    PostOffice(int n) {
        this->envelope = new Envelope[0];
        this->n = 0;
    }
    PostOffice(const PostOffice & other){
        copy(other);
    }
    int sendEnvelope(int id, char * receiver, int length, int width){
        if(n < 100){
            Envelope newEnvelope(id,receiver,width,length);
            envelope[n++] = newEnvelope;
            return envelope->price();
        }else{
            cout << "Error!" << endl;
        }
    }
    void printEnvelopsTo(char * receiver) {
        cout << "Envelope addressed to: " << receiver << ":" << endl;
        for(int i = 0; i < n; i++){
            if(strcmp(envelope[i].getReceiver(), receiver) == 0 ){
                cout << "ID" << i << endl;
            }
        }
    }

};

int Parcel::id = 0;

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
