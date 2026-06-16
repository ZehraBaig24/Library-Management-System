#include "BorrowStorage.hpp"
#include "BorrowRecord.hpp"
#include "Date.hpp"
#include <iostream>
#include <sstream>

BorrowStorage::BorrowStorage(const std::string& filePath): filePath_(filePath){
}

BorrowStorage::~BorrowStorage() = default;

std::string BorrowStorage::getFilePath() const{
    return filePath_;
}

//Helper method that takes a CSV line and writes parsed data into out. 
bool BorrowStorage::parseCsvBorrowRecord(const std::string& line, BorrowRecord& out){
    std::stringstream ss(line);
    std::string field; //Temporary string used to hold each CSV field as it's read.

    //reads characters from stream ss into field until it encounters the delimiter character ',' or EOF
    // skip borrowID as it is uniquely created in the constructor using a static Counter
    if(!std::getline(ss, field, ',')) return false; 

    if(!std::getline(ss, field, ',')) return false;
    int memberID = std::stoi(field);

    if(!std::getline(ss, field, ',')) return false;
    std::string resourceID = field;

    // issue date
    if(!std::getline(ss, field, ',')) return false; int iDay = std::stoi(field);
    if(!std::getline(ss, field, ',')) return false; int iMonth = std::stoi(field);
    if(!std::getline(ss, field, ',')) return false; int iYear = std::stoi(field);
    Date issue; issue.setDay(iDay); issue.setMonth(iMonth); issue.setYear(iYear);

    // due date (same pattern)
    if(!std::getline(ss, field, ',')) return false; int dDay = std::stoi(field);
    if(!std::getline(ss, field, ',')) return false; int dMonth = std::stoi(field);
    if(!std::getline(ss, field, ',')) return false; int dYear = std::stoi(field);
    Date due; due.setDay(dDay); due.setMonth(dMonth); due.setYear(dYear);

    // return date (same pattern)
    if(!std::getline(ss, field, ',')) return false; int rDay = std::stoi(field);
    if(!std::getline(ss, field, ',')) return false; int rMonth = std::stoi(field);
    if(!std::getline(ss, field, ',')) return false; int rYear = std::stoi(field);
    Date returnD; returnD.setDay(rDay); returnD.setMonth(rMonth); returnD.setYear(rYear);

    if(!std::getline(ss, field)) return false;
    bool returnStatus = (std::stoi(field) != 0);

    //create a BorrowRecord temporary with parsed values and assign it into out.
    out = BorrowRecord(memberID, resourceID, issue, due, returnD, returnStatus);
    return true;
}

void BorrowStorage::loadAllBorrowRecords(std::vector<BorrowRecord>& records){
    std::ifstream RecordFile(filePath_);
    if(!RecordFile){
        std::cout<<"No Borrow Records found!"<<std::endl;
        return;
    }
    
    std::string line;
    while(std::getline(RecordFile, line)){
        if(line.empty()) continue; //skip blank lines.
        BorrowRecord rec;
        try{    
        if(!BorrowStorage::parseCsvBorrowRecord(line, rec)){
            std::cout<<"Skipping incorrect CSV formatted Record "<<line<<std::endl;
            continue;
        }
        records.push_back(rec);
        }
        catch(const std::exception& e){
            std::cerr<<"Parsing failed! Borrow Records not loaded successfully!"<<e.what()<<std::endl;
        }
    }
}

void BorrowStorage::saveAllBorrowRecords(const std::vector<BorrowRecord>& records){
    std::ofstream out(filePath_);
    if(!out){
        std::cout<<"No Borrow Records found!"<<std::endl;
        return;
    }
    for(const BorrowRecord& rec : records){
        out<<rec.getBorrowID()<<','
           <<rec.getMemberID()<<','
           <<rec.getResourceID()<<','
           <<rec.getIssueDate()<<','
           <<rec.getDueDate()<<','
           <<rec.getReturnDate()<<','
           <<rec.getReturnStatus()<<'\n';

    }
}