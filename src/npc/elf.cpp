#include "../../include/npc.h"
#include <string>

Elf::Elf(std::string name, int x, int y)
    : BaseNPC(name, x, y, ELF_ATTACK_RANGE, ELF_TRAVEL_RANGE) {};

void Elf::print(std::ostream& os) const
{
    os << "[Elf] ";
    BaseNPC::print(os);
}

bool Elf::can_kill(BaseNPC& other)
{
    if (!can_fight_with(other))
        return false;
    return other.can_be_defeated_by(*this);
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

std::string Elf::get_type(Visitor& visitor)
{
    return visitor.visit(*this);
}