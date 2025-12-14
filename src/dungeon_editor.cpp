#include "../include/dungeon_editor.h"
#include "../include/observer.h"
#include <iostream>
#include <memory>
#include <vector>

DungeonEditor::DungeonEditor() : npc_factory(100, 100)
{
    observers.push_back(std::make_unique<TerminalObserver>());
    observers.push_back(std::make_unique<LogObserver>("log.txt"));
}

void DungeonEditor::add_any_npc()
{
    npcs.push_back(npc_factory.create_npc());
}

void DungeonEditor::add_elf()
{
    npcs.push_back(npc_factory.create_npc(NpcType::elf));
}

void DungeonEditor::add_knight()
{
    npcs.push_back(npc_factory.create_npc(NpcType::knight));
}

void DungeonEditor::add_rogue()
{
    npcs.push_back(npc_factory.create_npc(NpcType::rogue));
}

void DungeonEditor::save_to_file(std::string filename)
{
    npc_factory.save_to_file(npcs, filename);
}

void DungeonEditor::load_from_file(std::string filename)
{
    npcs = npc_factory.load_from_file(filename);
}

void DungeonEditor::print_npcs()
{
    for (const auto& npc : npcs)
        std::cout << *npc << '\n';
}

void DungeonEditor::start_battle(double attack_range)
{
    if (npcs.empty())
        return;

    std::vector<std::shared_ptr<BaseNPC>> survivors;

    for (const auto& npc1 : npcs)
    {
        if (!npc1->is_alive())
            continue;

        for (const auto& npc2 : npcs)
        {
            if (!npc2->is_alive() || (npc1 == npc2))
                continue;

            fight(*npc1, *npc2);

            if (!npc1->is_alive())
                break;
        }

        if (npc1->is_alive())
            survivors.push_back(npc1);
    }

    npcs = std::move(survivors);
}

void DungeonEditor::fight(BaseNPC& npc1, BaseNPC& npc2)
{
    if (npc2.can_kill(npc1))
    {
        murder(npc2, npc1);
    }
    else if (npc1.can_kill(npc2))
    {
        murder(npc1, npc2);
    }
}

void DungeonEditor::murder(BaseNPC& killer, BaseNPC& victim)
{
    victim.dies();
    for (const auto& observer : observers)
        observer->update(killer, victim);
}