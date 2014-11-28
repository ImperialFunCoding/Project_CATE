#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <ctime>
#include <map>
#include "html.hpp"
//#include "assigment.hpp"
//#include "module.hpp"


using namespace std;

/* All possible cate commands:
     cate update
     cate set <class> <period>
     cate pull <id>
     cate mods [modnumber]
     cate ass [-a]
     cate --help
*/

//global map for months


map <string, string> stringMonths;
/*
      { {"01" ,"Jan"},
        {"02", "Feb"},
        {"03", "Mar"},
        {"04", "Apr"},
        {"05", "May"},
        {"06", "Jun"},
        {"07", "Jul"},
        {"08", "Aug"},
        {"09", "Sep"},
        {"10", "Oct"},
        {"11", "Nov"},
        {"12", "Dec"} };
 
 */


void setStringMonths() {
    stringMonths["01"]  = "Jan";
    stringMonths["02"]  = "Feb";
    stringMonths["03"]  = "Mar";
    stringMonths["04"]  = "Apr";
    stringMonths["05"]  = "May";
    stringMonths["06"]  = "Jun";
    stringMonths["07"]  = "Jul";
    stringMonths["08"]  = "Aug";
    stringMonths["09"]  = "Sep";
    stringMonths["10"] = "Oct";
    stringMonths["11"] = "Nov";
    stringMonths["12"] = "Dec";
}


map <string, string> numMonths;

/*
      { {"Jan", "01"},
        {"Feb", "02"},
        {"Mar", "03"},
        {"Apr", "04"},
        {"May", "05"},
        {"Jun", "06"},
        {"Jul", "07"},
        {"Aug", "08"},
        {"Sep", "09"},
        {"Oct", "10"},
        {"Nov", "11"},
        {"Dec", "12"} };
*/


void setNumMonths() {
    numMonths["Jan"] = "01";
    numMonths["Feb"] = "02";
    numMonths["Mar"] = "03";
    numMonths["Apr"] = "04";
    numMonths["May"] = "05";
    numMonths["Jun"] = "06";
    numMonths["Jul"] = "07";
    numMonths["Aug"] = "08";
    numMonths["Sep"] = "09";
    numMonths["Oct"] = "10";
    numMonths["Nov"] = "11";
    numMonths["Dec"] = "12";
}





//Help section
const string helpSection = "Help Section";

//Path for attributes file
const string attPath = string(getenv("HOME"))+"/.cateFiles/attributes.txt";
const string assPath = string(getenv("HOME"))+"/.cateFiles/ass.txt";
const string modPath = string(getenv("HOME"))+"/.cateFiles/mods.txt";

//Valid cate commands
const string UPDATE = "update";
const string SET    = "set";
const string PULL   = "pull";
const string MODS   = "mods";
const string ASS    = "ass";
const string HELP   = "--help";

string validCommands[] = {UPDATE, SET, PULL, MODS, ASS, HELP};

// Function declarations
bool attFileExists();
void initAttributes();

bool elem(string e, string elems[], int size);
void execCommand(int size, char *argv[]);

void runUpdate();
bool isBefore(Assignment a1, Assignment a2);

void runHelp();

void runAllMods();
void runMod(string modNum);

bool isValidID(string id);
void runPull(string id);

bool isValidClass(string cl);
bool isValidPeriod(string period);

void runSet(string cl, string period);

int numDate(string date);
string stringDate(int date);
void runCurrAss();
void runAllAss();

string* getClassPeriod();

int main(int argc, char *argv[]) {
    if (argc > 4 || argc == 1) {
        cout << "Incorrect usage, see 'cate --help' for more information" << endl;
        return 1;
    }
    
    if (!attFileExists()) {
        initAttributes();
    }
    
    if (elem(string(argv[1]), validCommands, 6)) {
       execCommand(argc, argv);
    }
    else {
        cout << "Incorrect usage, see 'cate --help' for more information" << endl;
    }
    return 0;
}

// Checks if a string is in an array of strings
bool elem(string e, string elems[], int size) {
    for (int i = 0; i < size; i++) {
        if (elems[i] == e) return true;
    }
    return false;
}

