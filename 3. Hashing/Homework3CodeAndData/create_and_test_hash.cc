// Tommy Liang
// create_and_test_hash.cc: Creates the dictionary that we will check from for hw 3 and also complete part 1 of the homework.

#include <fstream>
#include <iostream>
#include <string>
#include "linear_probing.h"
#include "quadratic_probing.h"
#include "double_hashing.h"

using namespace std;

// You can add more functions here

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
                              const string &words_filename,
                              const string &query_filename)
{
    hash_table.MakeEmpty();
    // Part A
    fstream words_input_file_;
    words_input_file_.open(words_filename);

    if (words_input_file_.fail())
    {
        cerr << "File Not Found\n";
        exit(1);
    }
    string reader_words;
    while (getline(words_input_file_, reader_words))
    {
        hash_table.Insert(reader_words);
    }
    words_input_file_.close();
    // Output implementation for Part A
    int numElements = hash_table.getNumElements();
    int tableSize = hash_table.getTableSize();
    int numCollisions = hash_table.getNumCollisions();
    cout << "number_of_elements: " << numElements << endl;
    cout << "size_of_table: " << tableSize << endl;
    cout << "load_factor: " << (float)numElements / tableSize << endl;
    cout << "average_collisions: " << (float)numCollisions / numElements << endl;
    cout << "total_collisions: " << numCollisions << endl;
    cout << endl;

    // Part B
    fstream query_input_file_;
    query_input_file_.open(query_filename);

    if (query_input_file_.fail())
    {
        cerr << "File Not Found\n";
        exit(1);
    }
    string reader_query;
    // Output implementation for Part B
    while (getline(query_input_file_, reader_query))
    {
        hash_table.setCollisions(0);
        if (hash_table.Contains(reader_query))
            cout << reader_query << " Found " << hash_table.getNumCollisions() + 1 << endl;
        else
            cout << reader_query << " Not_Found " << hash_table.getNumCollisions() + 1 << endl;
    }
    query_input_file_.close();
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;
    if (argument_count == 5)
    {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear")
    {
        // Uncomment below when you have implemented linear probing.
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "quadratic")
    {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename,
                                 query_filename);
    }
    else if (param_flag == "double")
    {
        cout << "r_value: " << R << endl;
        // Uncomment below when you have implemented double hashing.
        HashTableDouble<string> double_probing_table;
        double_probing_table.setR(R);
        TestFunctionForHashTable(double_probing_table, words_filename,
                                 query_filename);
    }
    else
    {
        cout << "Unknown tree type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 4 and argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
