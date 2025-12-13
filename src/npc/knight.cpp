#include "../../include/npc.h"
#include "../../include/visitor.h"

Knight::Knight(std::string name, int x, int y)
    : BaseNPC(name, x, y) {};

void Knight::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

void Knight::print(std::ostream& os) const
{
    os << "[Knight] ";
    BaseNPC::print(os);
}