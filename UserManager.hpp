#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include <vector>
#include <string>
#include <iostream>
#include "UserManagement.hpp"
#include "MemberStorage.hpp"

using namespace std;

class User_Manager
{
private:
    vector<Member> members_;

    MemberStorage memberStore_;

     Administrator admin_; 

public:
    User_Manager();
    ~User_Manager();

    Member* login(const string &username,
                  const string &password);

    // Return pointer to member by user id, or nullptr if not found
    Member* getMemberById(int userId);

    void addMember(Member member);

    void saveMembers();

    void updateMember(int userId);

    void removeMember(int userId);

    void displayAllMembers() const;

    void displayMember(const Member* member);

    Administrator* adminLogin(const string &username,const string &password);
};

#endif