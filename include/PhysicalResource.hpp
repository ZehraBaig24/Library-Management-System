#ifndef PHYSICALRESOURCE_HPP
#define PHYSICALRESOURCE_HPP

#include <string>
#include "LibraryResource.hpp"
#include "BorrowRecord.hpp"
#include "Date.hpp"

#include <iostream>
#include <cstring>
#include <algorithm>

// Forward declarations
class Member;
class UserManagement;

// ============================================================
//            DERIVED CLASS : PhysicalResource
// ============================================================
//
// Represents physical library resources.
//
// Adds:
//   - late fine system
//   - damage charge system
// ============================================================

class PhysicalResource : public LibraryResource
{
private:

	// ========================================================
	// Fine charged per late day
	// ========================================================
	const double dailyFineRate_;


	// ========================================================
	// Fixed damage charge
	// ========================================================
	const double damageCharge_;

public:

	// ========================================================
	// Maximum capacity for resource storage
	// ========================================================
	static const int MAX_CAPACITY = 1000;

	// ========================================================
	// Default Constructor
	// ========================================================
	PhysicalResource();

	// ========================================================
	// Returns daily fine rate
	// ========================================================
	double getDailyFineRate() const;


	// ========================================================
	// Returns damage charge
	// ========================================================
	double getDamageCharge() const;


	// ========================================================
	// Calculates fine for overdue return
	// ========================================================
	double calculateLateFine(
		BorrowRecord &record) const;


	// ========================================================
	// Calculates damage charge
	//
	// Parameter:
	//   condition -> resource condition
	// ========================================================
	double calculateDamageCharge(
		const std::string &condition) const;


	// ========================================================
	// Applies physical return policy
	// ========================================================
	double applyReturnPolicy(
		BorrowRecord &record) override;


	// ========================================================
	// Destructor
	// ========================================================
	~PhysicalResource() = default;
};
#endif
