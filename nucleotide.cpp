#include "nucleotide.h"

char const Nucleotide:: m_nucleotides[] = {'A', 'G', 'C', 'T'};

Nucleotide:: Nucleotide(char nucleotide)
{
    if(isNucleotide(nucleotide))
    {
        m_nucleotide = nucleotide;
        pairMe(nucleotide);
    }
    else throw "Not a Nucleotide";
}

bool Nucleotide:: isNucleotide(const char& nucleotide)
{
    size_t i;
    for(i = 0; i < 4 && m_nucleotides[i] != nucleotide; i++);
    return i < 4;
}

void Nucleotide:: pairMe(const char& nucleotide)
{
    switch (nucleotide)
    {
        case 'A': m_pair = 'T';
            break;
        case 'C': m_pair = 'G';
            break;
        case 'T': m_pair = 'A';
            break;
        case 'G': m_pair = 'C';
            break;
    }
}

char Nucleotide::getPair() {
    return m_pair;
}
