#include <iostream>
#include <cstring>

using namespace std;

enum Type{
    APPETIZER,
    MAINCOURSE,
    DESSERT
};

class Brunch{
private:
    int ID;
    char name[31];
    double price;
    Type type;
    void copy(const Brunch & b){
        this->ID = b.ID;
        strcpy(this->name, b.name);
        this->price = b.price;
        this->type = b.type;
    }
public:
    Brunch(){}
    Brunch(const char * name, int id, double price, Type type) {
        this->ID = id;
        strcpy(this->name, name);
        this->price = price;
        this->type = type;
    }
    Brunch(const Brunch & other){
        copy(other);
    }

    friend ostream &operator<<(ostream &os, const Brunch &brunch) {
        os << brunch.name << " " << brunch.price << " " << brunch.type << endl;
        return os;
    }
    bool operator==(const Brunch & other){
        return (ID == other.ID);
    }
    Brunch & operator-=(double minus){
        price -= price * (minus / 100);
        return * this;
    }

    Type getType() const {
        return type;
    }
};

class Restaurant{
private:
    char name[41];
    Brunch * brunches;
    int n;
    static int LOYAL_DISCOUNT;
    void copy(const Restaurant & b){
        this->n = b.n;
        strcpy(this->name, b.name);
        brunches = new Brunch[this->n];
        for(int i = 0; i < n; i++){
            this->brunches[i] = b.brunches[i];
        }
    }
public:
    Restaurant(char *name = "") {
        this->n = 0;
        strcpy(this->name,name);
        brunches = new Brunch[0];
    }
    Restaurant(const Restaurant & other){
        copy(other);
    }
    Restaurant & operator=(const Restaurant & other){
        if(this!=&other){
            delete[] brunches;
            copy(other);
        }
        return * this;
    }

    ~Restaurant(){
        delete[] brunches;
    }

    Restaurant & operator+=(const Brunch & other){
        for(int i =0; i < n; i++){
            if(brunches[i] == other){
                return * this;
            }
        }
        Brunch * tmp = new Brunch[n+1];
        for(int i = 0; i < n; i++){
            tmp[i] = brunches[i];
        }
        tmp[n++] = other;
        delete[] brunches;
        brunches = tmp;
        return * this;
    }
    bool operator>(const Restaurant & other){
        return n > other.n;
    }

    static int getLOYAY_DISCOUNT() {
        return LOYAL_DISCOUNT;
    }

    static void setLOYAL_DISCOUNT(int loyalDiscount) {
        LOYAL_DISCOUNT = loyalDiscount;
    }

    friend ostream &operator<<(ostream &os, const Restaurant &restaurant) {
        os << restaurant.name << endl;
        for(int i = 0; i < restaurant.n; i++){
            os << restaurant.brunches[i];
        }
        return os;
    }
    // need to work on this method
    void decrease(Type type, double percent){}
};
// need to work on this method
Restaurant biggestMenu(Restaurant * restaurant, int n){}

