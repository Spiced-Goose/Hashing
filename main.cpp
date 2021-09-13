#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>



using namespace std;

struct arrayelement
{
    char protein[30];
    int count = 0;
};

arrayelement pHash[40];

arrayelement proteins[40];

char lookup[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
int g[26] = {20, 16, 12, 25, 26, 10, 12, 13, 5, 15, 28, 19, 14, 20, 10, 15, 3, 27, 7, 15, 11, 21, 8, 27, 18, 18};
//int g[26] = {14, 29, 30, 4, 21, 17, 19, 5, 14, 26, 0, 2, 24, 26, 11, 24, 3, 6, 2, 8, 18, 2, 0, 1, 5, 27};




int parseIndex(char x)
{
    for(int i = 0; i < 26; i++)
    {
        if(x == lookup[i])
        {
            return g[i];
        }
    }
    return 0;
}

void perfectHash(char value[80])
{

        int key = (parseIndex(value[0]) + parseIndex(value[1]) +
                   parseIndex(value[strlen(value - 1)]) + strlen(value)) % 40;
        key = abs(key);



        if(pHash[key].count == 0)
        {
            strcpy(pHash[key].protein, value);
            pHash[key].count++;
        }

        else if(strcmp(pHash[key].protein, value) == 0)
        {
            pHash[key].count++;
            return;
        }
        else
        {
            cout << "collision at " << pHash[key].protein << " and " << value << endl;
        }
}


void hashValue(char value[80])
{

    ///Hashed key = (first letter + 2 * last letter) % 40
    int key = (parseIndex(value[0]) + 2 * parseIndex(value[sizeof(value)/sizeof(*value) - 1])) % 40;


    if(proteins[key].count == 0)
    {
        strcpy(proteins[key].protein, value);
        proteins[key].count = 1;
        return;
    }

    while(proteins[key].count != 0)
    {
        if(strcmp(proteins[key].protein, value) == 0)
        {
            proteins[key].count++;
            return;
        }
        key++;
        if(key >= 40)
        {
            key = 0;
        }
    }

    strcpy(proteins[key].protein, value);
    proteins[key].count++;
}


int main()
{
    char buffer2[80];

    ifstream Hash("file3.txt");
    if(!Hash) {cerr << "Input file could not be opened\n"; exit(1);}

    while(Hash >> buffer2)
    {
        perfectHash(buffer2);
    }

    Hash.close();
}
