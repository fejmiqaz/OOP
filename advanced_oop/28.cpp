#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here

class Pizza {
protected:
    char name[20];
    char ingredients[100];
    float Price;
public:
    Pizza(){}
    Pizza(char *name, char *ingredients, float price) : Price(price) {
        strcpy(this->name, name);
        strcpy(this->ingredients, ingredients);
    }

    virtual float price() const = 0;

    friend ostream &operator<<(ostream &os, const Pizza &pizza) {
        os << pizza.name << ": " << pizza.ingredients << ", ";
        return os;
    }

    Pizza & operator*=(const Pizza & p){
        Price *= p.Price;
        return * this;
    }

    bool operator<(const Pizza & p) const{
        return price() < p.price();
    }

};

enum Size {
    small = 0,
    big = 1,
    family = 2
};

class FlatPizza : public Pizza {
private:
    Size size;
public:
    FlatPizza(char *name, char *ingredients, float price, Size size) : Pizza(name, ingredients, price) {
        if(size == 0){
            this->size = small;
        }else if(size == 1){
            this->size = big;
        }else if(size == 2){
            this->size = family;
        }
    }
    FlatPizza(char *name, char *ingredients, float price) : Pizza(name, ingredients, price), size(small) {}

    float price() const override {
        float adjPrice = 0.0;
        if(size == small){
            adjPrice = Price + Price * 0.1;
        }else if (size == big){
            adjPrice = Price + Price * 0.2;
        }else if(size == family){
            adjPrice = Price + Price * 0.3;
        }
        return adjPrice;
    }

    friend ostream &operator<<(ostream &os, FlatPizza pizza) {
        os << static_cast<const Pizza &>(pizza);
        if(pizza.size == small){ os << "small";}
        else if(pizza.size == big){ os << "big";}
        else if(pizza.size == family){ os << "family";}
        os << " - " << pizza.price() << endl;
        return os;
    }

};

class FoldedPizza : public Pizza {
private:
    static bool whiteFlour;
public:
    FoldedPizza(char *name, char *ingredients, float price) : Pizza(name, ingredients, price) {}

    static void setWhiteFlour(bool whiteFlour) {
        FoldedPizza::whiteFlour = whiteFlour;
    }

    float price() const override {
        float adjPrice = 0.0;
        if(whiteFlour){
            adjPrice = Price + Price * 0.1;
        }else{
            adjPrice = Price + Price * 0.3;
        }
        return adjPrice;
    }

    friend ostream &operator<<(ostream &os, FoldedPizza pizza1) {
        os << static_cast<const Pizza &>(pizza1);
        if(pizza1.whiteFlour){ os << "wf"; }
        else { os << "nwf"; }
        os << " - " << pizza1.price() << endl;
        return os;
    }

};

bool FoldedPizza::whiteFlour = true;

void expensivePizza(Pizza ** p, int n){
    float max = 0.0;
    int idx = 0;
    for(int i = 0; i < n; i++){
        if(p[i]->price() > max){
            max = p[i]->price();
            idx = i;
        }
    }
    if(FlatPizza * fp = dynamic_cast<FlatPizza*>(p[idx])){
        cout << *fp << endl;
    }else if(FoldedPizza * fp = dynamic_cast<FoldedPizza *>(p[idx])){
        cout << *fp << endl;
    }else{
        cout << *p[idx] << endl;
    }
}



// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
