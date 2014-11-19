#include <iostream>

using namespace std;

int turn(int c){
    return (c+1);
}

int main(){
    string a = "abc";
    char c = a[2];
    cout<<turn(c)<<endl;
}

