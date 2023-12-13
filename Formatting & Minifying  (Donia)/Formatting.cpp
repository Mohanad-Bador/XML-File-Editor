#include <iostream>
#include <sstream>
using namespace std;
#include "Funcs.h"
void formatS();

int main(){


    stringstream ss;
    streambuf* coutbuf = std::cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    formatS();
    std::cout.rdbuf(coutbuf);
    cout<<ss.str();


}






void formatS(){
vector <string> donia;

donia=file_to_vector("C:\\Users\\HP\\Downloads\\sample (1).xml");

/*
for(int i=0;i<donia.size();i++){
    cout<<donia[i];
}*/



string line;
int spaces=0;

for(int i=0;i<donia.size();i++){
string opent,closedt;
line=donia[i];
opent=getOpenTag(line);
closedt=getClosedTag(line);

        if (closedt.compare("FALSE") && !opent.compare("FALSE"))
        {
            spaces--;
        }

        for (int i = 0; i < spaces; i++)
        {
            cout << "    ";
        }
        cout << line << "\n";

        if (closedt.compare("FALSE") && opent.compare("FALSE"))
        {
            spaces--;
        }

        if (opent.compare("FALSE"))
        {
            spaces++;
        }


}



}
