#include <iostream>

using namespace std;

class Assignment {
    
private:
    string id;
    string name;
    string dueDate;
    string asstype;
    string link;
    string submitID;
    
public:
    Assignment(string n_id, string n_name, string n_asstype, string n_dueDate, string n_link, string n_submitID) {
        id = n_id;
        name = n_name;
        asstype = n_asstype;
        dueDate = n_dueDate;
        link = n_link;
        submitID = n_submitID;
    }
    
    string getID() {
        return id;
    }
    
    string getName() {
        return name;
    }
    
    string getDueDate() {
        return dueDate;
    }
    
    string getLink() {
        return link;
    }
    
    string assType() {
        return asstype;
    }
    
    string getSubmitID() {
        return submitID;
    }
    
};
    

