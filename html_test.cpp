#include <iostream>
#include "htmlpre.hpp"
#include <vector>

using namespace std;

int main(){
    vector<string> ss;
    ss=get_tags("");
    ss[0]="13";
    cout<<ss[0]<<endl;
    return 0;
}
