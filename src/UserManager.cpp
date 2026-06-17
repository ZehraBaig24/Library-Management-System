#include "UserManager.hpp"

User_Manager::User_Manager()
    : admin_("admin", "admin123", "Admin", "User"),
    memberStore_("members.txt")
{
    memberStore_.loadAllMembers(members_);
}

User_Manager::~User_Manager()
{
    memberStore_.saveAllMembers(members_);
}

void User_Manager::addMember(Member member)
{
     // Store in vector
    members_.push_back(member);
    members_.back().createAccount();
    memberStore_.saveAllMembers(members_);
}

void User_Manager::saveMembers()
{
    memberStore_.saveAllMembers(members_);
}
void User_Manager::removeMember(int userId)
{
   for (size_t i = 0; i < members_.size(); i++)
    {
        if (members_[i].getUserId() == userId)
        {
            members_.erase(members_.begin() + i);
            cout << "Member removed successfully!\n";
            memberStore_.saveAllMembers(members_);
            return;
        }
    }

    cout << "\t\t | Member not found. | \n";
}
void User_Manager::updateMember(int userId)
{
    for (size_t i = 0; i < members_.size(); i++)
    {
        if (members_[i].getUserId() == userId)
        {
            string first, last, address;

            cout << "\t\t Enter new first name: ";
            cin >> first;

            cout << "\t\t Enter new last name: ";
            cin >> last;

            cin.ignore();

            cout << "\t\t Enter new address: ";
            getline(cin, address);

            members_[i].setFirstName(first);
            members_[i].setLastName(last);
            members_[i].setAddress(address);

            memberStore_.saveAllMembers(members_);
            cout << "\t\t----- Member updated successfully! -----\n";
            return;
        }
    }

    cout << "\t\t | Member not found. | \n";
}



Member* User_Manager::login(const string &username,const string &password)
{
    for (size_t i = 0; i < members_.size(); i++)
    {
        if (members_[i].getUsername() == username &&
            members_[i].verifyPassword(password))
        {
            cout << "\t\t| Member '" << members_[i].getUsername()
                 << "' logged in. Welcome, " << members_[i].getFirstName() << "! |" << endl;
            return &members_[i];
        }
    }

    return nullptr;
}

void User_Manager::displayAllMembers() const
{
    if (members_.empty())
    {
        cout << "No members found.\n";
        return;
    }

    cout << "\n===== All Members =====\n";

    for (size_t i = 0; i < members_.size(); i++)
    {
        cout << "Member ID: "
             << members_[i].getUserId() << endl;

        cout << "Name: "
             << members_[i].getFirstName()
             << " "
             << members_[i].getLastName() << endl;

        cout << "Username: "
             << members_[i].getUsername() << endl;

        cout << "Balance: "
             << members_[i].getUserBalance() << endl;

        cout << "--------------------------\n";
    }
}

void User_Manager::displayMember(const Member* member)
{
    if (member == nullptr) {
        cout << "No member selected.\n";
        return;
    }

    cout << "\n\t\t------ Member Details ------\n";
    cout << "\t\t Member ID: " << member->getUserId() << endl;
    cout << "\t\t Name: " << member->getFirstName() << " " << member->getLastName() << endl;
    cout << "\t\t Username: " << member->getUsername() << endl;
    cout << "\t\t Balance: " << member->getUserBalance() << endl;
    cout << "\t\t Address: " << member->getAddress() << endl;
    cout << "\t\t Current Borrows: " << member->getBorrowCount() << endl;
    cout << "\t\t----------------------------\n";
}

Administrator* User_Manager::adminLogin(const string &username,const string &password)
{
    if (admin_.getUsername() == username &&
        admin_.verifyPassword(password))
    {
        cout << "\t  | "<<admin_.getFirstName() << " " << admin_.getLastName()
             << " logged in. Welcome, Administrator! | \n";
        return &admin_;
    }
    return nullptr;
}

Member* User_Manager::getMemberById(int userId)
{
    for (size_t i = 0; i < members_.size(); ++i)
    {
        if (members_[i].getUserId() == userId)
            return &members_[i];
    }
    return nullptr;
}
