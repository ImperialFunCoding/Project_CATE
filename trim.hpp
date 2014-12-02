#include <iostream>

using namespace std;


bool isSpace(char c){
    string trimOff= " \f\t\v\n\r";
    for (int i=0; trimOff[i]!='\0'; i++){
        if (c==trimOff[i]){
            return true;
        }
    }
    return false;
}
string trim(string s){
    string ts;
    for(int i=0; i<2; i++){
        s= s+" ";
        ts = "";
        bool flag = false;
        for (int i=s.length()-1; i>=0; i--){
            if (flag){
                ts += s[i];
            }else{
                if (!isSpace(s[i-1])){
                    flag = true;
                }
            }
        }
        s = ts;
    }
    return ts;
}
