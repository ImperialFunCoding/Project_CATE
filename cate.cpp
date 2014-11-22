#include <iostream>
#include <string>

using namespace std;

/* All possible cate commands:
     cate update
     cate set <class> <period>
     cate pull <id>
     cate mods
     cate ass [-a]
     cate --help
*/

// Valid cate commands
const string UPDATE = "update";
const string SET    = "set";
const string PULL   = "pull";
const string MODS   = "mods";
const string ASS    = "ass";
const string HELP   = "--help";

string validCommands[] = {UPDATE, SET, PULL, MODS, ASS, HELP};

//Function declarations
bool elem(string e, string elems[], int size);
void execCommand(int size, char *argv[]);
void runUpdate();
void runHelp();
void runMods();
bool isValidID(string id);
void runPull(string id);


int main(int argc, char *argv[]) {
    if (argc > 4) {
        cout << "Incorrect usage, see 'cate --help' for more information" << endl;
        return 1;
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
        
        
    } else if (string(argv[1]) == PULL) {
        if (size == 3 && isValidID(string(argv[2]))) {
          runPull(string(argv[2]));
        } else cout << "Correct usage: cate pull <id>" << endl;
        
    } else if (string(argv[1]) == MODS) {
        if (size == 2) runMods();
        else cout << "Correct usage: cate mods" << endl;
        
    } else if (string(argv[1]) == ASS) {
        
        
    } else if (string(argv[1]) == HELP) {
        if (size == 2) runHelp();
        else cout << "Correct usage: cate --help" << endl;
        
    } else cout << "Impossible!" << endl;
}

void runUpdate() {
    
}

void runHelp() {
    
}

void runMods() {
    
}

bool isValidID(string id) {
    return false;
}

void runPull(string id) {
    
}














