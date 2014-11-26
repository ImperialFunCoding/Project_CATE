#include <stdio.h>
#include <iostream>
#include <vector>
#include "trim.hpp"

using namespace std;

const string CATE_URL= "https://cate.doc.ic.ac.uk/";
//string manipulation functions
string tagName(string tag){
    string name;
    for (int i=1; i<tag.length(); i++){
        if (tag[i]==' ' || tag[i]=='>' || (tag[i]=='/' && tag[i+1]=='>')){
            break;
        }
        if (tag[i-1]=='<' && tag[i]=='/'){
            continue;
        }
        name+=tag[i];
    }
    return name;
}
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

//html manipulation functions
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
    command += "\""+url+"\"";

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
    vector<string> tagStack;
    string stringStack = "";
    for (int i = 0; html[i]!='\0'; i++){
        stringStack+=html[i];
        if (html[i]=='<'){
            stringStack="<";
        }else if (html[i]=='>'){
            tagStack.push_back(stringStack);
        }
    }
    return tagStack; 
}
vector<string> get_contents(string html){
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

vector<string> tagAttrKeys(string tag){
    vector<string> key;
    string stringStack="";
    bool ignore=false;
    for (int i=1; i<tag.length(); i++){
        if(tag[i]=='\"'){
        // using xor(^) to toogle true and false value
            ignore ^= true; 
        }
        if(ignore) continue;
        if (tag[i]==' ' || tag[i]=='>'
        || (tag[i]=='/' && tag[i+1]=='>')){
            stringStack="";
            continue;
        }
        if(tag[i]=='='){
            key.push_back(stringStack);
            stringStack="";
        }
        stringStack+=tag[i];
    }
    return key;
}
vector<string> tagAttrValues(string tag){
    vector<string> val;
    string stringStack="";
    bool ignore=false;
    for (int i=1; i<tag.length(); i++){
        if(tag[i]=='\"'){
        // using xor(^) to toogle true and false value
            ignore ^= true;
            continue;
        }
        if (tag[i]==' ' || tag[i]=='>'
        || (tag[i]=='/' && tag[i+1]=='>')){
            val.push_back(stringStack);
            stringStack="";
            continue;
        }
        stringStack+=tag[i];
        if(tag[i]=='=' && !ignore){
            stringStack="";
        }
    }
    val.erase(val.begin());
    return val;
}

//cate related functions
vector<string> getNotesURLs(vector<string> tags){
    vector<string> URLStack,tag_values;
    for (int i = 0; i < tags.size(); i++){
        tag_values=tagAttrValues(tags[i]);
        for(int i=0; i<tag_values.size(); i++){
            if(fileName(tag_values[i])=="notes.cgi"){
                URLStack.push_back(CATE_URL+tag_values[i]);
            }
        }
    }
    return URLStack;
}
