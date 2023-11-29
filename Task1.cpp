
// TASK 1 - NUMBER GUESSING GAME

#include <bits/stdc++.h>
using namespace std;

int main()
{

    cout << "Welcome to the Guess the Number game!\n\n";

    // TO Inquire about the maximum number the user wishes to specify for their guessing range.
    int userLimit;
    cout << "Enter the upper limit for your guess:";
    cin >> userLimit;

    cout << "I have selected a random number between 1 and " << userLimit << ". Try to guess it.\n\n";

    // To set the random number generator with the current time
    srand(time(0));

    // Generate a random number between 1 and N
    int secretNumber = rand() % userLimit + 1;

    // Initialize the user's guess to a number outside the valid range
    int userGuess = 0;

    // To count Number Of Guesses the user have taken to guess the
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
            cout << "You are exceeding guess limit! Try again.\n";
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
        cout << "\n";
    }

    return 0;
}
