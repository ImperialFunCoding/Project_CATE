#include <iostream>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <cassert>

using namespace std;

int str2int(string n);
string int2str(int n);
int dec2bin(int n);
int bin2dec(int n);

int str2int(string s){
//Pre: s only consist of numbers
    return atoi(s.c_str());
}

string int2str(int n){
    ostringstream oss;
    oss<<n;
    return oss.str();
}

int dec2bin(int n){
// Pre: 0<=n<1023
    assert(0<=n && n<1023);
    int m = log(n)/log(2);
    int b = 0;
    for(int i = 0; i <= m; i++){
        b += pow(10,i) * (n % 2);
        n = n/2;
    }
    return b;
}

int bin2dec(int n){
//Pre: 0<=n<111111111
    assert(0<=n && n<1111111111);
    if(n==0) return 0;
    int m = log10(n);
    int d = 0;
    for(int i = 0; i <= m ; i++){
        d += pow(2,i)*(n % 10);
        n = n / 10;
    }
    return d;
}
