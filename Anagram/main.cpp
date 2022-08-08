//
//  main.cpp
//  Anagram
//
//
#include <iostream>
#include <fstream>
#include <istream>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

// Functions for reading in dictionary
int loadWords(istream & dictfile, string dict[]);
int loadWords_aux(istream &dictfile, string dict[], int i);
int recBlends(string word,const string dict[], int size, string results[]);
// Functions for finding permutations
void  recBlends_aux(string a, int front, int end,const string dict[], int dict_total, int & matched, string results[]);
bool isInDictionary(const string dict[], int size, string word, int i);
void swapFunction(char & a, char & b);
bool isInDictionary(const string dict[], int size, string word, int i);
bool innerLoop(int i, int max, string b, string results[]);
void RecFor(string & a, int i, int front, int end,const string dict[], int dict_total, int & matched, string results[]);
void showResults(const string results[], int size);



int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = loadWords(dictfile, dict);

    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = recBlends(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        showResults(results, numMatches);
    
    
    
    string results3[5];
    string exampleDict[] = { "moe", "kool", "dee"};
    int numResults = recBlends("kloo", exampleDict, 3, results3); cout << numResults << endl;
    assert(numResults == 1 && results3[0] == "kool");
    cout << "woot" << endl;

    

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////             LOAD WORDS FROM FILE                   ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int loadWords(istream & dictfile, string dict[])
{
    string data;
    if (dictfile.eof())
    {
        return 0;
    }

    dictfile >> data;

    int counter = loadWords(dictfile, dict);
    if (counter < MAXDICTWORDS) {
        dict[counter] = data;
        counter++;
        return counter;
    }
    else
        return MAXDICTWORDS; //reached max capacity of array
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////          SWAP FUNCTION                    ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void swapFunction(char & input1, char & input2)
{
    char temp = input1;
    input1 = input2;
    input2 = temp;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////                    Find words in Dictionary                  ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isInDictionary(const string dict[], int size,string word, int i)
{
    if (size > i)
    {
        return false; // string not found
    }
    else
    {
        int centreSlice = (size + i) / 2;
        string check = dict[centreSlice];
        check[0] = tolower(check[0]); // makes all words lowecase
        if (word.compare(check) == 0) {
            return true;
        }
        else if (word.compare(check) > 0)
        {
            return isInDictionary( dict, size,word, centreSlice - 1);
        }
        else if (word.compare(check) < 0)
        {
            return isInDictionary( dict, centreSlice + 1,word, i);
        }
    }
return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////// Finds all the permutations of a word//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  recBlends_aux(string a, int front, int end,const string dict[],int dict_total, int & numResults, string results[])
{
if (front == end) // found a possible permutation
{
    if (isInDictionary(dict, 0,a,  dict_total)) // check if word exists
    {
            if (!(innerLoop(0, numResults, a, results))) // check if word is already in results
            {
                results[numResults] = a;
                numResults++;
            }
    }
}
else
{
    RecFor(a, front, front, end, dict, dict_total, numResults, results);
}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// BLENDING AND SLICING DONE HERE              ///////////////////////////////////////////////
////////This function will calculates permutations and collects all the remaining combinations then it swaps two
////characters and replacing the loop when it reaches max
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RecFor(string & a, int i, int front, int end,const string dict[], int dict_total, int & matched, string results[])
{
    if (i > end)
    {
        return;
    }
    swapFunction(a[front], a[i]);
    recBlends_aux(a, front + 1, end, dict, dict_total, matched, results);
    swapFunction(a[front], a[i]);
    RecFor(a, (i + 1), front, end, dict, dict_total, matched, results);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// BLENDING AND SLICING DONE HERE              ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int recBlends (string word,const string dict[], int size, string results[])
{
    int slice = word.size() - 1;
    int checker = 0;
    recBlends_aux(word, 0, slice, dict, size, checker, results);
    return checker;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////            Prints all the strings in results            //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void showResults(const string results[], int numMatches)
{
        if (numMatches - 1 < 0){
        return;
        }
        else{
        cout << "WORD MATCH FOUND =>  " << results[numMatches - 1]<< endl;
        showResults(results, numMatches - 1);
        }
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////          REC FOR FUNCTION                                     /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool innerLoop(int i, int max, string b, string results[])
{
    if (i == max)
        return false;
    if (b.compare(results[i]) == 0)
        return true;
    innerLoop(i + 1, max, b, results);
        return false;
}
