class Assignment {
    
public:
    Assignment(string n_id, string n_name, bool n_counted, string n_dueDate, string n_link) {
        id = n_id;
        name = n_name;
        counted = n_counted;
        dueDate = n_dueDate;
        link = n_link;
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
    
    bool isCounted {
        return counted;
    }
    
private:
    string id;
    string name;
    string dueDate;
    bool counted;
    string link;
};