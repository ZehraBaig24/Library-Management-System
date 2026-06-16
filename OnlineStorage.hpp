#ifndef ONLINESTORAGE_HPP
#define ONLINESTORAGE_HPP

#include "OnlineResource.hpp"
#include "Date.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <memory>
#include <vector>
#include <algorithm>


// ============================================================
//                ONLINE RESOURCE STORAGE
// ============================================================
// Handles file-based persistence of OnlineResource objects.
// Responsible ONLY for:
//   - Loading resources from file
//   - Saving resources into file
//
// Does NOT handle business logic.
// ============================================================
class OnlineResourceStorage
{
private:
    // File path used for storage
    std::string filepath;

public:

    // ========================================================
    // Default Constructor
    // Uses default file: "OnlineResources.txt"
    // ========================================================
    OnlineResourceStorage();

    
    // ========================================================
    // Parameterized Constructor
    // Allows custom storage file path
    // ========================================================
    OnlineResourceStorage(const std::string &filepath);

    // ========================================================
    // Get Current File Path
    // ========================================================
    std::string getFilepath() const;


    // ========================================================
    // Load All Online Resources From File
    //
    // Returns:
    // Vector of smart pointers containing OnlineResource objects
    // ========================================================
    std::vector<std::unique_ptr<OnlineResource>>
    loadAllOnlineResources();


    // ========================================================
    // Save All Online Resources To File
    //
    // Parameters:
    // online -> vector containing all resources in memory
    // ========================================================
    void saveAllOnlineResources(
        const std::vector<std::unique_ptr<OnlineResource>> &online);


    // ========================================================
    // Destructor
    // Default destructor is enough because smart pointers
    // automatically handle memory cleanup
    // ========================================================
    ~OnlineResourceStorage() = default;
};
#endif