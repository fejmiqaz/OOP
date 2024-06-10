#include<iostream>
#include<cstring>
using namespace std;

class UserAlreadyExistsException {
//TODO
private:
    string name;
public:
    explicit UserAlreadyExistsException(const string &name) : name(name) {}

    void message(){
        cout << "User with username " << name << " already exists!" << endl;
    }
};

class UserNotFoundException {
    string name;
public:
//TODO
    explicit UserNotFoundException(const string &name) : name(name) {}

    void message(){
        cout << "User with username " << name << " was not found!" << endl;
    }
};

class FriendsLimitExceededException {
private:
    int n;
//TODO
public:
    FriendsLimitExceededException(int n) : n(n) {}
    void message(){
        cout << "Can't have more than " << n << " friends." << endl;
    }
};

class User {
private:
    char username[50];
    int age;
    int friends;
    static int limit;

public:
    User(char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }

    static void setLimit(int l) {
        limit = l;

    }

    bool operator==(const User & u){
        return username == u.username;
    }

    int getFriends() const {
        return friends;
    }

    static int getLimit() {
        return limit;
    }


    User &operator++() {
        ++friends;
        return *this;
    }

    friend class SocialNetwork;


};

int User::limit = 3;


class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {

        for(int i = 0; i < n; i++){
            if(strcmp(users[i].username, u.username)==0){
                throw UserAlreadyExistsException(users[i].username);
            }
        }

        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(char *firstUsername, char *secondUsername) {
        int firstUsernameIDX = -1, secondUsernameIDX = -1;
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                firstUsernameIDX = i;
                for (int j = 0; j < n; j++) {
                    if (strcmp(users[j].username, secondUsername) == 0) {
                        secondUsernameIDX = j;
                        if(users[i].getFriends() >= User::getLimit()){
                            throw FriendsLimitExceededException(User::getLimit());
                        }
                        if(users[j].getFriends() >= User::getLimit()){
                            throw FriendsLimitExceededException(User::getLimit());
                        }
//                        if(strcmp(users[i].username,firstUsername) < 0){
//                            throw UserNotFoundException(firstUsername);
//                        }
//                        if(strcmp(users[j].username,secondUsername) < 0){
//                            throw UserNotFoundException(secondUsername);
//                        }
                        ++users[i];
                        ++users[j];
                        return;
                    }
                }
            }
        }
        if(firstUsernameIDX < 0){
            throw UserNotFoundException(firstUsername);
        }else if(secondUsernameIDX < 0){
            throw UserNotFoundException(secondUsername);
        }
    }

    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i=0;i<network.n;i++) {
            os << network. users[i] << endl;
        }
        return os;
    }
};


int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        char username[50]; int age;
        cin >> username >> age;
        try {
            User u(username, age);
            sn += u;
        } catch (UserAlreadyExistsException & u){
            u.message();
        }


    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        } catch (FriendsLimitExceededException & f){
            f.message();
        } catch (UserNotFoundException & u){
            u.message();
        }
    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    cin >> friendships;
    User::setLimit(maxFriends);
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        } catch (FriendsLimitExceededException & f){
            f.message();
        } catch (UserNotFoundException & u){
            u.message();
        }

    }
    cout << sn;
    return 0;
}