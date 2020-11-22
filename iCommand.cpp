#include "iCommand.h"
#include "indexed_dna_sequence.h"
#include "lastReference.h"

int newClass::num = 1;
int dupClass::num = 1;
map<int, Indexed_DNA_Sequence *> dupClass::dupMap;
int sliceClass::num = 1;
int concatClass::num = 1;
int pairClass::num = 1;

void newClass::newOperation(vector<string> commandMembers) {
    ostringstream oss;
    oss << commandMembers.at(1); // name
    if (commandMembers.at(1) == "Seq") {
        oss << num;
        num++;
    }
    Indexed_DNA_Sequence *indexedDnaSequence = new Indexed_DNA_Sequence(commandMembers.at(0), oss.str());
    Indexed_DNA_Sequence::dnaVector.push_back(indexedDnaSequence);
    indexedDnaSequence->printMe();
}

void loadClass::loadOperation(vector<string> commandMembers) {
    string loadSequence = getSequenceFromFile(commandMembers.at(0));
    string seqName = commandMembers.at(1);
    if (seqName.empty())
        seqName = commandMembers.at(0);
    Indexed_DNA_Sequence *indexedDnaSequence = new Indexed_DNA_Sequence(loadSequence, seqName);
    Indexed_DNA_Sequence::dnaVector.push_back(indexedDnaSequence);
    indexedDnaSequence->printMe();
}

bool saveClass::saveOperation(vector<string> commandMembers) {
    int seqID;
    istringstream(commandMembers.at(0)) >> seqID;
    string fName;
    if (commandMembers.at(1).empty())
        fName = Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->getSequenceName() + ".rawdna";
    else fName = commandMembers.at(1);
    writeSequenceToFile(fName, *Indexed_DNA_Sequence::dnaVector.at(seqID - 1));
    return true;
}

bool dupClass::dupOperation(vector<string> commandMembers) {
    int seqID;
    ostringstream oss;
    istringstream(commandMembers.at(0)) >> seqID;
    if (commandMembers.at(1) == "conseq") {
        oss << commandMembers.at(1) << "_" << dupClass::num;
        ++dupClass::num;
    } else oss << commandMembers.at(1);
    Indexed_DNA_Sequence *indexedDnaSequence = new Indexed_DNA_Sequence
            (Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->getDnaSequence(), oss.str());
    //insert the duplicated to the duplicate map
    dupClass::dupMap.insert(pair<int, Indexed_DNA_Sequence *>(seqID, indexedDnaSequence));
    Indexed_DNA_Sequence::dnaVector.push_back(indexedDnaSequence);
    indexedDnaSequence->printMe();
    return true;
}

void lenClass::lenOperation(vector<string> commandMembers) {
    int seqID;
    istringstream(commandMembers.at(0)) >> seqID;
    cout << Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->getDnaSequence().size() << endl;
    LastReference::lastCalcRes = Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->getDnaSequence().size();
}

void sliceClass::sliceOperation(vector<string> commandMembers) {
    int seqID, from_ind, to_ind;
    ostringstream oss;
    istringstream(commandMembers.at(0)) >> seqID;
    istringstream(commandMembers.at(1)) >> from_ind;
    istringstream(commandMembers.at(2)) >> to_ind;

    string sliced = Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->sliceDna(from_ind, to_ind);
    oss << Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->getSequenceName();
    if (commandMembers.size() == 3) {
        Indexed_DNA_Sequence::dnaVector.at(seqID - 1) = new Indexed_DNA_Sequence(sliced, oss.str());
        Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->printMe();
    } else if (commandMembers.size() == 5) {
        if (commandMembers.at(3) == ":") {
            if (commandMembers.at(4)[0] == '@') {
                commandMembers.at(4).erase(0, 1);
                if (commandMembers.at(4)[0] == '@') {
                    oss << "_s" << sliceClass::num;
                    ++sliceClass::num;
                } else {
                    oss.str("");
                    oss << commandMembers.at(4);
                }
                Indexed_DNA_Sequence *indexedDnaSequence = new Indexed_DNA_Sequence(sliced, oss.str());
                Indexed_DNA_Sequence::dnaVector.push_back(indexedDnaSequence);
                indexedDnaSequence->printMe();
            }
        } else cout << "Syntax error: slice <seqNum>[or seqName] from_ind to_ind [: @[newname or @]]" << endl;
    }

}

