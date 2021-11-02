// Author: Tommy Liang
// Date: 10/11/2021
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

namespace
{

  //helper method
  string GetSeqFromLine(string &line)
  {
    size_t point = line.find('/');
    string result = line.substr(0, point);
    line = line.substr(point + 1, line.length());
    return result;
  }
  // @db_filename: an input filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  template <typename TreeType>
  void QueryTree(const string &db_filename, TreeType &a_tree)
  {
    ifstream input_file(db_filename);
    if (!input_file.good())
    {
      cerr << "File does not exist!" << endl;
      exit(1);
    }
    string db_line, an_enz_acro, a_reco_seq;
    //skips the first 10 lines (header lines)
    for (unsigned i = 0; i < 10; i++)
      getline(input_file, db_line);
    //reads the line
    while (getline(input_file, db_line))
    {
      if (db_line.empty())
        continue;
      //gets only the enzyme acronym
      an_enz_acro = GetSeqFromLine(db_line);
      //seperates the recognition sequences
      while (db_line.length() > 2)
      {
        a_reco_seq = GetSeqFromLine(db_line);
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
        a_tree.insert(new_sequence_map);
      }
    }
    input_file.close();

    //for the test cases given in input_part2a.txt
    int count = 0;
    vector<string> user_input;
    while (count < 3)
    {
      cin >> a_reco_seq;
      user_input.push_back(a_reco_seq);
      count++;
    }

    for (int i = 0; i < count; i++)
      a_tree.printEnzAcro(user_input[i]);
    // Code for running Part2(a)
    // Parse input file @db_filename and feel tree @a_tree
    // Then prompt the user for exactly three strings (do a loop) and
    // provide the results of find() as described in the assignment.
  }

} // namespace

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST")
  {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  }
  else if (param_tree == "AVL")
  {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  }
  else
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;

  return 0;
}
