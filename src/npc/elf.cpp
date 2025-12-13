#include "../../include/npc.h"
#include "../../include/visitor.h"

Elf::Elf(std::string name, int x, int y)
    : BaseNPC(name, x, y) {};

void Elf::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void Elf::print(std::ostream& os) const
{
    os << "[Elf] ";
    BaseNPC::print(os);
}