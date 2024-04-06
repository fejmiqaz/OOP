#include<iostream>
#include<cstring>
using namespace std;

struct Player{
    char korisnickoIme[15];
    int nivo, poeni;
    void read(){
        cin.getline(korisnickoIme,15);
        cin >> nivo >> poeni;
    }
};

struct ComputerGame{
    char ime[50];
    Player lista[30];
    int n;
    void read(){
        cin.getline(ime,50);
        for(int i = 0; i < n; i++){
            lista[i].read();
        }
    }
};

void bestPlayer(ComputerGame *array, int n){
    int maxPoeni = -1, maxIndex = -1, maxIndexGame = -1, maxIndexPlayer = -1, maxNivo = -1;
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < array[i].n; j++) {
            if (array[i].lista[j].poeni > maxPoeni) {
                maxPoeni = array[i].lista[j].poeni;
                maxIndexPlayer = j;
                maxIndexGame = i;
            }
//                maxNivo = array[i].lista[j].nivo;
//            }else if((array[i].lista[j].poeni == maxPoeni) && (array[i].lista[j].nivo > maxNivo)){
//                maxIndexPlayer = j;
//                maxIndexGame = i;
//                maxNivo = array[i].lista[j].nivo;
//            }
        }
        cout << "Najdobar igrac e igracot so korisnicko ime " << array[maxIndexGame].lista[maxIndexPlayer].korisnickoIme << " koj ja igra igrata " << array[maxIndexGame].ime << endl;
//        maxIndexGame = -1;
//        maxIndexPlayer = -1;
//        maxPoeni = -1;
//        maxNivo = -1;
    }
}

int main() {
    int n,m;
    char ime[20];
    cin>>n;
    //create an array of max 100 computer games;
    ComputerGame poleigri[100];
    for (int i=0; i<n; i++) {
        ComputerGame nova;
        cin>>nova.ime>>nova.n;
        Player pole[30];
        for (int j=0; j<nova.n; j++) {
            Player nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    bestPlayer(poleigri,n);
    return 0;
}
