// Author: Tommy Liang
// Date: 10/11/2021
// Main file for Part1 of Homework 2.
// Constrution of the sequennce_map.h big 5, operators, and Merge function

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SequenceMap
{
public:
    //THE BIG FIVE

    //copy-constructor
    SequenceMap(const SequenceMap &rhs) = default;

    //move-constructor
    SequenceMap(SequenceMap &&rhs) = default;

    //copy-assignment
    SequenceMap &operator=(const SequenceMap &rhs) = default;

    //move-assignment
    SequenceMap &operator=(SequenceMap &&rhs) = default;

    //destructor
    ~SequenceMap() = default;

    //END OF THE BIG FIVE

    //Two parameter constructor
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro)
    {
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    //String comparison operator
    bool operator<(const SequenceMap &rhs) const
    {
        return recognition_sequence_ < rhs.recognition_sequence_;
    }

    //Overload operator <<
    friend ostream &operator<<(ostream &out, const SequenceMap &anotherMap)
    {
        for (unsigned i = 0; i < anotherMap.enzyme_acronyms_.size(); i++)
            out << anotherMap.enzyme_acronyms_[i] << " ";
        return out;
    }

    //Merges the enzyme_acronym_ strings together
    void Merge(const SequenceMap &other_sequence)
    {
        if (recognition_sequence_ == other_sequence.recognition_sequence_)
            for (unsigned i = 0; i < other_sequence.enzyme_acronyms_.size(); i++)
                enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
    }

    //print enzyme_acronyms_ function
    void printEnzymeAcronyms()
    {
        for (unsigned i = 0; i < enzyme_acronyms_.size(); i++)
            cout << enzyme_acronyms_[i] << " ";
        cout << endl;
    }

    //recognition sequence getter function
    string getRecognitionSeq()
    {
        return recognition_sequence_;
    }

private:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;
};