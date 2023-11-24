// TASK 1 - NUMBER GUESSING GAME

#include <bits/stdc++.h>
using namespace std;

int main()
{

    cout << "Welcome to the Guess the Number game!\n";
    cout << "I have selected a random number between 1 and 100. Try to guess it.\n";

    // TO Inquire about the maximum number the user wishes to specify for their guessing range.
    int userLimit;
    cout << "Please input the upper limit within which you intend to make your guess: ";
    cin >> userLimit;

    // Generate a random number between 1 and N
    int secretNumber = rand() % userLimit + 1;

    // Initialize the user's guess to a number outside the valid range
    int userGuess = 0;

    // To count Number Of Moves
    int count = 0;

    // Continue until the user guesses the correct number
    while (userGuess != secretNumber)
    {
        cout << "Enter your guess (1 to " << userLimit << "): ";
        cin >> userGuess;
        count++;
        // Providing feedback on the user's guess
        if (userGuess > userLimit)
        {
            cout << "User are Exceeding Your Limit to guess.\n";
        }
        else if (userGuess < secretNumber)
        {
            cout << "Guessed Number is low! Try again.\n";
        }
        else if (userGuess > secretNumber)
        {
            cout << "Guessed Number is High! Try again.\n";
        }
        else
        {
            cout << "Congratulations! You guessed the correct number \"" << secretNumber << "\" in " << count << " Guesses"
                 << "!\n";
        }
    }

    return 0;
}
