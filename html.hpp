#include "notes.hpp"
#include "assigment.hpp"
#include "module.hpp"

class Html {
    

    
public:
    
    //Implement the following member functions
    
    /* Since the IDs for specs and notes are different,
     * set the ID for specs with an 's' at the back,
     * eg. "345s"
     * and with an 'n' at the back of notes,
     * eg. "123n"
     */
    
    static Assignment* getAssignments(string cl, std::string period, std::string user) {
        // Returns an array of Assignments
        // The constructor for the Assignment class is:
        // Assignment(string n_id, string n_name, bool n_counted, string n_dueDate, string n_link);
        // Note: the n_counted variable denotes if the assigment is green on cate
        // Note: string dueDate in the format: "23 May 2014"
        return new Assignment[0];
    }
    
    
    static Module* getModules(std::string cl, std::string period, std::string user) {
        // Returns an array of Modules
        // The constructor for the Module class is:
        // Module(string n_modNumber, string n_name, Notes n_notes[]);
        // Note: the arguments for the constructor include an array of notes
        // The constructor for the Notes module is:
        // Notes(n_id, n_name, n_link);
        return new Module[0];
    }
    
    
    static bool isValidClass(std::string cl) {
        //Returns true if the class input eg. "c1", "c2" exists on cate
        return false;
    }
    
    
    static bool isValidPeriod(std::string period) {
        //Returns true if the period input eg. "autumn", "spring" exists on cate
        return false;
    }

private:
    
};