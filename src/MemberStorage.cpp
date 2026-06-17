#include "MemberStorage.hpp"

using namespace std;

MemberStorage::MemberStorage(string filePath)
    : filePath_(filePath){}

string MemberStorage::getFilePath() const
{
    return filePath_;
}

void MemberStorage::saveAllMembers(const vector<Member> &members)
{
    ofstream fout(filePath_);

    if (!fout)
    {
        cout << "File could not open.\n";
        return;
    }

    for (size_t i = 0; i < members.size(); i++)
    {
        fout << members[i].getUserId() << ","
             << members[i].getUsername() << ","
             << members[i].getPassword() << ","
             << members[i].getFirstName() << ","
             << members[i].getLastName() << ","
             << members[i].getAddress() << ","
             << members[i].getUserBalance() << "\n";
    }

    fout.close();
}

void MemberStorage::loadAllMembers(vector<Member>& members)
{
    ifstream fin(filePath_);

    if (!fin)
    {
        cout << "No file found.\n";
        return;
    }

    string line;

    while (getline(fin, line))
    {
        stringstream ss(line);

        string idStr, username, password;
        string firstName, lastName, address;
        string balanceStr;

        getline(ss, idStr, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, address, ',');
        getline(ss, balanceStr, ',');

        double balance = stod(balanceStr);

        Member member(username, password,
                      firstName, lastName,
                      balance, address);

        members.push_back(member);
    }

    fin.close();
}

