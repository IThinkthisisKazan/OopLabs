#include "htmldecodeFunctions.h"

using namespace std;

int main()
{
    std::string line;
    while (getline(std::cin, line))
    {
	    std::string decodedString = HtmlDecode(line);
	    std::cout << decodedString << endl;
    }
    return 0;
}