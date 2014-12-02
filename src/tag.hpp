#include <iostream>
#include <vector>
#include <string>

const string CATE_URL= "https://cate.doc.ic.ac.uk/";

//miscellaneous
string fileName(string url){
    string stringStack;
    for(int i=0; i < url.length(); i++){
        if(url[i]=='?'||url[i]=='#'){
            break;
        }
        stringStack += url[i];
    }
    return stringStack;
}
class Tag{
    /*
    string tag.name()
    int tag.attrSize()
    int tag.attrSize()
    string tag.attrKey(int n)
    string tag.attrValue(int n)
    */
private:
    vector<string> attrKeys(){
        vector<string> key;
        string stringStack="";
        bool ignore=false;
        for (int i=1; i<tag.length(); i++){
            if(tag[i]=='\"'){
            // using xor(^) to toogle true and false value
                ignore ^= true; 
            }
            if(ignore) continue;
            if (tag[i]==' ' || tag[i]=='>'
            || (tag[i]=='/' && tag[i+1]=='>')){
                stringStack="";
                continue;
            }
            if(tag[i]=='='){
                key.push_back(stringStack);
                stringStack="";
            }
            stringStack+=tag[i];
        }
        return key;
    }
    vector<string> attrValues(){
        vector<string> val;
        string stringStack="";
        bool ignore=false;
        for (int i=1; i<tag.length(); i++){
            if(tag[i]=='\"'){
            // using xor(^) to toogle true and false value
                ignore ^= true;
                continue;
            }
            if (tag[i]==' ' || tag[i]=='>'
            || (tag[i]=='/' && tag[i+1]=='>')){
                val.push_back(stringStack);
                stringStack="";
                continue;
            }
            stringStack+=tag[i];
            if(tag[i]=='=' && !ignore){
                stringStack="";
            }
        }
        val.erase(val.begin());
        return val;
    }
public:
    string tag;
    Tag(string t){
        tag = t;
    }
    string name(){
        string name;
        for (int i=1; i<tag.length(); i++){
            if (tag[i]==' ' || tag[i]=='>' || (tag[i]=='/' && tag[i+1]=='>')){
                break;
            }
            name+=tag[i];
        }
        return name;
    }
    int attrSize(){
        vector<string> attrs=this->attrKeys();
        return attrs.size();
    }
    int attrPos(string key){
        vector<string> keys=this->attrKeys();
        for(int i=0; i<keys.size();i++){
            if(keys[i]==key){
                return i;
            }
        }
        return -1;
    }
    string attrKey(int n){
        vector<string> keys=this->attrKeys();
        return keys[n];
    }
    string attrValue(int n){
        vector<string> vals=this->attrValues();
        return vals[n];
    }
    string findLink(string file){
        string url="";
        for (int i = 0; i < this->attrSize(); i++){
            if(fileName(this->attrValue(i))==file){
                url=CATE_URL+this->attrValue(i);
            }
        }
        return url;
    }
};
