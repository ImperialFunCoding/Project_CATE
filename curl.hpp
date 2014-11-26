#include <iostream>
#include "trim.hpp"
#include <vector>
#include <string>
#include <stdio.h>
#include "tag.hpp"

//miscellaneous
string fileName(string url){
    string stringStack;
    for(int i=0; i < url.length(); i++){
        if(url[i]=='?'||url[i]=='#'){
            break;
        }
        stringStack += url[i];
    }
    return stringStack;
}
string getHeader(string url, string user){
    FILE *f;
    string command = "curl -s "
        "-u \""+user+"\" "
        "--trace-ascii - \""+url+"\" | grep Authorization:";
    char buff[512];
    string header = "";

    if(!(f = popen(command.c_str(), "r"))){
        return "ERROR IN CALLING CURL. INVALID COMMAND.";
    }

    while(fgets(buff, sizeof(buff), f)!=NULL){
        header += buff;
    }
    pclose(f);
    header = header.substr(6);
    return header;
}  

class Curl {
public:
    string url;
    string html;
    vector<Tag> tags;
    vector<string> contents;

    //html manipulation functions
    Curl(string u, string header="",string form=""){
        url = u;
        //start fetch data
        FILE *f;
        string command = "curl -s -H \""+header+"\" ";
        char buff[512];
        if(form!=""){
            command += "-F \""+form+"\" ";
        }
        command += " \""+url+"\"";

        assert (f = popen(command.c_str(), "r"));

        while(fgets(buff, sizeof(buff), f)!=NULL){
            html += buff;
        }
        pclose(f);
        //end fetch data
        //split html
        tags = this->get_tags();
        contents = this->get_contents();
    }

    vector<Tag> get_tags(){
        vector<Tag> tagStack;
        string stringStack = "";
        for (int i = 0; html[i]!='\0'; i++){
            stringStack+=html[i];
            if (html[i]=='<'){
                stringStack="<";
            }else if (html[i]=='>'){
                Tag tag(stringStack);
                tagStack.push_back(tag);
            }
        }
        return tagStack; 
    }
    vector<string> get_contents(){
        vector<string> contentStack;
        string stringStack = "";
        for (int i = 0; html[i]!='\0'; i++){
            if (html[i]=='<'){
                contentStack.push_back(trim(stringStack));
            }else{
                stringStack+=html[i];
                if (html[i]=='>'){
                    stringStack="";
                }
            }
        }
        contentStack.erase(contentStack.begin());
        return contentStack; 
    }

};
