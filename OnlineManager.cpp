#include "OnlineManager.hpp"
#include <limits>

// ------------------------------------------------------
//                ONLINE RESOURCE MANAGER
// ------------------------------------------------------

Online_Resource_Manager::Online_Resource_Manager()
    : OnlineStore("OnlineResources.txt")
{
    Online = OnlineStore.loadAllOnlineResources();
}

Online_Resource_Manager::Online_Resource_Manager(const std::string &path)
    : OnlineStore(path)
{
    Online = OnlineStore.loadAllOnlineResources();
}

// Destructor: Save data to disk on shutdown
Online_Resource_Manager::~Online_Resource_Manager() {
    OnlineStore.saveAllOnlineResources(Online);
}

void printOnlineHeader()
{
    std::cout<<std::string(125 , '-')<<std::endl;
    std::cout << std::left;
    std::cout
        << std::setw(10) << "ID"
        << std::setw(32) << "Title"
        << std::setw(20) << "Author"
        << std::setw(15) << "Publication"
        << std::setw(13) << "Available"
        << std::setw(10) << "Type"
        << std::setw(15) << "Genre"
        << std::endl;

    std::cout<<std::string(125 , '-')<<std::endl;
}
// Add New Online Resource
void Online_Resource_Manager::add_OnlineResource()
{
    // Create a unique pointer r that owns an Online Resource Object
    auto r = std::make_unique<OnlineResource>();
     // ------------------------------------------------------
    //  Step 01 : Generate A Unique ID : OR-(id)
     // ------------------------------------------------------

    int maxID = 0;
    for (const auto &res : Online)
    {
        try
        {
            std::string rID= res->getResourceID(); // returns a string "OR-x"
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
    r->setResourceID("OR-"+ std::to_string(maxID + 1));   // Assign next ID as "OR-x"
    std::cout<<"\t\t New Resource ID : "<<r->getResourceID()<<std::endl;

     // ------------------------------------------------------
    //      Step 02 : Enter Resource Title from User 
     // ------------------------------------------------------

    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\t\t Enter Resource Title: ";
    std::getline(std::cin, input);

     if (input.empty())
    {
        std::cout << "\t\t | Invalid title. |\n";
        return;
    }
    r->setResourceTitle(input);

     // ------------------------------------------------------
    //  Step 03 : Input Author Name from User
    // ------------------------------------------------------
    std::cout << "\t\t Enter Author Name: ";
    std::getline(std::cin, input);

    if (input.empty())
    {
        std::cout << "\t\t | Invalid author name. |\n";
        return;
    }

    r->setResourceAuthor(input);

    // ------------------------------------------------------
    //  Step 04 : Input Publication Date from User
    // ------------------------------------------------------
    Date d;
    std::cout<<"\t\t Enter Publication Date:  "<<std::endl;
    d.setDate();  // Inputs and Validates Date inside itself
    r->setPublicationDate(d);

    // Clear any leftover newline after date input before using getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // ------------------------------------------------------
    //  Step 05 : Set Availability 
    // ------------------------------------------------------
    
    r->SetAvailability(true);

    // ------------------------------------------------------
    // Step 06 : Input Genre from User
    // ------------------------------------------------------
   
    std::cout << "\t\t Enter Genre: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "\t\t | Invalid genre. |\n";
        return;
    }
    r->setGenre(input);


    // ------------------------------------------------------
    //   Step 07: Input Resource Type from User
    // ------------------------------------------------------

    std::cout << "\t\t Enter Resource Type: ";
    std::getline(std::cin, input);
    if (input.empty())
    {
        std::cout << "\t\t | Invalid resource type. |\n";
        return;
    }
    r->setResourceType(input);

    // ------------------------------------------------------
    //   Step 08 : Save the resource into the vector
    // ------------------------------------------------------
    Online.push_back(std::move(r)); 
    // move(unique ptr) transfers ownership of the resource object from pointer r to the Online vector of pointers

    OnlineStore.saveAllOnlineResources(Online);

}
// ------------------------------------------------------
// Remove Online Resource
// ------------------------------------------------------
void Online_Resource_Manager::remove_OnlineResource( std::string rID )
{
        for (auto it = Online.begin(); it != Online.end(); ++it)
        {
                if ((*it)->getResourceID() == rID)
                {
                        Online.erase(it);
                        OnlineStore.saveAllOnlineResources(Online);
                         std::cout << "\t\t | Resource with ID " << rID << " Deleted Successfully. | \n";
                        return;
                }
        }

        std::cout << "\t\t | Resource with ID " << rID << " does not exist. | \n";
}
// ------------------------------------------------------
// Display Single Online Resource
// ------------------------------------------------------
void Online_Resource_Manager::display_OnlineResource(std::string rID)
{
    OnlineResource* r = searchByID (rID);
    if (r != nullptr)
        {
            std::cout << "\n\t\t -------------- RESOURCE DETAILS -------------- \n";
            std::cout << "\t\t ID               : " << r->getResourceID() << '\n';
            std::cout << "\t\t Title            : " << r->getTitle() << '\n';
            std::cout << "\t\t Author           : " << r->getAuthor() << '\n';
            std::cout << "\t\t Genre            : " << r->getGenre() << '\n';
            std::cout << "\t\t Type             : " << r->getResourceType() << '\n';
            std::cout << "\t\t Availability     : " << (r->getAvailabilityStatus() ? "Yes" : "No") << '\n';
            std::cout << "\t\t Publication Date : " << r->getPublicationDate() << '\n';
            std::cout << "\t\t Access Charge    : " << r->getAccessCharge() << "/-";
            std::cout << "\n\t\t ---------------------------------------------- \n";
            return;
        }
    else    
    std::cout << "\t\t | Resource with ID " << rID << " does not exist. | \n";
}

void Online_Resource_Manager::display_OnlineResource_tabular(const OnlineResource* r) const
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
              << std::setw(32) << r->getTitle()
              << std::setw(20) << r->getAuthor()
              << std::setw(15) << date
              << std::setw(13) << (r->getAvailabilityStatus() ? "Yes" : "No")
              << std::setw(10) << r->getResourceType()
              << std::setw(15) << r->getGenre()
              << std::endl;
}
// ------------------------------------------------------
// Display All Online Resources
// ------------------------------------------------------
void Online_Resource_Manager::displayAll_OnlineResources()
{
   Online=OnlineStore.loadAllOnlineResources();
    std::cout << std::left;

    printOnlineHeader();

    // Print each resource
    for (const auto &r : Online)
    {
        display_OnlineResource_tabular(r.get());
    }
    std::cout<<std::string(125 , '-')<<std::endl;
}

