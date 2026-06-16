#ifndef MEMBERSTORAGE_HPP
#define MEMBERSTORAGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "UserManagement.hpp"
using namespace std;

class MemberStorage
{
private:
    string filePath_;

public:
    MemberStorage(string filePath = "members.txt");

    string getFilePath() const;

    void saveAllMembers(const vector<Member> &members);

   void  loadAllMembers(vector<Member> &members);

    ~MemberStorage()=default;
};

#endif