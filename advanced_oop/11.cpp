#include <iostream>
#include <cstring>
using namespace std;

class Pair{
private:
    char * key;
    int value;
    void copy(const Pair & p){
        key = new char[strlen(key)+1];
        strcpy(this->key,p.key);
        this->value = p.value;
    }
public:
    Pair(){}
    Pair(char *key, int value) {
        this->key = new char[strlen(key)+1];
        strcpy(this->key, key);
        this->value = value;
    }
    Pair(const Pair & other){
        copy(other);
    }
    ~Pair(){
        delete [] key;
    }

    Pair & operator--(){
        --this->value;
        return * this;
    }
    Pair & operator--(int){
        Pair temp(*this);
        --(*this);
        return temp;
    }

    int getValue() const {
        return value;
    }

    Pair operator*( Pair & other){
        Pair result;
        if(strlen(this->key) < strlen(other.key)){
            result.key = new char[strlen(this->key)+1];
            strcpy(result.key, this->key);
        }else{
            result.key = new char[strlen(other.key)+1];
            strcpy(result.key,this->key);
        }
        result.value = this->value * other.value;
        return result;
    }

    friend ostream & operator<<(ostream & out, const Pair & p){
        out << "'" << p.key << "'" << " -> " << p.value << "'";
        return out;
    }
};
class Kolekcija{
private:
    Pair * pair;
    int n;
    void copy(const Kolekcija & c){
        pair = new Pair[this->n];
        this->n = c.n;
        for(int i = 0; i < this->n; i++){
            this->pair[i] = c.pair[i];
        }
    }
public:
    Kolekcija(){}
    Kolekcija(int n) {
        pair = new Pair[n];
        this->n = n;
    }
    Kolekcija(const Kolekcija & other){
        copy(other);
    }
    ~Kolekcija(){
        delete[] pair;
    }

    Kolekcija& operator+=(const Kolekcija & c){
        int newSize = this->n + c.n;
        Pair * newPair = new Pair[newSize];
        for(int i = 0; i < this->n;i++){
            newPair[i] = this->pair[i];
        }
        for(int i = 0; i < c.n;i++){
            newPair[this->n+i] = c.pair[i];
        }
        delete[] this->pair;
        this->pair = newPair;
        this->n = newSize;
        return * this;
    }

    Kolekcija & operator+=(const Pair & p){
        Pair * newPair = new Pair[n+1];
        for(int i = 0; i < n; i++){
            newPair[i] = pair[i];
        }
        newPair[n++] = p;
        delete[] pair;
        pair = newPair;
        return * this;
    }

    bool operator<(const Kolekcija & c){
        int productThis = 1;
        for(int i = 0; i < n; i++){
            productThis *= pair[i].getValue();
        }
        int productOther = 1;
        for(int i = 0; i < c.n; i++){
            productOther *= c.pair[i].getValue();
        }
        return productThis < productOther;
    }

    int greater(int value){
        int count = 0;
        for(int i = 0; i < n; i++){
            if(pair[i].getValue() > value){
                count++;
            }
        }
        return count;
    }

    friend ostream & operator<< (ostream & out, const Kolekcija & other){
        for(int i = 0; i < other.n; i++){
            out << other.pair[i];
        }
        return out;
    }
};
void read(char *k, float *v) {
    cin >> k;
    cin >> *v;
}
int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator --(int) -----" << endl;
    cout << p1--;
    cout << p1;
    cout << "----- operator -- -----" << endl;
    cout << --p2;
    cout << "----- operator * -----" << endl;
    Pair p = p1 * p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

    cout << "----- class Kolekcija -----" << endl;
    cout << "----- constructor -----" << endl;
    Kolekcija k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Kolekcija k2(k);
    cout << "----- operator < -----" << endl;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    k2 += p1;
    if(k < k2) {
        cout << "k < k2" << endl;
    } else {
        cout << "k >= k2" << endl;
    }
    cout << "----- greater -----" << endl;
    int x;
    cin >> x;
    int pp = k.greater(x);
    cout << pp;
    return 0;
}