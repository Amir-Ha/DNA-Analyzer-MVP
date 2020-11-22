#ifndef MVP_DATAANALYZER_INDEXED_DNA_SEQUENCE_H
#define MVP_DATAANALYZER_INDEXED_DNA_SEQUENCE_H

#include "dnaSequence.h"

class Indexed_DNA_Sequence : public DnaSequence
{
public:
    static vector<Indexed_DNA_Sequence*> dnaVector;

    Indexed_DNA_Sequence(const Indexed_DNA_Sequence& other);
    Indexed_DNA_Sequence(const string& sequence, const string& sequenceName);
    string getSequenceName() const { return m_sequenceName; }
    void printMe();
private:
    static int id;
    int m_seqID;
    string m_sequenceName;
};
#endif
