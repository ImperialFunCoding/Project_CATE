class Assignment {
    
private:
    std::string id;
    std::string name;
    std::string dueDate;
    bool counted;
    std::string link;
    
public:
    Assignment(std::string n_id, std::string n_name, bool n_counted, std::string n_dueDate, std::string n_link) {
        id = n_id;
        name = n_name;
        counted = n_counted;
        dueDate = n_dueDate;
        link = n_link;
    }
    
    std::string getID() {
        return id;
    }
    
    std::string getName() {
        return name;
    }
    
    std::string getDueDate() {
        return dueDate;
    }
    
    std::string getLink() {
        return link;
    }
    
    bool isCounted() {
        return counted;
    }
    
};
    

