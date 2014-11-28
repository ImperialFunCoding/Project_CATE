#include <iostream>
#include <stdio.h>
#include "html.hpp"
#include <vector>
#include <stdlib.h>

using namespace std;

int main(){
    Html html("c1","1","cmy14");
    for(int i=0; i<html.assignments; i++){
        cout<<html.assignments<<" ";
        cout<<html.assignments<<" ";
        cout<<html.assignments<<" ";
        cout<<html.assignments<<" ";
        cout<<html.assignments<<" ";
        cout<<html.assignments<<" ";
        cout<<html.assignments<<endl;
    }
    //fetch moduleIds and moduleNames
/*    int bgcolorPos,colspanPos,rowspanPos;
    string currentMod;
    //https://cate.doc.ic.ac.uk/handins.cgi?key=2014:1:110:c1:new:cmy14
    for(int i=0; i<curl.tags.size(); i++){
        if(curl.tags[i].name()=="td" && curl.tags[i].attrSize()>1){
            bgcolorPos=curl.tags[i].attrPos("bgcolor");
            colspanPos=curl.tags[i].attrPos("colspan");
            rowspanPos=curl.tags[i].attrPos("rowspan");
            if(colspanPos>=0){
                if(bgcolorPos>=0){
                    if((curl.tags[i].attrValue(bgcolorPos)=="#cdcdcd"//green
                     || curl.tags[i].attrValue(bgcolorPos)=="#ccffcc"//grey
                     || curl.tags[i].attrValue(bgcolorPos)=="#f0ccf0"//pink
                     || curl.tags[i].attrValue(bgcolorPos)=="white")
                     && curl.tags[i+3].name()=="a"
                     && curl.contents[i+3]!=""){
                        cout<<currentMod<<" "<<curl.contents[i+3];
                        if(curl.tags[i+5].name()=="a"){
                            cout<<" "<<html.findLink(curl.tags[i+5],"handins.cgi")<<endl;
                        }else{
                            cout<<endl;
                        }
                    }
                }
            }
            if(rowspanPos>=0){
                if(curl.contents[i+3].length()>3){
                    currentMod=curl.contents[i+3].substr(2);
                }
            }
        }
    }
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
    }
    */
    return 0;
}
