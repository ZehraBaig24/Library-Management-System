#ifndef BORROWRECORDMANAGER_HPP
#define BORROWRECORDMANAGER_HPP

#include<iostream>
using namespace std;
#include <vector>
#include <stdexcept>
#include <iomanip>
#include "BorrowRecord.hpp"
#include "BorrowStorage.hpp"


class Borrow_Record_Manager {
private:
    std::vector<BorrowRecord> Record_;
    BorrowStorage Storage_;

public:
    Borrow_Record_Manager();
    ~Borrow_Record_Manager();

    void addBorrowRecord(const BorrowRecord &record);
    const BorrowRecord& updateBorrowRecord(int borrow_Id);
    void DisplayBorrowRecord(int memberID);
    void DisplayAllBorrowRecords() const;
};

#endif // BORROWRECORDMANAGER_HPP
