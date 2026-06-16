#include "PhysicalStorage.hpp"

// ==========================================================
//               PHYSICAL RESOURCE STORAGE
// ==========================================================
PhysicalResourceStorage::PhysicalResourceStorage()
    : filepath("PhysicalResources.txt")
{
}

// ============================================================
// Parameterized Storage Constructor
// ============================================================
PhysicalResourceStorage::PhysicalResourceStorage(const std::string &path)
    : filepath(path)
{
}

// ============================================================
// Get File Path
// ============================================================
std::string PhysicalResourceStorage::getFilepath() const
{
    return filepath;
}



// ============================================================
// Load All Physical Resources From File
//
// Reads file data into memory array
// ============================================================
void PhysicalResourceStorage::loadAllPhysicalResources(
    PhysicalResource **Physical,
    int &count)
    //**Physical points to array of pointers that point to physical resources
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        std::cout << "No existing file found. Starting fresh.\n";
        return;
    }

    count = 0;

    std::string line;

    while (getline(file, line) && count < PhysicalResource::MAX_CAPACITY)
    {
        if (line.empty())
        {
            continue;
        }

        try
        {
            std::stringstream ss(line);

            std::string resourceID;
            std::string title;
            std::string author;
            std::string genre;
            std::string resourceType;
            std::string ddStr;
            std::string mmStr;
            std::string yyStr;
            std::string availStr;

            Date d;

            // =================================================
            // Read values from CSV
            // =================================================
            getline(ss, resourceID, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, availStr, ',');
            getline(ss, genre, ',');
            getline(ss, resourceType, ',');
            getline(ss, ddStr, ',');
            getline(ss, mmStr, ',');
            getline(ss, yyStr, ',');

            // =================================================
            // Set date
            // =================================================
            d.setDay(std::stoi(ddStr));
            d.setMonth(std::stoi(mmStr));
            d.setYear(std::stoi(yyStr));

            // =================================================
            // Create resource object
            // =================================================
            Physical[count] = new PhysicalResource();

            Physical[count]->setResourceID(resourceID);
            Physical[count]->setResourceTitle(title);
            Physical[count]->setResourceAuthor(author);
            Physical[count]->SetAvailability(availStr == "1");
            Physical[count]->setGenre(genre);
            Physical[count]->setResourceType(resourceType);
            Physical[count]->setPublicationDate(d);

            count++;
        }

        catch (const std::exception &e)
        {
            std::cout
                << "Skipping corrupted line: "
                << e.what()
                << std::endl;
        }
    }

    file.close();
}



// ============================================================
// Save All Physical Resources To File
//
// Writes memory array into file
// ============================================================
void PhysicalResourceStorage::saveAllPhysicalResources(
    PhysicalResource **Physical,
    int count)
{
    std::ofstream file(filepath);

    if (!file.is_open())
    {
        std::cout
            << "Error: Could not open file for saving.\n";

        return;
    }

    for (int i = 0; i < count; i++)
    {
        const Date &d = Physical[i]->getPublicationDate();

        file
            << Physical[i]->getResourceID() << ","
            << Physical[i]->getTitle() << ","
            << Physical[i]->getAuthor() << ","
            << (Physical[i]->getAvailabilityStatus() ? 1 : 0) << ","
            << Physical[i]->getGenre() << ","
            << Physical[i]->getResourceType() << ","
            << d.getDate() << ","
            << d.getMonth() << ","
            << d.getYear()
            << "\n";
    }

    file.close();
}
