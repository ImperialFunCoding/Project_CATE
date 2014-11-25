#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
string curl(string url, string user="", string form=""){
    FILE *f;
    string command = "curl -s ";
    char buff[512];
    string html = "";
    if(user!=""){
        command += "-u \""+user+"\" ";
    }
    if(form!=""){
        command += "-F \""+form+"\" ";
    }
    command += url;

    if(!(f = popen(command.c_str(), "r"))){
        return "ERROR IN CALLING CURL. INVALID COMMAND.";
    }

    while(fgets(buff, sizeof(buff), f)!=NULL){
        html += buff;
    }
    pclose(f);
    return html;
}

vector<string> get_tags(string html){
    vector<string> r;
    r.push_back("123");
    return r;
}
