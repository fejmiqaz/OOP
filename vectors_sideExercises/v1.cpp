#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;

// find the occurrence of the integer vector and print which one appears more than once

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    bool flag = false;
    int idx = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(a[i] == a[j]){
                flag = true;
                idx = i;
                break;
            }
        }
    }

    cout << a[idx] << endl;
    if(flag){
        cout << endl;
    }
}
