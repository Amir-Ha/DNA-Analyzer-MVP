#ifndef DNA_NUCLEOTIDE_H
#define DNA_NUCLEOTIDE_H
#include <cstddef>

/*typedef enum
{
    Adenine = 'A',
    Guanine = 'G',
    Cytosine = 'C',
    Thymine = 'T'
}nucleotides;*/

class Nucleotide
{
private:
    char m_nucleotide;
    char m_pair;
    static const char m_nucleotides[];
public:
    Nucleotide(char nucleotide);
    static bool isNucleotide(const char& nucleotide);
    void pairMe(const char& nucleotide);
    char getPair();
};
#endif
