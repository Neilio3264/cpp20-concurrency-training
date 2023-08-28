#include "Captain.h"
#include "zotikos.h"

using namespace std;

int main()
{
    string logFileName("../log/sailing.log");
    logger::log(logFileName) << "Logging Started";

    Captain captain(logFileName);

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
        cout << "Enter Next Command Code:" << endl;
        int commandCode;
        cin >> commandCode;
        if (cin.fail())
        {
            commandCode = -1;
        }

        captain.commandHandler(commandCode);

        if (commandCode == 100)
        {
            cout << "==== Exiting Command Center ====" << endl;
            cout << "--------------------------------" << endl;
            logger::log(logFileName, zotikos::log_state::QUIT) << "Logging Stopped";
            done = true;
        }

        this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return EXIT_SUCCESS;
}