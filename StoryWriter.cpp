
#include "StoryWriter.h"

random_device rd;
mt19937 mersenne(rd()); // initialize the Mersenne Twister with a random starting number

StoryWriter::StoryWriter(const string &path) { // constructor
    fout.open(path, ios::out | ios::trunc);
    this -> path = path;
    if (!fout.is_open()) {
        printSystemMessage("Unable to open file!", ERROR, true);
        exit(1);
    }
}

StoryWriter::~StoryWriter() {
    fout.close();
}

void StoryWriter::showFullStory() {
    fin.open(path);
    if (!fin.is_open()) {
        printSystemMessage("Unable to open file!", ERROR, true);
        exit(1);
    }
    if (fin.peek() == ifstream::traits_type::eof()) { // check if the file is empty
        printSystemMessage("The story is empty yet. ", INFO, true);
        return;
    }
    char ch;
    int char_count = 0; // character count for line feed after 140 characters
    printSystemMessage("There is the whole story. ", INFO, true);
    while (fin.get(ch)) {
        if(char_count > 140){
            cout << endl;
            char_count = 0;
        }
        cout << ch << flush;
        this_thread::sleep_for(chrono::milliseconds(10)); // Delay execution for 10 millisseconds
        char_count++;
    }
    cout << "\n\n";
    fin.close();
}

void StoryWriter::resetStory() {
    fstream file(path, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        printSystemMessage("Unable to open file!", ERROR, true); // error handling
        exit(1);
    }

    // Clearing file
    file.close();
    actors.clear();
    last_script_index = -1;
    is_story_empty = true;
    fout.seekp(0, ios::beg); // put fout cursor at the start of file
}

string StoryWriter::getRandomWords(WordTypes type, bool useProbabilty) { // method to get random sentense inroduction, story introduction, adverbs, or adjectives
    // if useProbability is true, output these words with a certain probability
    switch (type) {
        case SENTENCE_INTRODUCTION:  // sentense introduction
            return sentence_introduction[mersenne() % sentence_introduction.size()];

        case MANNER_ADVERBS: { // manner adverbs
            if (useProbabilty && mersenne() % 10 < manner_adverbs_frequency)
                return manner_adverbs[mersenne() % manner_adverbs.size()] + " ";
            else if (!useProbabilty)
                return manner_adverbs[mersenne() % manner_adverbs.size()] + " ";
            break;
        }

        case SUDDENNESS_ADVERBS: { // suddenness adverb
            if (useProbabilty && mersenne() % 10 < suddenness_adverbs_frequency)
                return ", " + suddenness_adverbs[mersenne() % suddenness_adverbs.size()] + ", ";
            else if (!useProbabilty)
                return ", " + suddenness_adverbs[mersenne() % suddenness_adverbs.size()] + ", ";
            break;
        }

        case STORY_INTRODUCTION: // story introduction
            return story_introduction[mersenne() % story_introduction.size()];

        case ADJECTIVES: { // adjectives
            if (useProbabilty && mersenne() % 10 < adjectives_frequency) {
                return adjectives[mersenne() % adjectives.size()] + " ";
            }
            else if (!useProbabilty) {
                return adjectives[mersenne() % adjectives.size()] + " ";
            }
            break;
        }
    }
    return " "; // return if none of the previous ones are not suitable
}

void StoryWriter::writeToFile(string &sentence) { // method to output to the console and write to a file
    fout << sentence << flush;
    int char_count = 0; // letter count for line feed after 140 characters
    for (char c : sentence) {
        if(char_count > 140){
            cout << endl;
            char_count = 0;
        }
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(10)); // Delay execution for 10 millisseconds
        char_count++;
    }
    sentence = "";
}

void StoryWriter::addActor() { // method to add an actor specifying its parameters
    string sentence;
    string name, noun, body_part, verb;
    int number;
    printSystemMessage("Enter the name of the character: ", INPUT);
    cin >> name;
    printSystemMessage("Enter a plural noun: ", INPUT);
    cin >> noun;
    printSystemMessage("Enter a body part: ", INPUT);
    cin >> body_part;
    printSystemMessage("Enter a verb: ", INPUT);
    cin >> verb;
    M0: printSystemMessage("Enter a number: ", INPUT);
    if (!(cin >> number)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printSystemMessage("Invalid choice. Please try again. ", ERROR, true); // error handling
        goto M0;
    }
    actors.push_back({ name, noun, body_part, verb, number });
    printSystemMessage(name + " succesfully added!", INFO, true);
}

