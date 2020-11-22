#include <iterator>
#include "dnaSequence.h"
#include <cmath>

bool isValidSequence(const std::string &sequence);

bool isValidSequence(char *sequence);

DnaSequence::DnaSequence(const std::string &sequence) {
    size_t i = 0;
    if (isValidSequence(sequence)) {
        m_dnaSequence = sequence;
        for (i = 0; i < m_dnaSequence.length(); i++)
            m_nucleotides.push_back(Nucleotide(m_dnaSequence[i]));
    } else throw "Sequence not valid.";
}

DnaSequence::DnaSequence(char *sequence) {
    if (sequence && isValidSequence(sequence)) {
        int i;
        m_dnaSequence = sequence;
        for (i = 0; i < m_dnaSequence.length(); i++)
            m_nucleotides.push_back(Nucleotide(m_dnaSequence[i]));
    } else throw "Sequence not valid.";
}

DnaSequence::DnaSequence(DnaSequence &otherDna) {
    m_dnaSequence = otherDna.m_dnaSequence;
    m_nucleotides = otherDna.m_nucleotides;
}

bool isValidSequence(char *const sequence) {
    char *run = sequence;
    while (*run && Nucleotide::isNucleotide(*run++));
    return *run == '\0';
}

bool isValidSequence(const std::string &sequence) {
    int i;
    for (i = 0; i < sequence.length() && Nucleotide::isNucleotide(sequence[i++]););
    return i >= sequence.length();
}

bool operator==(DnaSequence &sequence, const DnaSequence &other) {
    return sequence.getDnaSequence() == other.getDnaSequence();
}

bool operator==(DnaSequence &sequence, char *other) {
    return sequence.getDnaSequence() == other;
}

bool operator!=(DnaSequence &sequence, const DnaSequence &other) {
    return !(sequence.getDnaSequence() == other.getDnaSequence());
}

DnaSequence &DnaSequence::operator=(const DnaSequence &other) {
    m_dnaSequence = other.m_dnaSequence;
    m_nucleotides = other.m_nucleotides;
    return *this;
}

DnaSequence &DnaSequence::operator=(char *sequence) {
    m_dnaSequence = sequence;
    for (size_t i = 0; i < m_dnaSequence.length(); i++)
        m_nucleotides.push_back(Nucleotide(m_dnaSequence[i]));
    return *this;
}

DnaSequence &DnaSequence::operator=(const string &sequence) {
    m_dnaSequence = sequence;
    for (size_t i = 0; i < m_dnaSequence.length(); i++)
        m_nucleotides.push_back(Nucleotide(m_dnaSequence[i]));
    return *this;
}

ostream &operator<<(ostream &os, const DnaSequence &sequence) {
    os << "Dna Sequence: " << sequence.m_dnaSequence << endl;
    return os;
}

char DnaSequence::operator[](size_t index) {
    if (index < m_dnaSequence.length())
        return m_dnaSequence[index];
    return -1;
}

string DnaSequence::getDnaSequence() const {
    return m_dnaSequence;
}

string DnaSequence::sliceDna(int start, int end) {
    return m_dnaSequence.substr(start, end - start);
}

vector<Nucleotide> DnaSequence::getNucleotidesList() const {
    return m_nucleotides;
}

string getSequenceFromFile(string path) {
    ifstream file(path.c_str());
    if (file.is_open()) {
        string text;
        char c;
        while (file.get(c)) { text += c; }
        file.close();
        return text;
    }
    return "File does not exist.";
}

void writeSequenceToFile(const string& path, const DnaSequence &dnaSequence) {
    ofstream file(path.c_str());
    if (file.is_open()) {
        file << dnaSequence.getDnaSequence() << endl;
        file.close();
    } else throw "File does not exist.";
}

string showMePairingSequence(DnaSequence &dnaSequence) {
    string pairRes;
    for (int i = dnaSequence.getNucleotidesList().size() - 1; i >= 0; i--)
        pairRes += dnaSequence.getNucleotidesList().at(i).getPair();
    return pairRes;
}

int findSubSequence(string dnaSequence, string subSequence) {
    bool flag = false;
    int index = 0;
    if (subSequence.length() <= dnaSequence.length()) {
        int i;
        for (i = 0; i < dnaSequence.length(); i++) {
            if (dnaSequence[i] == subSequence[0]) {
                int j;
                for (j = 0; j < subSequence.length(); j++) {
                    if (dnaSequence[i + j] != subSequence[j])
                        break;
                }
                if (j == subSequence.length()) {
                    flag = true;
                    index = i;
                    break;
                }
            }
        }
        /*if (!flag)
            cout << subSequence << " is not a substring." << endl;
        else cout << "Found substring: " << subSequence << endl;*/
    }
    return flag ? index : -1;
}

int countOccurrences(const DnaSequence &dnaSequence, const string &subSequence) {
    int count = 0;
    if (subSequence.length() <= dnaSequence.getDnaSequence().length()) {
        int i = 0, index;
        do {
            if ((index = findSubSequence(dnaSequence.getDnaSequence().substr(i), subSequence)) != -1) {
                count++;
                i += subSequence.length() + index - 1;
            } else break;
            i++;
        } while (i < dnaSequence.getDnaSequence().length());
        cout << subSequence << " is found " << count << " times in " << dnaSequence.getDnaSequence() << endl;
    }
    return count;
}

vector<int> findAll(const DnaSequence &dnaSequence, const string &subSequence) {
    vector<int> indexesVec;
    int i = 0, index = 0;
    if (subSequence.length() <= dnaSequence.getDnaSequence().length()) {
        while ((index = findSubSequence(
                dnaSequence.getDnaSequence().substr(i),
                subSequence)) != -1) {
            indexesVec.push_back(index + i);
            i += index + subSequence.length();
        }
    }
    if (indexesVec.empty())
        indexesVec.push_back(-1);
    return indexesVec;
}

vector<string> findConsensusSequences(DnaSequence &dnaSequence)
{
    int i;
    string startCodon = "ATG";
    string endCodon1 = "TAG", endCodon2 = "TAA", endCodon3 = "TGA";
    vector<string> resultConsesus;
    vector<int> startCodonIndexes = findAll(dnaSequence, startCodon);
    for(i = 0; i < startCodonIndexes.size(); i++)
    {
        int nextIndex;
        if(i == startCodonIndexes.size() - 1)
            nextIndex = dnaSequence.getDnaSequence().length();
        else
            nextIndex = startCodonIndexes.at(i + 1);
        int currIndex = startCodonIndexes.at(i);
        if (findSubSequence(dnaSequence.sliceDna(currIndex + 3, nextIndex + 1), endCodon1) != -1)
            resultConsesus.push_back(dnaSequence.sliceDna(currIndex , nextIndex + 1));
        else if (findSubSequence(dnaSequence.sliceDna(currIndex + 3, nextIndex + 1), endCodon2) != -1)
            resultConsesus.push_back(dnaSequence.sliceDna(currIndex, nextIndex + 1));
        else if (findSubSequence(dnaSequence.sliceDna(currIndex + 3, nextIndex + 1), endCodon3) != -1)
            resultConsesus.push_back(dnaSequence.sliceDna(currIndex, nextIndex + 1));
    }

    return resultConsesus;
}