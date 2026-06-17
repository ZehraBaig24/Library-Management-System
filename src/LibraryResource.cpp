#include "LibraryResource.hpp"
#include "PhysicalResource.hpp"
#include "OnlineResource.hpp"

// ============================================================
// Constructors
// ============================================================

LibraryResource::LibraryResource()
    : title_(""), author_(""), publicationDate_(),
      availabilityStatus_(false),
      resourceID_(""),
      resourceType_(ResourceType::Unknown),
      genre_(Genre::Unknown) {}


PhysicalResource::PhysicalResource()
    : LibraryResource(), dailyFineRate_(500), damageCharge_(5000) {}

OnlineResource::OnlineResource()
    : LibraryResource(), accessCharge_(100) {}


// ============================================================
// Setters
// ============================================================

void LibraryResource::setResourceID(const std::string &resourceID)
{
    resourceID_ = resourceID;
}

void LibraryResource::setResourceTitle(const std::string &resourcetitle)
{
    title_ = resourcetitle;
}

void LibraryResource::setResourceAuthor(const std::string &resourceAuthor)
{
    author_ = resourceAuthor;
}

void LibraryResource::setPublicationDate(const Date &d)
{
    publicationDate_ = d;
}

void LibraryResource::SetAvailability(bool available)
{
    availabilityStatus_ = available;
}

// Convert string → enum (genre)
void LibraryResource::setGenre(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  
    if (input == "literature") genre_ = Genre::Literature;
    else if (input == "science") genre_ = Genre::Science;
    else if (input == "arts") genre_ = Genre::Arts;
    else if (input == "education") genre_ = Genre::Education;
    else if (input == "technology") genre_ = Genre::Technology;
    else genre_ = Genre::Unknown;
}

// Convert string → enum (resource type)
void LibraryResource::setResourceType(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    if (input == "book") resourceType_ = ResourceType::Book;
    else if (input == "reference") resourceType_ = ResourceType::Reference;
    else if (input == "multimedia") resourceType_ = ResourceType::Multimedia;
    else if (input == "journal") resourceType_ = ResourceType::Journal;
    else if (input == "greyliterature") resourceType_ = ResourceType::GreyLiterature;
    else resourceType_ = ResourceType::Unknown;
}

// ============================================================
// Status Control
// ============================================================

void LibraryResource::markIssued()
{
    if (!availabilityStatus_)
    {
        return;
    }
    availabilityStatus_ = false;
}

void LibraryResource::markReturned()
{
    if (availabilityStatus_)
    {
        return;
    }
    availabilityStatus_ = true;
}

// ============================================================
// Getters
// ============================================================

std::string LibraryResource::getResourceID() const { return resourceID_; }
std::string LibraryResource::getTitle() const { return title_; }
std::string LibraryResource::getAuthor() const { return author_; }
bool LibraryResource::getAvailabilityStatus() const { return availabilityStatus_; }

Date& LibraryResource::getPublicationDate() { return publicationDate_; }
const Date& LibraryResource::getPublicationDate() const { return publicationDate_; }



// ============================================================
// Enum → String
// ============================================================
std::string LibraryResource::getGenre() const
{
    switch (genre_)
    {
    case Genre::Literature: return "Literature";
    case Genre::Science: return "Science";
    case Genre::Arts: return "Arts";
    case Genre::Education: return "Education";
    case Genre::Technology: return "Technology";
    default: return "Unknown";
    }
}

std::string LibraryResource::getResourceType() const
{
    switch (resourceType_)
    {
    case ResourceType::Book: return "Book";
    case ResourceType::Reference: return "Reference";
    case ResourceType::Multimedia: return "Multimedia";
    case ResourceType::Journal: return "Journal";
    case ResourceType::GreyLiterature: return "Grey Literature";
    default: return "Unknown";
    }
}
