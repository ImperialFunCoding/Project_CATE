#include <iostream>
#include <assert.h>
#include "tell_term.h"

using namespace std;

vector<string> printers(string path){
    string lpstat = tell_term("lpstat -p");
    string stringStack;
    vector<string> printerStack;
    bool flag = false;
    for(int i=0; i<lpstat.length(); i++){
        if(lpstat[i]==' '){
            if(stringStack=="printer"){
                flag = true;
            }
            if(flag == true){
                printerStack.push_back(stringStack);
                flag = false;
            }
            stringStack="";
        }else{
            stringStack += lpstat[i];
        }
    }
}

int main(){
    cout<<print("")<<endl;

    return 0;
}
