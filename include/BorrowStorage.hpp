#ifndef BORROWSTORAGE_HPP
#define BORROWSTORAGE_HPP

#include <string>
#include <fstream>
#include <vector>

class BorrowRecord; // forward declaration

class BorrowStorage {
private:
    std::string filePath_;
    
public:
    BorrowStorage(const std::string& filePath);
    ~BorrowStorage();

    std::string getFilePath() const;
    bool parseCsvBorrowRecord(const std::string& line, BorrowRecord& out);
    void loadAllBorrowRecords(std::vector<BorrowRecord>& records);
    void saveAllBorrowRecords(const std::vector<BorrowRecord>& records);
};

#endif // BORROWSTORAGE_HPP
