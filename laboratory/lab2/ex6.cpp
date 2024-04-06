#include<iostream>
#include<cstring>
using namespace std;

class Country{
private:
    char name[100];
    char capital[100];
    double area;
    double population;
public:
    Country(char * _name = "Blank", char * _capital = "Blank", double _area = 0, double _population = 0) {
        strcpy(name,_name);
        strcpy(capital,_capital);
        area = _area;
        population = _population;
    }

    ~Country() {}

    const char *getName() const {
        return name;
    }

    void setName(char * _name){
        strcpy(name,_name);
    }

    const char *getCapital() const {
        return capital;
    }
    void setCapital(char * _capital){
        strcpy(capital,_capital);
    }

    double getArea() const {
        return area;
    }

    void setArea(double area) {
        Country::area = area;
    }

    double getPopulation() const {
        return population;
    }

    void setPopulation(double population) {
        Country::population = population;
    }
};

void printLargestPopulation(Country * countries, int n){
    int largestIndex = 0;
    for(int i = 0; i < n; i++){
        if(countries[i].getArea() > countries[largestIndex].getArea()){
            largestIndex = i;
        }
    }
    cout << "Country: " << countries[largestIndex].getName() << endl;
    cout << "Capital: " << countries[largestIndex].getCapital() << endl;
    cout << "Area: " << countries[largestIndex].getArea() << endl;
    cout << "Population: " << countries[largestIndex].getPopulation() << endl;
}



int main(){
    Country countries[100];
    char name[100], capital[100];
    double area, population;
    int n; cin >> n;
    cin.ignore();
    for(int i = 0; i < n; i++){
        cin.getline(name,100);
        cin.getline(capital,100);
        cin >> population >> area;
        countries[i].setName(name);
        countries[i].setCapital(capital);
        countries[i].setArea(area);
        countries[i].setPopulation(population);
        cin.ignore();
    }
    printLargestPopulation(countries,n);

}