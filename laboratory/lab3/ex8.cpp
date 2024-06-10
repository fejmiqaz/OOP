#include<iostream>
#include<cstring>
using namespace std;

class SpaceObject {
private:
    char name[100];
    char type[100];
    int distanceFromEarth;
    void copy(const SpaceObject & so){
        strcpy(this->name, so.name);
        strcpy(this->type, so.type);
        this->distanceFromEarth = so.distanceFromEarth;
    }
public:
    SpaceObject() {}
    SpaceObject(char *name, char *type, int distanceFromEarth) {
        strcpy(this->name, name);
        strcpy(this->type, type);
        this->distanceFromEarth = distanceFromEarth;
    }
    SpaceObject( const SpaceObject & other){
        copy(other);
    }

    int getDistanceFromEarth() const {
        return distanceFromEarth;
    }

    void print() const {
        cout  << "Favorite space object closest to earth: "<< name << " (" << type << ")  - distance: " << distanceFromEarth << " light years away from Earth" << endl;
    }
};

class Alien{
private:
    char name[100];
    int age;
    char homePlanet[100];
    int numObj;
    SpaceObject * spaceObjects;
    void copy(const Alien & so){
        strcpy(this->name, so.name);
        this->age = so.age;
        this->numObj = so.numObj;
        strcpy(this->homePlanet, so.homePlanet);
        spaceObjects = new SpaceObject[this->numObj];
        for(int i = 0; i < this->numObj;i++){
            this->spaceObjects[i] = so.spaceObjects[i];
        }
    }
public:
    Alien(){}
    Alien(char *name, int age, char *homePlanet, int numObj, SpaceObject * spaceObject) {
        strcpy(this->name, name);
        this->age = age;
        strcpy(this->homePlanet, homePlanet);
        this->numObj = numObj;
        this->spaceObjects = new SpaceObject[0];
    }
    Alien(const Alien & other){
        copy(other);
    }
    ~Alien() {
        delete [] spaceObjects;
    }

    void print(){
        cout << "Alien name: " << name << endl;
        cout << "Alien age: " << age << endl;
        cout << "Alien homePlanet: " << homePlanet << endl;
        if(numObj > 0){
            int closestIndex = 0, closestDistance = spaceObjects[0].getDistanceFromEarth();
            for(int i = 0; i < numObj; i++){
                if(spaceObjects[i].getDistanceFromEarth() < closestDistance){
                    closestDistance = spaceObjects[i].getDistanceFromEarth();
                    closestIndex = i;
                }
            }
            spaceObjects[closestIndex].print();
        }else{
            cout << "No favorite space objects." << endl;
        }
    }
};

int main(){
    char name[100], homePlanet[100];
    int age, numObj;
    cin >> name >> age >> homePlanet >> numObj;

    SpaceObject spaceObjects[numObj];
    for (int i = 0; i < numObj; i++)
    {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin >> spaceObjectName >> spaceObjectType >> distanceFromEarth;
        spaceObjects[i] = SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }

    Alien alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();

    return 0;
}
