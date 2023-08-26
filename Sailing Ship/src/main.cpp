#include <iostream>
#include "Captain.h"

using namespace std;

int main()
{
    Captain captain;

    cout << "==== Beginning Ship Command Center ====" << endl;
    cout << "---------------------------------------" << endl
         << endl;
    cout << "Please Enter Command Code: " << endl;
    cout << "   (1)   Order Cleaning" << endl;
    cout << "   (2)   Full Speed Ahead" << endl;
    cout << "   (3)   Stop Engine" << endl;
    cout << "   (100) Exit Command Center" << endl;
    cout << endl;
    while (true)
    {
        cout << "Command Code: ";
        int commandCode;
        cin >> commandCode;
        if (cin.fail())
        {
            cerr << "Error: Input Entered in not Command Code" << endl;
            commandCode = -1;
        }

        if (commandCode == 100)
        {
            cout << "==== Exiting Command Center ====" << endl;
            cout << "--------------------------------" << endl;
            break;
        }

        captain.commandHandler(commandCode);
    }
    return EXIT_SUCCESS;
}