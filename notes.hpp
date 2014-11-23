class Notes {
    
public:
    Notes(n_id, n_name, n_link) {
        id = n_id;
        name = n_name;
        link = n_link;
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

private:
    string id;
    string name;
    string link;
};