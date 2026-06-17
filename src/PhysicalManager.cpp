#include "PhysicalManager.hpp"

// ============================================================
//                  PHYSICAL RESOURCE MANAGER
// ============================================================


// ============================================================
// Default Constructor
//
// Initializes:
// - storage file
// - count = 0
// - all array pointers to nullptr
// ============================================================
Physical_Resource_Manager::Physical_Resource_Manager()
    : PhysicalStore("PhysicalResources.txt"), count(0)
{
    for (int i = 0; i < MAX_CAPACITY; i++)
    {
        Physical[i] = nullptr;
    }
    PhysicalStore.loadAllPhysicalResources(Physical, count);
}

void printPhysicalHeader()
{
    std::cout << std::left;
    // =========================================================
    // Table header
    // =========================================================
    
    std::cout
        << std::string(125, '-')
        << std::endl;

    std::cout
        << std::setw(10) << "ID"
        << std::setw(30) << "Title"
        << std::setw(25) << "Author"
        << std::setw(20) << "Publication"
        << std::setw(15) << "Genre"
        << std::setw(15) << "Type"
        << std::setw(10) << "Available"
        << std::endl;

    std::cout
        << std::string(125, '-')
        << std::endl;

}


// ============================================================
// Parameterized Constructor
//
// Allows custom storage file
// ============================================================
Physical_Resource_Manager::Physical_Resource_Manager(const std::string &path)
    : count(0), PhysicalStore(path)
{
    for (int i = 0; i < MAX_CAPACITY; i++)
    {
        Physical[i] = nullptr;
    }
    PhysicalStore.loadAllPhysicalResources(Physical, count);
}

// ============================================================
// Add Physical Resource
// ============================================================
void Physical_Resource_Manager::add_PhysicalResources()
{
    // =========================================================
    // Clear previous memory
    // =========================================================
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }

    count = 0;

    // =========================================================
    // Reload latest file data
    // =========================================================
    PhysicalStore.loadAllPhysicalResources(Physical, count);

    if (count >= MAX_CAPACITY)
    {
        std::cout << "\t\t | Storage full. |\n";
        return;
    }

    std::string title;
    std::string author;
    std::string inputGenre;
    std::string inputResourceType;

    Date publicationDate;

    std::cout << "\n\t\t ---- Add Physical Resource ----\n";

    std::cin.ignore();

    // =========================================================
    // Input title
    // =========================================================
    std::cout << "\t\tTitle : ";
    getline(std::cin, title);

    // =========================================================
    // Input author
    // =========================================================
    std::cout << "\t\tAuthor : ";
    getline(std::cin, author);

    // =========================================================
    // Input genre
    // =========================================================
    std::cout << "\t\tGenre : ";
    getline(std::cin, inputGenre);

    // =========================================================
    // Input resource type
    // =========================================================
    std::cout << "\t\tResource Type : ";
    getline(std::cin, inputResourceType);

    // =========================================================
    // Input publication date
    // =========================================================
    std::cout << "\t\tPublication Date:\n";
    publicationDate.setDate();

    // =========================================================
    // Generate automatic numeric ID
    // =========================================================
    int maxID = 0;
    for (int i = 0; i < count; i++)
       {
        try
        {
            std::string rID= Physical[i]->getResourceID(); // returns a string "PR-x"
            int id = std::stoi(rID.substr(3));     // extracts an int x
            if (maxID < id)                        // finds the maximum value of x within the vector
            {
                maxID = id;
            }
        }
        catch (...)
        {
            continue;
        }
       }

    std::string newID = "PR-"+ std::to_string(maxID + 1);

    // =========================================================
    // Create new resource
    // =========================================================
    Physical[count] = new PhysicalResource();

    Physical[count]->setResourceID(newID);
    Physical[count]->setResourceTitle(title);
    Physical[count]->setResourceAuthor(author);
    Physical[count]->setPublicationDate(publicationDate);
    Physical[count]->setGenre(inputGenre);
    Physical[count]->setResourceType(inputResourceType);
    Physical[count]->SetAvailability(true);

    count++;

    // =========================================================
    PhysicalStore.saveAllPhysicalResources(
        Physical,
        count);

    std::cout << "\t\t | Resource with ID " << newID << " Added Successfully. | \n";
}

