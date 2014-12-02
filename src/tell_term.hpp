#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

string tell_term(string command){
    FILE *f;
    char buff[512];
    string ss;
    assert(f=popen(command.c_str(),"r"));

    while(fgets(buff,sizeof(buff), f)!=NULL){
        ss += buff;
    }

    pclose(f);
    return ss;
}
