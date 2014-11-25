#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <stdio.h>
#include "html.hpp"


using namespace std;

/* All possible cate commands:
     cate update
     cate set <class> <period>
     cate pull <id>
     cate mods
     cate ass [-a]
     cate --help
*/

//Help section
const string helpSection = "Help Section";

// Path for attributes file
const string attPath = string(getenv("HOME"))+"/cateFiles/.attributes.txt";
const string assPath = string(getenv("HOME"))+"/cateFiles/.ass.txt";
const string modPath = string(getenv("HOME"))+"/cateFiles/.mods.txt";

// Valid cate commands
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

void runHelp();

void runMods();

bool isValidID(string id);
void runPull(string id);

bool isValidClass(string cl);
bool isValidPeriod(string period);

void runSet(string cl, string period);

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
            //NOTE - Gives segmentation fault: 11
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
        
        if (size == 2) runMods();
        else cout << "Correct usage: cate mods" << endl;
        
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
    cin >> username;
    string cl = *cp++;
    string pd = *cp;
    delete cp;
    Html html(cl, pd, username);
    Assignment* allAss = html.getAssignments();
    Module* allMods = html.getModules();
    
    ofstream ass(assPath);
    if (ass.is_open()) {
        for (int i = 0; i < html.assSize(); i++) {
            ass << allAss->getID() << endl << allAss->getName() << endl << allAss->getLink();
            allAss++;
        }
    }
    ass.close();
    
    ofstream mod(modPath);
    if (mod.is_open()) {
        for (int i = 0; i < html.modSize(); i++) {
            mod << allMods->getModNumber() << endl << allMods->getName() << endl;
            for (int j = 0; j < allMods->noteSize(); j++) {
                mod << allMods->getNotes()[j].getID() << endl << allMods->getNotes()[j].getName() << endl << allMods->getNotes()[j].getLink();
            }
            allMods++;
        }
    }
    mod.close();
}

void runHelp() {
    cout << helpSection << endl;
}

void runMods() {
    //Temporary result
    cout << "Listing modules" << endl;
}

bool isValidID(string id) {
    //Temporary value
    return (id == "345s");
}

void runPull(string id) {
    //Temporary result
    cout << "Pulled file" << endl;
}

bool isValidClass(string cl) {
    //Temporary value
    return (cl == "c1" || cl == "c2");
}

bool isValidPeriod(string period) {
    //Temporary value
    return (period == "autumn" || period == "spring");
}

void runSet(string cl, string period) {
    
    string path = "mkdir "+string(getenv("HOME"))+"/cateFiles";
    system(path.c_str());
    ofstream att;
    att.open(attPath);
    
    if (att.is_open()) {
        att << cl << "\n" << period;
        att.close();
        cout << "Attributes set to:\n" << "Class: " << cl << "\nPeriod: " << period << endl;
    } else cout << "Could not set attributes";

}

void runCurrAss() {
    //Temporary result
    cout << "Listing current assigments" << endl;
}

void runAllAss() {
    //Temporary result
    cout << "Listing all assigments" << endl;
}

bool attFileExists() {
    ifstream f;
    f.open(attPath);
    return f.good();
}

void initAttributes() {
    string path = "mkdir "+string(getenv("HOME"))+"/cateFiles";
    system(path.c_str());
    ofstream att;
    att.open(attPath);
    if (att.is_open()) {
        att << "c1\n" << "autumn";
    }
}

string* getClassPeriod() {
    ifstream f;
    f.open(attPath);
    string* cp = new string[2];
    //string cp[2];
    //pointer = cp;
    if (f.is_open()) {
        //getline(f, cp[0]);
        //getline(f, cp[1]);
        f >> cp[0] >> cp[1];
    }
    f.close();
    return cp;
}















