#include "../../include/npc.h"
#include <iostream>

double BaseNPC::distance(Position pos1, Position pos2)
{
    int dx = pos1.x - pos2.x;
    int dy = pos1.y - pos2.y;
    return sqrt(dx*dx + dy*dy);
}

bool BaseNPC::can_fight_with(BaseNPC& other)
{
    return alive && other.is_alive() && name != other.get_name() && is_near(other);
}

BaseNPC::BaseNPC(std::string name, int x, int y, double attack_range)
    : name(name), position(Position{x, y}), alive(true), attack_range(attack_range) {}
    
bool BaseNPC::is_near(BaseNPC& other)
{
    return distance(position, other.position) <= attack_range;
}

bool BaseNPC::is_alive()
{
    return alive;
}

void BaseNPC::dies()
{
    alive = false;
}

std::string BaseNPC::get_name(void)
{
    return name;
}

std::ostream& operator<<(std::ostream& os, const BaseNPC::Position& position)
{
    return os << "(" << position.x << ", " << position.y << ")";
}

void BaseNPC::print(std::ostream& os) const
{
    os << "'" << name << "' at " << position;
}

std::ostream& operator<<(std::ostream& os, const BaseNPC& npc)
{
    npc.print(os);
    return os;
}