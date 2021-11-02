// Author: Tommy Liang
// Date: 10/11/2021
// Main file for Part2(b) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

namespace
{
  //helper method to read sequences.txt or rebase210.txt
  string GetSeqFromLine(string &line)
  {
    size_t point = line.find('/');
    string result = line.substr(0, point);
    line = line.substr(point + 1, line.size() - point);
    return result;
  }
  // @db_filename: an input database filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  template <typename TreeType>
  void MakeTree(const string &db_filename, TreeType &a_tree)
  {
    ifstream input_file(db_filename);
    if (!input_file.good())
    {
      cerr << "File does not exist!" << endl;
      exit(1);
    }
    string db_line;
    //reads the line
    while (getline(input_file, db_line))
    {
      if (db_line[db_line.size() - 1] != '/')
        continue;
      //get only the enzyme acronym
      string an_enz_acro = GetSeqFromLine(db_line);
      //separates the recognition sequences
      while (db_line.length() > 2)
      {
        string a_reco_seq = GetSeqFromLine(db_line);
        SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
        a_tree.insert(new_sequence_map);
      }
    }
    input_file.close();
  }

  // @db_filename: an input database filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  // Testing for 4a
  // Counts the number of matching elements in db_filename to a_tree
  template <class TreeType>
  int SuccessfulQueries(const TreeType &a_tree, const string &db_filename)
  {
    ifstream input_file(db_filename);
    string sequence;
    int countOfSuccess = 0;
    int temp = 0;
    while (getline(input_file, sequence))
    {
      SequenceMap map(sequence, "");
      if (a_tree.contains(map, temp))
        countOfSuccess++;
    }
    input_file.close();
    return countOfSuccess;
  }

  // @db_filename: an input database filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  // Testing for 4b
  // Counts the number of recursions/steps for 4a
  template <class TreeType>
  int NumRecursions(const TreeType &a_tree, const string &db_filename)
  {
    ifstream input_file(db_filename);
    string sequence;
    int count = 0;
    while (getline(input_file, sequence))
    {
      SequenceMap map(sequence, "");
      a_tree.contains(map, count);
    }
    input_file.close();
    return count;
  }

  // @db_filename: an input database filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  // Testing for 5a and 5b
  // Counts the number of sucessful removes
  template <class TreeType>
  int SuccessfulRemoves(TreeType &a_tree, const string &db_filename)
  {
    ifstream input_file(db_filename);
    string sequence, junk;
    int count_delete = 0;
    int count_min = 0;
    int temp = 0;
    bool toggle = true;
    while (getline(input_file, sequence))
    {
      if (toggle)
      {
        toggle = false;
        SequenceMap map(sequence, "");
        if (a_tree.contains(map, temp))
          a_tree.remove(map, count_delete, count_min);
      }
      else
        toggle = true;
    }
    input_file.close();
    return count_delete + count_min;
  }

  // @db_filename: an input database filename.
  // @seq_filename: an input sequences filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  // Testing for all of part 2
  template <typename TreeType>
  void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree)
  {
    MakeTree(db_filename, a_tree);

    int num_Nodes = a_tree.numNodes();
    //2. Number of Nodes
    cout << "2: " << num_Nodes << endl;

    float avg_Depth = a_tree.avgDepth();
    //3a. Average Depth of tree
    cout << "3a: " << avg_Depth << endl;

    //3b. ratio of Average Depth of tree to Number of Nodes
    cout << "3b: " << avg_Depth / log2(num_Nodes) << endl;

    int num_Query = SuccessfulQueries(a_tree, seq_filename);
    //4a. Number of successful queries
    cout << "4a: " << num_Query << endl;

    //4b. Average recursion calls per query
    cout << "4b: " << (float)NumRecursions(a_tree, seq_filename) / num_Query << endl;

    int total_Remove = SuccessfulRemoves(a_tree, seq_filename);
    //5a. Number of successful removes
    //cout << total_Remove << endl;
    cout << "5a: " << num_Nodes - a_tree.numNodes() << endl;

    //5b. Average recursion calls per remove
    cout << "5b: " << (float)total_Remove / (num_Nodes - a_tree.numNodes()) << endl;

    //6a. Number of Nodes after remove
    cout << "6a: " << a_tree.numNodes() << endl;

    //6b. Average depth after remove
    cout
        << "6b: " << a_tree.avgDepth() << endl;

    //6c. Average depth ratio after remove
    cout << "6c: " << a_tree.avgDepth() / log2(a_tree.numNodes()) << endl;
  }
} // namespace

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST")
  {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  }
  else if (param_tree == "AVL")
  {
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  }
  else
  {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