void StoryWriter::addActor(const Actor& actor) { // method to add an existing actor
    actors.push_back(actor);
}

void StoryWriter::removeActor() { // method to  remove an actor specifying its parameters
    string name;
    printSystemMessage("Enter the name of the actor to remove: ", INPUT);
    getline(cin, name);
    for (vector<Actor>::size_type i = 0; i < actors.size(); i++) {
        if (actors[i].getName() == name) {
            actors.erase(actors.begin() + i);
            printSystemMessage(name + " removed successfully!", INFO, true);
            return;
        }
    }
    printSystemMessage("Actor not found!", ERROR, true);
}

void StoryWriter::removeActor(Actor& actor) {// method to remove an existing actor
    for (vector<Actor>::size_type i = 0; i < actors.size(); i++) {
        if (actors[i] == actor) {
            actors.erase(actors.begin() + i);
            printSystemMessage("\n" + actor.getName() + " deleted successfully!", INFO, true);
        }
    }
}

void StoryWriter::resetNounPlural(Actor &a) {// method to redefine the noun plural of the actor
    M1: printSystemMessage(a.getName() + "'s \"" + a.getNounPlural() + "\" was removed. Enter the next noun plural: ", INPUT);
    string new_noun_plural;
    getline(cin, new_noun_plural);
    if (new_noun_plural.empty()) {
        printSystemMessage("Error. Try to type something data correctly. ", ERROR, true);
        goto M1;
    }
    a.setNounPlural(new_noun_plural);
    string sentence = getRandomWords(SENTENCE_INTRODUCTION) + a.getName() + " found " + new_noun_plural + ". Now it can be used. ";
    writeToFile(sentence); // write to file and output to the console
}

void StoryWriter::resetBodyPart(Actor &a) {// method to redefine the body of the actor
    M2: printSystemMessage(a.getName() + "'s \"" + a.getBodyPart() + "\" was disabled. Enter another body part: ", INPUT);
    string new_body_part;
    getline(cin, new_body_part);
    if (new_body_part.empty()) {
        printSystemMessage("Error. Try to type something data correctly. ", ERROR, true);
        goto M2;
    }
    a.setBodyPart(new_body_part);
    string sentence = getRandomWords(SENTENCE_INTRODUCTION) + a.getName() + " began to be able do something with " + new_body_part + ". ";
    writeToFile(sentence); // write to file and output to the console
}

void StoryWriter:: resetVerb(Actor& a) { // method to redefine the verb of the actor
    M3: printSystemMessage("Now " + a.getName() + " can't " + a.getVerb() + ". Enter another verb: ", INPUT);
    string new_verb;
    getline(cin, new_verb);
    if (new_verb.empty()) {
        printSystemMessage("Error. Try to type something data correctly. ", ERROR, true);
        goto M3;
    }
    a.setVerb(new_verb);
    string sentence = getRandomWords(SENTENCE_INTRODUCTION) + a.getName() + " began to be able to " + new_verb + ". ";
    writeToFile(sentence); // write to file and output to the console
}

