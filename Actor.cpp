

#include "Actor.h"
#include "HelperFunctions.h"

Actor::Actor() : name(""), noun_plural(""), body_part(""), verb(""), num(0) {}
Actor::Actor(string name, string noun_plural, string body_part, string verb, int num) {
    this->name = name;
    this->noun_plural = noun_plural;
    this->body_part = body_part;
    this->verb = verb;
    this->num = num;
}

string Actor::getName() {return name;}
string Actor::getNounPlural() { return noun_plural; }
string Actor::getBodyPart() { return body_part; }
string Actor::getVerb() { return verb; }
int Actor::getNum() { return num; }

void Actor::setName(string name) { this->name = name; }
void Actor::setNounPlural(string noun_plural) {
    printSystemMessage("Hooray! Now " + this->name + " has \"" + noun_plural + "\"", INFO, true);
    this->noun_plural = noun_plural;
}
void Actor::setBodyPart(string body_part) {
    printSystemMessage("Hooray! Now " + name + " can do something with " + body_part, INFO, true);
    this->body_part = body_part;
}
void Actor::setVerb(string verb) {
    printSystemMessage("Hooray! Now " + name + " can " + verb, INFO, true);
    this->verb = verb;
}
void Actor::setNum(int num) { this->num = num; }



int Actor::operator == (Actor& a) {
    if (name == a.name) { // We believe that there cannot be characters with the same names, while everything else can be the same
        return 1;
    }
    return 0;
}