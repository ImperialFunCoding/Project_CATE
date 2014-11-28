/*
useful command for fetching htmls

personal page
curl --user user "https://cate.doc.ic.ac.uk/personal.cgi?keyp=2014:"+user

timetable
curl --user user "https://cate.doc.ic.ac.uk/timetable.cgi?period=1&class=c1&keyt=2014%3Anone%3Anone%3A"+user

submit declearation
curl -u user -d "help-0=&help-1=&help-2=&help-3=&help-4=&help-5=&help-6=&help-7=&inLeader=&inMember=&version=0&key=2014:1:23:"+cl+":leader:"+user "https://cate.doc.ic.ac.uk/handins.cgi?key=2014:1:23:c1:new:"+user

submit cate_token.txt
curl -u user -F "key=2014:1:23:"+cl+":submit:"+user -F "file-516-none=@cate_token.txt" "https://cate.doc.ic.ac.uk/handins.cgi?key=2014:1:23:c1:new:"+user
*/
#include "assigment.hpp"
#include "module.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include "curl.hpp"
#include <stdlib.h>

using namespace std;


static string* declaration(string user, string cl, string period, string sId){
    string header = getHeader(CATE_URL,user);
    cout<<endl<<"Submiting empty declaration..."<<endl;
    string url ="https://cate.doc.ic.ac.uk/handins.cgi?key=2014:"+period+":"+sId+":"+cl+":new:"+user;
    Curl curl_inLeader(url,header);
    string inLeader;
    string* array=new string[2];
    array[0] = header;
    for(int i=0; i<curl_inLeader.tags.size();i++){
        if(curl_inLeader.tags[i].name()=="input"){
            if(curl_inLeader.tags[i].attrPos("name")>=0){
                int pos = curl_inLeader.tags[i].attrPos("name");
                if(curl_inLeader.tags[i].attrValue(pos)=="inLeader"){
                    int pos = curl_inLeader.tags[i].attrPos("value");
                    inLeader = curl_inLeader.tags[i].attrValue(pos);
                }
            }
        }
        if(curl_inLeader.tags[i].findLink("hardcover.cgi")!=""){
            array[1]=curl_inLeader.tags[i].findLink("hardcover.cgi");
        }
    }
    vector<string> forms;
    forms.push_back("help-0=");
    forms.push_back("help-1=");
    forms.push_back("help-2=");
    forms.push_back("help-3=");
    forms.push_back("help-4=");
    forms.push_back("help-5=");
    forms.push_back("help-6=");
    forms.push_back("help-7=");
    forms.push_back("inLeader="+inLeader);
    forms.push_back("inMember=");
    forms.push_back("version=0");
    forms.push_back("key=2014:"+period+":"+sId+":"+cl+":leader:"+user);

    Curl curl_declear(url,header,forms);
    return array;
}

static void submit(string user, string cl, string period, string sId){
    //Pre: .git folder exist
    string* array = declaration(user,cl,period,sId);
    string header = array[0];
    string hardcover = array[1];
    string url ="https://cate.doc.ic.ac.uk/handins.cgi?key=2014:"+period+":"+sId+":"+cl+":new:"+user;
    cout<<endl;
    if(hardcover==""){
        vector<string> forms2;
        forms2.push_back("key=2014:1:23:c1:submit:cmy14");
        forms2.push_back("file-516-none=@cate_token.txt");
        string command = "git rev-parse HEAD > cate_token.txt";
        system(command.c_str());
        cout<<"Submiting cate_token.txt..."<<endl;
        Curl submit(url,header,forms2);
        cout<<endl;
        system("rm cate_token.txt");
        return;
    } else{
        cout<<"Downloading hard cover..."<<endl;
        cout<<"Fetching "+hardcover<<endl;
        string command = "curl -s -H "+header+" "+hardcover+">hardcover-"+sId+".ps";
        system(command.c_str());
        cout<<"Hardcover fetched at: ./hardcover-"+sId+".ps"<<endl<<endl;
        return;
    }
}


