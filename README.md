# Hybrid Library Management System

A console-based Library Management System built in C++ as part of the CS-116 Object-Oriented Programming course at NED University of Engineering & Technology (Spring 2026).

## Project Description

This system manages both physical and online library resources, supporting two types of users — Members and Administrators. It demonstrates core OOP principles including inheritance, polymorphism, abstract classes, encapsulation, and file handling.

## Features

### Member
- Register and log in to a personal account
- Borrow and return online resources
- Search resources by ID, title, author, or genre
- View personal borrow history
- Update personal details, password, and account balance

### Administrator
- Add and remove physical and online resources
- Issue physical resources to members
- Process returns with automatic fine and damage charge calculation
- Generate borrow history and currently issued resource reports

## OOP Concepts Used

| Concept | Where Applied |
|--------|---------------|
| Abstract Base Class | LibraryResource |
| Inheritance | PhysicalResource, OnlineResource |
| Polymorphism | applyReturnPolicy() |
| Encapsulation | Getters and setters |
| File Handling | .txt files |
| Enums | Genre, ResourceType |
| Modular Design | Separate .hpp and .cpp files |

## Project Structure

LMS PROJECT/

├── main.cpp  
├── lms.hpp / lms.cpp  
├── UserManagement.hpp/.cpp  
├── UserManager.hpp/.cpp  
├── MemberStorage.hpp/.cpp  
├── LibraryResource.hpp/.cpp  
├── PhysicalResource.hpp/.cpp  
├── OnlineResource.hpp/.cpp  
├── PhysicalManager.hpp/.cpp  
├── OnlineManager.hpp/.cpp  
├── BorrowRecord.hpp/.cpp  
├── BorrowRecordManager.hpp/.cpp  
├── PhysicalStorage.hpp/.cpp  
├── OnlineStorage.hpp/.cpp  
├── BorrowStorage.hpp/.cpp  
├── Date.hpp/.cpp  
├── members.txt  
├── PhysicalResources.txt  
├── OnlineResources.txt  
└── Borrow Record Storage.txt  

## How to Run

### Option 1
1. Download project folder  
2. Keep all .txt files in same directory  
3. Run lms.exe  

### Option 2
Compile using:

g++ -std=c++17 -o lms main.cpp lms.cpp LibraryResource.cpp PhysicalResource.cpp OnlineResource.cpp PhysicalManager.cpp OnlineManager.cpp BorrowRecordManager.cpp UserManagement.cpp UserManager.cpp PhysicalStorage.cpp OnlineStorage.cpp BorrowStorage.cpp MemberStorage.cpp BorrowRecord.cpp Date.cpp

Run:
lms.exe

### Option 3
Open in VS Code  
Press Ctrl + Shift + B  
Run lms.exe

## Default Admin Login

Username: admin  
Password: admin123

## Notes

- .txt files must stay in same folder  
- Resource IDs: PR001, OR001  
- Max 2 resources per member  
- Online access: 2 days  
- Late return fine applies  

## Contributors

Group G1-03 | CS-116 OOP | Spring 2026 | NED University

| Roll No | Name |
|--------|------|
| CS-25014 | Zainab Khan |
| CS-25016 | Horia Younus |
| CS-25017 | Zehra Baig |
| CS-25018 | Abeer Ahmed |

## Project Report

The detailed project report for this Library Management System is included below.

[Download Report](Report%20(G1-3).pdf)

## UML Diagram

![UML Diagram](UML.png)

## License

Academic project for NED University of Engineering & Technology
