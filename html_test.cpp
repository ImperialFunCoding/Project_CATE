#include <iostream>
#include <stdio.h>
#include "html.hpp"
#include <vector>
#include <stdlib.h>

using namespace std;

int main(){
    Html html("c1","1","cmy14");
    
    /*getModuleID
    string cl="c1";
    string period="1";
    string user = "cmy14";
    string url ="https://cate.doc.ic.ac.uk/timetable.cgi?period=1&class=c1&keyt=2014%3Anone%3Anone%3Acmy14";
    string header= getHeader(CATE_URL,user);
    //fetch moduleIds and moduleNames
    Curl curl(url,header);
    vector<string> modNames=html.getModuleNames(curl.contents);
    vector<string> modIds=html.getModuleIds(curl.tags);
    for(int i=0; i<modNames.size(); i++){
        if(modIds.size()>i && atoi(modIds[i].c_str())>0){
            Curl curl_notes("https://cate.doc.ic.ac.uk/notes.cgi?key=2014:"+modIds[i]+":1:c1:new:cmy14",header);
            vector<string> noteIds= html.getNoteIds(curl_notes.tags);
            vector<string> noteNames = html.getNoteNames(curl_notes.tags,curl_notes.contents);
            cout<<modIds[i]<<" "<<modNames[i];
            cout<<" -> "<<endl;
            for(int i=0; i<noteIds.size();i++){
                cout<<"  "<<noteIds[i]<<". "<<noteNames[i]<<endl;
            }
        }else{
            cout<<" "<<" "<<modNames[i];
        }
        cout<<endl;
    }*/
    return 0;
}
