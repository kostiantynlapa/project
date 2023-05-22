#pragma once

#ifndef FINAL_STORYWRITER_H
#define FINAL_STORYWRITER_H

#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <string>
#include "HelperFunctions.h"
#include "Actor.h"

using namespace std;
// probability ratios
const int manner_adverbs_frequency = 6;
const int suddenness_adverbs_frequency = 5;
const int adjectives_frequency = 6;

enum WordTypes { MANNER_ADVERBS, SUDDENNESS_ADVERBS, SENTENCE_INTRODUCTION, STORY_INTRODUCTION, ADJECTIVES };
using namespace std;

class StoryWriter {
    vector<Actor> actors; // dynamic array of action characters

    vector<string> manner_adverbs = { "accidentally", "angrily", "anxiously", "awkwardly", "badly", "beautifully", "blindly", "boldly", "bravely", "calmly", "fondly", "happily",
                                      "lazily", "madly", "mysteriously", "neatly", "obediently", "painfully", "rarely", "roughly", "sadly", "silently", "smoothly", "tensely", "truthfully", "wildly" };

    vector<string> suddenness_adverbs = { "occasionally", "unexpectedly", "suddenly", "abruptly", "swiftly", "all of a sudden", "out of the blue", "in an instant", "at once",
                                          "without warning", "instantaneously" };

    vector<string> story_introduction = { "Once upon a time ", "It all began when ", "In a far-off land, ", "Long ago, in a kingdom far away ", "It was a dark and stormy night when ",
                                          "Legend has it that ", "On a bright and sunny day ", "There once was a time when " };

    vector<string> sentence_introduction = { "Suddenly, ", "Unfortunately, ", "Happily, ", "Therefore, ", "However, ", "Nevertheless, ", "Yet, ", "Then, ", "It just so happened that " };

    vector<string> adjectives = { "calm", "cozy", "gentle", "dreamy", "charming", "peaceful", "relaxed", "mystical", "fascinating", "charismatic", "hypnotic", "surreal", "magical",
                                  "fantastical", "energizing", "classy", "funny", "amusing", "entertaining", "hilarious", "optimistic", "strong", "functional", "practical", "innovative" };

    ofstream fout; // output stream object to file
    ifstream fin; // input stream oject of file
    string path;

    int last_script_index = -1;
    bool is_story_empty = true;

public:
    StoryWriter(const string& path); // constructor
    ~StoryWriter();
    void showFullStory();
    void resetStory();
    string getRandomWords(WordTypes type, bool useProbabilty = false);
    void writeToFile(string& sentence);
    void addActor();
    void addActor(const Actor& actor);
    void removeActor();
    void removeActor(Actor& actor);
    void resetNounPlural(Actor& a);
    void resetBodyPart(Actor& a);
    void resetVerb(Actor& a);
    void generateSentence();
    void alternativeScenarios1();
    void alternativeScenarios2();
    void alternativeScenarios3();
};

#endif //FINAL_STORYWRITER_H
