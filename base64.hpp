#include <iostream>
#include "binary.hpp"
#include "bitString.hpp"

using namespace std;

int getNumberOfZerosToAdd(int n){
    int m = n%6;
    if(m==0){
        return n;
    }else{
        return 6-m+n;
    }
}
char base64table(int c){
    if(0<=c && c<=25){
        return c+65;
    }else if(26<=c && c<=51){
        return c+71;
    }else if(52<=c && c<=61){
        return c-4;
    }
    switch(c){
        case 62:
            return '+';
        case 63:
            return '/';
    }
}
string base64encode(string s){
    bitString bs(8,s);
    int z = bs.fillWithZeros(getNumberOfZerosToAdd(bs.size()));

    string encodedString = "";
    while(bs.size()>0){
        string bsTemp = "";
        for(int i=0; i<6; i++){
            bsTemp += bs.pop(0);
        }
        encodedString += base64table(bin2dec(str2int(bsTemp)));
    }
    switch(z){
        case 0:
            break;
        case 2:
            encodedString += "=";
            break;
        case 4:
            encodedString += "==";
            break;
        default:
            cout<<z<<endl;
            assert(false && "IMPOSSIBLE!");
    }

    return encodedString;
}

