class Notes {
    
public:
    Notes(std::string n_id, std::string n_name, std::string n_link) {
        id = n_id;
        name = n_name;
        link = n_link;
    }
    
    std::string getID() {
        return id;
    }
    
    std::string getName() {
        return name;
    }
    
    std::string getLink() {
        return link;
    }

private:
    std::string id;
    std::string name;
    std::string link;
};