#include "htmldecodeFunctions.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<pair<string, string>> HTML_ENTITIES = { {
                                                        {"\"", "&quot;"},
                                                        {"'", "&apos;"},
                                                        {"<", "&lt;"},
                                                        {">", "&gt;"},
                                                        {"&", "&amp;"}
													} };

string FindAndReplace(string& source, const string& searchString, const string& replacementString)
{
    string result = "";
    if (source.empty())
    {
        return result;
    }
    size_t pos = 0;
    size_t replacementPos = 0;
    while (replacementPos != string::npos)
    {
        replacementPos = source.find(replacementString, pos);
        if (replacementPos != string::npos)
        {
            result.append(source, pos, replacementPos - pos);
            pos = replacementPos + replacementString.size();
            result.append(searchString);
        }
        else
        {
        result.append(source, pos, source.size());
            break;
        } 
    }
    return result;
}

string HtmlDecode(const string& htmlCode)
{
    string decoded = htmlCode;
    for (auto & entity : HTML_ENTITIES)
    {
        decoded = FindAndReplace(decoded, entity.first, entity.second);
    }
    return decoded;
}