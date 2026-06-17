#ifndef LMS_HPP
#define LMS_HPP

#include "OnlineManager.hpp"
#include "PhysicalManager.hpp"
#include "BorrowRecordManager.hpp"
#include "UserManager.hpp"

#include <stdexcept>
#include <iostream>
#include <limits>
#include <string>


class lms{
    Online_Resource_Manager OnlineResourceDatabase;
    Physical_Resource_Manager PhysicalResourceDatabase;
    Borrow_Record_Manager BorrowRecordDatabase;
    User_Manager UserManagerDatabase;

    public:
    lms()=default;
    void run();
    ~lms()=default;

};

#endif
