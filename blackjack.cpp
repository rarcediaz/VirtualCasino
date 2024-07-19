/*
 *  Author: Rodrigo Arce Diaz
 *   
 * 
 * Last Update: July 18, 2024
 * 
 */

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "playerCard.hpp"
#include <stdlib.h>
#include <time.h>

using std::cout;
using std::cin;

float blackJackLogic(float bet){
    int dealerAmmount;
    int playerAmmount;
    bool turn = true;
    char HorS;
    bool dealerTurn = true;
    srand(time(NULL));
    dealerAmmount = rand() % 10 + 1;
    cout << "\nDealer: " << dealerAmmount << endl;
    playerAmmount = rand() % 10 + 1;
    cout << "\nPlayer: " << playerAmmount << endl;
    playerAmmount += rand() % 10 + 1;
    cout << "\nPlayer: " << playerAmmount << endl;

    while(turn){
        if(playerAmmount > 21){
            cout << "\nPlayer: " << playerAmmount << endl;
            cout << "Sorry you lost this hand.\n\n";
            return -bet;
        }
        cout << "\nWould you like to hit or stand (h or s) ?" << endl;
        cin >> HorS;
        if(HorS == 'h'){
            playerAmmount += rand() % 10 + 1;
            cout << "\nPlayer: " << playerAmmount << endl;
        } else if(HorS == 's' || playerAmmount == 21){
            cout << "Stand at " << playerAmmount << endl;
            turn = false;
        }
        else{
            cout << "\nThat is not a valid option." << endl;
        }

    }
    while(dealerTurn){
        if(dealerAmmount > 21){
            cout << "The dealer bust!" << endl;
            cout << "You win $" << bet*2 << endl;
            return bet*2;
        } else if(dealerAmmount < 17 ){
            cout << "Dealer Hit!" << endl;
            dealerAmmount += rand() % 10 + 1;
            cout << "Dealer Amount: " << dealerAmmount << endl;
        } else dealerTurn = false;
        
    }
    if(dealerAmmount > playerAmmount){
        cout << "Dealer: " << dealerAmmount << "\nPlayer: " << playerAmmount << endl;
        cout << "Sorry you lost this hand.\n\n";
        return -bet;
    } else if(dealerAmmount < playerAmmount){
        cout << "Dealer: " << dealerAmmount << "\nPlayer: " << playerAmmount << endl;
        cout << "You win $" << bet*2 << endl << endl;
        return bet*2;
    } else

    cout << "Dealer: " << dealerAmmount << "\nPlayer: " << playerAmmount << endl;
    cout << "Push, you get your bet ammount back, $" << bet << endl << endl;
    return 0;

}

float amountCheck(float balance){
    bool running = true;
    float betAmount;
    while (running){
        if(balance == 0){
            cout << "You have no money to bet.\n\n";
            return balance;
        }
        cout << "Balance: " << fixed << setprecision(2) << balance << endl;
        cout << "Enter Bet Amount or 0 to exit: ";
        if(balance == 0){
            return balance;
        }
        cin >> betAmount;
        if(betAmount == 0){
            running = false;
            break;
        }
        while (betAmount < 5.00 || betAmount > 1000 || betAmount > balance){
            cout << "That is not a valid bet amount, enter a valid ammount: ";
            cin >> betAmount;
        }

        balance += blackJackLogic(betAmount);

    }

    return balance;
}

User* blackJack(User* user){
    cout << "\n\nWELCOME TO BLACKJACK\n\n";

    int choice;

    cout << "Rules Explained Here: \n\n";
    
    bool atTable = true;
    while(atTable){
        cout << "1) Make a bet(Min: $5.00 , Max: $1000)\n"
             << "0) Leave Table\n";
        cin >> choice;

        switch(choice) {
            case 1 : {
                
            float earnings = amountCheck(user->getBalance());
            user->setBalance(earnings);
            break;

            }
           
            
            case 0 :
            atTable = false;
            break;

            default : 
            cout << "That Choice is not valid, try again.\n";
            break;
        }

    }
    return user;
}
