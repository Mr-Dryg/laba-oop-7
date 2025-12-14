#include "../../include/npc.h"

Elf::Elf(std::string name, int x, int y)
    : BaseNPC(name, x, y, ELF_ATTACK_RANGE) {};

void Elf::print(std::ostream& os) const
{
    os << "[Elf] ";
    BaseNPC::print(os);
}

bool Elf::can_kill(BaseNPC& other)
{
    if (is_near(other))
    {
        return other.can_be_defeated_by(*this);
    }
    return false;
}

bool Elf::can_be_defeated_by(Elf& other)
{
    return false;
}

bool Elf::can_be_defeated_by(Knight& other)
{
    return false;
}

bool Elf::can_be_defeated_by(Rogue& other)
{
    return true;
}