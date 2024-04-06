#include <iostream>
#include <cstring>
using namespace std;

// TODO: Implement 'Achievement' and 'UserProfile' classes

// TODO: Implement showAchievementsProgress function

class UserProfile;

class Achievement{
private:
    char name[100];
    char description[1000];
    static int totalUserAchievements;
    void copy(const Achievement & a){
        strcpy(this->name, a.name);
        strcpy(this->description, a.description);
        this->totalUserAchievements = a.totalUserAchievements;
    }
    friend class UserProfile;
public:
    Achievement() {}
    Achievement(char *name, char *description) {
        strcpy(this->name, name);
        strcpy(this->description, description);
        this->totalUserAchievements = 1;
    }
    Achievement(const Achievement & other){
        copy(other);
    }

    static void incrementTotalUserAchievements(){
        totalUserAchievements++;
    }

    void print(){
        cout << name << endl;
        cout << description << endl;
        cout << totalUserAchievements;
    }
    friend void showAchievementsProgress(UserProfile * profiles, int n, Achievement * achievements, int m);
};

class UserProfile{
private:
    char name[100];
    Achievement * achievements;
    int n;
    void copy(const UserProfile & up){
        strcpy(this->name, up.name);
        this->n = up.n;
        achievements = new Achievement[this->n];
        for(int i = 0; i < this->n;i++){
            this->achievements[i] = up.achievements[i];
        }
    }
    friend class Achievement;
public:
    UserProfile() {}
    UserProfile(char *name) {
        strcpy(this->name,name);
        this->n = 0;
        achievements = new Achievement[0];
    }
    UserProfile(const UserProfile & other){
        copy(other);
    }

    void addAchievement(Achievement &ach){
        Achievement * temp = new Achievement[n+1];
        for(int i = 0; i < n; i++){
            temp[i] = achievements[i];
        }
        temp[n++] = ach;
        delete[] achievements;
        achievements = temp;
    }
    void print(){
        cout << name << endl;
        for(int i = 0; i < n; i++){
            achievements[i].print();
        }
    }
    friend void showAchievementsProgress(UserProfile * profiles, int n, Achievement * achievements, int m);
};

void showAchievementsProgress(UserProfile * profiles, int n, Achievement * achievements, int m){
    cout.precision(2);
    cout << fixed;

    for (int i = 0; i < m; i++) {
        int usersWithAchievement = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < profiles[j].n; k++) {
                if (strcmp(profiles[j].achievements[k].name, achievements[i].name) == 0) {
                    usersWithAchievement++;
                    break;
                }
            }
        }
        double percentage = (usersWithAchievement * 100.0) / n;
        cout << achievements[i].name << ": " << achievements[i].description << " - " << percentage << "%" << endl;
    }

    double averageAchievements = Achievement::totalUserAchievements * 100.0 / (n * m);
    cout << "Average number of obtained achievements: " << averageAchievements << "%" << endl;
}


// Don't modify
int main() {
//    UserProfile user("Fejmi");
//    Achievement achievement;
//    user.addAchievement(achievement);
//    user.print();


    char testcase[100];
    cin.getline(testcase, 100);

    int n;
    cin >> n;
    cin.ignore();

    char ignore[100];
    cin.getline(ignore, 100);
    UserProfile users[100];
    for (int i = 0; i < n; ++i) {
        char name[100];
        cin >> name;
        users[i] = UserProfile(name);
    }

    int m;
    cin >> m;
    cin.ignore();

    cin.getline(ignore, 100);
    Achievement achievements[100];
    for (int i = 0; i < m; ++i) {
        char name[100], description[100];
        cin.getline(name, 100);
        cin.getline(description, 100);
        achievements[i] = Achievement(name, description);
    }

    int k;
    cin >> k;
    cin.ignore();

    cin.getline(ignore, 100);
    for (int i = 0; i < k; ++i) {
        int numUser, numAchievement;
        cin >> numUser >> numAchievement;
        numUser -= 1;
        numAchievement -= 1;
        users[numUser].addAchievement(achievements[numAchievement]);
    }

    if (testcase[8] == 'A') {  // Testing Achievement methods.
        for (int i = 0; i < m; ++i) {
            achievements[i].print();
        }
        Achievement::incrementTotalUserAchievements();
    } else if (testcase[8] == 'U') {  // Testing UserProfile methods.
        for (int i = 0; i < n; ++i) {
            users[i].print();
        }
    } else {  // Testing showAchievementsProgress function.
        showAchievementsProgress(users, n, achievements, m);
    }

    return 0;
}