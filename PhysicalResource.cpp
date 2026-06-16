#include "PhysicalResource.hpp"

// ============================================================
// Physical Resource Logic
// ============================================================

double PhysicalResource::getDailyFineRate() const { return dailyFineRate_; }
double PhysicalResource::getDamageCharge() const { return damageCharge_; }

double PhysicalResource::calculateLateFine(BorrowRecord &record) const
{
    int overdueDays =
        record.getReturnDate().getTotalDays() -
        record.getDueDate().getTotalDays();

    if (overdueDays <= 0)
        return 0.0;

    return overdueDays * dailyFineRate_;
}

double PhysicalResource::calculateDamageCharge(const std::string &condition) const
{
    std::string c = condition;
    std::transform(c.begin(), c.end(), c.begin(), ::tolower); 

    if (c == "perfect") return 0.0;
    if (c == "damaged") return damageCharge_;

    return 0.0;
}

double PhysicalResource::applyReturnPolicy(BorrowRecord &record)
{
    this->markReturned();
    double lateFine = calculateLateFine(record);
    std::string condition;
    std::cout << "Condition (perfect/damaged): ";
    std::cin >> condition;
    double damageCharge = calculateDamageCharge(condition);
    double total = lateFine + damageCharge;
    if (total <= 0)
    {
        std::cout << "No charges applied.\n";
        return 0.0;
    }
    return total;
}