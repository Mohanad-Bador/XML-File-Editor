#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <sstream>
#include <QString>
using namespace std;
//Prototypes of the Functions
static vector <string> file_to_vector(string file_loc);
static string getOpenTag(string t);
static string getClosedTag(string t);
static void formatS(string path);
QString minifyS(string path);
string FORMAT (string path);
string MINIFY(string path);
