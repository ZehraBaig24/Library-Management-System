#include "OnlineResource.hpp"

// ============================================================
// Online Resource Logic
// ============================================================
const int OnlineResource::totalAccessDays=14;

double OnlineResource::getAccessCharge() const { return accessCharge_; }
double OnlineResource::applyReturnPolicy(BorrowRecord &record)
{
    this->markReturned();
    const double refund = OnlineResource::calculateAccessCharge(record);
    return refund;
}

double OnlineResource::calculateAccessCharge(BorrowRecord &record)
{
    int usedDays = record.getReturnDate().getTotalDays() - record.getIssueDate().getTotalDays();

    if (usedDays < 0)
    {
        usedDays = 0;
    }

    int remainingDays = totalAccessDays - usedDays;

    if (remainingDays <= 0)
    {
        return 0.0;
    }

    const double refund = remainingDays * this->getAccessCharge();
    return refund;
}
