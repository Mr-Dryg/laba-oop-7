#include "../../include/npc.h"
#include <iostream>
#include <algorithm>

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

BaseNPC::BaseNPC(std::string name, int x, int y, double attack_range, int travel_range)
    : name(name), position(Position{x, y}),
    alive(true), attack_range(attack_range),
    travel_range(travel_range), rng() {}
    
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

Position BaseNPC::get_position(void)
{
    return position;
}

MyCoroutine BaseNPC::start_move(int map_size)
{
    while (alive)
    {
        int dist = rng.get_int(1, travel_range);
        switch (rng.get_int(1, 4))
        {
            case 1:
                position.x = std::min(position.x + dist, map_size - 1);
                break;
            case 2:
                position.x = std::max(position.x - dist, 0);
                break;
            case 3:
                position.y = std::min(position.y + dist, map_size - 1);
                break;
            case 4:
                position.y = std::max(position.y - dist, 0);
                break;
        }
        co_yield 0;
    }
    co_return;
}

// void BaseNPC::move_by(int dx, int dy)
// {
//     position.x += dx;
//     position.y += dy;
// }

std::ostream& operator<<(std::ostream& os, const Position& position)
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