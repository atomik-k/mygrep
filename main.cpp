#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Options
{
public:
    bool lineNum = false;
    bool reverse = false;
    bool occurences = false;
    bool caseSens = true;
};

// Increment 1 tason haku ↓
int incr1()
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

// Increment 2 tason haku ↓
int incr2(string query, string fileName)
{
    ifstream file(fileName);
    if (!file)
    {
        // Tiedosto puuttuu tai virheellinen tiedosto
        cerr << "Error opening file" << endl;
        return 1;
    }
    bool match = false;

    string currLine;
    bool skip = false;
    while (getline(file, currLine))
    {
        for (int i = 0; i < currLine.length(); i++)
        {
            if (skip)
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
                    match = true;
                }
            }
        }
    }
    if (!match)
    {
        // Jos hakusanaa ei loytynyt
        cout << "No matches found for query '" << query << "' in the file '" << fileName << "'" << endl;
    }
    file.close();

    return 0;
}

// Main
int main(int argc, char const *argv[])
{
    if (argc <= 2)
    {
        // Increment 1 jos ei ole annettuja argumentteja
        return incr1();
    }

    if (argc <= 3)
    {
        // Increment 2 jos ei ole asetusargumenttia
        return incr2(argv[1], argv[2]);
    }

    ifstream file(argv[3]);
    if (!file)
    {
        // Tiedosto puuttuu tai virheellinen tiedosto
        cerr << "Error opening file" << endl;
        return 1;
    }
    string query = argv[2];

    // Asetukset ja niiden tarkastus
    Options ops;
    string opText = argv[1];
    if (opText[0] == '-' && opText[1] == 'o')
    {
        for (int i = 2; i < opText.length(); i++)
        {
            switch (opText[i])
            {
            case 'o':
                ops.occurences = true;
                break;
            case 'l':
                ops.lineNum = true;
                break;
            case 'r':
                ops.reverse = true;
                break;
            case 'i':
                ops.caseSens = false;
            }
        }
    }
    else
    {
        // Virheellinen asetussyöte
        cerr << "Bad arguments" << endl;
        return 1;
    }

    bool match = false;

    string currLine;
    bool skip = false;
    int line = 1, occur = 0;
    while (getline(file, currLine))
    {
        if (!ops.caseSens) // muuttaa hakusanan ja rivin samankokoisiksi
        {
            transform(currLine.begin(), currLine.end(), currLine.begin(), ::tolower);
            transform(query.begin(), query.end(), query.begin(), ::tolower);
        }
        line++;
        for (int i = 0; i < currLine.length(); i++)
        {
            if (i == currLine.length() - 1 && ops.reverse) // tulostaa reverse
            {
                if (ops.lineNum)
                {
                    cout << line << ":";
                }
                cout << "\t" << currLine << "\n";
            }
            if (skip)
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
                    if (ops.lineNum && !ops.reverse) // lineNum hakuehto
                        cout << line << ":";
                    if (ops.occurences) // occurrences hakuehto
                        occur++;
                    if (!ops.reverse)
                        cout << "\t" << currLine << "\n";
                    skip = true;
                    match = true;
                }
            }
        }
    }
    if (!match)
    {
        // Jos hakusanaa ei loytynyt
        cout << "No matches found for query '" << query << "'" << endl;
    }
    else if (ops.occurences && !ops.reverse)
    {
        // Jos hakusana loytyy norm jarjestyksessa
        cout << "Occurrences of line containing '" << query << "': " << occur << endl;
    }
    else if (ops.occurences && ops.reverse)
    {
        // Jos hakusana lotyy not jarjestyksessa
        cout << "Occurences of line NOT containing '" << query << "': " << line - occur << endl;
    }

    // Sulkee tiedoston
    file.close();

    return 0;
}
