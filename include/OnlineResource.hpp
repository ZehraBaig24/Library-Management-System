
#ifndef ONLINERESOURCE_HPP
#define ONLINERESOURCE_HPP

#include <string>
#include <iostream>
#include <cstring>

#include "BorrowRecord.hpp"
#include "Date.hpp"
#include "LibraryResource.hpp"

// Forward declarations
class Member;
class OnlineManager;
class PhysicalManager;

// ============================================================
//              DERIVED CLASS : OnlineResource
// ============================================================
//
// Represents digital/online resources.
//
// Adds:
//   - access charges
//   - borrow restrictions
// ============================================================

class OnlineResource : public LibraryResource
{
private:

	// ========================================================
	// Cost charged when accessing resource
	// ========================================================
	const double accessCharge_;
	static const int totalAccessDays;

public:

	// ========================================================
	// Default Constructor
	// ========================================================
	OnlineResource();


	// ========================================================
	// Returns access charge
	// ========================================================
	double getAccessCharge() const;


	// ========================================================
	// Deducts access charge from member balance
	// ========================================================
	double calculateAccessCharge(BorrowRecord &record);


	// ========================================================
	// Applies online return policy
	// ========================================================
	double applyReturnPolicy(
		BorrowRecord &record) override;


	// ========================================================
	// Destructor
	// ========================================================
	~OnlineResource() = default;
};

#endif