int main() {
    int test_case;
    cin >> test_case;
    switch (test_case) {
        case 0: {
            cout << "TESTING BRUNCH CONSTRUCTOR" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            cout << "TEST PASSED" << endl;
            break;
        }
        case 1: {
            cout << "TESTING BRUNCH OPERATOR <<" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            cout << appetizer;
            cout << mainCourse;
            cout << dessert;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 2: {
            cout << "TESTING BRUNCH OPERATOR -=" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            cout << appetizer;
            cout << mainCourse;
            cout << dessert;

            appetizer -= 10;
            mainCourse -= 20.2;
            mainCourse -= 25;

            cout << appetizer;
            cout << mainCourse;
            cout << dessert;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 3: {
            cout << "TESTING RESTAURANT CONSTRUCTOR and <<" << endl;

            Restaurant restaurant("Little Italy");
            cout << restaurant;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 4: {
            cout << "TESTING RESTAURANT OPERATOR += and <<" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            Restaurant restaurant("Little Italy");
            restaurant += appetizer;
            restaurant += mainCourse;
            restaurant += dessert;

            Restaurant::setLOYAL_DISCOUNT(15.5);
            cout << restaurant;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 5: {
            cout << "TESTING RESTAURANT OPERATOR += and <<" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);

            Restaurant restaurant("Little Italy");
            restaurant += appetizer;
            restaurant += mainCourse;
            restaurant += dessert;
            restaurant += dessert;

            Restaurant::setLOYAL_DISCOUNT(20);
            cout << restaurant;

            cout << "TEST PASSED" << endl;
            break;

        }
        case 6: {
            cout << "TESTING RESTAURANT COPY-CONSTRUCTOR and OPERATOR =" << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);
            Brunch appetizer1("Caprese", 4, 150, Type::APPETIZER);
            Brunch dessert1("Mousse", 5, 350, Type::DESSERT);

            Restaurant restaurant("Little Italy");
            restaurant += appetizer;
            restaurant += mainCourse;
            restaurant += dessert;

            Restaurant restaurant2(restaurant);
            Restaurant restaurant4;
            {
                Restaurant restaurant3("Galaxy");
                restaurant3 += appetizer1;
                restaurant3 += dessert1;
                restaurant4 = restaurant3;
            }

            cout << restaurant2;
            cout << restaurant4;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 7: {
            cout << "TESTING RESTAURANT OPERATOR > " << endl;

            Brunch appetizer("Salad", 1, 200, Type::APPETIZER);
            Brunch appetizer1("Caprese", 1, 150, Type::APPETIZER);
            Brunch mainCourse("Salmon", 2, 400, Type::MAINCOURSE);
            Brunch mainCourse1("Seafood", 2, 500, Type::MAINCOURSE);
            Brunch dessert("Cheesecake", 3, 300, Type::DESSERT);
            Brunch dessert1("Mousse", 4, 300, Type::DESSERT);


            Restaurant restaurant1("Little Italy");
            restaurant1 += appetizer;
            restaurant1 += mainCourse;
            restaurant1 += dessert;


            Restaurant restaurant2("Ember");
            restaurant2 += appetizer1;
            restaurant2 += mainCourse1;
            restaurant2 += dessert;
            restaurant2 += dessert1;


            if (restaurant2 > restaurant1) {
                cout << "TEST PASSED" << endl;
            }

            break;
        }
        case 8: {
            cout << "TESTING METHOD decrease" << endl;

            char rName[40];
            cin.ignore();
            cin.getline(rName, 40);
            Restaurant restaurant(rName);

            int n;
            cin >> n;

            char name[30];
            int id;
            float cost;
            int type;

            for (int i=0; i<n; i++) {
                cin.ignore();
                cin.getline(name,30);
                cin >> id;
                cin >> cost;
                cin >> type;

                Brunch brunch(name, id, cost, (Type)type);
                restaurant+=brunch;
                restaurant+=brunch;
            }

            float perc;
            cin >> perc;
            cin >> type;

            cout << restaurant;
            restaurant.decrease((Type)type, perc);
            cout << restaurant;

            cout << "TEST PASSED" << endl;
            break;
        }
        case 9: {
            cout << "TESTING METHOD biggestMenuRestaurant" << endl;

            int n;
            cin >> n;
            Restaurant restaurants[n];

            char rName[40];

            for (int i=0; i<n; i++) {
                cin.ignore();
                cin.getline(rName, 40);
                Restaurant restaurant(rName);

                int m;
                cin >> m;

                char name[30];
                int id;
                float cost;
                int type;

                for (int j=0; j<m; j++) {
                    cin.ignore();
                    cin.getline(name,30);
                    cin >> id;
                    cin >> cost;
                    cin >> type;

                    Brunch brunch(name, id, cost, (Type)type);
                    restaurant+=brunch;
                }

                restaurants[i]=restaurant;

            }

            Restaurant biggestMenuRestaurant = biggestMenu(restaurants, 2);
            cout << biggestMenuRestaurant;

            cout << "TEST PASSED" << endl;

            break;
        }
    }

    return 0;
}