#pragma once
#include "npc.h"
#include <string>

class Elf;
class Knight;
class Rogue;

class Visitor
{
public:
    std::string visit(Elf& npc);
    std::string visit(Knight& npc);
    std::string visit(Rogue& npc);
};