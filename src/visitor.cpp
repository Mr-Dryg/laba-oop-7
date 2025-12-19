#include "../include/visitor.h"
#include <string>

std::string Visitor::visit(Elf& npc)
{
    return "Elf";
}

std::string Visitor::visit(Knight& npc)
{
    return "Knight";
}

std::string Visitor::visit(Rogue& npc)
{
    return "Rogue";
}