class Html {
    
private:
    string getURL(char p,string id=""){
        string url;
        url = CATE_URL;
        switch(p){
            case 't':
                url += "timetable.cgi"
                    "?period="+period+"&class="+cl+""
                    "&keyt=2014\%3Anone\%3Anone\%3A"+user;
                break;
            case 'n':
                assert(id!="");
                url += "notes.cgi"
                    "?key=2014:"+id+":"+period+":"
                    ""+cl+":new:"+user;
                break;
            case 'g':
                assert(id!="");
                url += "given.cgi"
                    "?key=2014:"+period+":"+id+":"
                    ""+cl+":new:"+user;
                break;
            case 'h':
                assert(id!="");
                url += "handins.cgi"
                    "?key=2014:"+period+":"+id+":"
                    ""+cl+":new:"+user;
                break;
            case 's':
                assert(id!="");
                string type;
                switch(id[0]){
                    case 'n':
                        type = "NOTES";
                        break;
                    case 's':
                        type = "SPECS";
                        break;
                    default:
                        assert(false && "THE ID IS NOT RIGHT");
                }
                url += "showfile.cgi"
                    "?key=2014:"+period+":"+id+":"
                    ""+cl+":"+type+":"+user;
                break;
        }
        return url;
    }

    vector<string> findLinks(vector<Tag> tags,string file){
        vector<string> URLStack;
        for (int i = 0; i < tags.size(); i++){
            if(tags[i].findLink(file)!=""){
                URLStack.push_back(tags[i].findLink(file));
            }
        }
        return URLStack;
    }
    string getShowfileId(Tag tag){
        string URL = tag.findLink("showfile.cgi");
        int colon,colon2;
        //start from 6 to skip https://
        colon2 = URL.find_first_of(":",6);
        colon  = URL.find_first_of(":",colon2+1);
        colon2 = URL.find_first_of(":",colon+1);
        return URL.substr(colon+1,colon2-colon-1);
    }
    vector<string> getShowfileIds(vector<Tag> tags){
        vector<string> idStack;
        for(int i=0; i< tags.size();i++){
            if(getShowfileId(tags[i])!=""){
                idStack.push_back(getShowfileId(tags[i]));
            }
        }
        return idStack; 
    }
    vector<string> getShowfileURLs(vector<Tag> tags){
        //Pre: tags is from notes.cgi
        return findLinks(tags,"showfile.cgi");
    }
    vector<string> getShowfileNames(vector<Tag> tags,vector<string> contents){
        vector<string> nameStack;
        for(int i=0; i<tags.size(); i++){
            for(int j=0; j<tags[i].attrSize(); j++){
                if(fileName(tags[i].attrValue(j))=="showfile.cgi"){
                    nameStack.push_back(contents[i]);
                }
            }
        }
        return nameStack;    
    }

    vector<string> getNotesType(vector<Tag> tags, vector<string> contents){
        vector<string> typeStack;
        for (int i = 0; i < tags.size(); i++){
            for(int j=0; j<tags[i].attrSize(); j++){
                if(fileName(tags[i].attrValue(j))=="showfile.cgi"){
                    typeStack.push_back(contents[i+3]);
                }
            }
        }
        return typeStack;
    }

    vector<string> getModuleIds(vector<Tag> tags){
        //Pre: tags is from timetable.cgi
        vector<string> URLs = this->findLinks(tags,"notes.cgi");
        vector<string> idStack;
        int rowspanPos;
        int bgcolorPos;
        int j=0;
        for(int i=0; i<tags.size();i++){
            rowspanPos=tags[i].attrPos("rowspan");
            bgcolorPos=tags[i].attrPos("bgcolor");
            if(tags[i].name()=="td"
            && rowspanPos>=0 
            && bgcolorPos>=0){
                if(tags[i].attrValue(bgcolorPos)=="white"&&tags[i+1].name()=="b"){
                    if(tags[i+6].name()=="a"){
                        int colon,colon2;
                        colon  = URLs[j].find_first_of(":",6);
                        colon2 = URLs[j].find_first_of(":",colon+1);
                        idStack.push_back(URLs[j++].substr(colon+1,colon2-colon-1));
                    }else{
                        idStack.push_back("-1");
                    }
                }
            }
        }
        return idStack;
    }

