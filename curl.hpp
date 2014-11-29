#include <iostream>
#include "trim.hpp"
#include <vector>
#include <string>
#include <stdio.h>
#include "tag.hpp"

string getHeader(string url, string user){
    FILE *f;
    int i;
    string header = "";
    do{
        i=0;
        header = "";
        string command = "curl -s "
            "-u \""+user+"\" "
            "--trace-ascii - \""+url+"\" | grep \"Authorization:\\|401\\ Authorization\\ Required\"";
        char buff[512];

        if(!(f = popen(command.c_str(), "r"))){
            return "ERROR IN CALLING CURL. INVALID COMMAND.";
        }

        while(fgets(buff, sizeof(buff), f)!=NULL){
            header += buff;
            if(header[header.size()-1]=='\n'){
                i++;
            }
        }
        pclose(f);
    }while(i!=1);
    header = header.substr(6,header.size()-7);
    return header;
}  

class Curl {
public:
    string url;
    string html;
    vector<Tag> tags;
    vector<string> contents;

    //html manipulation functions
    Curl(string u, string header="",vector<string> forms=vector<string>()){
        url = u;
        //start fetch data
        FILE *f;
        cout<<"Fetching "<<u<<endl;
        string command = "curl -s -H \""+header+"\" ";
        char buff[512];
        for(int i=0; i<forms.size(); i++){
            command += "-F \""+forms[i]+"\" ";
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
