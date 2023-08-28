#include "Captain.h"
#include "zotikos.h"

using namespace std;

int main()
{
    string logFileName("../log/sailing.log");
    logger::log(logFileName) << "Logging Started";

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

    bool done = false;
    while (done)
    {
        cout << "Command Code:" << endl;
        int commandCode;
        cin >> commandCode;
        if (cin.fail())
        {
            commandCode = -1;
        }

        if (commandCode == 100)
        {
            cout << "==== Exiting Command Center ====" << endl;
            cout << "--------------------------------" << endl;
            logger::log(logFileName, zotikos::log_state::QUIT) << "Logging Stopped";
            done = true;
        }

        captain.commandHandler(commandCode);
    }
    return EXIT_SUCCESS;
}