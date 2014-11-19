#include <iostream>
#include "base64.hpp"

using namespace std;

int main(){
    string input="any carnal pleasur";
    cout<<base64encode(input)<<endl;
}

