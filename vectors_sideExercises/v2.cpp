#include<iostream>
#include<vector>
using namespace std;

int main(){
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0;i < n; i++){
        cin >> a[i];
    }

    bool found = false;
    int idx;
    for(int i = 0; i < n; i++){
        if(a[i] < a[i-1] && a[i] < a[i+1]){
            found = true;
            idx = i;
        }
    }

    if(found){
        cout << a[idx] << endl;
    }

    return 0;
}