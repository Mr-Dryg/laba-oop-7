#include "../include/dungeon_editor.h"
#include "../include/observer.h"
#include <iostream>
#include <memory>
#include <vector>

DungeonEditor::DungeonEditor(int map_size)
    : map_size(map_size), npc_factory(map_size, map_size), rng()
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

void DungeonEditor::print_map()
{
    std::vector<std::vector<char>> map_grid(map_size, std::vector<char>(map_size, '.'));
    Visitor visitor;

    for (const auto& npc_ptr : npcs)
    {
        if (npc_ptr->is_alive())
        {
            Position pos = npc_ptr->get_position();

            if (pos.x >= 0 && pos.x < map_size && pos.y >= 0 && pos.y < map_size)
            {
                char npc_symbol = '.';

                npc_symbol = npc_ptr->get_type(visitor)[0];

                if (map_grid[pos.y][pos.x] == '.')
                    map_grid[pos.y][pos.x] = npc_symbol;
                else
                    map_grid[pos.y][pos.x] = '#';
            }
        }
    }

    std::cout << "\n  ";

    for (int x = 0; x < map_size; ++x)
        std::cout << x % 10 << "";
    std::cout << "\n";
    
    for (int y = 0; y < map_size; ++y)
    {
        std::cout << y % 10 << "";
        
        for (int x = 0; x < map_size; ++x)
            std::cout << map_grid[y][x] << "";
        std::cout << "\n";
    }
    std::cout << std::endl;
    // std::cout << "Legend: E - Elf, K - Knight, R - Rogue, . - empty\n";
}

MyCoroutine DungeonEditor::start_battle()
{
    if (npcs.empty())
        co_return;

    std::vector<MyCoroutine> npc_coroutines;
    for (auto& npc : npcs)
        npc_coroutines.push_back(npc->start_move(map_size));

    while (!npcs.empty())
    {
        for (auto& npc_coro : npc_coroutines)
            npc_coro.resume();

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
    co_return;
}

void DungeonEditor::fight(BaseNPC& npc1, BaseNPC& npc2)
{
    int npc1_strength = rng.get_int(1, 6);
    int npc2_strength = rng.get_int(1, 6);
    if (npc2.can_kill(npc1) && npc2_strength > npc1_strength)
    {
        murder(npc2, npc1);
    }
    else if (npc1.can_kill(npc2) && npc1_strength > npc2_strength)
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