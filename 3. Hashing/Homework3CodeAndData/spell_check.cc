// Tommy Liang
// spell_check.cc: A simple spell checker.
// spell_check.cc: Reads a sample text file and a dictionary file and compares
// to see if the words from the sample text file matches with the dictionary file.
// This file also has the implementation that accounts for 3 certian scenarios of spell checking.

#include <fstream>
#include <iostream>
#include <string>

// You can change to quadratic probing if you
// haven't implemented double hashing.
#include "linear_probing.h"
#include "quadratic_probing.h"
#include "double_hashing.h"
using namespace std;

// You can add more functions here.

// Creates and fills double hashing hash table with all words from
// dictionary_file
HashTableDouble<string> MakeDictionary(const string &dictionary_file)
{
  HashTableDouble<string> dictionary_hash;
  fstream input_file;
  input_file.open(dictionary_file);

  if (input_file.fail())
  {
    cerr << "File Not Found!\n";
    exit(1);
  }

  string reader;
  while (getline(input_file, reader))
  {
    // cout << "Inserting " << reader << endl;
    dictionary_hash.Insert(reader);
  }
  input_file.close();
  return dictionary_hash;
}

// For each word in the document_file, it checks the 3 cases for a word being
// misspelled and prints out possible corrections
void SpellChecker(const HashTableDouble<string> &dictionary,
                  const string &document_file)
{
  fstream input_file;
  input_file.open(document_file);

  if (input_file.fail())
  {
    cerr << "File Not Found!\n";
    exit(1);
  }

  string reader;
  while (input_file >> reader)
  {
    // chaging the input to lowercase letters
    for (size_t i = 0; i < reader.length(); i++)
      reader[i] = tolower(reader[i]);
    size_t index = reader.length() - 1;
    // parser for non-letters and non-digits
    while (reader[index] < 'a' || reader[index] > 'z')
    {
      // break if we encounter an integer
      if (reader[index] >= '0' && reader[index] <= '9')
        break;
      reader = reader.substr(0, index);
      index--;
    }

    if (dictionary.Contains(reader))
      cout << reader << " is CORRECT" << endl;
    else
    {
      cout << reader << " is INCORRECT" << endl;
      // CASE A: missing one letter
      for (size_t i = 0; i <= reader.length(); i++)
      {
        for (int j = 'a'; j <= 'z'; j++)
        {
          string word = reader;
          string temp(1, (char)j);
          word.insert(i, temp);
          if (dictionary.Contains(word))
            cout << "*** " << reader << " -> " << word << " *** case A" << endl;
        }
      }

      // CASE B: one extra letter
      for (size_t i = 0; i < reader.length(); i++)
      {
        string word = reader;
        word.erase(i, 1);
        if (dictionary.Contains(word))
          cout << "*** " << reader << " -> " << word << " *** case B" << endl;
      }
      // CASE C: swapping adjacent characters
      for (size_t i = 0; i < reader.length() - 1; i++)
      {
        string word = reader;
        char temp = word[i];
        word[i] = word[i + 1];
        word[i + 1] = temp;
        if (dictionary.Contains(word))
          cout << "*** " << reader << " -> " << word << " *** case C" << endl;
      }
    }
  }
  input_file.close();
}

// @argument_count: same as argc in main
// @argument_list: save as argv in main.
// Implements
int testSpellingWrapper(int argument_count, char **argument_list)
{
  const string document_filename(argument_list[1]);
  const string dictionary_filename(argument_list[2]);

  // Call functions implementing the assignment requirements.
  HashTableDouble<string> dictionary = MakeDictionary(dictionary_filename);
  SpellChecker(dictionary, document_filename);

  return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }

  testSpellingWrapper(argc, argv);

  return 0;
}