/*
 *  Author: Rodrigo Arce Diaz
 *   
 * 
 * Last Update: September 4, 2024
 * 
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "database.hpp"
#include "playerCard.hpp"
#include "blackjack.cpp"

using std::cout;
using std::cin;

//Logged In Menu System
User* loggedMenu(User* user){
    cout << "\nWelcome " << user->getFirstName() <<"!\n"; 
    bool running = true;
    int choice;
    float deposit;
    float withdraw;
    while(running){
        cout << "What would you like to do?\n"
        << "1) Check Account Balance\n"
        << "2) Deposit Credit\n"
        << "3) Withdraw Credit\n"
        << "4) Play a game\n"
        << "0) Log Out\n";
        cin >> choice;
        switch(choice){
            //Displays Users Balance
            case 1 :
            cout << "\nBalance: $" << user->getBalance() << endl;
            break;

            //Allows user to add balance up to 10,000
            case 2 :
            cout << "\nHow much would you like to deposit (Max of $10,000): ";
            cin >> deposit;
            if(deposit > 10000){
                cout << "That is over the deposit limit!\n";
            } else if(deposit <= 0){
                cout << "You can't deposit nothing!\n";
            } else{
                user->addToBalance(deposit);
                cout << "Deposited $" << deposit << endl
                << "New Balance: $" << user->getBalance() << endl;
            }
            break;

            //Allows user to withdraw credits from their account
            case 3 : 
            cout << "\nHow much would you like to withdraw: ";
            cin >> withdraw;
            //Checker 
            if (withdraw > user->getBalance()){
                cout <<"You can't withdraw more than what is in your account!\n";
            } else if(withdraw <= 0){
                cout << "You can't withdraw a negative amount!\n";
            } else{
                user->addToBalance(-withdraw);
                cout << "Withdrawn $" << withdraw << endl
                << "New Balance $" << user->getBalance() << endl;
            }

            break;
            //Game Selection
            case 4 : {
            bool gameSelection = true;
            int game;
            while(gameSelection){
                cout << "\nWhich game would you like to play?\n"
                << "1) BlackJack\n"
                << "2) Roulette\n"
                << "3) Dice\n"
                << "0) Back\n";
        
                cin >> game;
                switch(game){
                    //Sends the user to blackjack
                    case 1 : 
                    user = blackJack(user);
                    break;

                    case 2 :
                    cout <<"This feature has not yet been implemented\n";
                    break;

                    case 3 : 
                    //Implement Dice Game
                    cout << "This feature has not yet been implemented\n";
                    break;

                    case 0 :
                    gameSelection = false;
                    break;

                    default : 
                    cout << "That Choice is not valid, try again.\n";
                    break;

                }


                }
            }
            


            break;

            case 0 :
            running = false;

            break;

            default : 
            cout << "That Choice is not valid, try again.\n";
        }


    }
    return user;
}
//Reads all the preloaded users from a file and creates user objects for them
void loadUsersFromFile(Database<string, User>& casinoBase, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, firstName, lastName, password, balanceStr;
        float balance;

        if (getline(ss, username, ',') &&
            getline(ss, firstName, ',') &&
            getline(ss, lastName, ',') &&
            getline(ss, balanceStr, ',') &&
            getline(ss, password)) {

            balance = stof(balanceStr);
            User newUser(username);
            newUser.setFirstName(firstName);
            newUser.setLastName(lastName);
            newUser.addToBalance(balance); // Initial balance
            newUser.setPassword(password);
            //Inserts the user into the database once created
            casinoBase.insert(username, newUser);
        }
    }
    file.close();
}

//Saves all the users to a file to be used when opening the application again
void saveUsersToFile(Database<string, User>& casinoBase, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    for (const auto& key : casinoBase.getAllKeys()) {
        User user = casinoBase.search(key);
        file << user.getUsername() << ","
             << user.getFirstName() << ","
             << user.getLastName() << ","
             << fixed << setprecision(2) << user.getBalance() << ","
             << user.getPassword() << endl;
    }

    file.close();
}



int main(){
    //Creates a hashmap database
    Database<string, User> casinoBase;
    loadUsersFromFile(casinoBase, "users.txt");
    
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
             << "1) Login\n" 
             << "2) Create an account\n" 
             << "3) Delete an account\n" 
             << "4) View Users\n" 
             << "0) Exit\n" << endl;
    
        cin >> input;
        
        switch(input){
        //Goes to the login menu if successful login
        case 1 : {
                cout << "\nEnter Username: ";
                cin >> username;
                try{
                    User user = casinoBase.search(username);
                    cout << "Password: ";
                    cin >> password;
                    if (user.checkPassword(password)) {
                        User* updateUser = loggedMenu(&user);
                        casinoBase.insert(username, *updateUser);
                    } else {
                        cout << "Password does not match username!" << endl;
                    }
                } catch (const std::runtime_error& e) {
                    cout << e.what() << endl;
                }
                break;
            }             
            //Creates an account as long as the username is not already used
            case 2 : {
                cout << "\nEnter a username: ";
                cin >> username;
                try {
                    User existingUser = casinoBase.search(username);
                    cout << "Error: That Username is already in use!\n";
                } catch (const std::runtime_error& e) {
                User newUser(username);
                cout << "Enter password: ";
                cin >> password;
                newUser.setPassword(password);
                cout << "Enter First Name: ";
                cin >> firstName;
                newUser.setFirstName(firstName);
                cout << "Enter Last Name: ";
                cin >> lastName;
                newUser.setLastName(lastName);
                casinoBase.insert(username, newUser);
                cout << "New User created.\n" 
                << "Username: " << newUser.getUsername() << endl
                << "Name: " << newUser.getFirstName() << " " << newUser.getLastName() << endl
                << "Balance: " << fixed << setprecision(2) << newUser.getBalance() << endl;
                }
                break;
            }
            //Used to delete a user from the system
            case 3 : {
                cout << "\nEnter Username: ";
                cin >> username;
                try{
                    User userToDelete = casinoBase.search(username);
                    cout << "Enter Password: ";
                    cin >> password;
                    if(userToDelete.checkPassword(password)){
                        cout << "Are you sure you want to delete your account (y/n) ? ";
                        char dec;
                        cin >> dec;
                        if(dec == 'y'){
                            casinoBase.remove(username);
                            cout <<  "User: " << username << " successfully deleted." << endl;
                            
                        } 
                        
                    } else {
                        cout << "The password is not correct for the username.\n";
                    }
                } catch (const runtime_error& e){
                    cout << e.what() << endl;
                }

                break;
            }
            //Prints out a list of all the usernames
            case 4 : 
                casinoBase.printUsers(cout);
                break;
            
            case 0 : 
                running = false;
                break;
            
            default : 
            cout << "That Choice is not valid, try again.\n";
            
        }        


    }
    //Saves all of the users to file upon exiting of the menu
    saveUsersToFile(casinoBase, "users.txt");

    cout << "Thank you for using the virtual casino app!\n" << endl;
    return 0;
}

