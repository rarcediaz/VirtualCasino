/*  playerCard.hpp
 * 
 *  Author: Rodrigo Arce Diaz
 *   
 * 
 * Last Update: July 18, 2024
 * 
 */


#ifndef _PLAYERCARD_HPP_
#define _PLAYERCARD_HPP_

#include <ostream>
#include <iomanip>
#include <string>
using namespace std;

class User {
    private:

    string username;
    string firstname;
    string lastname;
    float balance;
    string password;

    public:

    User(string& username);

    //Getters
    string getUsername() const;
    string getFirstName() const;
    string getLastName() const;
    float getBalance() const;

    //Setters
    void setUsername(const string& username);
    void setFirstName(const string& firstname);
    void setLastName(const string& lastname);
    void addToBalance(float pay);
    void setPassword(const string& password);
    bool checkPassword(const string& attempt);
    
    

};

User::User(string& username){
    this->username = username;
    balance = 0.00;
}

string User::getUsername() const{
    return username;
}

string User::getFirstName() const{
    return firstname;
}

string User::getLastName() const{
    return lastname;
}

float User::getBalance() const{
    return balance;
}

void User::setUsername(const string& username){
    this->username = username;
}

void User::setFirstName(const string& firstname){
    this->firstname = firstname;
}

void User::setLastName(const string& lastname){
    this->lastname = lastname;
}

void User::setPassword(const string& password){
    this->password = password;
}

void User::addToBalance(float pay){
    balance += pay;
}

bool User::checkPassword(const string& attempt){
    if(attempt == password){
        return true;
    }
    else
    return false;
}

#endif
