#include <iostream>
#include <iomanip>
#include <assert.h>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include "tell_term.hpp"

using namespace std;

vector<string> getPrinters(){
    string lpstat = tell_term("lpstat -p");
    string stringStack;
    vector<string> printerStack;
    bool printerSeen = false;
    bool unique = true;
    for(int i=0; i<lpstat.length(); i++){
        if(lpstat[i]==' ' || lpstat[i]=='\r' || lpstat[i]=='\n'){
            if(printerSeen == true){
                printerStack.push_back(stringStack);
                printerSeen = false;
            }
            if(stringStack=="printer"){
                printerSeen = true;
            }
            stringStack="";
        }else{
            stringStack += lpstat[i];
        }
    }
    return printerStack;
}
string askPrinter(){
    vector<string> printers = getPrinters();
    string p;
    int n=-1;
    cout<<"Select a printer you want to use:"<<endl;
    cout<<left<<setw(3)<<"ID"<<"Printer name"<<endl;
    for(int i=0; i<printers.size();i++){
        cout<<left<<setw(3)<<i<<printers[i]<<endl;
    }
    do{
<<<<<<< HEAD
        cout<<"Enter the printer ID: ";
=======
        cout<<"Enter the printer ID:";
>>>>>>> 87a08ff89587c8e7189c8c381818e010d3132297
        cout.flush();
        getline(cin,p);
        n=atoi(p.c_str());
        if(n>printers.size()-1 || n<0){
            cout<<"Invalid printer ID."<<endl;
        }
    } while(n>printers.size()-1 || n<0);

    return printers[n];
}

void printRequest(string path, string printer){
    string command = "lpr -P \""+printer+"\" "+path;
    system(command.c_str());
<<<<<<< HEAD
    cout<<"Your printing job has been sent to "+printer<<"."<<endl;
=======
    cout<<"Your printing job has been sent to "+printer<<endl;
    //tell_term("lpq -P "+printer);
>>>>>>> 87a08ff89587c8e7189c8c381818e010d3132297
}
