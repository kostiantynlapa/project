
#include "Actor.h"
#include "HelperFunctions.h"
#include "StoryWriter.h"

int main() {

    // we display the screen saver
    cout << endl << endl << endl;
    printSystemMessage("\t\t\t\t\t  WELCOME TO THE GAME\n", START, true);
    printSystemMessage("\t\t\t\t\t  ___________________\n", START, true);
    printSystemMessage("\t\t\t\t\t                                            _                           _         ", START, true);
    printSystemMessage("\t\t\t\t\t                                   ___     (_) _____                   (_)        ", START, true);
    printSystemMessage("\t\t\t\t\t    ___ ____  __    ____ _     _   |  |     _  | () | _____ __    ____  _    __   __   __ ____           ", START, true);
    printSystemMessage("\t\t\t\t\t   / __|  __//  \\  |_  / \\ \\_/ /   |  |    | | |____ | __ //  \\  |  __/| |  /  \\  ||\\\\ ||/  __|      ", START, true);
    printSystemMessage("\t\t\t\t\t  | (__| |  / () \\  / /_  \\   /    |  |___ | | | () || |  / () \\ | |   | | / () \\ || \\\\||\\__ \\      ", START, true);
    printSystemMessage("\t\t\t\t\t  \\___/|_| /_/ \\_ \\/____|  |_|     |______||_| |____||_| /_/  \\_\\|_|   |_|/_/ \\__\\||  \\\\| |___/    ", START, true);
    printSystemMessage("\n\t\t\t\t\t\t\t  ___________________", START, true);

    // wait for the user to press Enter
    printSystemMessage("\t\t\t\t\t\t\t Press Enter to continue...", START, true);
    cin.ignore();

    StoryWriter story("story.txt");
    int choice = 0;
    int step_count = 0;
    chrono::steady_clock::time_point end_time; // a variable to store the time when the user chose to view the history

    while (true) { // menu
        cout << "Menu:\n";
        cout << "1. Add actor\n";
        cout << "2. Generate story\n";
        cout << "3. Delete actor\n";
        cout << "4. Output the whole story\n";
        cout << "5. Clear story\n";
        cout << "6. Exit\n";
        M9: cout << "Enter your choice: ";
        if (!(cin >> choice)) { // error handling
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printSystemMessage("Invalid choice. Please try again. ", ERROR, true);
            goto M9;
        }
        cin.ignore();

        // start of the stopwatch
        if (choice == 1 || choice == 2 || choice == 3) {
            end_time = chrono::steady_clock::now();
        }
        // end of the stopwatch
        if (choice == 4) {
            auto duration = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - end_time).count();
            if (duration < 60)
                cout << "It took " << duration << " seconds to make a story. " << endl;
            else if (duration >= 60 && duration < 120) {
                duration = chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now() - end_time).count();
                cout << "It took " << duration << " minute to make a story. " << endl;
            }
            else {
                duration = chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now() - end_time).count();
                cout << "It took " << duration << " minutes to make a story. " << endl;
            }
        }

        switch (choice) {
            case 1:
                story.addActor(); // add actor
                step_count++;
                break;
            case 2: {
                string answer;
                printSystemMessage("Instruction: press enter to continue generating or type any symbol to come back to the menu: ", INFO, true);
                cin.ignore();
                while (true) {
                    story.generateSentence();
                    step_count++;
                    getline(cin, answer); // use getline instead of cin to get all characters entered
                    if (answer.empty()) { // if user pressed enter, continue generating
                        continue;
                    }
                    else { // back to menu
                        break;
                    }
                }
                break;
            }
            case 3:
                story.removeActor(); // remove actor
                step_count++;
                break;
            case 4:
                story.showFullStory();
                step_count++;
                break;
            case 5:
                story.resetStory();
                step_count = 0;
                printSystemMessage("Story was cleared successfully. ", INFO, true); // end program
                break;
            case 6:
                printSystemMessage("Steps amount: " + to_string(step_count),INFO, true);
                printSystemMessage("Goodbye. Have a nice day. ", INFO, true); // end program
                return 0;
            default:
                printSystemMessage("Invalid choice. Please try again. ", ERROR, true);
                goto M9;
        }
    }
}

