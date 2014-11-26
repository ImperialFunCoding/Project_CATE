#include <iostream>
#include "htmlpre.hpp"
#include <vector>

using namespace std;

int main(){
    string cl="c1";
    string period="1";
    string user = "cmy14";
    string url = "https://cate.doc.ic.ac.uk/timetable.cgi"
        "?period="+period+"&class="+cl+""
        "&keyt=2014\%3Anone\%3Anone\%3A"+user;
    string html = curl(url, user);
    vector<string> tags = get_tags(html);
    vector<string> tag_keys;
    vector<string> tag_vals;
    vector<string> contents = get_contents(html);
    vector<string> notesURLs= getNotesURLs(tags);;
    for(int i = 0; i<notesURLs.size();i++){
        cout<<notesURLs[i]<<endl;
    }
    /*for (int i = 0; i<tags.size(); i++){
        tag_keys=tagAttrKeys(tags[i]);
        tag_vals=tagAttrValues(tags[i]);
        cout<<tagName(tags[i])<<" | "<<contents[i]<<" |";
        for(int i = 0; i<tag_keys.size();i++){
            cout<<" "<<tag_keys[i];
        }
        cout<<" |";
        for(int i = 0; i<tag_vals.size();i++){
            cout<<" "<<tag_vals[i];
        }
        cout<<endl;
    }*/
    return 0;
}
