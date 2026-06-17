#include "lms.hpp"

namespace {

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid numeric input. Please try again.\n";
    }
}

double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid numeric input. Please try again.\n";
    }
}

std::string readWord(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

std::string readLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, value);
    return value;
}

std::string readResourceId(const std::string& prompt) {
    std::string id;
    bool validFormat = false;
    while (!validFormat) {
        std::cout << prompt;
        std::cin >> id;
        if (id.length() >= 2 && (id.substr(0, 2) == "PR" || id.substr(0, 2) == "OR")) {
            validFormat = true;
        } else {
            std::cout << "Invalid ID format. Must start with 'PR' (Physical) or 'OR' (Online).\n";
        }
    }
    return id;
}

Member buildMemberFromInput() {
    const std::string username = readWord("\t\t Enter username: ");
    const std::string password = readWord("\t\t Enter password: ");
    const std::string firstName = readWord("\t\t Enter first name: ");
    const std::string lastName = readWord("\t\t Enter last name: ");
    const double balance = readDouble("\t\t Enter initial balance: ");
    const std::string address = readLine("\t\t Enter address: ");

    return Member(username, password, firstName, lastName, balance, address);
}

void showMainMenu() {
    std::cout << "\n================ WELCOME TO HYBRID LIBRARY MANAGEMENT SYSTEM ================\n";
    std::cout << "\n\t \033[3m  \" Nothing Is Pleasanter Than Exploring A Library \033[0m \"  "<<endl;
    std::cout << "\t\t\t\t\t\t- Walter Savage Landor"<<endl; 
    std::cout << "1. Member Login\n";
    std::cout << "2. Create Member Account\n";
    std::cout << "3. Admin Login\n";
    std::cout << "0. Exit\n";
    std::cout << "==============================================================================\n";
}

void showMemberMenu(const Member* member) {
    std::cout << "\n================================ MEMBER MENU ================================\n";
    std::cout << "\n\t \033[3m  \" A Reader Lives A Thousand Lives Before He Dies , \033[0m " <<endl;
    std::cout << "\t\t \033[3m A Man Who Never Reads Lives Only One. \" \033[m "<<endl;
    std::cout << "\t\t\t\t\t\t- George R. R. Martin"<<endl; 
    if (member != nullptr) {
        std::cout << "Welcome " << member->getFirstName() << " " << member->getLastName() << "\n";
    }
    std::cout << "1. Manage My Account\n";
    std::cout << "2. Physical Resource Interface\n";
    std::cout << "3. Online Resource Interface\n";
    std::cout << "0. Logout\n";
    std::cout << "==============================================================================\n";
}

void showMemberAccountMenu() {
    std::cout << "\n============================== MANAGE MY ACCOUNT =============================\n";
    std::cout << "1. Update Personal Details\n";
    std::cout << "2. Update Balance (Deposit)\n";
    std::cout << "3. Update Password\n";
    std::cout << "4. View Borrow History\n";
    std::cout << "0. Back\n";
    std::cout << "==============================================================================\n";
}

void showPhysicalMenu() {
    std::cout << "\n========================== PHYSICAL RESOURCE MENU ==========================\n";
    std::cout << "1. Search Physical Resource by ID\n"; 
    std::cout << "2. Search Physical Resource by Title\n";
    std::cout << "3. Search Physical Resource by Author\n";
    std::cout << "4. Search Physical Resource by Genre\n";
    std::cout << "5. View All Available Physical Resources\n";
    std::cout << "6. View All Physical Resources\n";
    std::cout << "0. Back\n";
    std::cout << "===============================================================================\n";
}

void showOnlineMenu() {
    std::cout << "\n========================== ONLINE RESOURCE MENU ===========================\n";
    std::cout << "1. Borrow Resource\n";
    std::cout << "2. Return Resource\n";
    std::cout << "3. Search Online Resource by ID\n";
    std::cout << "4. Search Online Resource by Title\n";
    std::cout << "5. Search Online Resource by Author\n";
    std::cout << "6. Search Online Resource by Genre\n";
    std::cout << "7. View All Available Resources\n";
    std::cout << "8. View All Online Resources\n";
    std::cout << "0. Back\n";
    std::cout << "==============================================================================\n";
}
}

void showAdminMenu() {
    std::cout << "\n=============================== ADMIN MENU ===============================\n";
    std::cout << "1. Add Physical Resource\n";
    std::cout << "2. Add Online Resource\n";
    std::cout << "3. Issue Physical Resource\n";
    std::cout << "4. Process Return of Physical Resource\n";
    std::cout << "5. Remove Physical Resource\n";
    std::cout << "6. Remove Online Resource\n";
    std::cout << "7. Generate Reports\n";
    std::cout << "0. Logout\n";
    std::cout << "==============================================================================\n";
}