void Online_Resource_Manager::searchByTitle(const std::string& title)
{
    std::string target = title;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    bool found = false;
    for (const auto &r : Online)
    {
        std::string current = r->getTitle();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        if (current == target)
        {
           display_OnlineResource(r->getResourceID());
            found = true;
            return;
        }
    }

    if (!found)
    {
        std::cout << "\t\t | Resource Not Found In The System. |\n";
    }
}

void Online_Resource_Manager::searchByAuthor(const std::string& author)
{
    std::string target = author;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    bool found = false;
    for (const auto &r : Online)
    {
        std::string current = r->getAuthor();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        if (current == target)
        {
            display_OnlineResource(r->getResourceID());
            found = true;
            return;
        }
    }

    if (!found)
    {
        std::cout << "\t\t | Resource Not Found In The System. |\n";
    }
}

void Online_Resource_Manager::searchByGenre(const std::string& genre)
{
    std::string target = genre;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    bool found = false;
    for (const auto &r : Online)
    {
        std::string current = r->getGenre();
        std::transform(current.begin(), current.end(), current.begin(), ::tolower);
        if (current == target)
        {
            
            if(found==false)
            printOnlineHeader();
            display_OnlineResource_tabular(r.get());
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "\t\t | Resource Not Found In The System. |\n";
    }
}

void Online_Resource_Manager::searchByAvailability(bool available)
{
    bool found = false;

    for (const auto &r : Online)
    {
        if (r->getAvailabilityStatus() == available)
        {
            if(found==false)
            printOnlineHeader();
            display_OnlineResource_tabular(r.get());
            found = true;
        }
    }

    if (!found)
    {
        std::cout << "\t\t | Resource Not Found In The System. |\n";
    }
    else
    std::cout<<std::string(125 , '-')<<std::endl;
}

OnlineResource* Online_Resource_Manager::searchByID(const std::string& rID)
{
    Online = OnlineStore.loadAllOnlineResources();

    for (auto &r : Online)
    {
        if (r->getResourceID() == rID)
        {
            return r.get();
        }
    }

    return nullptr;
}

double Online_Resource_Manager::updateResource(BorrowRecord &record)
{
    Online = OnlineStore.loadAllOnlineResources();

    for (const auto &resource : Online)
    {
        if (resource != nullptr && resource->getResourceID() == record.getResourceID())
        {
            double refundAmount = resource->applyReturnPolicy(record);
            return refundAmount;
        }
    }

    std::cout << "\t\t | Online resource not found for this borrow record. |\n";
    return 0.0;
}