#include<iostream>
#include<cstring>
using namespace std;

class InvalidTeamName : public std::exception {
private:
    std::string teamName;

public:
    InvalidTeamName(const std::string& name) : teamName(name) {}

    const char* what() const noexcept override {
        return ("Invalid team name: " + teamName).c_str();
    }
};

class Goal{
private:
    char * goalScorer;
    int time;
    char team[50];
    void copy(const Goal & g){
        this->goalScorer = new char[strlen(g.goalScorer)+1];
        strcpy(this->goalScorer,g.goalScorer);
        this->time = g.time;
        strcpy(this->team,g.team);
    }
public:
    Goal(){}
    Goal(char *goalScorer, int time, char *team) {
        this->goalScorer = new char[strlen(goalScorer)+1];
        strcpy(this->goalScorer,goalScorer);
        this->time = time;
        strcpy(this->team,team);
    }
    Goal(const Goal & other){
        copy(other);
    }
    ~Goal(){
        delete [] goalScorer;
    }
    friend ostream & operator<<(ostream & out, const Goal & goal){
        out << goal.time << " " << goal.team<< endl;
        return out;
    }
    Goal&operator++(){
        time++;
        return *this;
    }
    Goal operator++(int ){
        Goal tmp(*this);
        ++(*this);
        return tmp;
    }
    Goal & operator--(){
        time--;
        return *this;
    }
    Goal operator--(int){
        Goal tmp(*this);
        --(*this);
        return tmp;
    }
};

class Game{
private:
    static int n;
    Goal * goals;
    char team[50];
    char name[50];
    void copy(const Game & g){
        this->n = g.n;
        strcpy(this->name,g.name);
        goals = new Goal[this->n];
        for(int i = 0; i < this->n; i++){
            this->goals[i] = g.goals[i];
        }
    }
public:
    Game(){}
    Game( char *name, char * team) {
        strcpy(this->team, team);
        strcpy(this->name, name);
        goals = new Goal[0];
    }
    ~Game(){
        delete [] goals;
    }

    Game & operator+=(const Goal & g){
        Goal * tmp = new Goal[n+1];
        for(int i = 0; i < n; i++){
            tmp[i] = goals[i];
        }
        tmp[n++] = g;
        delete[] goals;
        goals = tmp;
        return * this;
    }

    friend ostream & operator<< (ostream & out, const Game & other){
        for(int i = 0; i < n; i++){
            out << other.goals[i];
        }
        return out;
    }
};

int main(){
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch(InvalidTeamName &e) {
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}