    vector<string> getModuleNames(vector<string> contents){
        //Pre: contents is from timetable.cgi
        vector<string> moduleStack;
        for (int i=0; i < contents.size(); i++){
            if(contents[i].length()>=3){
                if(contents[i][0]=='-'){
                    moduleStack.push_back(contents[i].substr(2));
                }
            }
        }
        return moduleStack;
    }
    
    string getAssDueDate(vector<Tag> tags, vector<string> contents){
        bool seenDue=false;
        for(int i=0;i<tags.size();i++){
            if(seenDue){
                if(tags[i].name()=="td"){
                    return contents[i+3].substr(6);
                }
            }else{
                if(tags[i].name()=="td"){
                    if(contents[i+1]=="Due"){
                        seenDue=true;
                    }
                }
            }
        }
        return "-1";
    }

    string getHandinsId(Tag tag){
        string URL = tag.findLink("handins.cgi");
        if(URL!=""){
            int colon,colon2;
            colon2 = URL.find_first_of(":",6);
            colon  = URL.find_first_of(":",colon2+1);
            colon2 = URL.find_first_of(":",colon+1);
            return URL.substr(colon+1,colon2-colon-1);
        }
        return "-1";
    }
    vector<string> getAssSid(vector<Tag> tags,vector<string> contents){
        int bgcolorPos, colspanPos;
        vector<string> ids;
        for(int i=0; i<tags.size(); i++){
            if(tags[i].name()=="td" && tags[i].attrSize()>1){
                bgcolorPos=tags[i].attrPos("bgcolor");
                colspanPos=tags[i].attrPos("colspan");
                if(colspanPos>=0){
                    if(bgcolorPos>=0){
                        if((tags[i].attrValue(bgcolorPos)=="#cdcdcd"//green
                         || tags[i].attrValue(bgcolorPos)=="#ccffcc"//grey
                         || tags[i].attrValue(bgcolorPos)=="#f0ccf0"//pink
                         || tags[i].attrValue(bgcolorPos)=="white")
                         && tags[i+3].name()=="a"
                         && contents[i+3]!=""){
                            if(tags[i+5].name()=="a"
                        &&tags[i+6].attrValue(tags[i+6].attrPos("src") )=="icons/h.gif"
                                ){

                                string id = getHandinsId(tags[i+5]);
                                ids.push_back(id);
                            }else{
                                ids.push_back("-1");
                            }
                        }
                    }
                }
            }
        }
        return ids;
    }
    vector<string> getAssTypes(vector<Tag> tags,vector<string> contents){
        int bgcolorPos, colspanPos;
        vector<string> typeStack;
        for(int i=0; i<tags.size(); i++){
            if(tags[i].name()=="td" && tags[i].attrSize()>1){
                bgcolorPos=tags[i].attrPos("bgcolor");
                colspanPos=tags[i].attrPos("colspan");
                if(colspanPos>=0){
                    if(bgcolorPos>=0){
                        if((tags[i].attrValue(bgcolorPos)=="#cdcdcd"//grey
                         || tags[i].attrValue(bgcolorPos)=="#ccffcc"//green
                         || tags[i].attrValue(bgcolorPos)=="#f0ccf0"//pink
                         || tags[i].attrValue(bgcolorPos)=="white")
                         && tags[i+3].name()=="a"
                         && contents[i+3]!=""){
                            if(tags[i].attrValue(bgcolorPos)=="#cdcdcd"){
                                typeStack.push_back("grey");
                            }else if(tags[i].attrValue(bgcolorPos)=="#ccffcc"){
                                typeStack.push_back("green");
                            }else if(tags[i].attrValue(bgcolorPos)=="#f0ccf0"){
                                typeStack.push_back("pink");
                            }else if(tags[i].attrValue(bgcolorPos)=="white"){
                                typeStack.push_back("white");
                            }else assert(false && "IMPOSSIBLE!");
                        }
                    }
                }
            }
        }
        return typeStack;
    }
    vector<string> getAssCurMods(vector<Tag> tags, vector<string> contents){
        vector<string> curMods;
        string currentMod;
        int bgcolorPos,colspanPos,rowspanPos;
        for(int i=0; i<tags.size(); i++){
            if(tags[i].name()=="td" && tags[i].attrSize()>1){
                bgcolorPos=tags[i].attrPos("bgcolor");
                colspanPos=tags[i].attrPos("colspan");
                rowspanPos=tags[i].attrPos("rowspan");
                if(colspanPos>=0){
                    if(bgcolorPos>=0){
                        if((tags[i].attrValue(bgcolorPos)=="#cdcdcd"//green
                         || tags[i].attrValue(bgcolorPos)=="#ccffcc"//grey
                         || tags[i].attrValue(bgcolorPos)=="#f0ccf0"//pink
                         || tags[i].attrValue(bgcolorPos)=="white")
                         && tags[i+3].name()=="a"
                         && contents[i+3]!=""){
                            curMods.push_back(currentMod);
                        }
                    }
                }
            }
            if(rowspanPos>=0){
                if(contents[i+3].length()>2){
                    if(contents[i+3][0]=='-'){
                        currentMod=contents[i+3].substr(2);
                    }
                }
            }
        }
        return curMods;
    }

public:
    string cl, period, user;
    string header;

