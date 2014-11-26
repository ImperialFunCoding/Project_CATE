#include <iostream>
#include <stdio.h>
#include "html.hpp"
#include <vector>
#include <stdlib.h>

using namespace std;

int main(){
    Html html("c1","1","cmy14");
    
    string cl="c1";
    string period="1";
    string user = "cmy14";
    string url ="https://cate.doc.ic.ac.uk/timetable.cgi?period=1&class=c1&keyt=2014%3Anone%3Anone%3Acmy14";
    string header= "";//getHeader(CATE_URL,user);
    //fetch moduleIds and moduleNames
    Curl curl(url,header);
    for(int i=0; i<curl.tags.size(); i++){
        if(curl.tags[i].name()=="td" && curl.tags[i].attrSize()>1){
            if(curl.tags[i].hasAttr("bgcolor") && curl.tags[i].hasAttr("colspan")){
                cout<<curl.tags[i].tag<<curl.contents[i+3]<<endl;
            }
        }
    }
    /*
    vector<string> assIds = html.getShowfileIds(curl.tags);
    vector<string> assURLs = html.getShowfileURLs(curl.tags);
    vector<string> assNames = html.getShowfileNames(curl.tags,curl.contents);

    for(int i=0; i<assIds.size();i++){
        cout<<assIds[i]<<" "<<assNames[i]<<" "<<endl;
    }
    for(int i=0; i < curl.tags.size();i++){
        cout<<curl.tags[i].name()<<" "<<curl.contents[i]<<endl;
        for(int j=0; j<curl.tags[i].attrSize(); j++){
            cout<<"  "<<curl.tags[i].attrKey(j)<<" = ";
            cout<<curl.tags[i].attrValue(j)<<endl;
        }
    }*/
    return 0;
}
