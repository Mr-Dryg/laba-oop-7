#include "../../include/npc.h"

Knight::Knight(std::string name, int x, int y)
    : BaseNPC(name, x, y, KNIGHT_ATTACK_RANGE) {};

void Knight::print(std::ostream& os) const
{
    os << "[Knight] ";
    BaseNPC::print(os);
}

bool Knight::can_kill(BaseNPC& other)
{
    if (!can_fight_with(other))
        return false;
    return other.can_be_defeated_by(*this);
}

bool Knight::can_be_defeated_by(Elf& other)
{
    return true;
}

bool Knight::can_be_defeated_by(Knight& other)
{
    return false;
}

bool Knight::can_be_defeated_by(Rogue& other)
{
    return false;
}