#ifndef PHYSICALMANAGER_HPP
#define PHYSICALMANAGER_HPP

#include "PhysicalStorage.hpp"
#include "PhysicalResource.hpp"

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>
#include <algorithm>


// ============================================================
//          PHYSICAL RESOURCE MANAGER CLASS
// ============================================================
//
// Handles:
//
//   - adding resources
//   - removing resources
//   - displaying resources
//   - memory management
//
// Uses PhysicalResourceStorage for persistence.
// ============================================================
class Physical_Resource_Manager
{
private:

    // ========================================================
    // Maximum number of physical resources supported
    // ========================================================
    static const int MAX_CAPACITY = 1000;


    // ========================================================
    // File storage handler
    // ========================================================
    PhysicalResourceStorage PhysicalStore;


    // ========================================================
    // Array storing pointers to PhysicalResource objects
    // ========================================================
    PhysicalResource* Physical[MAX_CAPACITY];


    // ========================================================
    // Current number of loaded resources
    // ========================================================
    int count;

public:

    // ========================================================
    // Default Constructor
    //
    // Uses default storage file
    // ========================================================
    Physical_Resource_Manager();


    // ========================================================
    // Parameterized Constructor
    //
    // Allows custom storage file
    // ========================================================
    Physical_Resource_Manager(
        const std::string& filepath);


    // ========================================================
    // Destructor
    //
    // Cleans dynamically allocated memory
    // ========================================================
    ~Physical_Resource_Manager();


    // ========================================================
    // Add New Physical Resource
    // ========================================================
    void add_PhysicalResources();


    // ========================================================
    // Remove Existing Physical Resource
    // ========================================================
    void remove_PhysicalResources( std::string resourceID);


    // ========================================================
    // Display Single Physical Resource
    // ========================================================
    void display_PhysicalResources( std::string resourceID);


    // ========================================================
    // Display All Physical Resources
    // ========================================================
    void displayAll_PhysicalResources();

    void display_Resource_tabular(const PhysicalResource* r) const;

    void searchByTitle(const std::string& title);
    void searchByAuthor(const std::string& author);
    void searchByGenre(const std::string& genre);
    void searchByAvailability(bool available);
    PhysicalResource* searchByID(const std::string& rID);


    // ========================================================
    // Update Physical Return Policy
    // ========================================================
    double updateResource(BorrowRecord &record);
};
#endif
