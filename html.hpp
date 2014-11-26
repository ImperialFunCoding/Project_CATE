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
#include <stdio.h>

using namespace std;

class Html {
    
private:
    //Private fields here
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
public:
    
    //Implement the following member functions

    /* Since the IDs for specs and notes are different,
     * set the ID for specs with an 's' at the back,
     * eg. "345s"
     * and with an 'n' at the back of notes,
     * eg. "123n"
     */

    string cl, period, user;
    
    Html(string c, string p, string u) {
        //Class constructor here
        
        // The constructor for the Assignment class is:
        // Assignment(string n_id, string n_name, bool n_counted, string n_dueDate, string n_link);
        // Note: the n_counted variable denotes if the assigment is green on cate
        // Note: string dueDate in the format: "23 May 2014"
        
        
        // The constructor for the Module class is:
        // Module(string n_modNumber, string n_name, Notes n_notes[], int n_numNotes);
        // Note: the arguments for the constructor include an array of notes
        // The constructor for the Notes module is:
        // Notes(n_id, n_name, n_link);
        cl      = c;
        period  = p;
        user    = u;
        
    }
    
    Assignment* getAssignments() {
        // Returns an array of Assignments
        
        return NULL;
    }
    
    int assSize() {
        //Return the size of the assigments array
        
        return 0;
    }
    
    
    Module* getModules() {
        // Returns an array of Modules
                return NULL;
    }
    
    int modSize() {
        //Return the size of the modules array
        return 0;
    }
    
    
    bool isValidClass(string cl) {
        //Returns true if the class input eg. "c1", "c2" exists on cate
        return false;
    }
    
    
    static bool isValidPeriod(string period) {
        //Returns true if the period input eg. "autumn", "spring" exists on cate
        return false;
    }
    
};
