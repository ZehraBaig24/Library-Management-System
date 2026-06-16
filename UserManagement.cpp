#include "UserManagement.hpp"
#include "UserManager.hpp"
#include "OnlineManager.hpp"
#include "PhysicalManager.hpp"
#include "BorrowRecordManager.hpp"

// ============================================================
//  USER— Implementation
// ============================================================

User::User() : username_(""), password_(""), firstName_(""), lastName_("")
{
}
User::User(const string &username, const string &password, const string &firstName, const string &lastName) 
: username_(username), password_(password), firstName_(firstName), lastName_(lastName)
{
}
string User::getUsername() const
{
    return username_;
}
string User::getPassword() const
{
    return password_;
}

string User::getFirstName() const
{
    return firstName_;
}

string User::getLastName() const
{
    return lastName_;
}

void User::setUsername(const string &username)
{
    if (username.empty())
        throw invalid_argument("\t\t | Username cannot be empty. |\n");
    username_ = username;
}

void User::setFirstName(const string &firstName)
{
    if (firstName.empty())
        throw invalid_argument("| First name cannot be empty. |\n");
    firstName_ = firstName;
}

void User::setLastName(const string &lastName)
{
    if (lastName.empty())
        throw invalid_argument("| Last name cannot be empty. |\n");
    lastName_ = lastName;
}

void User::setPassword(const string &password)
{
    if (password.size() < 6)
        throw invalid_argument("| Password must be atleast 6 characters. |\n");
    password_ = password;
}

bool User::verifyPassword(const string &inputPassword) const
{
    return (inputPassword == password_);
}

void User::updatePassword()
{
    string oldPass, newPass, confirmPass;

    cout << "\t\t Enter current password : " ;
    cin >> oldPass;

    if (!verifyPassword(oldPass))
    {
        cout << "\t\t | Incorrect current password | " << endl;
        return;
    }

    cout << "\t\t Enter the new password(min 6 characters) : " ;  cin >> newPass;
    cout << "\t\t Confirm new password: ";
    cin >> confirmPass;

    if (newPass != confirmPass)
    {
        cout << "\t\t | Passwords do not match. |" << endl;
        return;
    }

    try
    {
        setPassword(newPass);
        cout << "\t\t ----- Password updated successfully.------" << endl;
    }

    catch (const invalid_argument &e)
    {
        cout << "Error: " << e.what() << endl;
    }
}

// ============================================================
//  MEMBER — Implementation
// ============================================================

int Member::idCount_ = 0;

Member::Member() : User(), userId_(++idCount_), balance_(0.0), address_(""), currentBorrowCount_(0)
{
}

Member::Member(const string &username, const string &password, const string &firstName, const string &lastName, double balance, const string &address) 
: User(username, password, firstName, lastName), userId_(++idCount_), balance_(balance), address_(address), currentBorrowCount_(0)
{
}

// ----- Getters -----
int Member::getUserId() const
{
    return userId_;
}

double Member::getUserBalance() const
{
    return balance_;
}

int Member::getBorrowCount() const
{
    return currentBorrowCount_;
}

string Member::getAddress() const
{
    return address_;
}

int Member::getIdCount()
{
    return idCount_;
}

// ----- Setters -----
void Member::setBorrowCount(int currentBorrowCount)
{
    if (currentBorrowCount < 0)
        throw invalid_argument("\t\t | Borrow count cannot be negative. |\n");
    currentBorrowCount_ = currentBorrowCount;
}

void Member::setBalance(double balance)
{
    if (balance < 0.0)
        throw invalid_argument("\t\t | Balance cannot be negative. |\n");
    balance_ = balance;
}

void Member::setAddress(const string &address)
{
    if (address.empty())
        throw invalid_argument("\t\t | Address cannot be empty. |\n");
    address_ = address;
}

void Member::createAccount() 
{

    if (address_.empty())
    {
        cout << "\t\t Enter your address: ";
        cin.ignore();
        getline(cin, address_);
    }

    if (balance_ <= 0.0)
    {
        cout << "\t\t Enter initial account balance: RS.";
        cin >> balance_;
        if (cin.fail() || balance_ < 0.0)
        {
            cin.clear();
            cin.ignore();
            cout << "\t\t| Invalid input, Balance set to 0. |" << endl;
            balance_ = 0.0;
        }
    }

    cout << "\t\t ---- Account created successfully! ----" << endl;
    cout << "\t\t Member ID: " << userId_ << endl;
    cout << "\t\t Name: " << firstName_ << endl;
    cout << "\t\t Username: " << username_ << endl;
    cout << "\t\t Balance: " << balance_ << endl;
    cout << "\t\t Address: " << address_ << endl;
}

bool Member::canBorrow() const // ----- Private Helper -----
{
    // Returns true if member is under the borrow limit
    return (currentBorrowCount_ < maxBorrowLimit_);
}