//Executes the correct function based on command-line input
void execCommand(int size, char *argv[]) {
    if (string(argv[1]) == UPDATE) {
        
        if (size == 2) runUpdate();
        else cout << "Correct usage: cate update" << endl;
        
    } else if (string(argv[1]) == SET) {
        
        if (size == 4) {
            if (isValidClass(string(argv[2])) && isValidPeriod(string(argv[3]))) {
                runSet(string(argv[2]), string(argv[3]));
            } else cout << "Error: class and/or period not valid" << endl;
        } else cout << "Correct usage: cate set <class> <period>" << endl;
        
    } else if (string(argv[1]) == PULL) {
        
        if (size == 3) {
            if (isValidID(string(argv[2]))) {
                runPull(string(argv[2]));
            } else cout << "Error: pull id not valid" << endl;
        } else cout << "Correct usage: cate pull <id>" << endl;
        
    } else if (string(argv[1]) == MODS) {
        
        if (size == 2) runAllMods();
        else if (size == 3) runMod(string(argv[2]));
        else cout << "Correct usage: cate mods [modnumber]" << endl;
        
    } else if (string(argv[1]) == ASS) {
        
        if (size == 2) {
            runCurrAss();
        } else if (size == 3 && string(argv[2]) == "-a") {
            runAllAss();
        } else cout << "Correct usage: cate ass [-a]" << endl;
        
    } else if (string(argv[1]) == HELP) {
        
        if (size == 2) runHelp();
        else cout << "Correct usage: cate --help" << endl;
        
    } else cout << "Impossible!" << endl;
}

////////// Executive Functions //////////

void runUpdate() {
    string *cp = getClassPeriod();
    string username;
    cout << "Please enter your cate username:" << endl;
    getline(cin, username);
    string cl = cp[0];
    string pd = cp[1];
    
    Html html(cl, pd, username);
    vector<Assignment> allAss = html.getAssignments();
    vector<Module> allMods = html.getModules();
    
    cout << "Saving data..." << endl;

    /*
    vector<Assignment> allAss;
    allAss.push_back(Assignment("s125", "Maths", "green", "11 Dec 2014", "www.google.com", "123", "m"));
    allAss.push_back(Assignment("s345", "Physics", "white", "25 Nov 2014", "www.facebook.com", "123", "m"));
    */
    
    setNumMonths();
    
    sort(allAss.begin(), allAss.end(), isBefore);
    
    ofstream ass(assPath.c_str());
    if (ass.is_open()) {
        for (int i = 0; i < allAss.size(); i++) {
            ass << allAss[i].getID() << endl << allAss[i].getName() << endl << allAss[i].assType() << endl  << allAss[i].getDueDate() << endl << allAss[i].getLink() << endl << allAss[i].getSubmitID() << endl << allAss[i].getModule() << endl;
        }
    }
    ass.close();

    /*
    vector<Notes> notesFrench;
    notesFrench.push_back(Notes("n317", "Notes F1", "www.hotmail.com"));
    notesFrench.push_back(Notes("n715", "Notes F2", "www.espn.com"));

    vector<Notes> notesSpanish;
    notesSpanish.push_back(Notes("n654", "Notes S1", "www.hello.com"));
    notesSpanish.push_back(Notes("n976", "Notes S2", "www.hola.com"));

    vector<Module> allMods;
    allMods.push_back(Module("1", "French", notesFrench, 2));
    allMods.push_back(Module("2", "Spanish", notesSpanish, 2));
    */
    
    ofstream mod(modPath.c_str());
    if (mod.is_open()) {
        for (int i = 0; i < allMods.size(); i++) {
            mod << allMods[i].getModNumber() << endl;
            mod << allMods[i].getName() << endl;
            for (int k = 0; k < allMods[i].getNotes().size(); k++) {
                mod << allMods[i].getNotes()[k].getID() << endl;
                mod << allMods[i].getNotes()[k].getName() << endl;
                mod << allMods[i].getNotes()[k].getLink() << endl;
                mod << allMods[i].getNotes()[k].getType() << endl;
            }
            mod << endl;
        }
    }
    mod.close();

    cout << "Update complete." << endl;
    
}

