#ifndef LIBRARYRESOURCE_HPP
#define LIBRARYRESOURCE_HPP


#include "BorrowRecord.hpp"
#include "Date.hpp"

#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>


// Forward declarations
class Member;
class PhysicalResource;
class OnlineResource;
class User;


// ============================================================
// ENUM : GENRE
//
// Represents category/genre of library resource
// ============================================================
enum class Genre
{
	Literature,
	Science,
	Arts,
	Education,
	Technology,
	Unknown
};


// ============================================================
// ENUM : RESOURCE TYPE
//
// Represents type/category of resource
// ============================================================
enum class ResourceType
{
	Book,
	Reference,
	Multimedia,
	Journal,
	GreyLiterature,
	Unknown
};



// ============================================================
//                BASE CLASS : LibraryResource
// ============================================================
//
// Abstract base class for all resources.
//
// Parent class of:
//   - OnlineResource
//   - PhysicalResource
//
// Stores common data:
//
//   - title
//   - author
//   - publication date
//   - availability
//   - resource ID
//   - genre
//   - type
// ============================================================
class LibraryResource
{
protected:

	// ========================================================
	// Resource title
	// ========================================================
	std::string title_;


	// ========================================================
	// Resource author
	// ========================================================
	std::string author_;


	// ========================================================
	// Publication date
	// ========================================================
	Date publicationDate_;


	// ========================================================
	// Availability status
	//
	// true  -> available
	// false -> issued/unavailable
	// ========================================================
	bool availabilityStatus_;


	// ========================================================
	// Unique resource ID
	// ========================================================
	std::string resourceID_;


	// ========================================================
	// Resource type
	// ========================================================
	ResourceType resourceType_;


	// ========================================================
	// Resource genre
	// ========================================================
	Genre genre_;

public:

	// ========================================================
	// Default Constructor
	// ========================================================
	LibraryResource();

	// ========================================================
	// Getter Functions
	// ========================================================
	bool getAvailabilityStatus() const;

	std::string getTitle() const;

	std::string getAuthor() const;

	std::string getResourceID() const;

	std::string getResourceType() const;

	std::string getGenre() const;

	Date& getPublicationDate();

	const Date& getPublicationDate() const;


	// ========================================================
	// Setter Functions
	// ========================================================
	void setResourceID(
		const std::string &resourceID);

	void setResourceTitle(
		const std::string &resourcetitle);

	void setResourceAuthor(
		const std::string &resourceAuthor);

	void setPublicationDate(
		const Date &d);

	void setGenre(
		std::string genre);

	void setResourceType(
		std::string resourcetype);

	void SetAvailability(
		bool available);


	// ========================================================
	// Marks resource as issued/unavailable
	// ========================================================
	void markIssued();


	// ========================================================
	// Marks resource as returned/available
	// ========================================================
	void markReturned();


	// ========================================================
	// PURE VIRTUAL FUNCTION
	//
	// Different for:
	//   - online resources
	//   - physical resources
	//
	// Makes LibraryResource an abstract class
	// ========================================================
	virtual double applyReturnPolicy(
		BorrowRecord &record) = 0;


	// ========================================================
	// Virtual Destructor
	// ========================================================
	virtual ~LibraryResource() = default;
};

#endif
