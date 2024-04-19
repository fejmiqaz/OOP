#include<iostream>
#include<cstring>
using namespace std;

//your code here

class Race{
private:
    char city[40];
    int year, month;
    float seconds, km;
    void copy(const Race & r){
        strcpy(this->city,r.city);
        this->year = r.year;
        this->month = r.month;
        this->seconds = r.seconds;
        this->km = r.km;
    }
public:
    Race(char *city = "", int year = 2000, int month = 1, float seconds = 0.0, float km = 0.0){
        strcpy(this->city, city);
        this->year = year;
        this->month = month;
        this->seconds= seconds;
        this->km = km;
    }
    Race(const Race & other){
        copy(other);
    }

    Race & operator=(const Race & other){
        if(this!=&other){
            copy(other);
        }
        return * this;
    }

    static void complexity(float seconds, float km){
        float complexity = seconds / km;
        cout << complexity;
    }

    friend ostream & operator<<(ostream & out, const Race & r){
        out << r.city << " " << r.month << " " << r.year << " "; complexity(r.seconds, r.km);
        return out;
    }
    friend class MotoGPRace;
};

class MotoGPRace{
private:
    Race * race;
    float * bestTime;
    int n, numLaps;
    void copy(const MotoGPRace & mgpr){
        this->bestTime = new float(*mgpr.bestTime);
        this->n = mgpr.n;
        this->numLaps = mgpr.numLaps;
        this->race  = new Race[this->n];
        for(int i = 0; i < this->n;i++){
            this->race[i] = mgpr.race[i];
        }
    }
public:
    MotoGPRace(){}
    MotoGPRace(float *bestTime, int n, int numLaps){
        if(bestTime != nullptr){
            this->bestTime = new float(*bestTime);
        }else{
            this->bestTime = new float;
        }
        this->n = n;
        this->numLaps = numLaps;
        this->race = new Race[0];
    }
    MotoGPRace(const MotoGPRace & other){
        copy(other);
    }

    MotoGPRace & operator=(const MotoGPRace & other){
        if(this!=&other){
            delete[] bestTime;
            delete[] race;
            copy(other);
        }
        return * this;
    }

    ~MotoGPRace(){
        delete[] bestTime;
        delete[] race;
    }

    MotoGPRace & operator+=(const Race & m){
        Race * tmp = new Race[this->n];
        for(int i = 0; i < n; i ++){
            tmp[i] = race[i];
        }
        tmp[n++] = m;
        delete[] race;
        race = tmp;
        return * this;
    }

    static void complexity(float seconds, float km, float bestTimeAVG, int numLaps, float motoGPCoefficient){
        float initialComplexity = seconds / km;
        float additionalComplexity = bestTimeAVG * motoGPCoefficient;
        if(numLaps > 22){
            additionalComplexity += 0.2 * initialComplexity;
        }
        cout << initialComplexity + additionalComplexity;
    }

    MotoGPRace &operator++(){
        numLaps++;
        return * this;
    }
    MotoGPRace &operator++(int){
        MotoGPRace copy(*this);
        numLaps++;
        return  copy;
    }

    friend ostream& operator<<(ostream & out, const MotoGPRace & m){
        for(int i = 0; i < m.n; i++){
            out << m.race[i];
        }
        return out;
    }

};

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

        mgt+=time1;
        mgt+=time2;

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
