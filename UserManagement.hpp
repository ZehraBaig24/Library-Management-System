#ifndef USERMANAGEMENT_HPP
#define USERMANAGEMENT_HPP

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include <stdexcept>

#include "BorrowRecord.hpp"
#include "LibraryResource.hpp"
#include "Date.hpp"


// Forward declarations
class Borrow_Record_Manager;
class Online_Resource_Manager;
class Physical_Resource_Manager;
class User_Manager;
class LibraryResource;

using namespace std;

// User (Abstract Base Class)

class User
{
protected:
    string username_;
    string password_;
    string firstName_;
    string lastName_;

public:
    User();
    User(const string &username,
         const string &password,
         const string &firstName,
         const string &lastName);

    virtual ~User()=default;

    // Getters
    string getUsername() const;
    string getPassword() const;
    string getFirstName() const;
    string getLastName() const;

    // Setters
    void setUsername(const string &username);
    void setPassword(const string &password);
    void setFirstName(const string &firstName);
    void setLastName(const string &lastName);

    // Behaviour
    void updatePassword();
    bool verifyPassword(const string &inputPassword) const;

};


// Member Class

class Member : public User
{
private:
    int userId_;
    double balance_;
    string address_;
    int currentBorrowCount_;
    

    static int idCount_;
    static const int maxBorrowLimit_ = 2;
    static const int resourceAccessDays_ = 14;

    vector<BorrowRecord> borrowHistory_;
    

public:
    Member();
    Member(const string &username,
           const string &password,
           const string &firstName,
           const string &lastName,
           double balance,
           const string &address);

    virtual ~Member()=default;

    // Getters
    int getUserId() const;
    double getUserBalance() const;
    int getBorrowCount() const;
    string getAddress() const;
    static int getIdCount();

    // Setters
    void setBorrowCount(int currentBorrowCount);
    void setBalance(double balance);
    void setAddress(const string &address);

    void createAccount();

    // Member functions
    bool canBorrow() const; // helper function
    void borrowOnlineResource(const string &resourceId,
                                       Online_Resource_Manager& onlineMgr,
                                       Borrow_Record_Manager& borrowMgr);
    bool returnOnlineResource(int borrowId,
                              Borrow_Record_Manager& borrowMgr,
                              Online_Resource_Manager& onlineMgr);
    void updateBalance(double amount);
    BorrowRecord *viewBorrowHistory();
};

class Administrator : public User
{
public:
    // Constructors / Destructor
    Administrator();
    Administrator(const string& username,
                  const string& password,
                  const string& firstName,
                  const string& lastName);
    ~Administrator()=default;
 
    // Member methods
    void issuePhysicalResource(const string &resourceId,
                               int memberId,
                               User_Manager& userMgr,
                               Physical_Resource_Manager& physMgr,
                               Borrow_Record_Manager& borrowMgr);
    void processReturnOfPhysicalResouce(int borrowId,
                                        Borrow_Record_Manager& borrowMgr,
                                        Physical_Resource_Manager& physMgr);
};
#endif