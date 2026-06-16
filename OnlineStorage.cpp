#include "OnlineStorage.hpp"


// ==========================================================
//               ONLINE RESOURCE STORAGE
// ==========================================================


// ==========================================================
// Default Constructor
// ==========================================================
OnlineResourceStorage::OnlineResourceStorage()
    : filepath("OnlineResources.txt")
{
}


// ==========================================================
// Parameterized Constructor
// ==========================================================
OnlineResourceStorage::OnlineResourceStorage(const std::string &path)
    : filepath(path)
{
}


// ==========================================================
// Get file path
// ==========================================================
std::string OnlineResourceStorage::getFilepath() const
{
    return filepath;
}


// ==========================================================
// Load all resources from file into memory
// ==========================================================
std::vector<std::unique_ptr<OnlineResource>>
OnlineResourceStorage::loadAllOnlineResources()
{
    std::vector<std::unique_ptr<OnlineResource>> online;

    std::ifstream file(filepath);

    // Check if file opened successfully
    if (!file.is_open())
    {
        std::cout << "No existing online resources file found. Starting fresh." << std::endl;
        return online;
    }

    std::string line;

    // Read file line-by-line
    while (std::getline(file, line))
    {
        try
        {
            std::stringstream ss(line);

            // Create smart pointer resource
            auto r = std::make_unique<OnlineResource>();

            std::string temp;
            Date d;

            // ==================================================
            // Read Resource ID
            // ==================================================
            std::getline(ss, temp, ',');
            r->setResourceID(temp);

            // ==================================================
            // Read Title
            // ==================================================
            std::getline(ss, temp, ',');
            r->setResourceTitle(temp);

            // ==================================================
            // Read Author
            // ==================================================
            std::getline(ss, temp, ',');
            r->setResourceAuthor(temp);

            // ==================================================
            // Read Availability
            // ==================================================
            std::getline(ss, temp, ',');
            r->SetAvailability(temp == "1");

            // ==================================================
            // Read Genre
            // ==================================================
            std::getline(ss, temp, ',');
            r->setGenre(temp);

            // ==================================================
            // Read Resource Type
            // ==================================================
            std::getline(ss, temp, ',');
            r->setResourceType(temp);

            // ==================================================
            // Read Day
            // ==================================================
            std::getline(ss, temp, ',');
            d.setDay(std::stoi(temp));

            // ==================================================
            // Read Month
            // ==================================================
            std::getline(ss, temp, ',');
            d.setMonth(std::stoi(temp));

            // ==================================================
            // Read Year
            // ==================================================
            std::getline(ss, temp, ',');
            d.setYear(std::stoi(temp));

            // Set publication date
            r->setPublicationDate(d);

            // Add resource into vector
            online.push_back(std::move(r));
        }

        // Skip corrupted lines safely
        catch (const std::exception &e)
        {
            std::cout << "Skipping corrupted line: "
                      << e.what() << std::endl;
        }
    }

    file.close();

    return online;
}


// ==========================================================
// Save all resources from memory into file
// ==========================================================
void OnlineResourceStorage::saveAllOnlineResources(
    const std::vector<std::unique_ptr<OnlineResource>> &online)
{
    std::ofstream file(filepath);

    if (!file.is_open())
    {
        std::cout << "Error opening file.\n";
        return;
    }

    // Write every resource into file
    for (const auto &r : online)
    {
        const Date &d = r->getPublicationDate();

        file
            << r->getResourceID() << ","
            << r->getTitle() << ","
            << r->getAuthor() << ","
            << (r->getAvailabilityStatus() ? 1 : 0) << ","
            << r->getGenre() << ","
            << r->getResourceType() << ","
            << d.getDate() << ","
            << d.getMonth() << ","
            << d.getYear()
            << "\n";
    }

    file.close();
}