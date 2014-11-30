#include <iostream>
#include <assert.h>
#include "tell_term.hpp"
#include <vector>

using namespace std;

vector<string> getPrinters(){
    string lpstat = tell_term("lpstat -p");
    string stringStack;
    vector<string> printerStack;
    bool flag = false;
    for(int i=0; i<lpstat.length(); i++){
        if(lpstat[i]==' ' || lpstat[i]=='\n'){
            if(flag == true){
                printerStack.push_back(stringStack);
                flag = false;
            }
            if(stringStack=="printer"){
                flag = true;
            }
            stringStack="";
        }else{
            stringStack += lpstat[i];
        }
    }
    return printerStack;
}

int main(){
    vector<string> printers = getPrinters();
    for(int i; i<printers.size();i++){
        cout<<printers[i]<<endl;
    }

    return 0;
}