bool isBefore(Assignment a1, Assignment a2) {
    return numDate(a1.getDueDate()) < numDate(a2.getDueDate());
}

void runHelp() {
    cout << helpSection << endl;
}

void runAllMods() {
    //Temporary result
    //cout << "Listing all modules" << endl;
    
    ifstream mods(modPath.c_str());
    if (mods.is_open()) {
        cout << left <<setw(5) << "Mod" << "Name" << endl;
        //string line;
        bool printThis = true;
        while (!mods.eof()) {
            if (printThis) {
                string num;
                string name;
                getline(mods, num);
                getline(mods, name);
                if (num == "-1") num = "-";
                cout << setw(5) << num << name << endl;
                printThis = false;
            } else {
                string line;
                getline(mods, line);
                if (line.empty()) printThis = true;
            }
        }
        mods.close();
        
    } else cout << "No modules to show" << endl;
}

void runMod(string modNum) {
    //Temporary result
    //cout << "Listing given module" << endl;
    
    ifstream mods(modPath.c_str());
    if (mods.is_open()) {
        bool found = false;
        while(!mods.eof()) {
            string line;
            getline(mods, line);
            if (line == modNum) {found = true; break;}
        }
        if (found) {
            string name;
            getline(mods, name);
            
            cout << "Module: " << name << endl;
            cout << left << setw(5) << "ID" << "Name" << endl;
            
            while(!mods.eof()) {
                string id;
                string name;
                string link;
                string type;
                getline(mods, id);
                getline(mods, name);
                getline(mods, link);
                getline(mods, type);
                
                if (id.empty()) break;
                
                cout << setw(5) << id << name << endl;
            }
        } else cout << "Module not found" << endl;
    }
    mods.close();
}

bool isValidID(string id) {
    //Temporary value
    //return (id == "345s");
    return true;
}

void runPull(string id) {
    //Temporary result
    //cout << "Pulled file" << endl;

    if (id[0] == 'n') {
        
        string link;
        string name;
        string fileType;
        ifstream note(modPath.c_str());
        if (note.is_open()) {
            bool found = false;
            while (!note.eof()) {
                string line;
                getline(note, line);
                if (line == id) {found = true; break;}
            }

            if (!found) {
                cout << "Error: pull id not valid" << endl;
                return;
            }

            getline(note, name);
            getline(note, link);
            getline(note, fileType);

            //cout << link << endl;
        }
        note.close();
        //get username from link
        string user = link.substr(link.find(":NOTES:"));
        user = user.substr(7);
        string saveAs = " > \"" + name + "." + fileType + "\"";
        string pullCommand = "curl -s -H \""+ getHeader(CATE_URL,user) +"\" \"" + link +"\"" + saveAs;
        //cout << pullCommand << endl;
        cout << "Pulling file for " + user + "." << endl;
        system(pullCommand.c_str());

    } else if (id[0] == 's') {
        
        string link;
        string name;
        ifstream spec(modPath.c_str());
        if (spec.is_open()) {
            bool found = false;
            while (!spec.eof()) {
                string line;
                getline(spec, line);
                if (line == id) {found = true; break;}
            }

            if (!found) {
                cout << "Error: pull id not valid" << endl;
                return;
            }
            
            getline(spec, name);
            getline(spec, link);
            getline(spec, link);
            getline(spec, link);

            //cout << link << endl;
        }
        spec.close();
        //get username from link
        string user = link.substr(link.find(":SPECS:"));
        user = user.substr(7);
        string saveAs = " > \"" + name + "." + "pdf\"";
        string pullCommand = "curl -s -H \""+ getHeader(CATE_URL,user) +"\" \"" + link +"\"" + saveAs;
        //cout << pullCommand << endl;
        cout << "Pulling file for " + user + "." << endl;
        system(pullCommand.c_str());

        
    } else cout << "Error: pull id not valid" << endl;
}

bool isValidClass(string cl) {
    //Temporary value
    return (cl == "c1" || cl == "c2" || cl == "c3");
    //if (!(cl.length() == 2)) return false;
    //if (c[0] == 'c' ||
}

