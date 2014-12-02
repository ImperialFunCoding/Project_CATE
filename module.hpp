#include "notes.hpp"
#include <vector>

class Module {
   
private:
    std::string modNumber;
    std::string name;
    vector<Notes> notes;
    int numNotes;
    
public:
    Module(std::string n_modNumber, std::string n_name, vector<Notes> n_notes, int n_numNotes) {
        modNumber = n_modNumber;
        name = n_name;
        notes = n_notes;
        numNotes = n_numNotes;
    }
    
    std::string getModNumber() {
        return modNumber;
    }
    
    std::string getName() {
        return name;
    }
    
    vector<Notes> getNotes() {
        return notes;
    }
    
    int noteSize() {
        return numNotes;
    }
    
};