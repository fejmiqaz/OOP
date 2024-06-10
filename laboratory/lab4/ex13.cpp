#include<iostream>
#include<string>
using namespace std;

class ResultsManager {
public:
    static string simplifyFormat(const string& line){
        string simplifiedLine = line;
        size_t pos = simplifiedLine.find("x");
        while(pos != string::npos){
            simplifiedLine.replace(pos,1,"50");
            pos = simplifiedLine.find("x",pos + 1);
        }
        return simplifiedLine;
    }

    static int calculateResult(const string& line){
        int sum = 0;
        size_t pos = 0;
        while(pos < line.length()){
            string pointsStr;
            while(pos < line.length() && line[pos] != ' '){
                pointsStr += line[pos];
                pos++;
            }

            if(!pointsStr.empty()){
                int points = stoi(pointsStr);
                sum+= points;
            }
            pos++;

        }
        return sum;
    }

};

int main(){
    string line1, line2;
    getline(cin,line1);
    getline(cin, line2);

    string simplifiedLine1 = ResultsManager::simplifyFormat(line1);
    string simplifiedLine2 = ResultsManager::simplifyFormat(line2);

    int result1 = ResultsManager::calculateResult(simplifiedLine1);
    int result2 = ResultsManager::calculateResult(simplifiedLine2);

    if(result1 > result2){
        cout << "Player 1 wins with " << (result1 - result2) << " additional points.";
    }else if (result2 > result1){
        cout << "Player 2 wins with " << (result2 - result1) << " additional points.";
    }else{
        cout << "It's a tie!";
    }
}