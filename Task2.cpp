// TASK 2 - SIMPLE CALCULATOR

#include <iostream>

using namespace std;

// Function declarations
float add(float x, float y) {
    return x + y;
}

float subtract(float x, float y) {
    return x - y;
}

float multiply(float x, float y) {
    return x * y;
}

float divide(float x, float y) {
    if (y != 0) {
        return x / y;
    } else {
        cout << "Cannot divide by zero." << endl;
        return 0; // Returning 0 for division by zero
    }
}

int main() {
    cout << "Welcome You to Use Calculator !\n\n";


    float num1, num2;
    char choice;

    do {
        // User input
        cout << "Enter the first number: ";
        cin >> num1;
        cout << "Enter the second number: ";
        cin >> num2;

        // Display menu
        cout << "\nSelect operation:" << endl;
        cout << "1. Addition" << endl;
        cout << "2. Subtraction" << endl;
        cout << "3. Multiplication" << endl;
        cout << "4. Division" << endl;
        cout << "5. All Operations (1 to 4)" << endl;

        cout << "Enter choice (1, 2, 3, 4 or 5 ): ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << num1 << " + " << num2 << " = " << add(num1, num2) << endl;
                break;
            case '2':
                cout << num1 << " - " << num2 << " = " << subtract(num1, num2) << endl;
                break;
            case '3':
                cout << num1 << " * " << num2 << " = " << multiply(num1, num2) << endl;
                break;
            case '4':
                cout << num1 << " / " << num2 << " = " << divide(num1, num2) << endl;
                break;
            case '5':
                cout << num1 << " + " << num2 << " = " << add(num1, num2) << endl;
                cout << num1 << " - " << num2 << " = " << subtract(num1, num2) << endl;
                cout << num1 << " * " << num2 << " = " << multiply(num1, num2) << endl;
                cout << num1 << " / " << num2 << " = " << divide(num1, num2) << endl;
                break;
            default:
                cout << "Invalid input. Please enter a valid choice." << endl;
        }

        // Ask the user if they want to continue
        cout << "Do you want to perform another calculation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Exiting the calculator. Goodbye!" << endl;

    return 0;
}
