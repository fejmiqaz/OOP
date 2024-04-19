#include<iostream>
#include<cstring>
using namespace std;

class Online{
private:
    static bool premiumUser;
    int id[12];
public:
    Online(int * id, char * event, float price, bool premiumUser) {
        this->premiumUser = premiumUser;
        for(int i = 0; i < 12; i++){
            this->id[i] = id[i];
        }
    }
    friend ostream & operator<<(ostream & out, const Online & o){
        return out << o.premiumUser;
    }
    friend class Tickets;
};
class Offline{
private:
    static bool hasReservation;
public:
    explicit Offline(int * ID, char * event, float price, bool hasReservation) {
        this->hasReservation = hasReservation;
    }
    Offline(const Offline & other){
        this->hasReservation = other.hasReservation;
    }
    friend ostream & operator<<(ostream & out, const Offline & o){
        return out << o.hasReservation;
    }
    friend class Tickets;
};

class Tickets{
private:
    int id[12];
    char event[100];
    double price;
    static int discount;
    Online * online;
    Offline * offline;
public:
    Tickets(){
        this->discount = 0;
    }
    Tickets(int *id, char *event, double price, Online *online, Offline *offline){
        for(int i = 0; i < 12; i++){
            this->id[i] = id[i];
        }
        strcpy(this->event, event);
        this->price = price;
    }
    bool falsifikat(int from, int to){
        int last4 = id[8] * 1000 + id[9] * 100 + id[10] * 10 + id[11];
        return last4 >= from && last4 <= to;
    }
    float presmetajCena(){
        if(Online::premiumUser == true){
            price -= 0.15 * price;
        }
        if(Offline::hasReservation == true){
            price += 0.1 * price;
        }
        return price;
    }
    static void changeDiscount(int d){
        discount = d;
    }
    friend ostream & operator<<(ostream & out, const Tickets & t){
        return out << t.id << " " << t.price << " " << t.event << " " << t.discount;
    }
};

static void vkupenPrihod(Tickets ** t, int n, int from, int to){
    double totalIncome = 0.0;
    for(int i = 0; i < n; i++){
        if(!t[i]->falsifikat(from,to)){
            totalIncome += t[i]->presmetajCena();
        }
    }
    cout << "Total income: " << totalIncome << endl;
}

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
