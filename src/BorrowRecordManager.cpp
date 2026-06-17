#include "BorrowRecordManager.hpp"
#include <iomanip>

Borrow_Record_Manager::Borrow_Record_Manager() :
Storage_("Borrow Record Storage.txt"){
    // reserve() preallocates capacity without adding elements.
    // It's a performance optimization to avoid costly reallocations as the vector grows.
	Record_.reserve(100);
    Storage_.loadAllBorrowRecords(Record_); //Initializes and Populates Record_ vector
}

Borrow_Record_Manager::~Borrow_Record_Manager() {
    Storage_.saveAllBorrowRecords(Record_);
}

void Borrow_Record_Manager::addBorrowRecord(const BorrowRecord &record){
	Record_.push_back(record);
	Storage_.saveAllBorrowRecords(Record_);
}
const BorrowRecord& Borrow_Record_Manager::updateBorrowRecord(int borrow_Id){
    // Search Record_ vector for matching borrow ID
for(BorrowRecord&rec : Record_)
    {
        if (rec.getBorrowID() == borrow_Id)
        {
            // Check if already returned
            if (rec.getReturnStatus())
            {
                throw std::string("Borrowed Resource has already been returned!");
            }
            // Mark as returned using BorrowRecord::setReturnStatus(bool)
            rec.setReturnStatus(true);
            rec.setReturnDate(Date::today());
            Storage_.saveAllBorrowRecords(Record_);
            return rec; //return updated Record's ref to the caller
        }
    }
    throw std::string("No active borrow record found found for the resource!");
}

    void Borrow_Record_Manager::DisplayBorrowRecord(int memberID){ //shows BorrowHistory of a member
            cout << std::left << std::setw(10) << "BORROW ID"
                 << std::setw(12) << "MEMBER ID"
                 << std::setw(15) << "RESOURCE ID"
                 << std::setw(12) << "ISSUE DATE"
                 << std::setw(12) << "DUE DATE"
                 << std::setw(14) << "RETURN DATE"
                 << "RETURN STATUS" << std::endl;
          cout << std::string(87, '-') << std::endl; //create a string with the character '-' repeated 87 times
            
          for(const BorrowRecord& rec: Record_){  //loop for each object referred as rec in the vector Record_
                if(memberID==rec.getMemberID()){
                cout << std::left << std::setw(10) << rec.getBorrowID() //alight to left as default is right alignment
                         << std::setw(12) << rec.getMemberID()
                         << std::setw(15) << rec.getResourceID()
                    //Converting each field of d/m/y of Date object to a string and contatenating it with "/" to display it as a whole
                         << std::setw(12) << (std::to_string(rec.getIssueDate().getDate()) + "/" + 
                                              std::to_string(rec.getIssueDate().getMonth()) + "/" + 
                                              std::to_string(rec.getIssueDate().getYear()))
                         << std::setw(12) << (std::to_string(rec.getDueDate().getDate()) + "/" + 
                                              std::to_string(rec.getDueDate().getMonth()) + "/" + 
                                              std::to_string(rec.getDueDate().getYear()))
                         << std::setw(14) << (rec.getReturnStatus() ? (std::to_string(rec.getReturnDate().getDate()) + "/" + 
                                                                        std::to_string(rec.getReturnDate().getMonth()) + "/" + 
                                                                        std::to_string(rec.getReturnDate().getYear())) : "-")
                         << (rec.getReturnStatus() ? "Returned" : "Not Returned") << std::endl;
                        }
            }

    }
    void Borrow_Record_Manager::DisplayAllBorrowRecords() const{ //shows all active BorrowRecords in LMS
        cout << std::left << std::setw(10) << "BORROW ID"
             << std::setw(12) << "MEMBER ID"
             << std::setw(15) << "RESOURCE ID"
             << std::setw(12) << "ISSUE DATE"
             << std::setw(12) << "DUE DATE"
             << std::setw(14) << "RETURN DATE"
             << "RETURN STATUS" << std::endl;
        cout << std::string(87, '-') << std::endl;

        for(const BorrowRecord& rec: Record_){  //loop for each object referred as rec in the vector Record_  
            cout << std::left << std::setw(10) << rec.getBorrowID()
                 << std::setw(12) << rec.getMemberID()
                 << std::setw(15) << rec.getResourceID()
                 << std::setw(12) << (std::to_string(rec.getIssueDate().getDate()) + "/" + 
                                      std::to_string(rec.getIssueDate().getMonth()) + "/" + 
                                      std::to_string(rec.getIssueDate().getYear()))
                 << std::setw(12) << (std::to_string(rec.getDueDate().getDate()) + "/" + 
                                      std::to_string(rec.getDueDate().getMonth()) + "/" + 
                                      std::to_string(rec.getDueDate().getYear()))
                 << std::setw(14) << (rec.getReturnStatus() ? (std::to_string(rec.getReturnDate().getDate()) + "/" + 
                                                                std::to_string(rec.getReturnDate().getMonth()) + "/" + 
                                                                std::to_string(rec.getReturnDate().getYear())) : "-")
                 << (rec.getReturnStatus() ? "Returned" : "Not Returned") << std::endl;
        }
    }
