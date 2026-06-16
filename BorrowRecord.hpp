#ifndef BORROWRECORD_HPP
#define BORROWRECORD_HPP

#include <string>
#include "Date.hpp"

class BorrowRecord {
private:
    int borrowID_;
    int memberID_;
    std::string resourceID_;
    Date issueDate_;
    Date dueDate_;
    Date returnDate_;
    bool returnStatus_;
    static int IDCount_;

public:
    BorrowRecord(int memberID = 0, const std::string& resourceID = "", const Date& issueDate = Date(), const Date& dueDate = Date(), const Date& returnDate = Date(), bool returnStatus = false);

    int getMemberID() const;
    int getBorrowID() const;
    static int getIDCount();

    std::string getResourceID() const;
    Date getIssueDate() const;
    Date getDueDate() const;
    Date getReturnDate() const;
    bool getReturnStatus() const;

    //Setter methods only for attributes that can be updated in Borrow Record
    void setReturnStatus(bool status);
    void setReturnDate(const Date &d);
};

#endif // BORROWRECORD_HPP
