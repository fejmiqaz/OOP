#include<iostream>
#include<string>
using namespace std;

class Song {
protected:
    string artist, title;
    static string verses[20];
public:
    Song(const string &artist, const string &title, string *verses) : artist(artist), title(title){
        for(int i = 0; i < verses->length(); i++){
            this->verses[i] = verses[i];
        }
    }
    static int getNumVerses(){
        int count = 0;
        for(int i = 0; i < 20; i++){
            if(!verses[i].empty()){
                count++;
            }
        }
        return count;
    }

    void addVerse(const string& verse){
        int idx = getNumVerses();
        if(getNumVerses() < 20){
            verses[idx] = verse;
        }else{
            cout << "Cannot add verse." << endl;
        }
    }

    static string completeSong() {
        string song;
        for(int i = 0; i < 20; i++){
            if(!verses[i].empty()){
                song += verses[i];
                song += "\n";
            }
        }
        return song;
    }

    bool rhymingVerses(const string & verse1IDX, const string & verse2IDX){
        if(verse1IDX.length() >= 3 && verse2IDX.length() >= 3){
            string ending1 = verse1IDX.substr(verse1IDX.length() - 3);
            string ending2 = verse2IDX.substr(verse2IDX.length() - 3);
            return (ending1 == ending2);
        }
        return false;
    }

    static int occurrence(const string& word){
         int count = 0;
         for(int i = 0; i < 20; i++){
             size_t pos = verses[i].find(word);
             while(pos != string::npos){
                 count++;
                 pos = verses[i].find(word, pos+1);
             }
         }
         return count;
    }

    friend ostream &operator<<(ostream &os, const Song &song) {
        return os << song.artist << " - " << song.title << " : " << endl << Song::completeSong();
    }

};

string Song::verses[20];

int main(){
    string artist, title;
    int n;
    getline(cin,artist);
    getline(cin,title);
    cin >> n;
    cin.ignore();
    string verses[20];
    for(int i = 0; i < n; i++){
        getline(cin,verses[i]);
    }
    Song song(artist, title, verses);
    cout << song;
    return 0;
}