void replaceClass::replaceOperation(vector<string> commandMembers) {
    int seqID, index;
    ostringstream oss;
    istringstream(commandMembers.at(0)) >> seqID;
    istringstream(commandMembers.at(1)) >> index;
    string replaceDNA = Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->getDnaSequence();
    replaceDNA.replace(index, 1, commandMembers.at(2));
    if (commandMembers.size() == 3) {
        Indexed_DNA_Sequence::dnaVector.at(seqID - 1) = new Indexed_DNA_Sequence(replaceDNA,
                                                                                 Indexed_DNA_Sequence::dnaVector.at(
                                                                                         seqID - 1)->getSequenceName());
        Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->printMe();
    }
    /*else if(commandMembers.size() == 5){
        if (commandMembers.at(3) == ":") {
            if (commandMembers.at(4)[0] == '@') {
                commandMembers.at(4).erase(0, 1);
                if (commandMembers.at(4)[0] == '@') {
                    oss << "_p" << replaceClass::num;
                    ++replaceClass::num;
                } else {
                    oss.str("");
                    oss << commandMembers.at(2);
                }
                Indexed_DNA_Sequence *indexedDnaSequence = new Indexed_DNA_Sequence(paired, oss.str());
                Indexed_DNA_Sequence::dnaVector.push_back(indexedDnaSequence);
                indexedDnaSequence->printMe();
            }
        } else cout << "Syntax error: pair <seqNum> [: [@<new_seq_name>|@@]]" << endl;
    }*/
}

void concatClass::concatOperation(vector<string> commandMembers) {
    int seqID1, seqID2;
    ostringstream oss;
    istringstream(commandMembers.at(0)) >> seqID1;
    istringstream(commandMembers.at(1)) >> seqID2;
    string concatDNA = Indexed_DNA_Sequence::dnaVector.at(seqID1 - 1)->getDnaSequence() +
                       Indexed_DNA_Sequence::dnaVector.at(seqID2 - 1)->getDnaSequence();
    if (commandMembers.size() > 2) {
        if (commandMembers.at(2) == ":") {
            if (commandMembers.at(3)[0] == '@') {
                commandMembers.at(3).erase(0, 1);
                if (commandMembers.at(3)[0] == '@') {
                    oss << Indexed_DNA_Sequence::dnaVector.at(seqID1 - 1)->getSequenceName() <<
                        "_" << Indexed_DNA_Sequence::dnaVector.at(seqID2 - 1)->getDnaSequence();
                    oss << "_c" << concatClass::num;
                    ++concatClass::num;
                } else {
                    oss.str("");
                    oss << commandMembers.at(3);
                }
                Indexed_DNA_Sequence *indexedDnaSequence = new Indexed_DNA_Sequence(concatDNA, oss.str());
                Indexed_DNA_Sequence::dnaVector.push_back(indexedDnaSequence);
                indexedDnaSequence->printMe();
            }
        } else cout << "Syntax error: pair <seqNum> [: [@<new_seq_name>|@@]]" << endl;
    } else {
        Indexed_DNA_Sequence::dnaVector.at(seqID1 - 1) = new Indexed_DNA_Sequence(concatDNA,
                                                                                  Indexed_DNA_Sequence::dnaVector.at(
                                                                                          seqID1 -
                                                                                          1)->getSequenceName());
        Indexed_DNA_Sequence::dnaVector.at(seqID1 - 1)->printMe();
    }

}


void pairClass::pairOperation(vector<string> commandMembers) {
    int seqID;
    ostringstream oss;
    istringstream(commandMembers.at(0)) >> seqID;
    string paired = showMePairingSequence(
            reinterpret_cast<DnaSequence &>(*Indexed_DNA_Sequence::dnaVector.at(seqID - 1)));
    oss << Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->getSequenceName();
    if (commandMembers.size() == 1) {
        Indexed_DNA_Sequence::dnaVector.at(seqID - 1) = new Indexed_DNA_Sequence(paired, oss.str());
        Indexed_DNA_Sequence::dnaVector.at(seqID - 1)->printMe();
    } else if (commandMembers.size() == 3) {
        if (commandMembers.at(1) == ":") {
            if (commandMembers.at(2)[0] == '@') {
                commandMembers.at(2).erase(0, 1);
                if (commandMembers.at(2)[0] == '@') {
                    oss << "_p" << pairClass::num;
                    ++pairClass::num;
                } else {
                    oss.str("");
                    oss << commandMembers.at(2);
                }
                Indexed_DNA_Sequence *indexedDnaSequence = new Indexed_DNA_Sequence(paired, oss.str());
                Indexed_DNA_Sequence::dnaVector.push_back(indexedDnaSequence);
                indexedDnaSequence->printMe();
            }
        } else cout << "Syntax error: pair <seqNum> [: [@<new_seq_name>|@@]]" << endl;
    }
}
