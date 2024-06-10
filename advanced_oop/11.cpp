#include <iostream>
#include <cstring>
using namespace std;

class Pair{
private:
    char * key;
    float value;
    void copy(const Pair & p){
        key = new char[strlen(p.key)+1];
        strcpy(this->key,p.key);
        this->value = p.value;
    }
public:
    Pair(){}
    Pair(char *key, float value) {
        this->key = new char[strlen(key)+1];
        strcpy(this->key, key);
        this->value = value;
    }
    Pair(const Pair & other){
        copy(other);
    }

    Pair & operator=(const Pair & other){
        if(this!=&other){
            delete[] key;
            copy(other);
        }
        return * this;
    }

    ~Pair(){
        delete [] key;
    }

    Pair & operator--(){
        this->value--;
        return * this;
    }
    Pair operator--(int){
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
        out << "'" << p.key << "'" << " -> " << p.value << endl;
        return out;
    }
};

class Collection{
private:
    Pair * pair;
    int n;
    void copy(const Collection & c){
        n = c.n;
        pair = new Pair[n];
        for(int i = 0; i < n; i++){
            pair[i] = c.pair[i];
        }
    }
public:
    Collection(){
        this->n = 0;
    }
    Collection(int n) {
        pair = new Pair[0];
    }
    Collection(const Collection & other){
        copy(other);
    }
    ~Collection(){
        delete[] pair;
    }

    Collection &operator+=(const Pair & c){
        if((c.getValue() && n) == 0){
            return * this;
        }
        Pair * tmp = new Pair[n + 1];
        for(int i = 0; i < this->n;i++){
            tmp[i] = pair[i];
        }
        tmp[n++] = c;
        delete[]pair;
        pair = tmp;
        return * this;

    }

    bool operator<(const Collection & c){
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

    int greater(int value) const {
        int count = 0;
        for(int i = 0; i < n; i++){
            if(pair[i].getValue() > value){
                count++;
            }
        }
        return count;
    }

    friend ostream & operator<< (ostream & out, const Collection & other){
        out  << "Size: "<< other.n << endl;
        for(int i = 0; i < other.n; i++){
            out << other.pair[i];
            if(i < other.n - 1){
                out << endl;
            }
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

    cout << "----- class Collection -----" << endl;
    cout << "----- constructor -----" << endl;
    Collection k;
    cout << "----- operator += -----" << endl;
    k += p1;
    k += p2;
    k += p3;
    cout << "----- operator << -----" << endl;
    cout << k;
    cout << "----- copy constructor -----" << endl;
    Collection k2(k);
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
//    char key[50];
//    float value;
//    cout << "----- class Pair -----" << endl;
//    read(key, &value);
//    cout << "----- constructor -----" << endl;
//    Pair p1(key, value);
//    read(key, &value);
//    Pair p2(key, value);
//    Pair p3(p1);
//    cout << "----- operator << -----" << endl;
//    cout << p1;
//    cout << p2;
//    cout << "----- operator --(int) -----" << endl;
//    cout << p1--;
//    cout << p1;
//    cout << "----- operator -- -----" << endl;
//    cout << --p2;
//    cout << "----- operator * -----" << endl;
//    Pair p = p1 * p2;
//    cout << "----- operator = -----" << endl;
//    p3 = p;
//    cout << p3;
//
//    cout << "----- class Collection -----" << endl;
//    cout << "----- constructor -----" << endl;
//    Kolekcija k;
//    cout << "----- operator += -----" << endl;
//    k += p1;
//    k += p2;
//    k += p3;
//    cout << "----- operator << -----" << endl;
//    cout << k;
//    cout << "----- copy constructor -----" << endl;
//    Kolekcija k2(k);
//    cout << "----- operator < -----" << endl;
//    if(k < k2) {
//        cout << "k < k2" << endl;
//    } else {
//        cout << "k >= k2" << endl;
//    }
//    k2 += p1;
//    if(k < k2) {
//        cout << "k < k2" << endl;
//    } else {
//        cout << "k >= k2" << endl;
//    }
//    cout << "----- greater -----" << endl;
//    int x;
//    cin >> x;
//    int pp = k.greater(x);
//    cout << pp;
//    return 0;
}