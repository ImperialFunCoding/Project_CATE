#include "notes.hpp"

class Module {
   
private:
    std::string modNumber;
    std::string name;
    Notes* notes;
    int numNotes;
    
public:
    Module(std::string n_modNumber, std::string n_name, Notes n_notes[], int n_numNotes) {
        modNumber = n_modNumber;
        name = n_name;
        notes = n_notes;
    }
    
    std::string getModNumber() {
        return modNumber;
    }
    
    std::string getName() {
        return name;
    }
    
    Notes* getNotes() {
        return notes;
    }
    
    int noteSize() {
        return numNotes;
    }
    
};