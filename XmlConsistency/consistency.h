#ifndef CONSISTENCY_H
#define CONSISTENCY_H
#include"../Graph/Functions.h"

struct err_data
{
    string err_type;
    int err_loc;
};

bool isFileConsistent(vector<string> xmlVectorFile , stack <string>& tagStack);

bool error_detector(string openTag , string closedTag , stack <string>& tagStack , string& errorType);

vector <err_data> detectError(vector<string> xmlVectorFile);

vector <string> error_corrector(vector <string> xmlVectorFile, vector <err_data> error_vector);

string printError (vector <err_data> error_vector);


#endif