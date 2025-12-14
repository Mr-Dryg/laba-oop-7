#include "../../include/npc.h"

Rogue::Rogue(std::string name, int x, int y)
    : BaseNPC(name, x, y, ROGUE_ATTACK_RANGE) {};

void Rogue::print(std::ostream& os) const
{
    os << "[Rogue] ";
    BaseNPC::print(os);
}

bool Rogue::can_kill(BaseNPC& other)
{
    if (is_near(other))
    {
        return other.can_be_defeated_by(*this);
    }
    return false;
}

bool Rogue::can_be_defeated_by(Elf& other)
{
    return false;
}

bool Rogue::can_be_defeated_by(Knight& other)
{
    return true;
}

bool Rogue::can_be_defeated_by(Rogue& other)
{
    return false;
}