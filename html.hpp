#include "assigment.hpp"
#include "module.hpp"

class Html {
    
private:
    //Private fields here

    
public:
    
    //Implement the following member functions
    
    /* Since the IDs for specs and notes are different,
     * set the ID for specs with an 's' at the back,
     * eg. "345s"
     * and with an 'n' at the back of notes,
     * eg. "123n"
     */
    
    
    
    Html(std::string cl, std::string period, std::string user) {
        //Class constructor here
        
        // The constructor for the Assignment class is:
        // Assignment(string n_id, string n_name, bool n_counted, string n_dueDate, string n_link);
        // Note: the n_counted variable denotes if the assigment is green on cate
        // Note: string dueDate in the format: "23 May 2014"
        
        
        // The constructor for the Module class is:
        // Module(std::string n_modNumber, std::string n_name, Notes n_notes[], int n_numNotes);
        // Note: the arguments for the constructor include an array of notes
        // The constructor for the Notes module is:
        // Notes(n_id, n_name, n_link);
        
    }
    
    Assignment* getAssignments() {
        // Returns an array of Assignments
        
        return nullptr;
    }
    
    int assSize() {
        //Return the size of the assigments array
        
        return 0;
    }
    
    
    Module* getModules() {
        // Returns an array of Modules
                return nullptr;
    }
    
    int modSize() {
        //Return the size of the modules array
        return 0;
    }
    
    
    bool isValidClass(std::string cl) {
        //Returns true if the class input eg. "c1", "c2" exists on cate
        return false;
    }
    
    
    static bool isValidPeriod(std::string period) {
        //Returns true if the period input eg. "autumn", "spring" exists on cate
        return false;
    }
    
};