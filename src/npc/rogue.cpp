#include "../../include/npc.h"
#include "../../include/visitor.h"

Rogue::Rogue(std::string name, int x, int y)
    : BaseNPC(name, x, y) {};

void Rogue::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void Rogue::print(std::ostream& os) const
{
    os << "[Rogue] ";
    BaseNPC::print(os);
}