void StoryWriter::generateSentence() { // method to generate sentence
    if (actors.size() == 0) { // checking for actors
        printSystemMessage("Error. No actors available. Please add an actor first.", ERROR, true);
        return;
    }

    string sentence;
    if (is_story_empty) {   // check if story is empty
        // output story indroduction if there is none in the file.
        int random = mersenne() % 3;
        sentence += getRandomWords(STORY_INTRODUCTION);
        if (random == 0) {
            sentence += "some friends lived in the same area and often gathered for impromptu barbecues or game nights. ";
        }
        else if (random == 1) {
            sentence += "the friends rejoiced together, their joy amplified by the presence of those they held most dear.";
        }
        else if (random == 2) {
            sentence += "the soft glow of fireflies danced in the air, casting a gentle warmth over the sleepy town. ";
        }
        writeToFile(sentence); // write to file and output to the console
        is_story_empty = false;
        return;
    }


    M4: int random_screenplay = mersenne() % 10; // generating number from 0 till 9 to determine which script we use
    if (actors.size() == 1 && random_screenplay > 2 && random_screenplay < 7) {  // one actor is unavailable for that particular script
        goto M4;
    }

    if (random_screenplay < 3) { // 1st script
        int index = mersenne() % actors.size(); // define the index in such a way that later it is possible to refer to this object in the vector
        Actor a1 = actors[index];

        sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " ";
        M5: int random = mersenne() % 4; // generating number from 0 till 3 to determine which scenario we use
        if(last_script_index == random + 10) goto M5;

        if (random == 0) { // 0nd scenario of the first script
            sentence += getRandomWords(MANNER_ADVERBS, true);
            sentence += a1.getVerb() + " " + to_string(a1.getNum()) + " times. ";
            writeToFile(sentence);
            last_script_index = 10;
        } else if(random == 1) { // 1st scenario of the first script
            sentence += "take " + a1.getNounPlural() + " by " + a1.getBodyPart() + " and" + getRandomWords(SUDDENNESS_ADVERBS, true) + "throw it away. ";
            writeToFile(sentence);
            resetNounPlural(actors[index]);
            last_script_index = 11;
        } else if (random == 2) { // 2nd scenario of the first script
            sentence += "was " + getRandomWords(MANNER_ADVERBS) + a1.getVerb() + "ing. But";
            sentence += getRandomWords(SUDDENNESS_ADVERBS, true);
            sentence += "felt that the " + a1.getBodyPart() + " hurt.";
            sentence += "Now can't do anything with the " + a1.getBodyPart() + ". ";
            writeToFile(sentence);
            resetBodyPart(actors[index]);
            last_script_index = 12;
        } else if(random == 3){
            sentence += a1.getBodyPart() + " tremble looking through " + a1.getNounPlural() + ". ";
            writeToFile(sentence);
            last_script_index = 13;
        }

    }
    else if (random_screenplay > 2 && random_screenplay < 7 && actors.size() > 1) { // 2nd script. Available only if the size of the actors vector > 1
        sentence += getRandomWords(SENTENCE_INTRODUCTION);
        M9: int random = mersenne() % 4; // Generating number from 0 till 3 to determine which scenario we use
        if(last_script_index == random + 20) goto M9;
        Actor a1 = actors[mersenne() % actors.size()];
        M7: Actor a2 = actors[mersenne() % actors.size()];
        if (a1 == a2) {
            goto M7;
        }
        if (random == 0) {
            sentence += a1.getName() + " run away from " + a2.getName() + ", who";
            sentence += getRandomWords(SUDDENNESS_ADVERBS, false) + "started " + a2.getVerb() + "ing. ";
            writeToFile(sentence); // write to file and output to the console
            last_script_index = 20;
        }
        else if (random == 1) {
            sentence += a1.getName() + " and " + a2.getName();
            sentence += getRandomWords(SUDDENNESS_ADVERBS, true);
            sentence += "began to act: " + a1.getName() + " was " + a1.getVerb() + "ing, and ";
            sentence += a2.getName() + " was " + getRandomWords(MANNER_ADVERBS) + a2.getVerb() + "ing. ";
            writeToFile(sentence); // write to file and output to the console
            last_script_index = 21;
        } else if(random == 2){
            sentence += a1.getName() + " got stuck and fell. ";
            sentence += getRandomWords(SENTENCE_INTRODUCTION) + a2.getName() + " reached and helped " + a1.getName() + " up. ";
            writeToFile(sentence);
            last_script_index = 22;
        } else if(random == 3){
            sentence += a1.getName() + getRandomWords(SUDDENNESS_ADVERBS, true) + "takes ";
            sentence += a2.getName() + "'s " + a2.getNounPlural() + ". ";
            writeToFile(sentence);
            last_script_index = 23;
        }

    }
    else if (random_screenplay > 6) { // 3rd script. Using alternative scenarios(interacting with the user)
        M8: int random = mersenne() % 3;
        if(last_script_index == random + 30) goto M8;
        switch (random) {
            case 0:
                alternativeScenarios1(); // 1st scenario
                last_script_index = 30;
                break;
            case 1:
                alternativeScenarios2(); // 2nd scenario
                last_script_index = 31;

                break;
            case 2:
                alternativeScenarios3(); // 3rd scenario
                last_script_index = 32;
                break;
        }
    }
}