double Physical_Resource_Manager::updateResource(BorrowRecord &record)
{
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }
    count = 0;
    PhysicalStore.loadAllPhysicalResources(Physical, count);

    for (int i = 0; i < count; i++)
    {
        if (Physical[i] != nullptr && Physical[i]->getResourceID() == record.getResourceID())
        {
            return Physical[i]->applyReturnPolicy(record);
        }
    }

    std::cout << "\t\t | Physical resource not found for this borrow record. | \n";
    return 0.0;
}


// ============================================================
// Remove Physical Resource
// ============================================================
void Physical_Resource_Manager::remove_PhysicalResources( std::string rID )
{
    // =========================================================
    // Clear memory
    // =========================================================
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }
    count = 0;

    // =========================================================
    // Reload latest data
    // =========================================================
    PhysicalStore.loadAllPhysicalResources(Physical, count);

    if (count == 0)
    {
        std::cout << "\t\t | No resources available. |\n";
        return;
    }
    bool found = false;

    for (int i = 0; i < count; i++)
    {
        if (Physical[i]->getResourceID() == rID)
        {
            delete Physical[i];

            // Shift elements left
            for (int j = i; j < count - 1; j++)
            {
                Physical[j] = Physical[j + 1];
            }

            Physical[count - 1] = nullptr;

            count--;

            found = true;

            std::cout << "\t\t | Resource with ID " << rID << " Deleted Successfully. | \n";

            break;
        }
    }

    if (!found)
    {
          std::cout << "\t\t | Resource with ID " << rID << " does not exist. | \n";
    }

    // Save updated file
    PhysicalStore.saveAllPhysicalResources(
        Physical,
        count);
}



// ============================================================
// Display Single Physical Resource
// ============================================================
void Physical_Resource_Manager::display_PhysicalResources( std::string rID)
{
    // =========================================================
    // Clear memory
    // =========================================================
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }

    count = 0;

    // Reload data
    PhysicalStore.loadAllPhysicalResources(
        Physical,
        count);

    if (count == 0)
    {
         std::cout << "\t\t | No resources available. |\n";
        return;
    }

    PhysicalResource *r = searchByID(rID);
    if (!r)
    {
        std::cout << "\t\t | Resource with ID " << rID << " does not exist. | \n";
        return;
    }

    std::cout<< "\n\t\t-------------- RESOURCE DETAILS --------------\n";
    std::cout<< "\t\t Resource ID      : "<< r->getResourceID()<< std::endl;
    std::cout<< "\t\t Title            : "<< r->getTitle()<< std::endl;
    std::cout<< "\t\t Author           : "<< r->getAuthor()<< std::endl;
    std::cout<< "\t\t Genre            : "<< r->getGenre()<< std::endl;
    std::cout<< "\t\t Resource Type    : "<< r->getResourceType()<< std::endl;
    std::cout<< "\t\t Available        : "<< (r->getAvailabilityStatus() ? "Yes": "No")<< std::endl;
    std::cout<< "\t\tPublication Date  : "<< r->getPublicationDate()<<std::endl;
    std::cout<< "\n\t\t ---------------------------------------------- \n";
    
}



// ============================================================
// Display All Physical Resources
// ============================================================
void Physical_Resource_Manager::displayAll_PhysicalResources()
{
    // =========================================================
    // Clear memory
    // =========================================================
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }

    count = 0;

    // Reload latest data
    PhysicalStore.loadAllPhysicalResources(
        Physical,
        count);

    if (count == 0)
    {
        std::cout
            << "\t\t | No physical resources found. |\n";

        return;
    }

    printPhysicalHeader();
    // =========================================================
    // Print all resources
    // =========================================================
    for (int i = 0; i < count; i++)
    {
        display_Resource_tabular(Physical[i]);
    }
    std::cout << std::string(125, '-') << std::endl;
    std::cout << "\nTotal Resources: " << count << std::endl;
}



