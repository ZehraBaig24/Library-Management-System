#include "BorrowRecord.hpp"

int BorrowRecord::IDCount_ = 0;

BorrowRecord::BorrowRecord(int memberID, const std::string& resourceID, const Date& issueDate, const Date& dueDate, const Date& returnDate, bool returnStatus)
    : borrowID_(++IDCount_),
      memberID_(memberID),
      resourceID_(resourceID),
      issueDate_(issueDate),
      dueDate_(dueDate),
      returnDate_(returnDate),
      returnStatus_(returnStatus) {}

int BorrowRecord::getMemberID() const {
    return memberID_;
}

int BorrowRecord::getBorrowID() const {
    return borrowID_;
}

int BorrowRecord::getIDCount() {
    return IDCount_;
}

std::string BorrowRecord::getResourceID() const {
    return resourceID_;
}

Date BorrowRecord::getIssueDate() const {
    return issueDate_;
}

Date BorrowRecord::getDueDate() const {
    return dueDate_;
}

Date BorrowRecord::getReturnDate() const {
    return returnDate_;
}

bool BorrowRecord::getReturnStatus() const {
    return returnStatus_;
}

//setter methods only for fields that can be updated in the Record

void BorrowRecord::setReturnStatus(bool status) {
    returnStatus_ = status;
}

void BorrowRecord::setReturnDate(const Date& d) {
    returnDate_ = d;
}