void StoryWriter::alternativeScenarios1() {// 1st scenario
    string sentence;
    int index = mersenne() % actors.size(); // define the index in such a way that later it is possible to refer to this object in the vector
    Actor a1 = actors[index];
    string answer;
    sentence += a1.getName() + " was crushed by stones. ";
    writeToFile(sentence); // write to file and output to the console

    getYesNoAnswer("Was " + a1.getName() + " able to get out? ", answer);
    if (answer == "yes") {
        sentence += a1.getName() + " was able to get out and was barely hurt. But " + a1.getNounPlural() + " was badly damaged and " + a1.getName() + " threw it away. ";
        writeToFile(sentence); // write to file and output to the console
        resetNounPlural(actors[index]);
        A1_1: sentence += a1.getName() + " felt pain in " + a1.getBodyPart() + ". ";
        writeToFile(sentence); // write to file and output to the console

        getYesNoAnswer("Can " + a1.getName() + " still " + a1.getVerb() + "?", answer);
        if (answer == "yes") {
            sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " still could " + a1.getVerb() + " and moved on. ";
            writeToFile(sentence); // write to file and output to the console
        }
        else if (answer == "no") {
            sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " can no longer " + a1.getVerb() + ". ";
            writeToFile(sentence); // write to file and output to the console
            resetVerb(actors[index]);
        }
    }
    else if (answer == "no") {
        sentence += a1.getName() + " could not get out and called for help. ";
        writeToFile(sentence); // write to file and output to the console

        getYesNoAnswer("Was there someone who can help?", answer);
        if (answer == "yes") {
            string a2_name;
            if (actors.size() > 1) { // get the name of a random actor and if there is 1 actor in the vector set the name to "stranger"
                A1_2: Actor a2 = actors[mersenne() % actors.size()];
                if (a1 == a2) {
                    goto A1_2;
                }
                a2_name = a2.getName();
            }
            else a2_name = "stranger";
            sentence += getRandomWords(SENTENCE_INTRODUCTION) + a2_name + " heard " + a1.getName() + " and came to help.\n";
            sentence += "\"" + a2_name + ", I don't want to die, help me.\" -, " + a1.getName() + " said.\n";
            sentence += "\"Don't worry, it's nothing to worry about\" -, " + a2_name + " said.\n";
            writeToFile(sentence);
            goto A1_1;
        }
        else {
            sentence += "No one heard " + a1.getName();
            writeToFile(sentence); // write to file and output to the console

            getYesNoAnswer("Are " + a1.getName() + "'s vital organs damaged?", answer);
            if (answer == "yes") {
                sentence += a1.getName() + " died within" + to_string(a1.getNum()) + " hours. ";
                writeToFile(sentence); // write to file and output to the console
                removeActor(actors[index]); // removing from vector

            }
            else if (answer == "no") {
                sentence += getRandomWords(SENTENCE_INTRODUCTION) + "a " + getRandomWords(ADJECTIVES) + "tourist passing by heard " + a1.getName() + " and helped him. ";
                writeToFile(sentence); // write to file and output to the console

                getYesNoAnswer("Would you like to thank your " + getRandomWords(ADJECTIVES) + "savior? ", answer);
                if (answer == "yes") {
                    sentence += "\"Thank you " + getRandomWords(ADJECTIVES) + "brother, if it wasn't for you I would have died.\" -, " + a1.getName() + " said.\n";
                    sentence += "\"Don't worry, everyone would do the same in my place\" -, tourist said\n";
                    sentence += "\"I want to thank you and give you " + a1.getNounPlural() + "\" -, " + a1.getName() + " said.\n";
                    writeToFile(sentence); // write to file and output to the console
                    resetNounPlural(actors[index]);
                }
            }
        }
    }
}

