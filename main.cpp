#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void incr1()
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
}

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        incr1();
    }

    ifstream file(argv[2]);
    if (!file)
    {
        cerr << "Error opening file" << endl;
        return 1;
    }
    string query = argv[1];

    string currLine;
    bool skip = false;
    while (getline(file, currLine))
    {
        for (int i = 0; i < currLine.length(); i++)
        {
            if(skip)
            {
                skip = false;
                break;
            }
            if (currLine[i] != query[0])
            {
                continue;
            }
            for (int j = 0; j < query.length(); j++)
            {
                if (query[j] != currLine[i + j])
                {
                    break;
                }
                if (j == query.length() - 1)
                {
                    cout << "\t" << currLine << "\n";
                    skip = true;
                }
            }
        }
    }

    file.close();

    return 0;
}
