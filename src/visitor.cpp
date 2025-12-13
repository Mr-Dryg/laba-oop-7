#include "../include/visitor.h"
#include <iostream>
#include <memory>

NpcType& TypeVisitor::get_npc_type(void)
{
    return npc_type;
}

void TypeVisitor::visit(Elf& elf)
{
    npc_type = NpcType::elf;
}

void TypeVisitor::visit(Knight& knight)
{
    npc_type = NpcType::knight;
}

void TypeVisitor::visit(Rogue& rogue)
{
    npc_type = NpcType::rogue;
}

BattleVisitor::BattleVisitor(double attack_range, std::vector<std::unique_ptr<Observer>>* observers)
    : attack_range(attack_range), observers(observers) {}

void BattleVisitor::set_current_npc(std::shared_ptr<BaseNPC> npc)
{
    cur_npc = npc;
    npc->accept(type_visitor);
    cur_npc_type = type_visitor.get_npc_type();
}

bool BattleVisitor::are_alive(BaseNPC& npc1, BaseNPC& npc2)
{
    return npc1.is_alive() && npc2.is_alive();
}

bool BattleVisitor::possibility_of_battle(BaseNPC& npc1, BaseNPC& npc2)
{
    bool cond1 = are_alive(npc1, npc2);
    bool cond2 = npc1.is_near(npc2, attack_range);
    bool cond3 = npc1.get_name() != npc2.get_name();
    return cond1 && cond2 && cond3;
}

void BattleVisitor::murder(BaseNPC& killer, BaseNPC& victim)
{
    victim.dies();
    for (const auto& observer : *observers)
        observer->update(killer, victim);
}

void BattleVisitor::visit(Elf& elf)
{
    if (!possibility_of_battle(*cur_npc, elf))
        return;

    if (cur_npc_type == NpcType::rogue)
        murder(*cur_npc, elf);
    else if (cur_npc_type == NpcType::knight)
        murder(elf, *cur_npc);
}

void BattleVisitor::visit(Knight& knight)
{
    if (!possibility_of_battle(*cur_npc, knight))
        return;

    if (cur_npc_type == NpcType::elf)
        murder(*cur_npc, knight);
    else if (cur_npc_type == NpcType::rogue)
        murder(knight, *cur_npc);
}

void BattleVisitor::visit(Rogue& rogue)
{
    if (!possibility_of_battle(*cur_npc, rogue))
        return;

    if (cur_npc_type == NpcType::knight)
        murder(*cur_npc, rogue);
    else if (cur_npc_type == NpcType::elf)
        murder(rogue, *cur_npc);
}