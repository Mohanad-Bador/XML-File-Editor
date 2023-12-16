#include "Formatting.h"


// int main()
// {
//     cout<<MINIFY("C:\\Users\\HP\\Downloads\\sample (1).xml")<<"\n";
//     cout<<"#########################\n";
//     cout<<FORMAT("C:\\Users\\HP\\Downloads\\sample (1).xml");
// }




string FORMAT (string path)
{
    stringstream ss;
    streambuf* coutbuf = std::cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    formatS(path);
    std::cout.rdbuf(coutbuf);
    return ss.str();
}


string MINIFY(string path)
{
    stringstream ss;
    streambuf* coutbuf = std::cout.rdbuf();
    cout.rdbuf(ss.rdbuf());
    minifyS(path);
    std::cout.rdbuf(coutbuf);
    return ss.str();

}

static void minifyS(string path)
{
    vector <string> donia;

    donia=file_to_vector(path);


    for(int i=0; i<donia.size(); i++)
    {
        cout<<donia[i];
    }
}






static void formatS(string path)
{
    vector <string> donia;

    donia=file_to_vector(path);

    /*
    for(int i=0;i<donia.size();i++){
        cout<<donia[i];
    }*/



    string line;
    int spaces=0;

    for(int i=0; i<donia.size(); i++)
    {
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



static vector <string> file_to_vector(string file_loc)
{
    vector<string> xml_file;

    ifstream oldfile;
    oldfile.open(file_loc, ios::in); //open a file to perform read operation using file object
    if (oldfile.is_open())     //checking whether the file is open
    {
        string tp;
        while (getline(oldfile, tp))
        {


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

static string getOpenTag(string t)
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

static string getClosedTag(string t)
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



