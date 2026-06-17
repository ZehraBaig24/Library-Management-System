#ifndef PHYSICALSTORAGE_HPP
#define PHYSICALSTORAGE_HPP

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <iostream>

#include "PhysicalResource.hpp"
#include "Date.hpp"

// ============================================================
//              PHYSICAL RESOURCE STORAGE CLASS
// ============================================================
//
// Handles ONLY file operations:
//
//   - loading resources from file
//   - saving resources into file
//
// This class does NOT manage business logic.
// ============================================================
class PhysicalResourceStorage
{
private:

    // ========================================================
    // File path where resources are stored
    // ========================================================
    std::string filepath;

public:

    // ========================================================
    // Default Constructor
    //
    // Uses default file:
    // "PhysicalResources.txt"
    // ========================================================
    PhysicalResourceStorage();


    // ========================================================
    // Parameterized Constructor
    //
    // Allows custom storage file
    // ========================================================
    PhysicalResourceStorage(
        const std::string &filepath);


    // ========================================================
    // Get File Path
    // ========================================================
    std::string getFilepath() const;


    // ========================================================
    // Load All Physical Resources
    //
    // Reads resources from file into memory array
    //
    // Parameters:
    //   Physical -> array of pointers
    //   count    -> current number of resources
    // ========================================================
    void loadAllPhysicalResources(
        PhysicalResource** Physical,
        int &count);


    // ========================================================
    // Save All Physical Resources
    //
    // Writes memory array data back into file
    // ========================================================
    void saveAllPhysicalResources(
        PhysicalResource** Physical,
        int count);


    // ========================================================
    // Default Destructor
    // ========================================================
    ~PhysicalResourceStorage() = default;
};

#endif