bool isValidPeriod(string period) {
    //Temporary value
    return (period == "1" || period == "2");
}

void runSet(string cl, string period) {
    
    string path = "mkdir -p "+string(getenv("HOME"))+"/.cateFiles";
    popen(path.c_str(), "r");
    ofstream att;
    att.open(attPath.c_str());
    
    if (att.is_open()) {
        att << cl << "\n" << period;
        att.close();
        cout << "Attributes set to:\n" << "Class: " << cl << "\nPeriod: " << period << endl;
    } else cout << "Could not set attributes";

}

void runCurrAss() {
    //Temporary result
    //cout << "Listing current assignments" << endl;
    
    
    ifstream ass(assPath.c_str());
    if (ass.is_open()) {
        
        setNumMonths();
        
        //Converting system time to today's date
        time_t now = time(0);
        string current = ctime(&now);
        string mon = current.substr(4,3);
        string day = current.substr(8, 2);
        string year = current.substr(20);
        string today = day + " " + mon + " " + year;
        //cout << today << endl;
        
        cout << left << setw(6) << "ID" << setw(15) << "Name" << setw(20) << "Type" << setw(15) << "Due Date" << setw(20) << "Module" << endl;
        
        while (!ass.eof()) {
            string id;
            getline(ass, id);
            string name;
            getline(ass, name);
            string assType;
            getline(ass, assType);
            string dueDate;
            getline(ass, dueDate);
            string link;
            getline(ass, link);
            string submitID;
            getline(ass, submitID);
            string module;
            getline(ass, module);
            
            //Print ass if due date has not passed
            if (numDate(today) < numDate(dueDate)) {
                cout << left << setw(6) << id << setw(15) << name << setw(20) << assType << setw(15) << dueDate << setw(20)<< module << endl;
            }

        }
        //cout << stringDate(20140511) << endl;
    } else cout << "No Assignments to show" << endl;
    
}

//Gives date in the form yyyymmdd
int numDate(string date) {
    if (date.empty()) return 0;
    if (date == "-1") return -1;
    string day = date.substr(0, 2);
    string mon = date.substr(3, 3);
    string year = date.substr(7, 4);
    //cout << numMonths[mon] << endl;
    string newDate = year + numMonths[mon] + day;
    return stoi(newDate);
}


//Gives date in the form "dd mon yyyy"
string stringDate(int date) {
    string strDate = to_string(date);
    return strDate.substr(6, 2) + " " + stringMonths[strDate.substr(4, 2)] + " " + strDate.substr(0, 4);
}


void runAllAss() {
    //cout << "Listing all assigments:\n" << endl;
    cout << left << setw(6) << "ID" << setw(15) << "Name" << setw(20) << "Type" << setw(15) << "Due Date" << setw(20) << "Module" << endl;
    ifstream fin(assPath.c_str());
    if (fin.is_open()) {
        while (!fin.eof()) {
            string id;
            getline(fin, id);
            string name;
            getline(fin, name);
            // isCounted is a bool value, stored as 0 or 1 in file
            string assType;
            getline(fin, assType);
            if (assType == "1") assType = "Assesed";
            else if (assType == "0") assType = "Non-Assesed";
            string dueDate;
            getline(fin, dueDate);
            string link;
            getline(fin, link);
            string submitID;
            getline(fin, submitID);
            string module;
            getline(fin, module);
            
            cout << left << setw(6) << id << setw(15) << name << setw(20) << assType << setw(15) << dueDate << setw(20)<< module << endl;
        }
        
    } else cout << "No Assignments to show" << endl;
}

bool attFileExists() {
    ifstream f;
    f.open(attPath.c_str());
    return f.good();
}

void initAttributes() {
    string path = "mkdir -p "+string(getenv("HOME"))+"/.cateFiles";
    popen(path.c_str(), "r");
    ofstream att;
    att.open(attPath.c_str());
    if (att.is_open()) {
        att << "c1\n" << "1";
    }
    att.close();
}

string* getClassPeriod() {
    ifstream f;
    f.open(attPath.c_str());
    string* cp = new string[2];
    if (f.is_open()) {
        f >> cp[0] >> cp[1];
    }
    f.close();
    return cp;
}















