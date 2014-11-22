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

//Help section
const string helpSection = "Help Section";

// Valid cate commands
const string UPDATE = "update";
const string SET    = "set";
const string PULL   = "pull";
const string MODS   = "mods";
const string ASS    = "ass";
const string HELP   = "--help";

string validCommands[] = {UPDATE, SET, PULL, MODS, ASS, HELP};

// Function declarations

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

int main(int argc, char *argv[]) {
    if (argc > 4 || argc == 1) {
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
    //Temporary result
    cout << "Update" << endl;
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
    return (cl == "c1");
}

bool isValidPeriod(string period) {
    //Temporary value
    return (period == "autumn");
}

void runSet(string cl, string period) {
    //Temporary result
    cout << "Set" << endl;
}

void runCurrAss() {
    //Temporary result
    cout << "Listing current assigments" << endl;
}

void runAllAss() {
    //Temporary result
    cout << "Listing all assigments" << endl;
}