void StoryWriter::alternativeScenarios2() {
    string sentence;
    int index = mersenne() % actors.size(); // define the index in such a way that later it is possible to refer to this object in the vector
    Actor a1 = actors[index];
    string answer;
    sentence += getRandomWords(STORY_INTRODUCTION) + "after " + a1.getName() + "`s " + getRandomWords(ADJECTIVES) + "death of the father, becomes the new monarch and inherits the " + a1.getNounPlural() + ". ";
    writeToFile(sentence); // write to file and output to the console

    getYesNoAnswer("Should " + a1.getName() + " change army commander? ", answer);
    if (answer == "yes") {
        sentence += a1.getName() + " thinks about it and decides to put a " + getRandomWords(ADJECTIVES) + "friend to this position. ";
        sentence += a1.getName() + " begins to " + getRandomWords(MANNER_ADVERBS) + "occupy new territories. ";
        sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " felt pain in " + a1.getBodyPart() + ". ";
        writeToFile(sentence); // write to file and output to the console

        getYesNoAnswer("Is " + a1.getName() + " still able to fight? ", answer);
        if (answer == "yes") {
            sentence += a1.getName() + " continues the war. ";
            writeToFile(sentence); // write to file and output to the console
            A2_1:
            sentence += getRandomWords(SENTENCE_INTRODUCTION) + "news comes from the Kingdom. A rebellion was raised against the " + getRandomWords(ADJECTIVES) + "monarch. ";
            writeToFile(sentence); // write to file and output to the console

            getYesNoAnswer("Should " + a1.getName() + " return to homeland? ", answer);
            if (answer == "yes") {
                sentence += a1.getName() + " turns the army back and comes back to the Kingdom. ";
                writeToFile(sentence); // write to file and output to the console
                A2_2:
                if (actors.size() > 1) {
                    A2_3: Actor a2 = actors[mersenne() % actors.size()];
                    if (a1 == a2) {
                        goto A2_3;
                    }
                    sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " has a powerful ally - " + a2.getName() + ". ";
                    sentence += "This ally provides strong support. " + getRandomWords(SENTENCE_INTRODUCTION, true) + "the rebellion is suppressed without heavy losses. ";
                    writeToFile(sentence); // write to file and output to the console
                }
                else {
                    sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " has no powerful ally. So, the monarch loses the " + a1.getBodyPart() + " and the rebellion is crushed with huge damage. ";
                    writeToFile(sentence); // write to file and output to the console
                }
            }
            else if (answer == "no") {
                sentence += a1.getName() + " decides not to turn the army back. ";
                sentence += "Soon, support in the " + getRandomWords(ADJECTIVES) + "capital is weakening. ";
                A2_4:
                if (actors.size() > 1) {
                    A2_5: Actor a2 = actors[mersenne() % actors.size()];
                    if (a1 == a2) {
                        goto A2_5;
                    }
                    sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " has a powerful ally - " + a2.getName() + ". ";
                    sentence += "This ally provides strong support. " + getRandomWords(SENTENCE_INTRODUCTION) + "the monarch loses the " + a1.getBodyPart() + " and the rebellion is suppressed with huge damage. ";
                    writeToFile(sentence); // write to file and output to the console
                }
                else {
                    sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " does not have a powerful ally. ";
                    sentence += "The army starts losing. After 3 weeks, only 1000 soldiers are left. The rebels win and overthrow " + a1.getName() + ". Soon, the Kingdom falls apart. ";
                    writeToFile(sentence); // write to file and output to the console
                }
            }
        }
        else if (answer == "no") {
            sentence += a1.getName() + " stops the war, but stays on new " + getRandomWords(ADJECTIVES) + "territories. ";
            writeToFile(sentence); // write to file and output to the console
            goto A2_1;
        }
    }
    else if (answer == "no") {
        sentence += a1.getName() + " " + getRandomWords(SUDDENNESS_ADVERBS) + "decides not to change anything, breaking promise to give this position to a friend, who starts a rebellion. ";
        writeToFile(sentence); // write to file and output to the console

        getYesNoAnswer("Find a compromise? ", answer);
        if (answer == "yes") {
            sentence += a1.getName() + " reacts quickly and accepts rebel's terms. ";
            writeToFile(sentence); // write to file and output to the console
            goto A2_2;
        }
        else if (answer == "no") {
            sentence += a1.getName() + " " + getRandomWords(MANNER_ADVERBS) + "decides not to accept rebel's terms. ";
            writeToFile(sentence); // write to file and output to the console
            goto A2_4;
        }
    }
}

