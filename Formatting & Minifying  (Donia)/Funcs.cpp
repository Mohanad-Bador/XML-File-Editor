#include "Funcs.h"


vector <string> file_to_vector(string file_loc)
{
    vector<string> xml_file;

    ifstream oldfile;
    oldfile.open(file_loc, ios::in); //open a file to perform read operation using file object
    if (oldfile.is_open()) {   //checking whether the file is open
        string tp;
        while (getline(oldfile, tp)) {


               tp.erase(remove(tp.begin(), tp.end(), ' '), tp.end()); //remove space from string


            xml_file.push_back(tp);

        }
        oldfile.close();
        return xml_file;
    }
    else
    {
        cout << " Failed to open" << endl;
    }

}

string getOpenTag(string t)
{
    int start = -1;
    int end = -1;
    start = t.find("<", 0);
    end = t.find(">", start);
    if (start != -1 && t[start + 1] != '/' && t[start + 1] != '?' && t[start + 1] != '!')
        return t.substr(start + 1, end - start - 1);
    else
        return "FALSE";
}

string getClosedTag(string t)
{
    int start = -1;
    int end = -1;
    start = t.find("/", 0);
    end = t.find(">", start);
    if (start != -1)
        return t.substr(start + 1, end - start - 1);
    else
        return "FALSE";
}



