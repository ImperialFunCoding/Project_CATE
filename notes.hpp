#include <iostream>

using namespace std;

class Notes {
    
public:
    Notes(string n_id, string n_name, string n_link, string n_fileType) {
        id = n_id;
        name = n_name;
        link = n_link;
        fileType = n_fileType;
    }
    
    string getID() {
        return id;
    }
    
    string getName() {
        return name;
    }
    
    string getLink() {
        return link;
    }
    
    std::string getType() {
        return fileType;
    }

private:
    string id;
    string name;
    string link;
    string fileType;
};