void StoryWriter::alternativeScenarios3() {
    string sentence;
    int index = mersenne() % actors.size(); // define the index in such a way that later it is possible to refer to this object in the vector
    Actor a1 = actors[index];
    string answer;
    sentence += getRandomWords(STORY_INTRODUCTION) + "next " + a1.getName() + " left the desert and fell behind the group " + a1.getNounPlural() + ". ";
    writeToFile(sentence); // write to file and output to the console

    getYesNoAnswer("Will " + a1.getName() + " be able to get out of the desert? ", answer);
    if (answer == "yes") {
        sentence += a1.getName() + " takes out all the things from the " + getRandomWords(ADJECTIVES) + "backpack. ";
        sentence += a1.getName() + " " + getRandomWords(MANNER_ADVERBS) + "looks for " + a1.getNounPlural() + " which was no longer there. ";
        sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " felt pain in " + a1.getBodyPart() + ". ";
        writeToFile(sentence); // write to file and output to the console

        getYesNoAnswer("Can we go further? ", answer);
        if (answer == "yes") {
            sentence += a1.getName() + " continues. ";
            writeToFile(sentence); // write to file and output to the console
            A3_1:
            sentence += getRandomWords(SENTENCE_INTRODUCTION) + "despite all the difficulties, it goes on. ";
            writeToFile(sentence); // write to file and output to the console


            getYesNoAnswer("Should " + a1.getName() + " return to the " + getRandomWords(ADJECTIVES) + "group? ", answer);
            if (answer == "yes") {
                sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " still could " + a1.getVerb() + ", continued to move. ";
                writeToFile(sentence); // write to file and output to the console
            }
            else if (answer == "no") {
                sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " can no longer " + a1.getVerb() + ". ";
                writeToFile(sentence); // write to file and output to the console
                resetVerb(actors[index]);
            }
        }
        if (answer == "no") {
            sentence += a1.getName() + " couldn't catch up with the group to get out. ";
            sentence += "Trees are visible. ";
            if (actors.size() > 1) {
                A3_2: Actor a2 = actors[mersenne() % actors.size()];
                if (a1 == a2) {
                    goto A3_2;
                }
                sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + " was with " + a2.getName() + ". ";
                sentence += "This was my tour guide. " + getRandomWords(SENTENCE_INTRODUCTION) + "The " + getRandomWords(ADJECTIVES) + "tourist loses their " + a1.getBodyPart();
                writeToFile(sentence); // write to file and output to the console
            }
            else {
                sentence += getRandomWords(SENTENCE_INTRODUCTION) + a1.getName() + ", the " + getRandomWords(ADJECTIVES) + "guide, did not show up. ";
                sentence += "The hot sand burned the tourist's feet, and the " + getRandomWords(ADJECTIVES) + "sun was so hot that it was impossible to go further. ";
                writeToFile(sentence); // write to file and output to the console
            }
        }
    }
    else if (answer == "no") {
        sentence += a1.getName() + " goes further and finds an " + getRandomWords(ADJECTIVES) + "oasis. ";
        writeToFile(sentence); // write to file and output to the console
        goto A3_1;
    }

    if (answer == "yes") {
        sentence += a1.getName() + " " + getRandomWords(MANNER_ADVERBS) + "managed to get out. ";
        writeToFile(sentence); // write to file and output to the console
    }
    else if (answer == "no") {
        sentence += a1.getName() + " " + getRandomWords(SUDDENNESS_ADVERBS) + " then there were thickets of vegetation and not an " + getRandomWords(ADJECTIVES) + "oasis. ";
        writeToFile(sentence); // write to file and output to the console

        getYesNoAnswer("Have " + a1.getName() + " figured out how to get out? ", answer);
        if (answer == "yes") {
            sentence += a1.getName() + " did not give up, pushed through and found the " + getRandomWords(ADJECTIVES) + "group that was looking for him. ";
            writeToFile(sentence); // write to file and output to the console
        }
        else if (answer == "no") {
            sentence += a1.getName() + " " + getRandomWords(MANNER_ADVERBS) + "couldn't get out. ";
            writeToFile(sentence); // write to file and output to the console
            removeActor(actors[index]); // removing from vector
        }
    }
}
