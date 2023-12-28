#include "consistency.h"
#include<sstream>


bool isFileConsistent(vector<string> xmlVectorFile , stack <string>& tagStack){
    
    string line;
    for (int i = 0; i < xmlVectorFile.size(); i++)
    {
        line = xmlVectorFile[i];
        string openTag = getOpenTag(line);
        string closedTag = getClosedTag(line);

        if (openTag != "False")
        {
            tagStack.push(openTag);    // valid open tag is pushed into stack
        }
        if (closedTag != "False")
        {
            if (tagStack.empty())     // closed tag with no opening tag
            {
                return false;
            }
            else 
            {
                if (closedTag == tagStack.top())
                {
                    tagStack.pop();         //Matching tags found
                }
                else
                {
                    return false;
                }           
            }  
        }
        else
        {
            return false;
        }
            
        }

    if (tagStack.empty())
        return true;
    else 
        return false;        // element in the stack with no closing tag
}
////////////////////////////////////////////////

bool error_detector(string openTag , string closedTag , stack <string>& tagStack , string& errorType){
    stack <string> temp;

    if (openTag != "False" && closedTag != "False")
    {
        if (openTag != closedTag)
        {
            errorType = "Mismatching tags: " + openTag + " and " + closedTag;
            return false;
        }    
    }
    if (openTag != "False")
    {
        tagStack.push(openTag);    // valid open tag is pushed into stack
    }
    if (closedTag != "False")
    {
        if (tagStack.empty())     // closed tag with no opening tag
        {
            errorType = "<" + closedTag + ">";
            return false; 
        }
        else{

            if (closedTag == tagStack.top())
            {
                tagStack.pop();
            }
            else
            {
                while (!tagStack.empty() && closedTag != tagStack.top())
                {
                    temp.push(tagStack.top());
                    tagStack.pop();              // stored the mismatched top of the tag stack to another stack  
                }
                if (tagStack.empty())
                {
                    errorType = "<" + closedTag + ">";    // closed tag with no open tag
                    while (!temp.empty())
                    {
                        tagStack.push(temp.top());        // resotring elements of temp into the original tag stack
                        temp.pop();
                    }
                    
                }
                else                                    // opening tag at the top of the stack with no closing tag
                {
                    tagStack.pop();
                    while (!temp.empty())
                    {
                        tagStack.push(temp.top());        // resotring elements of temp into the original tag stack
                        temp.pop();
                    }
                    errorType = "</" + tagStack.top() + ">";
                    tagStack.pop();     
                }
                return false;
            }  
        }
        return true; 
    }
    return true; 
}



////////////////////////////////////////////////

vector <err_data> detectError(vector<string> xmlVectorFile){
    vector<err_data> ErrorsVector;
    stack <string> tagStack;
    err_data errorData;
    string errorType;
    string line;
    int err_loc = -1;
    string openTag;
    string closedTag;



    for (int i = 0; i < xmlVectorFile.size(); i++)
    {
        line = xmlVectorFile[i];
        openTag = getOpenTag(line);          
        closedTag = getClosedTag(line);      

        if (openTag != "False" || closedTag != "False")
        {    
            if (!error_detector(openTag ,  closedTag , tagStack , errorType))
            {   
                if (errorType.size() > 24)           // 24 is the minimum number of characters for mismatchin tags error
                {
                    errorData.err_type = errorType; 
                    errorData.err_loc = i;
                    ErrorsVector.push_back(errorData);
                }
                else
                {
                    errorData.err_type = errorType;
                    errorData.err_loc = i;
                    ErrorsVector.push_back(errorData);
                } 
            }
        } 
    }

    int i = xmlVectorFile.size();
    while (!tagStack.empty())
    {   
        string err = "</" + tagStack.top() + ">";
        errorData.err_type = err;
        errorData.err_loc = i;
        ErrorsVector.push_back(errorData);
        i++;
        tagStack.pop();

    }

    return ErrorsVector;
}


vector <string> error_corrector(vector <string> xmlVectorFile, vector <err_data> error_vector)
{
    int counter = 0;
    vector <string> corrected_vector;
    for (int i = 0; i < xmlVectorFile.size(); i++)
    {
        if (i == error_vector[counter].err_loc)
        {
            if (error_vector[counter].err_type.size() > 24)                //not matching tags error
            {
                string temp_s = replace_str(xmlVectorFile[i], getClosedTag(xmlVectorFile[i]), getOpenTag(xmlVectorFile[i]));
                corrected_vector.push_back(temp_s);
            }
            else                          //normal error
            {
                corrected_vector.push_back(error_vector[counter].err_type);
                corrected_vector.push_back(xmlVectorFile[i]);
            }
            if (counter < error_vector.size() - 1)
                counter++;
        }
        else
            corrected_vector.push_back(xmlVectorFile[i]);
    }
    if (counter < error_vector.size() - 1)
    {
        for (int i = counter; i < error_vector.size(); i++)
        {
            corrected_vector.push_back(error_vector[i].err_type);
        }
    }
    return corrected_vector;
}

string printError (vector <err_data> error_vector) {
    stringstream ss;
    streambuf* coutbuf = std::cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    for (auto &i : error_vector) {
        if (i.err_type.size() > 25) {
            cout << "Error at line " << i.err_loc + 1 << ": " << i.err_type << endl;
        }
        else
            cout << "Error at line " << i.err_loc + 1 << ": Missing " << i.err_type << endl;
    }
    std::cout.rdbuf(coutbuf);
    return ss.str();
}