void showReportGeneratorMenu() {
    std::cout << "\n============================ REPORT GENERATOR =============================\n";
    std::cout << "1. Print All Customers' Borrow History Report\n";
    std::cout << "2. Print Currently Issued Physical Resources' Report\n";
    std::cout << "3. Print Currently Issued Online Resources' Report\n";
    std::cout << "0. Back\n";
    std::cout << "==============================================================================\n";
    
}
 // namespace

void lms::run() {
    bool running = true;

    while (running) {
        showMainMenu();
        const int mainChoice = readInt("\t\t\tSelect option: ");

        switch (mainChoice) {
            case 1: {
                std::cout << "\n\t  ------------------- Member Login -------------------\n";
                const std::string username = readWord("\t\t Enter username: ");
                const std::string password = readWord("\t\t Enter password: ");
                Member* currentMember = UserManagerDatabase.login(username, password);

                if (currentMember == nullptr) {
                    std::cout << "\t\t\t| Invalid username or password. |\n";
                    break;
                }

                bool memberSession = true;
                while (memberSession) {
                    showMemberMenu(currentMember);
                    const int memberChoice = readInt("\t\t\tSelect option: ");

                    switch (memberChoice) {
                        case 1: {
                            bool accountMenu = true;
                            UserManagerDatabase.displayMember(currentMember);
                            while (accountMenu) {
                                showMemberAccountMenu();
                                const int accountChoice = readInt("\t\t\tSelect option: ");

                                switch (accountChoice) {
                                    case 1:
                                        UserManagerDatabase.updateMember(currentMember->getUserId());
                                        UserManagerDatabase.saveMembers();
                                        break;
                                    case 2: {
                                        const double amount = readDouble("\t\t Enter amount to deposit: ");
                                        currentMember->updateBalance(amount);
                                        UserManagerDatabase.saveMembers();
                                        break;
                                    }
                                    case 3:
                                        currentMember->updatePassword();
                                        UserManagerDatabase.saveMembers();
                                           break;
                                    case 4:
                                        BorrowRecordDatabase.DisplayBorrowRecord(currentMember->getUserId());
                                        break;
                                    case 0:
                                        accountMenu = false;
                                        break;
                                    default:
                                        std::cout << "\t\t | Invalid option. Try again. |\n";
                                        break;
                                }
                            }
                            break;
                        }
                        case 2:  {
                            bool physicalMenu = true;
                            while (physicalMenu) {
                                showPhysicalMenu();
                                const int choice = readInt("\t\t\tSelect option: ");

                                switch (choice) {
                                    case 1: {
                                        const std::string resourceId = readResourceId("\t\t Enter the Resource ID to search: ");
                                        PhysicalResourceDatabase.display_PhysicalResources(resourceId);
                                        break;
                                    }
                                    case 2: {
                                        const std::string title = readLine("\t\t Enter Resource Title: ");
                                        PhysicalResourceDatabase.searchByTitle(title);
                                        break;
                                    }
                                    case 3: {
                                        const std::string author = readLine("\t\t Enter Author Name: ");
                                        PhysicalResourceDatabase.searchByAuthor(author);
                                        break;
                                    }
                                    case 4:{
                                        const std::string genre = readWord("\t\t Enter Genre: ");
                                        PhysicalResourceDatabase.searchByGenre(genre);
                                        break;
                                    }
                                    case 5:{
                                        PhysicalResourceDatabase.searchByAvailability(true);
                                        break;
                                    }
                                    case 6: {
                                        PhysicalResourceDatabase.displayAll_PhysicalResources();
                                        break;
                                    }
                                    case 0:
                                        physicalMenu = false;
                                        break;
                                    default:
                                        std::cout << "\t\t | Invalid option. Try again. |\n";
                                        break;
                                }
                            }
                            break;
                        }
                        case 3: {
                            bool onlineMenu = true;
                            while (onlineMenu) {
                                showOnlineMenu();
                                const int choice = readInt("\t\t\tSelect option: ");

                                switch (choice) {
                                    case 1: {
                                        const std::string resourceID = readResourceId("\t\t Enter the Resource ID: ");
                                        currentMember->borrowOnlineResource(resourceID, OnlineResourceDatabase, BorrowRecordDatabase);
                                        UserManagerDatabase.saveMembers();
                                        break;
                                    }
                                    case 2: {
                                        const int borrowId = readInt("\t\t Enter Borrow ID to return: ");
                                        currentMember->returnOnlineResource(borrowId, BorrowRecordDatabase, OnlineResourceDatabase);
                                        UserManagerDatabase.saveMembers();
                                        break;
                                    }
                                    case 3: {
                                        const std::string resourceId = readResourceId("\t\t Enter the Resource ID to search: ");
                                        OnlineResourceDatabase.display_OnlineResource(resourceId);
                                        break;
                                    }
                                    case 4: {
                                        const std::string title = readLine("\t\t Enter Resource Title: ");
                                        OnlineResourceDatabase.searchByTitle(title);
                                        break;
                                    }
                                    case 5: {
                                        const std::string author = readLine("\t\t Enter Author Name: ");
                                        OnlineResourceDatabase.searchByAuthor(author);
                                        break;
                                    }
                                    case 6:{
                                        const std::string genre = readWord("\t\t Enter Genre: ");
                                        OnlineResourceDatabase.searchByGenre(genre);
                                        break;                                   
                                    }
                                    case 7:{
                                        OnlineResourceDatabase.searchByAvailability(true);
                                        break;
                                    }
                                    case 8:{
                                         OnlineResourceDatabase.displayAll_OnlineResources();
                                         break;
                                    }
                                    case 0:
                                        onlineMenu = false;
                                        break;
                                    default:
                                        std::cout << "\t\t | Invalid option. Try again. |\n";
                                        break;
                                }
                            }
                            break;
                        }
                        case 0:
                            memberSession = false;
                            break;
                        default:
                            std::cout << "\t\t | Invalid option. Try again. |\n";
                            break;
                    }
                }
                break;
            }
            case 2: {
                Member newMember = buildMemberFromInput();
                UserManagerDatabase.addMember(newMember);
                break;
            }
            case 3: {
                const std::string username = readWord("\t\t Enter admin username: ");
                const std::string password = readWord("\t\t Enter admin password: ");
                Administrator* admin=UserManagerDatabase.adminLogin(username, password);

                    if (admin == nullptr) {
                        break;
                    }

                bool adminSession = true;
                while (adminSession) {
                    showAdminMenu();
                    const int adminChoice = readInt("\t\t\tSelect option: ");

                    switch (adminChoice) {
                        case 1:
                            PhysicalResourceDatabase.add_PhysicalResources();
                            break;
                        case 2:
                            OnlineResourceDatabase.add_OnlineResource();
                            break;
                        case 3: {
                            // Issue Physical Resource
                            const std::string resourceId = readWord("\t\t Enter physical resource ID to issue: ");
                            const int memberId = readInt("\t\t Enter member ID: ");
                            admin->issuePhysicalResource(resourceId, memberId, UserManagerDatabase, PhysicalResourceDatabase, BorrowRecordDatabase);
                            break;
                        }
                        case 4: {
                            // Process Return of Physical Resource
                            const int borrowId = readInt("\t\t Enter borrow ID being returned: ");
                            admin->processReturnOfPhysicalResouce(borrowId, BorrowRecordDatabase, PhysicalResourceDatabase);
                            break;
                        }
                        case 5: {
                            const std::string resourceId = readWord("\t\t Enter physical resource ID to remove: ");
                            PhysicalResourceDatabase.remove_PhysicalResources(resourceId);
                            break;
                        }
                        case 6: {
                            const std::string resourceId = readWord("\t\t Enter online resource ID to remove: ");
                            OnlineResourceDatabase.remove_OnlineResource(resourceId);
                            break;
                        }
                        case 7: {
                            bool reportGeneration = true;
                            while (reportGeneration) {
                                showReportGeneratorMenu();
                                const int reportChoice = readInt("\t\t\tSelect option: ");

                                switch (reportChoice) {
                                    case 1:
                                        BorrowRecordDatabase.DisplayAllBorrowRecords();
                                        break;
                                    case 2:
                                        PhysicalResourceDatabase.searchByAvailability(false);
                                        break;
                                    case 3:
                                        OnlineResourceDatabase.searchByAvailability(false);
                                        break;
                                    case 0:
                                        reportGeneration = false;
                                        break;
                                    default:
                                        std::cout << "\t\t | Invalid option. Try again. |\n";
                                        break;
                                }
                            }
                            break;
                        }
                        case 0:
                            adminSession = false;
                            break;
                        default:
                            std::cout << "\t\t | Invalid option. Try again. |\n";
                            break;
                    }
                }
                break;
            }
            case 0:
                running = false;
                std::cout << "\t\t ---| Exiting the Library , Goodbye! |---\n";
                break;
            default:
                std::cout << "\t\t | Invalid option. Try again. |\n";
                break;
        }
    }
}
