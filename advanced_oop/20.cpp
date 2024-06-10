#include<iostream>
#include<cstring>
using namespace std;

//your code here

class InvalidTimeException {
public:
    void message(){
        cout << "Invalid Time" << endl;
    }
};

class Race {
protected:
    char cityName[40];
    int year, month;
    float bestTime, km;
public:
    Race(){}
    Race(char *cityName, int year, int month, float bestTime, float km) : year(year), month(month),
                                                                          bestTime(bestTime), km(km) { strcpy(this->cityName,cityName);}

    virtual float complexity(){
        return bestTime / km;
    }

    friend ostream &operator<<(ostream &os, Race race) {
        os << race.cityName << " " << race.month << "." << race.year << " " << race.complexity() << endl;
        return os;
    }

    Race & operator*(Race r){
        complexity() * r.complexity();
        return * this;
    }

    Race & operator=(const Race & other){
        if(this!=&other){
            return * this;
        }
    }

};

class MotoGPRace : public Race {
private:
    float * bestTimesOfPreparation;
    int numberOfBestTimes, numberOfLaps;
    static double coefficient;
public:
    MotoGPRace(){}

    MotoGPRace(char *cityName, int year, int month, float bestTime, float km) : Race(cityName, year, month, bestTime, km) {}

    MotoGPRace(char *cityName, int year, int month, float bestTime, float km, float *bestTimesOfPreparation,
               int numberOfBestTimes, int numberOfLaps) : Race(cityName, year, month, bestTime, km),
                                                          numberOfBestTimes(numberOfBestTimes),
                                                          numberOfLaps(numberOfLaps) {this->bestTimesOfPreparation = new float[numberOfBestTimes+1];}

    float complexity() override {
        double avg = 0.0;
        for(int i = 0; i< numberOfBestTimes; i++){
            avg = bestTimesOfPreparation[i] / numberOfBestTimes;
        }
        avg * coefficient;

        if(numberOfLaps > 22){
            avg *= 1.2;
        }
        return avg;
    }

    void setNumberLaps(int numberOfLaps) {
        MotoGPRace::numberOfLaps = numberOfLaps;
    }

    MotoGPRace & operator+=( const float r){

        for(int i = 0; i < numberOfBestTimes;i++){
            if(r < 9.5){
                throw InvalidTimeException();
            }
        }

        float * tmp = new float[numberOfBestTimes+1];
        for(int i = 0; i < numberOfBestTimes; i++){
            tmp[i] = bestTimesOfPreparation[i];
        }
        tmp[numberOfBestTimes++] = r;
        delete[] bestTimesOfPreparation;
        bestTimesOfPreparation = tmp;
    }



    static void setK(double coefficient) {
        MotoGPRace::coefficient = coefficient;
    }

    MotoGPRace & operator++(int){
        numberOfLaps++;
        return * this;
    }

    int getNumberLaps() const {
        return numberOfLaps;
    }

};

double MotoGPRace::coefficient = 0.4;

int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int choice;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing - classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace* nn = dynamic_cast<MotoGPRace*>(rArray[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3){
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1,time2;
        cin>>time1>>time2;




        try {
            mgt+=time1;
        }catch (InvalidTimeException & i){
            i.message();
        }

        try {
            mgt+=time2;
        }catch (InvalidTimeException & i){
            i.message();
        }

        cout<<mgt;
    }
    if (testCase == 4){
        cout <<"===== Testing - operator++ ======"<<endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes,n,numberLaps);
        float v,koef2;
        cout<<(mgt++).getNumberLaps()<<endl;
        cout<<mgt;
        mgt++;
        cout<<mgt;
    }
    if (testCase == 5){
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6){
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin>>newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin>>newBest;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace * pok= dynamic_cast<MotoGPRace *>(rArray[i]);
            if(pok!=0)
            {
                (*pok)++;
                (*pok)+=newBest;
                if(flag==1)
                {
                    flag = 0;
                    *pok+=1.4;

                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}
