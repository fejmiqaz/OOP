#include<iostream>
#include<cstring>

using namespace std;

class Invalid_ID_Exception {
public:
    void message(){
        cout << "The id number has a non-digit value" << endl;
    }
    void message2(){
        cout << "The id number has more than 9 characters" << endl;
    }
};

class DonaciskiApel {
private:
    char name[50];
    char id[50];
    int collected, neededFunds;
public:
    DonaciskiApel() {}

    bool hasNonDigits(char * s){
        int cnt = 0;
        for(int i = 0; i < strlen(s); i++){
            if(isalpha(s[i])){
                cnt++;
            }
        }
        if(cnt >= 1){
            return true;
        }else{
            return false;
        }
    }

    DonaciskiApel(char *name, char *id, int neededFunds) {
//        name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->id, id);
        this->collected = 0;
        this->neededFunds = neededFunds;
    }

    void setCollected(int collected) {
        DonaciskiApel::collected = collected;
    }

    const char *getId() const {
        return id;
    }

    bool operator==(const DonaciskiApel & d){
        return !(strcmp(id, d.id))==0;
    }

    friend ostream &operator<<(ostream &os, const DonaciskiApel &apel) {
        os << apel.id << " " << apel.name << " ";
        if (apel.collected == 0) {
            os << apel.neededFunds - apel.collected << " more denars are needed";
        } else if (apel.collected > 0){
            os << "collected" << endl;
        }
        return os;
    }

    int operator+=(int s) {
        collected += s;
        return collected;
    }

//    ~DonaciskiApel() {
//        delete[] name;
//    }

    bool operator<(const DonaciskiApel & d){
        return neededFunds < d.neededFunds;
    }
};


class DonaciskoDurstvo {
private:
    char name[30];
    DonaciskiApel *donactionAction;
    int n;
public:
    explicit DonaciskoDurstvo(char *name) {
        strcpy(this->name, name);
        this->n = 0;
        donactionAction = new DonaciskiApel[n];
    }

    DonaciskoDurstvo &operator+=(const DonaciskiApel &d) {

        for(int i = 0; i < n; i++){
            if(donactionAction[i].getId() == d.getId()){
                return * this;
            }
        }

        DonaciskiApel *tmp = new DonaciskiApel[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = donactionAction[i];
        }
        tmp[n++] = d;
        delete[] donactionAction;
        donactionAction = tmp;
        return * this;
    }

    bool primiiDonacija(char * id, int donatedFund) {
        for(int i = 0; i < strlen(id); i++){
            if(reinterpret_cast<const char *>(id[i]) == donactionAction[i].getId()){
                donactionAction[i].setCollected(donatedFund);
                return true;
            }
        }
        return false;
    }

    friend ostream &operator<<(ostream &os, const DonaciskoDurstvo &durstvo) {
        for(int i = 0; i < durstvo.n; i++){
            os << durstvo.donactionAction[i] << endl;
        }
        os << "President: " << durstvo.name << endl;
        return os;
    }
};

int main() {


    DonaciskoDurstvo donacii("Velko Velkovski");
    int n;
    char naziv[50], id[50];
    int potrebnasuma, doniranasuma;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin.get();
        cin.getline(naziv, 50);
        cin >> id >> potrebnasuma;

        DonaciskiApel edna(naziv, id, potrebnasuma);
        donacii += edna;

    }

    //donation
    cin >> n;
    for (int i = 0; i < n; i++) {

        cin >> id >> doniranasuma;

        try {
            if (strlen(id) > 9) {
                throw Invalid_ID_Exception();
            }
//            if (!donacii.primiiDonacija(id, doniranasuma)) {
//                cout << "The donation is not taken. Wrong ID." << endl;
//            }
        }catch (Invalid_ID_Exception &e){
            e.message();
        }

        try {
            if (!donacii.primiiDonacija(id, doniranasuma)) {
                cout << "The donation is not taken. Wrong ID." << endl;
            }
        } catch (Invalid_ID_Exception &e) {
            e.message2();
        }

    }
    cout << "===============" << endl;
    cout << donacii;

}
