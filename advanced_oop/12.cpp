#include <iostream>
#include <cstring>
using namespace std;

// your code here

class Word {
private:
    char *name;

    void copy(const Word &w) {
        name = new char[strlen(w.name) + 1];
        strcpy(this->name, w.name);
    }

public:
    Word(char *name = "UNDEFINED") {
        name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    Word(const Word &other) {
        copy(other);
    }

    friend ostream &operator<<(ostream & out, const Word &w){
        out << w.name;
        return out;
    }
};

class Sentence {
private:
    Word *word;
    int num, total_capacity;

    void copy(const Sentence &s) {
        this->num = s.num;
        this->total_capacity = s.total_capacity;
        word = new Word[this->num];
        for (int i = 0; i < this->num; i++) {
            this->word[i] = s.word[i];
        }
    }

public:
    Sentence(int totalCapacity = 10) {
        word = new Word[0];
        this->num = 0;
        this->total_capacity = totalCapacity;
    }

    Sentence(const Sentence &other) {
        copy(other);
    }
    friend ostream & operator<<(ostream & out, const Sentence & s){
        for(int i = 0; i < s.num; i++){
            out << s.word[i];
        }
        return out;
    }
    ~Sentence(){
        delete[] word;
    }
    void add(const Word & w) {
        if (this->num >= this->total_capacity) {
            this->total_capacity += 10;
            Word * temp = new Word[this->total_capacity];
            for(int i = 0; i < this->num; i++){
                temp[i] = word[i];
            }
            delete[] word;
            word = temp;
        }
        this->word[num++] = w;
    }

    void print() const {
        for(int i = 0; i < num;i++){
            cout << word[i];
            if(i < num - 1){
                cout << " ";
            }
        }
        cout << endl;
    }

    void swap(int i, int j){
        if(i >= 0 && i < num && j >= 0 && j < num){
            Word temp = word[i];
            word[i] = word[j];
            word[j] = temp;
        }else{
            cout << "Invalid indices for swap" << endl;
        }
    }
};

int main() {
    int n;
    cin >> n;
    cin.get();
    cout << "CONSTRUCTOR" << endl;
    Sentence s;
    cout << "ADD WORD" << endl;
    for (int i = 0; i < n; ++i) {
        char w[100];
        cin.getline(w, 100);
        Word word(w);
        s.add(word);
    }
    cout << "PRINT SENTENCE" << endl;
    s.print();
    cout << "COPY" << endl;
    Sentence x = s;
    cout << "SwAP" << endl;
    x.swap(n / 2, n / 3);
    x.print();
    cout << "ORIGINAL" << endl;
    s.print();
    return 0;
}
