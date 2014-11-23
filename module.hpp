class Module {
    
public:
    Module(string n_modNumber, string n_name, Notes n_notes[]) {
        modNumber = n_modNumber;
        name = n_name;
        notes = n_notes;
    }
    
    string getModNumber() {
        return modNumber;
    }
    
    string getName() {
        return name;
    }
    
    Notes[] getNotes() {
        return notes;
    }
    
private:
    string modNumber;
    string name;
    Notes notes[];
};