void Member::borrowOnlineResource(const string &resourceId,
                                           Online_Resource_Manager& onlineMgr,
                                           Borrow_Record_Manager& borrowMgr)
{
    // --- Step 1: Validate resource ID ---
    if (resourceId.empty())
    {
        cout << "Error:  resource ID cannot be empty.\n";
        return;
    }

    // --- Step 2: Check borrow limit ---
    if (!canBorrow())
    {
        cout << "Error: Maximum borrow limit reached! (" << maxBorrowLimit_ << ").\n";
        return;
    }

    if(resourceId.substr(0, 2) == "OR"){
    
        OnlineResource* resource = onlineMgr.searchByID(resourceId);
    
        // --- Step 3: Check if resource is found ---
        if (resource == nullptr)
        {
            cout << "Invalid ID! No Online Resource with ID " << resourceId << " is available." << endl;
            return;
        }
        
        // --- Step 4: Check if balance is sufficient ---
        if(getUserBalance() <= resource->getAccessCharge() * resourceAccessDays_){
            cout << "Insufficient balance for this resource." << endl;
            return;
        }
    
     // --- Step 5: Check if resource is available ---
    if (!resource->getAvailabilityStatus())
    {
        cout << "Resource " << resource->getTitle()
             << " is currently unavailable." << endl;
        return;
    }
    
    // --- Step 5: Mark resource as issued ---
    resource->markIssued();

    // --- Step 6: Create the BorrowRecord ---
    Date today = Date::today();
    Date dueDate = today + resourceAccessDays_;

    BorrowRecord record(userId_, resourceId, today, dueDate, Date(), false);

    // --- Step 7: Persist using the shared borrow-record manager ---
    borrowMgr.addBorrowRecord(record);
    ++currentBorrowCount_;
    
    cout
        << "\t Borrowed: " << resource->getTitle() << " successfully!"
        << "  |  Borrow ID: " << record.getBorrowID() << "  |  Current borrows: " 
        << currentBorrowCount_ << endl;
    updateBalance(-(resource->getAccessCharge() * resourceAccessDays_));
    }
    else
    {
    cout<<"Invalid Online Resource ID!\n"
        <<"Try searching in Physical Resources for IDs starting with PR-xx."<<endl;
    return;
    }
}

bool Member::returnOnlineResource(int borrowId,
                                  Borrow_Record_Manager& borrowMgr,
                                  Online_Resource_Manager& onlineMgr)
{
    try{
        const BorrowRecord& cur = borrowMgr.updateBorrowRecord(borrowId); //current updated Borrow Record is received
        BorrowRecord curCopy = cur; // mutable copy for updateResource
    
        if (cur.getResourceID().substr(0, 2) == "OR"){
            double refundAmount = onlineMgr.updateResource(curCopy);
            updateBalance(refundAmount);
        }
        if (currentBorrowCount_ > 0)
            {
                --currentBorrowCount_;
            }
            cout << "Resource returned successfully." << "  |  Borrow ID: " << borrowId
                 << "  |  Currently Issued Resources are: " << currentBorrowCount_ << endl;
            return true;
    }
    catch(const string &e){
        cerr<<e<<endl;
    }
    return false;
}

void Member::updateBalance(double amount)
{
    // Positive amount  = deposit/top-up
    // Negative amount  = fine/charge deduction

    if(amount==0)
    return;
    
    double newBalance = balance_ + amount;

    if (newBalance < 0.0)
    {
        cout << "Insufficient balance for this transaction.\n"
             << " Current balance: RS." << balance_ << "\n"
             << " Charge          : RS." << -amount << endl;
        return;
    }

    balance_ = newBalance;
    cout << "Balance updated."
         << "  |  " << (amount >= 0 ? "Deposit" : "Charge")
         << ": RS." << (amount >= 0 ? amount : -amount)
         << "  |  New balance: RS." << balance_ << "\n";
}

BorrowRecord* Member::viewBorrowHistory()
{
    Borrow_Record_Manager borrowMgr;
    borrowMgr.DisplayBorrowRecord(userId_);
    return nullptr;
}


// ============================================================
//  ADMINISTRATOR — Implementation
// ============================================================

Administrator::Administrator()
    : User()
{
}

Administrator::Administrator(const string &username, const string &password, const string &firstName, const string &lastName)
             : User(username, password, firstName, lastName)
{
}

void Administrator::issuePhysicalResource(const string &resourceId,
                                          int memberId,
                                          User_Manager& userMgr,
                                          Physical_Resource_Manager& physMgr,
                                          Borrow_Record_Manager& borrowMgr)
{
    Member* member = userMgr.getMemberById(memberId);
    if (member == nullptr)
    {
        cout << "Member ID not found." << endl;
        return;
    }

    // Check borrow limit
    if (!member->canBorrow())
    {
        cout << "Member has reached maximum borrow limit." << endl;
        return;
    }

    PhysicalResource* resource = physMgr.searchByID(resourceId);
    if (resource == nullptr)
    {
        cout << "Physical resource with ID " << resourceId << " not found." << endl;
        return;
    }

    if (!resource->getAvailabilityStatus())
    {
        cout << "Resource " << resource->getTitle() << " is currently unavailable." << endl;
        return;
    }

    // Mark as issued
    resource->markIssued();

    // Create borrow record (no balance check for physical issuance)
    Date today = Date::today();
    // Physical resources use the standard resource access days (2 days)
    Date dueDate = today + 2;

    BorrowRecord record(memberId, resourceId, today, dueDate, Date(), false);
    borrowMgr.addBorrowRecord(record);

    // Update member borrow count
    member->setBorrowCount(member->getBorrowCount() + 1);
    userMgr.saveMembers();

    // Persist resource availability
    ;

    cout << "Resource with ID: " << resourceId << " issued successfully to Member ID: " << memberId << endl;
}

void Administrator::processReturnOfPhysicalResouce(int borrowId,
                                                   Borrow_Record_Manager& borrowMgr,
                                                   Physical_Resource_Manager& physMgr)
{
    try{
        const BorrowRecord& cur = borrowMgr.updateBorrowRecord(borrowId); //current updated Borrow Record is received
        BorrowRecord curCopy = cur; // mutable copy for updateResource
        
        if(cur.getResourceID().substr(0, 2) == "PR")  
        {
            double charges = physMgr.updateResource(curCopy);
            cout << "Charges applied: RS." << charges << endl;
        }  
    }
    catch(const string &e){
        cerr<<e<<endl;
    }
}
