
#ifndef DNA_DNASEQUENCE_H
#define DNA_DNASEQUENCE_H
#include "nucleotide.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class DnaSequence
{
private:
    string m_dnaSequence;
    vector<Nucleotide> m_nucleotides;
public:
    explicit DnaSequence(char *codons);
    explicit DnaSequence(const std::string& codons);
    DnaSequence(DnaSequence& otherDna);

    string getDnaSequence() const;
    vector<Nucleotide> getNucleotidesList() const;
    DnaSequence& operator= (const DnaSequence& other);
    DnaSequence& operator= (char *sequence);
    DnaSequence& operator= (const string& sequence);

    string sliceDna(int start, int end);
    char operator[](size_t index);
    friend ostream &operator<<(ostream &os, const DnaSequence &sequence);
};

bool operator==(DnaSequence &sequence, const DnaSequence &other);
bool operator!=(DnaSequence &sequence, const DnaSequence &other);
bool operator==(DnaSequence &sequence, char* other);

string getSequenceFromFile(string path);

void writeSequenceToFile(const string& path, const DnaSequence& dnaSequence);

string showMePairingSequence(DnaSequence &dnaSequence);

int findSubSequence(string dnaSequence, string subSequence);

int countOccurrences(const DnaSequence& dnaSequence, const string& subSequence);

vector<int> findAll(const DnaSequence& dnaSequence, const string& subSequence);

vector<string> findConsensusSequences(DnaSequence& dnaSequence);
#endif