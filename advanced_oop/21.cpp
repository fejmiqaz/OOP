#include<iostream>
#include<cstring>
using namespace std;

class Tickets {
protected:
    int ID[12];
    char event[100];
    float price;
    static int discount;
public:
    Tickets(int *id, char *event, float price) : price(price) {
        strcpy(this->event,event);
        for(int i = 0; i < 12; i++){
            this->ID[i] = id[i];
        }
    }

    virtual float presmetajCena() = 0;

    bool falsifikat(int from, int to){
        for(int i = 12-4; i < 12; i++){
            if(ID[i] < from || ID[i] > to){
                return false;
            }
        }
        return true;
    }

    static void changeDiscount(int d){
        discount = d;
    }

    friend ostream &operator<<(ostream &os, const Tickets &tickets) {
        for(int i = 0; i < 12; i++){
            os << tickets.ID[i];
        }
        os << "-" << tickets.event << "-" << tickets.price;
        return os;
    }

    Tickets & operator+=(const Tickets & t){
        return reinterpret_cast<Tickets &>(price += t.price);
    }

};

int Tickets::discount = 0;

class Online : public Tickets {
private:
    bool isPremium;
public:
    Online(int *id, char *event, float price1, bool isPremium) : Tickets(id, event, price1), isPremium(isPremium) {}

    float presmetajCena() override {
        if(isPremium) {
            return price * 0.85;
        }else{
            return price;
        }
    }
};


class Offline : public Tickets {
private:
    bool hasReservation;
public:
    Offline(int *id, char *event, float price, bool hasReservation) : Tickets(id, event, price),
                                                                      hasReservation(hasReservation) {}

    float presmetajCena() override {
        if(hasReservation){
            return price * 1.1;
        }else{
            return price;
        }
    }
};

void vkupenPrihod(Tickets ** t, int n, int from, int to){
    float totalIncome = 0;
    for(int i = 0; i < n; i++){
        if(t[i]->falsifikat(from,to)){
            totalIncome += t[i]->presmetajCena();
        }
    }
    cout << totalIncome << endl;
}

//    bool falsifikat(int from, int to) const override {
//        for(int i = 9; i < 12; i++){
//            if(id[i] >= from && id[i] <= to){
//                return false;
//            }
//        }
//        return true;
//    }

//void vkupenPrihod(Tickets ** ticket, int n, int from, int to){
//    float totalIncome = 0;
//    for(int i = 0; i < n; i++){
//        if(!ticket[i]->falsifikat(from,to)){
//            totalIncome+=ticket[i]->presmetajCena();
//        }
//    }
//    cout << totalIncome << endl;
//}

int main() {
    int testCase;
    cin >> testCase;
    int ID[12];
    char nastan[100];
    float price;
    bool premium;
    bool rezervacija;
    int od, doo;

    if (testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> premium;
        Online o1(ID, nastan, price, premium);
        cout << o1 << endl;
        for (int i = 0; i < 12; i++)
            cin >> ID[i];
        cin >> nastan;
        cin >> price;
        cin >> rezervacija;
        Offline o2(ID, nastan, price, rezervacija);
        cout << o2 << endl;

    }
    else if (testCase == 2) {
        cout << "===== TESTING METHOD vkupenPrihod()  ======" << endl;
        int n;
        cin >> n;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; j++)
                cin >> ID[j];
            cin >> nastan;
            cin >> price;

            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        cin >> od;
        cin >> doo;
        vkupenPrihod(t, n, od, doo);
        for (int i = 0; i < n; ++i) {
            delete t[i];
        }
        delete[] t;
    }
    else if (testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        //cout<<n<<endl;
        Tickets** t = new Tickets*[n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 12; ++j)
                cin >> ID[j];
            cin >> nastan;
            //cout<<nastan<<endl;
            cin >> price;
            //cout<<price<<endl;
            if (i % 2 == 0){
                cin >> premium;
                t[i] = new Online(ID, nastan, price, premium);
            }
            else {
                cin >> rezervacija;
                //cout<<rezervacija<<endl;
                t[i] = new Offline(ID, nastan, price, rezervacija);
            }
        }
        int d;
        cin >> d;
        Tickets::changeDiscount(d);
        for (int i = 0; i < n; ++i)
            cout << *t[i] << endl;

    }
}
