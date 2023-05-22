

#include "HelperFunctions.h"

void printSystemMessage(const string& sentence, SystemMessages msg, bool deadline) { // function to print system msg with different background colors using ANSI code
    switch (msg) {
        case ERROR:
            cerr << "\033[31;1;7m" << sentence << "\033[0m "; // red
            break;
        case INFO:
            cout << "\033[32;1;7m" << sentence << "\033[0m "; // yellow
            break;
        case INPUT:
            cout << "\n\033[33;1;7m" << sentence << "\033[0m "; // green
            break;
        case START:
            cout << "\033[34m" << sentence << "\033[0m"; //BLUE
            break;
    }
    if (deadline) {
        cout << endl;
    }
}


void getYesNoAnswer(const string& question, string& answer) { // method to get yes/no answer from user
    A:  printSystemMessage(question, INPUT);
    getline(cin, answer); // use getline instead of cin to get all characters entered

    for (char& c : answer) c = tolower(c); // convert string to lowercase
    if (answer.empty() || (answer != "yes" && answer != "no")) { // check for validity and return the user back if invalid
        printSystemMessage("Invalid choice. Please try again. ", ERROR, true);
        goto A;
    }
}