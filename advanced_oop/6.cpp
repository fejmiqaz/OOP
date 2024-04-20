#include<iostream>
#include<cstring>
#include<cctype>
using namespace std;

class Character{
private:
    char *variable;
//    void copy(const Character & ch){
//        strcpy(this->variable, ch.variable);
//    }
    void copy(const Character& ch) {
        this->variable = new char[strlen(ch.variable) + 1];
        strcpy(this->variable, ch.variable);
    }
public:
    Character(){}
    Character(char ch){
        this->variable = new char[2];
        this->variable[0] = ch;
        this->variable[1] = '\0';
    }
    Character(const Character & other){
        copy(other);
    }

    Character & operator=(const Character & other){
        if(this!=&other){
            delete[] variable;
            copy(other);
        }
        return * this;
    }

//    Character(const char *variable){
//        if(variable!= nullptr){
//            this->variable = new char [strlen(variable)+1];
//            strcpy(this->variable,variable);
//        }
//    }
//    Character(const Character & other){
//        copy(other);
//    }
    ~Character(){
        delete [] variable;
    }
    bool operator==(const Character & other) const{
        return strcmp(variable, other.variable) == 0;
    }
    bool operator!=(const Character & other) const{
        return !(*this == other);
    }

    char *getVariable() const {
        return variable;
    }
    void setVariable(char ch){
//        if(this->variable != nullptr){
//            delete [] this->variable;
//        }
//        this->variable = new char[strlen(variable)+ 1];
//        strcpy(this->variable, variable);
        if (this->variable != nullptr) { // Free existing memory if needed
            delete[] this->variable;
        }
        this->variable = new char[2]; // Allocate memory for the character and null terminator
        this->variable[0] = ch; // Set the character
        this->variable[1] = '\0';
    }
    friend ostream & operator<<(ostream & out, Character & ch );
};
ostream & operator<<(ostream & out, Character & ch ){
    out << ch.variable;
    return out;
}

class CharSequence{
private:
    int n;
    Character * character;
    void copy(const CharSequence & ch){
        this->n = ch.n;
        character = new Character[this->n];
        for(int i = 0; i < this->n; i++){
            this->character[i] = ch.character[i];
        }
    }
public:
    CharSequence(){}
    CharSequence(char * ch){
        this->n = 0;
        character = new Character[0];
    }
    ~CharSequence(){
        delete [] character;
    }
    Character operator[] (int i){
        if(i < 0 || i >= n){
            cout << "Out of range";
        }
        for(int i = 0; i < n; i++){
            return character[i];
        }
    }
    CharSequence & operator+= (const Character &c){
        Character * temp = new Character[n+1];
        for(int i = 0; i < n; i++){
            temp[i] = character[i];
        }
        temp[n++]=c;
        delete[] character;
        character = temp;
        return * this;
    }
    bool operator==(const CharSequence & cs) const{
        if(n != cs.n){
            return false;
        }
        for(int i = 0; i < this->n; i++){
            if(character[i] != cs.character[i]){
                return false;
            }
        }
        return true;
    }
    int operator[](char * c) const{
        int counter = 0;
        for(int i = 0; i < n; i++){
            if(character[i].getVariable() == c ){
                counter++;
            }
        }
        return counter;
    }
    CharSequence toUpperCase(){
        CharSequence upperCaseSequence(this->n);
        for(int i = 0; i < this->n;i++){
           char c = toupper(character[i].getVariable()[0])
            upperCaseSequence.character[i].setVariable(&c);
        }
        return upperCaseSequence;
    }

    friend ostream &operator<<(ostream &out, const CharSequence &ch){
        out << ch.character << endl;
        return out;
    }
};

int main(){
    int n;
    cin >> n;

    if(n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator <<" << endl;
        cout << cc << endl;
    } else if(n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    } else if(n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for(int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    } else if(n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs("If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << cs['e'] << endl;
    } else if(n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        cout << cs.toUpperCase() << endl;
    } else if(n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }
    return 0;
}
