#include <iostream>
#include <cassert>

using namespace std;

class bitString{
public:
    string bs;
    bitString() {bs = "";}
    bitString(int n) {bs = int2str(n);}
    bitString(int n,string s) {
        bs = "";
        for(int i=0; i<s.size(); i++){
            bitString bs_temp( dec2bin( s[i] ) );
            bs_temp.fillFrontWithZeros(n);
            bs+=bs_temp.toString();
        }
    }

    int size(){
        return bs.size();
    }
    int id(int n){
        return bs[n];
    }
    char pop(int n){
        char x = bs[n];
        bs.erase(n,n+1);
        return x;
    }

    int toInt(){
    //Pre: bs only consist of numbers
        return str2int(bs);
    }

    string toString(){
        return bs;
    }

    int fillFrontWithZeros(int n){
    //Pre: bs.size()<=n
    //Post: this will return how many 0s are filled.
        assert( bs.size() <= n );
        int z=0;
        while(bs.size()<n){
            bs = "0" + bs;
            z++;
        }
        return z;
    }
    int fillWithZeros(int n){
    //Pre: bs.size()<=n
    //Post: this will return how many 0s are filled.
        assert( bs.size() <= n );
        int z=0;
        while(bs.size()<n){
            bs = bs + "0";
            z++;
        }
        return z;
    }

private:
    string getBitStr(int n, string s){
    }
};
