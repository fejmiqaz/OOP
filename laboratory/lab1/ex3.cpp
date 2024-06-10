#include<iostream>
#include<cstring>

using namespace std;

struct FootballPlayer{
    char name[50];
    int jNumber, goals;
};
struct FootballTeam{
    char name[50];
    FootballPlayer footballPlayer[12];
    int scoredGoals = 0;
    void read(){
        cin.ignore();
        cin.getline(name,50);
        for(int i = 0; i < 11; i++){
            cin >> footballPlayer[i].name >> footballPlayer[i].jNumber >> footballPlayer[i].goals;
            scoredGoals += footballPlayer[i].goals;
        }
    }
};

void bestTeam(FootballTeam * teams, int n){
    int idxMaxGoal = 0, maxGoals = 0;
    for(int i = 0; i < n; i++){
        if(teams[i].scoredGoals > maxGoals){
            maxGoals = teams[i].scoredGoals;
            idxMaxGoal = i;
        }
    }
    cout << "Najdobar tim e: " << teams[idxMaxGoal].name << endl;
}

int main(){
    int n;
    cin >> n;
    FootballTeam footballTeam[100];
    for(int i = 0; i < n; i++){
        footballTeam[i].read();
    }
    bestTeam(footballTeam,n);

    return 0;
}