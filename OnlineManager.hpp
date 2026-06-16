#ifndef ONLINEMANAGER_HPP
#define ONLINEMANAGER_HPP

class OnlineResource; // Forward declaration

#include "Date.hpp"
#include "OnlineStorage.hpp"
#include "BorrowRecord.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>    // for tabular display
#include <stdexcept>  //for exceptions
#include <memory>     // for smart pointers
#include <algorithm>  // to transform any string into lowercase
#include<vector>
#include <string>




// ============================================================
//                ONLINE RESOURCE MANAGER
// ============================================================
// Handles all business logic related to online resources.
//
// Responsibilities:
//   - Add resource
//   - Remove resource
//   - Display single resource
//   - Display all resources
//
// Uses OnlineResourceStorage for file persistence.
// ============================================================
class Online_Resource_Manager
{
private:

    // Storage handler object
    OnlineResourceStorage OnlineStore;


    // In-memory list of all online resources
    // unique_ptr prevents memory leaks automatically
    std::vector<std::unique_ptr<OnlineResource>> Online;

    // ========================================================
    // Reloads all resources from file into memory
    // ========================================================
    void reload();

public:

    // ========================================================
    // Default Constructor
    // Uses default storage file
    // ========================================================
    Online_Resource_Manager();


    // ========================================================
    // Parameterized Constructor
    // Allows custom storage file path
    // ========================================================
    Online_Resource_Manager(const std::string &filepath);


    // ========================================================
    // Destructor
    // No manual delete required because unique_ptr handles it
    // ========================================================
    ~Online_Resource_Manager();


    // ========================================================
    // Add New Online Resource
    // ========================================================
    void add_OnlineResource();


    // ========================================================
    // Remove Existing Online Resource
    // ========================================================
    void remove_OnlineResource( std::string rID);


    // ========================================================
    // Display One Resource By ID
    // ========================================================
    void display_OnlineResource( std::string rID);


    // ========================================================
    // Display All Resources In Tabular Format
    // ========================================================
    void displayAll_OnlineResources();

    void display_OnlineResource_tabular(const OnlineResource* r) const;

    void searchByTitle(const std::string& title);
    void searchByAuthor(const std::string& author);
    void searchByGenre(const std::string& genre);
    void searchByType(const std::string& type);
    void searchByAvailability(bool available);
    OnlineResource* searchByID(const std::string& rID);


    // ========================================================
    // Update Online Resource Return Policy
    // ========================================================
    double updateResource(BorrowRecord &record);
};

#endif