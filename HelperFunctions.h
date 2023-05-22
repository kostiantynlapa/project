#pragma once

#ifndef FINAL_HELPERFUNCTIONS_H
#define FINAL_HELPERFUNCTIONS_H

#include <string>
#include <random>
#include <iostream>

using namespace std;


enum SystemMessages { ERROR, INFO, INPUT, START };
using namespace std;


void printSystemMessage(const string& sentence, SystemMessages msg, bool deadline = false); // function to print system msg with different background colors using ANSI code
void getYesNoAnswer(const string& question, string& answer); // method to get yes/no answer from user

#endif //FINAL_HELPERFUNCTIONS_H
