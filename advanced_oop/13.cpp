#include<iostream>
#include<cstring>
using namespace std;

class Pasta{
private:
    char * name;
    float price;
    int discount, calories;
    void copy(const Pasta & copy){
        name = new char[strlen(copy.name)+1];
        strcpy(this->name, copy.name);
        price = copy.price;
        discount = copy.discount;
        calories = copy.calories;
    }

public:
    Pasta(){
        price = 0;
        discount = 0;
        calories = 0;
        strcpy(name, "unfound");
    }
    Pasta(char *name, float price, int discount, int calories){
        name = new char[strlen(name)+1];
        strcpy(this->name,name);
        this->price = price;
        this->discount = discount;
        this->calories = calories;
    }
    Pasta(const Pasta & other){
        copy(other);
    }
    ~Pasta(){
        delete[] name;
    }

    void dby5(){
        discount-=5;
    }

    void setName(char *name) {
        Pasta::name = name;
    }

    void setDiscount(int discount) {
        Pasta::discount = discount;
    }

    friend ostream& operator<<(ostream & out, const Pasta & other){
        out << other.name << " " << other.calories << " " << other.price << " ";
        if(other.discount > 0){
            out << "(" << other.discount << ")" << endl;
        }
        return out;
    }
    void print(){
        cout << name << " " << calories << " " << price << " " << discount << endl;
    }
};

class ItalianRestaurant{
private:
    char name[50];
    Pasta * pasta;
    int n;
    void copy(const ItalianRestaurant & ir){
        this->pasta = new Pasta[this->n];
        for(int i = 0; i < this->n; i++){
            this->pasta[i] = ir.pasta[i];
        }
        this->n = ir.n;
        strcpy(this->name, ir.name);
    }
public:
    ItalianRestaurant(){
        strcpy(name, "italianRestaurant");
        n = 0;
    }
    ItalianRestaurant(char *name, int n){
        pasta = new Pasta[0];
        this->n = n;
        strcpy(this->name,name);
    }
    ItalianRestaurant(const ItalianRestaurant & other){
        copy(other);
    }
    ~ItalianRestaurant(){
        delete[] pasta;
    }
};

int main(){
    Pasta pasta;
    pasta.print();

    return 0;
}