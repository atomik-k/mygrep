#include <iostream>
#include <locale.h>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    string search, query;
    int matchPos = 0;
    bool match = false;

    cout << "Give a string to search: ";
    getline(cin, search);
    cin.clear();

    cout << "Give search string: ";
    getline(cin, query);

    for (int i = 0; i < search.length(); i++)
    {
        if (match == true)
            break;
        if (search[i] != query[0])
            continue;
        for (int j = 0; j < query.length(); j++)
        {
            if (query[j] != search[i + j])
                break;
            if (j == query.length() - 1)
            {
                match = true;
                matchPos = i;
            }
        }
    }

    if (match)
    {
        cout << "'" << query << "' found in '" << search << "' in position " << matchPos;
    }
    else
    {
        cout << "'" << query << "' NOT found in '" << search << "'";
    }

    return 0;
}
