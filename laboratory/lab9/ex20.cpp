#include <iostream>
#include <fstream>
#include<cstring>
#include<iomanip>

using namespace std;

void writeToFile() {
    std::ofstream outFile("text.txt");
    char c;
    while((c = std::cin.get()) != '#') {
        outFile.put(c);
    }
    outFile.close();
}

int main() {
    writeToFile();

    //Your code

    ifstream in("text.txt");

    char c;
    int total = 0, upper = 0, lower = 0;
    while(in.get(c)){
        if(isalpha(c)){
            total++;
            if(isupper(c)){
                upper++;
            }else if(islower(c)){
                lower++;
            }
        }
    }
    in.close();

    cout << fixed << setprecision(4) << showpoint;
    cout << static_cast<double>(upper) / total << endl;
    cout << static_cast<double>(lower) / total << endl;



    return 0;
}