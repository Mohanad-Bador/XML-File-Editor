#include "Post.h"

Post::Post()
{
   this->body=" ";

}
string Post:: getBody()
{
    return body;
}
vector<string> Post::getTopics()
{
    return topics;
}
Post::~Post()
{

}