/*  database.hpp
 * 
 *  Author: Rodrigo Arce Diaz
 *   
 * 
 * Last Update: July 17, 2024
 * 
 */

#ifndef _DATABASE_HPP_
#define _DATABASE_HPP_

#include <unordered_map>
#include <ostream>
#include "playerCard.hpp"

class Database{
    private:
    std::unordered_map<std::string, User> users;

    public:

    void addUser(const string& user);

    void removeUser(const std::string& username);

    User* getUser(const std::string& username);

    void printUsers(std::ostream& os);


};

class UsernameAlreadyExists : public exception {
    public:
        virtual const char* what() const noexcept {
            return "Username already exists.";
    }
};

void Database::addUser(const string& user){
    //Add a checker 
    auto userCheck = users.find(user);

    if(userCheck != nullptr){
        throw UsernameAlreadyExists();
    } else

    //Create new user
    ;
}

void Database::removeUser(const std::string& username){
    users.erase(username);
}

User* Database::getUser(const std::string& username){
    auto Usersearch = users.find(username);
    if(Usersearch != users.end()){
        return &(Usersearch->second);
    }

    return nullptr;
}

void Database::printUsers(std::ostream& os){
    if(users.empty()){
        os << "No Users in the System." << std::endl;
        return;
    }

    for (const auto& pair : users){
        const User& user = pair.second;
        os << "Username: " << user.getUsername() << std::endl
        << "Name: " << user.getFirstName() << " " << user.getLastName() << std::endl << endl;
        
    }

}




#endif