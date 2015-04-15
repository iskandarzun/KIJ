
#include <iostream>
#include "sha256.h"
 
using std::string;
using std::cout;
using std::cin;
using std::endl;
 
int main(int argc, char *argv[])
{
    string input;
    cin >> input;
    while(input != "0" )
    {
        //string input;
    //cin >> input;
    string output1 = sha256(input);
 
    cout << "sha256('"<< input << "'):" << output1 << endl;
    cin>>input;
    }
    return 0;
}
