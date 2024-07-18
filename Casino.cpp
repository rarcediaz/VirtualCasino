/*
 *  Author: Rodrigo Arce Diaz
 *   
 * 
 * Last Update: July 17, 2024
 * 
 */

#include <iostream>
#include <iomanip>

#include "database.hpp"
#include "playerCard.hpp"

void loggedMenu(User* user){

}


int main(){

    Database casinoBase;
    int input;
    bool running = true;
    string username;
    string password;
    string firstName;
    string lastName;
    cout << "Welcome to the online virtual casino application!" << endl;
    cout << "What would you like to do?" << endl;
    
    while(running){
        
        cout << "Enter a number for the following:\n"
             << "1) Login\n" << "2) Create an account\n" << "3) Delete an account\n" << "4) View Users\n" << "0) Exit";
    
        cin >> input;

        switch(input){
        case 1 :
                cout << "Enter Username: ";
                cin >> username;
                User* user = casinoBase.getUser(username);
                if(user == nullptr){
                    cout << "User does not Exist! " << endl; //Change to Exception
                } else
                cout << "Password: ";
                cin >> password;
                bool check = user->checkPassword(password);
                if(check == true){
                    loggedMenu(user);
                } else{
                    cout << "Password does not match username!" << endl;
                }

                input = 6;
            break;

            case 2 :
                cout << "Enter a username: ";
                cin >> username;
                casinoBase.addUser(username);
                User* newUser = casinoBase.getUser(username);
                cout << "Enter password: ";
                cin >> password;
                newUser->setPassword(password);
                cout << "Enter First Name: ";
                
                cin >> firstName;
                newUser->setFirstName(firstName);
                cout << "Enter Last Name: ";
                cin >> lastName;
                newUser->setLastName(lastName);

                cout << "New User created.\n" 
                << "Username: " << newUser->getUsername()
                << "Name: " << newUser->getFirstName() << " " << newUser->getLastName()
                << "Balance: " << fixed << setprecision(2) << newUser->getBalance() << endl;

                input = 6;
            
            break;

            case 3 :
                cout << "Enter Username: ";
                cin >> username;
                User* userToDelete = casinoBase.getUser(username);
                bool check = userToDelete->checkPassword(username);
                if(check == false){
                    cout << "The password does not match the username.\n";
                    break;

                } else
                cout << "Are you sure you want to delete your account (y/n) ? ";
                char dec;
                if(dec == 'n'){
                    break;
                } else
                casinoBase.removeUser(username);
                input = 6;
            break;
                
            case 4 :
                casinoBase.printUsers(cout);
            break;

            case 0 : 
                running = false;
            break;

        }        


    }
    cout << "Thank you for using the virtual casino app!\n" << endl;

}