void Physical_Resource_Manager::display_Resource_tabular(const PhysicalResource* r) const
{
    if (r == nullptr)
    {
        return;
    }
      Date d = r->getPublicationDate();
     std::string date = std::to_string(d.getDate()) + "/" +
                       std::to_string(d.getMonth()) + "/" +
                       std::to_string(d.getYear());

    std::cout << std::left
              << std::setw(10) << r->getResourceID()
              << std::setw(30) << r->getTitle()
              << std::setw(25) << r->getAuthor()
              << std::setw(20) << date
              << std::setw(15) << r->getGenre()
              << std::setw(15) << r->getResourceType()
              << std::setw(10) << (r->getAvailabilityStatus() ? "Yes" : "No")
              << std::endl;
}


void Physical_Resource_Manager::searchByTitle(const std::string& title)
{
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }
    count = 0;
    PhysicalStore.loadAllPhysicalResources(Physical, count);

    std::string target = title;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);
    bool found = false;

    for (int i = 0; i < count; i++)
    {
        std::string current = Physical[i]->getTitle();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        if (current == target)
        {
           display_PhysicalResources(Physical[i]->getResourceID());
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "\t\t | Resource Not Found In The System. |\n";
    }
}


void Physical_Resource_Manager::searchByAuthor(const std::string& author)
{
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }
    count = 0;
    PhysicalStore.loadAllPhysicalResources(Physical, count);

    std::string target = author;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);
    bool found = false;

    for (int i = 0; i < count; i++)
    {
        std::string current = Physical[i]->getAuthor();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        if (current == target)
        {
            display_PhysicalResources(Physical[i]->getResourceID());
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "\t\t | Resource Not Found In The System. |\n";
    }
}


void Physical_Resource_Manager::searchByGenre(const std::string& genre)
{
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }
    count = 0;
    PhysicalStore.loadAllPhysicalResources(Physical, count);

    std::string target = genre;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);
    bool found = false;

    for (int i = 0; i < count; i++)
    {
        std::string current = Physical[i]->getGenre();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        if (current == target)
        {
              if(found==false)
            printPhysicalHeader();
            display_Resource_tabular(Physical[i]);
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "\t\t | Resource Not Found In The System. |\n";
    }
    else
    std::cout << std::string(125, '-') << std::endl;
}


void Physical_Resource_Manager::searchByAvailability(bool available)
{
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }
    count = 0;
    PhysicalStore.loadAllPhysicalResources(Physical, count);

    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (Physical[i]->getAvailabilityStatus() == available)
        {
              if(found==false)
            printPhysicalHeader();
            display_Resource_tabular(Physical[i]);
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "\t\t | Resource Not Found In The System. |\n";
    }
    else
    std::cout << std::string(125, '-') << std::endl;
}


PhysicalResource* Physical_Resource_Manager::searchByID(const std::string& rID)
{
    for (int i = 0; i < count; i++)
    {
        delete Physical[i];
        Physical[i] = nullptr;
    }
    count = 0;
    PhysicalStore.loadAllPhysicalResources(Physical, count);

    for (int i = 0; i < count; i++)
    {
        if (Physical[i]->getResourceID() == rID)
        {
            return Physical[i];
        }
    }

    return nullptr;
}


// ============================================================
// Destructor
//
// Cleans dynamically allocated memory and persists to disk
// ============================================================
Physical_Resource_Manager::~Physical_Resource_Manager()
{
    PhysicalStore.saveAllPhysicalResources(Physical, count);
    for (int i = 0; i < count; i++)
    {
        if (Physical[i] != nullptr)
        {
            delete Physical[i];
            Physical[i] = nullptr;
        }
    }
}