    vector<Module> modules;
    vector<Assignment> assignments;
   
    Html(string c, string p, string u) {
        cl      = c;
        period  = p;
        user    = u;

        //this will ask for password
        header  = getHeader(CATE_URL,user);

        //module
        Curl curl(this->getURL('t'),header);
        vector<string> modNames=this->getModuleNames(curl.contents);
        vector<string> modIds=this->getModuleIds(curl.tags);
        vector<Module> mods;
        for(int i=0; i<modNames.size(); i++){
            if(modIds.size()>i && atoi(modIds[i].c_str())>0){
                Curl curl_notes(CATE_URL+"notes.cgi?key=2014:"+modIds[i]+":"+period+":"+cl+":new:"+user,header);
                vector<string> noteIds= this->getShowfileIds(curl_notes.tags);
                vector<string> noteNames = this->getShowfileNames(curl_notes.tags,curl_notes.contents);
                vector<string> noteURLs = this->getShowfileURLs(curl_notes.tags);
                vector<string> noteTypes = this->getNotesType(curl_notes.tags,curl_notes.contents);
                vector<Notes> notes;
                for(int j=0; j<noteIds.size();j++){
                    Notes note("n"+noteIds[j],noteNames[j],noteURLs[j], noteTypes[j]);
                    notes.push_back(note);
                }
                Module mod(modIds[i],modNames[i],notes,noteIds.size());
                mods.push_back(mod); 
            }else{
                Module mod("-1",modNames[i],vector<Notes>(),0);
                mods.push_back(mod); 
            }
        }
        modules = mods;
        
        //assignments
        vector<string> assIds       = getShowfileIds(curl.tags);
        vector<string> assNames     = getShowfileNames(curl.tags,curl.contents);
        vector<string> assTypes     = getAssTypes(curl.tags,curl.contents);
        vector<string> assLinks     = getShowfileURLs(curl.tags);
        vector<string> assSids      = getAssSid(curl.tags,curl.contents);
        vector<string> assCurMods   = getAssCurMods(curl.tags,curl.contents);
        for(int i=0; i<assIds.size(); i++){
            assIds[i]="s"+assIds[i];
            if(assSids[i]!="-1"){
                Curl curl_ass(this->getURL('h',assSids[i]),header);
                string assDueDate  = getAssDueDate(curl_ass.tags,curl_ass.contents);
                Assignment ass(assIds[i],assNames[i],assTypes[i],
                    assDueDate,assLinks[i],assSids[i],assCurMods[i]);
                assignments.push_back(ass);
            }else{
                Assignment ass(assIds[i],assNames[i],assTypes[i],
                    "-1",assLinks[i],assSids[i],assCurMods[i]);
                assignments.push_back(ass);
            }
        }
        
    }
    
    vector<Assignment> getAssignments() {
        // Returns an array of Assignments
        return assignments;
    }
    
    vector<Module> getModules() {
        // Returns an array of Modules
        return modules;
    }
};
