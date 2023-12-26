#include "XMLParser.h"
#include<vector>
#include<stack>
#include "Functions.h"
#include "User.h"
#include "Post.h"
#include "Graph.h"


XMLParser::XMLParser()
{

}
vector<User *> XMLParser ::parseXML(string filepath)
{
    vector<string> xml_vector=file_to_vector(filepath);
    vector<User *> users;
    stack<User *> nstack;
    stack<User *> fstack;
    stack<Post *> pstack;

    for(int i=0;i<xml_vector.size();i++)
    {
        string opentag=getOpenTag(xml_vector[i]);
        string closedtag=getClosedTag(xml_vector[i]);
        if(closedtag=="False" && opentag != "False")
        {
            if(opentag =="user")
            {
                User * user =new User;
                nstack.push(user);
            }
            else if(opentag=="post")
            {
                Post * post =new Post;
                pstack.push(post);
            }
            else if(opentag=="follower")
            {
                User * user =new User;
                user->id=getTagValue(xml_vector[++i]);
                fstack.push(user);
            }
            else if(opentag=="body")
            {
                string body=xml_vector[i+1];
                pstack.top()->body=body;
            }
            else if(opentag =="topic")
            {
                string topic=xml_vector[i+1];
                pstack.top()->topics.push_back(topic);
            }

        }
        if(closedtag!="False" && opentag != "False")
        {
            if(opentag =="id")
            {
                nstack.top()->id=getTagValue(xml_vector[i]);
            }
            else if(opentag == "name")
            {
                 nstack.top()->name=getTagValue(xml_vector[i]);
            }
        }
        if(closedtag!="False" && opentag == "False")
        {
            if(closedtag=="user")
            {
                User * user=nstack.top();
                users.push_back(user);
                //graph.addUser(user);
                nstack.pop();
            }
             if(closedtag=="post")
            {
                Post * post=pstack.top();
                nstack.top()->posts.push_back(post);
                pstack.pop();
            }
            if(closedtag=="follower")
            {
                User * user=fstack.top();
                nstack.top()->addFollower(user);
                fstack.pop();
            }
        }
    }
    return users;


}
XMLParser::~XMLParser()
{

}
