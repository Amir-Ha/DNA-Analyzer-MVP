#ifndef MVP_DATAANALYZER_ICOMMAND_H
#define MVP_DATAANALYZER_ICOMMAND_H

#include <sstream>
#include "map"
#include "indexed_dna_sequence.h"
#include <iterator>

using namespace std;

class iCommand {
public:
    virtual void runCommand(vector<string> commandMembers) = 0;
};

class newClass {
private:
    static int num;
public:
    void newOperation(vector<string> commandMembers);
};

class loadClass {
public:
    void loadOperation(vector<string> commandMembers);
};

class saveClass {
public:
    bool saveOperation(vector<string> commandMembers);
};

class dupClass {
private:
    static int num;
    static map<int, Indexed_DNA_Sequence *> dupMap;
public:
    bool dupOperation(vector<string> commandMembers);
};

class sliceClass {
private:
    static int num;
public:
    void sliceOperation(vector<string> commandMembers);
};

class replaceClass {
private:
    static int num;
public:
    void replaceOperation(vector<string> commandMembers);
};

class concatClass {
private:
    static int num;
public:
    void concatOperation(vector<string> commandMembers);
};

class pairClass {
private:
    static int num;
public:
    void pairOperation(vector<string> commandMembers);
};

class lenClass {
public:
    void lenOperation(vector<string> commandMembers);
};

class atIndexClass {
public:
    void atIndexOperation(vector<string> commandMembers);
};

class newCommand : public iCommand {
private:
    newClass *mNew;

public:
    newCommand(newClass *newClass) : mNew(newClass) {}

    void runCommand(vector<string> commandMembers) {
        if (commandMembers.size() < 2)
            commandMembers.push_back("Seq");
        mNew->newOperation(commandMembers);
    }
};

class loadCommand : public iCommand {
private:
    loadClass *mLoad;

public:
    loadCommand(loadClass *loadClass) : mLoad(loadClass) {}

    void runCommand(vector<string> commandMembers) {
        if (commandMembers.size() < 2)
            commandMembers.push_back("");
        mLoad->loadOperation(commandMembers);
    }
};

class saveCommand : public iCommand {
private:
    saveClass *mSave;

public:
    saveCommand(saveClass *saveClass) : mSave(saveClass) {}

    void runCommand(vector<string> commandMembers) {
        if (commandMembers.empty()) {
            cout << "wrong syntax, fix: save <seq> [<filename>]" << endl;
            return;
        }
        if (commandMembers.size() < 2)
            commandMembers.push_back("");

        int seqID;
        istringstream(commandMembers.at(0)) >> seqID;
        if (seqID - 1 < Indexed_DNA_Sequence::dnaVector.size())
            mSave->saveOperation(commandMembers);
        else cout << "Sequence doesn't exist, fix: enter a valid index" << endl;
    }
};

class dupCommand : public iCommand {
private:
    dupClass *mDup;

public:
    dupCommand(dupClass *dupClass) : mDup(dupClass) {}

    void runCommand(vector<string> commandMembers) {
        if (commandMembers.at(0)[0] == '#') {
            commandMembers.at(0).erase(0, 1);
            int seqID;
            istringstream(commandMembers.at(0)) >> seqID;
            if (seqID - 1 < Indexed_DNA_Sequence::dnaVector.size()) {
                if (commandMembers.size() < 2)
                    commandMembers.push_back("conseq");
                mDup->dupOperation(commandMembers);
            } else cout << "Sequence doesn't exist, fix: enter a valid index" << endl;
        } else cout << "wrong syntax, fix: dup #<num> (optional: name)" << endl;
    }
};

class sliceCommand : public iCommand {
private:
    sliceClass *mSlice;

public:
    sliceCommand(sliceClass *sliceClass) : mSlice(sliceClass) {}

    void runCommand(vector<string> commandMembers) {
        if (commandMembers.size() >= 3) {
            int seqID;
            istringstream(commandMembers.at(0)) >> seqID;
            if (seqID - 1 < Indexed_DNA_Sequence::dnaVector.size()) {
                mSlice->sliceOperation(commandMembers);
            } else cout << "Sequence id doesn't exist, try again" << endl;
        } else cout << "wrong syntax, fix: slice <seqNum>[or seqName] from_ind to_ind [: @[newname or @]]" << endl;
    }
};

class replaceCommand : public iCommand {
private:
    replaceClass *mReplace;

public:
    replaceCommand(replaceClass *replaceClass) : mReplace(replaceClass) {}

    void runCommand(vector<string> commandMembers) {
        if (commandMembers.size() >= 3) {
            int seqID;
            istringstream(commandMembers.at(0)) >> seqID;
            if (seqID - 1 < Indexed_DNA_Sequence::dnaVector.size())
                mReplace->replaceOperation(commandMembers);
            else cout << "Sequence id doesn't exist, try again" << endl;
        } else cout << "wrong syntax, fix: replace <seq> <index> <new_letter> [: [@<new_seq_name>|@@]]" << endl;
    }
};

class concatCommand : public iCommand {
private:
    concatClass *mConcat;

public:
    concatCommand(concatClass *concatClass) : mConcat(concatClass) {}

    void runCommand(vector<string> commandMembers) {
        if (commandMembers.size() > 1) {
            int seqID1, seqID2;
            istringstream(commandMembers.at(0)) >> seqID1;
            istringstream(commandMembers.at(1)) >> seqID2;
            if (seqID1 - 1 < Indexed_DNA_Sequence::dnaVector.size() &&
                seqID2 - 1 < Indexed_DNA_Sequence::dnaVector.size())
                mConcat->concatOperation(commandMembers);
            else cout << "Sequence id doesn't exist, try again" << endl;
        } else cout << "wrong syntax, fix: pair <seqNum> [: [@<new_seq_name>|@@]]" << endl;
    }
};

class pairCommand : public iCommand {
private:
    pairClass *mPair;

public:
    pairCommand(pairClass *pairClass) : mPair(pairClass) {}

    void runCommand(vector<string> commandMembers) {
        if (!commandMembers.empty()) {
            int seqID;
            istringstream(commandMembers.at(0)) >> seqID;
            if (seqID - 1 < Indexed_DNA_Sequence::dnaVector.size())
                mPair->pairOperation(commandMembers);
            else cout << "Sequence id doesn't exist, try again" << endl;
        } else cout << "wrong syntax, fix: pair <seqNum> [: [@<new_seq_name>|@@]]" << endl;
    }
};

class lenCommand : public iCommand {
private:
    lenClass *mLen;

public:
    lenCommand(lenClass *lenClass) : mLen(lenClass) {}

    void runCommand(vector<string> commandMembers) {
        if (commandMembers.size() == 1) {
            if (commandMembers.at(0)[0] == '#') {
                int seqID;
                commandMembers.at(0).erase(0, 1);
                istringstream(commandMembers.at(0)) >> seqID;
                if (seqID - 1 < Indexed_DNA_Sequence::dnaVector.size())
                    mLen->lenOperation(commandMembers);
                else cout << "Sequence doesn't exist, fix: enter a valid index" << endl;
            }

        } else cout << "wrong syntax, fix: len <seqNum>[or ##]" << endl;
    }
};

#endif