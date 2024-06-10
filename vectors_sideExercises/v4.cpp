#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){

    string str;
    vector<string> str1;

    while(getline(cin,str) && str != "#"){
        for(int i = 0; i < str.length(); i++){
            if(isspace(str[i]))
                if(!str.empty() && islower(str[i])){
                    str[i] = toupper(str[i]);
                }
            str1.push_back(str);
        }
    }

    for( const string & str1 : str1){
        cout << str1 << endl;
    }




    return 0;
}