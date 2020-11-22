#include "indexed_dna_sequence.h"

int Indexed_DNA_Sequence::id = 1;
vector<Indexed_DNA_Sequence*> Indexed_DNA_Sequence::dnaVector;

Indexed_DNA_Sequence::Indexed_DNA_Sequence(const string& sequence, const string& sequenceName) : DnaSequence(sequence)
{
    m_seqID = id;
    id++;
    m_sequenceName = sequenceName;
}

Indexed_DNA_Sequence:: Indexed_DNA_Sequence(const Indexed_DNA_Sequence& other) : DnaSequence(other.getDnaSequence()){
    m_seqID = other.m_seqID;
    m_sequenceName = other.m_sequenceName;
}

void Indexed_DNA_Sequence::printMe()
{
    cout << "[" << m_seqID << "] " <<  getDnaSequence() << " " << m_sequenceName << endl;
}