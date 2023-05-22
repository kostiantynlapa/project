#pragma once

#ifndef FINAL_ACTOR_H
#define FINAL_ACTOR_H

#include <string>
using namespace std;

class Actor { // class of action characters
    string name;
    string noun_plural;
    string body_part;
    string verb;
    int num;
public:
    Actor();

    Actor(string name, string noun_plural, string body_part, string verb, int num);

    string getName();

    string getNounPlural();

    string getBodyPart();

    string getVerb();

    int getNum();

    void setName(string name);

    void setNounPlural(string noun_plural);

    void setBodyPart(string body_part);

    void setVerb(string verb);

    void setNum(int num);

    int operator==(Actor &a);
};

#endif //FINAL_ACTOR_H
