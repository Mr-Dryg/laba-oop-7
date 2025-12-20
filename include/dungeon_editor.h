#pragma once
#include "npc.h"
#include "npc_coroutine.h"
#include "observer.h"
#include "npc_factory.h"
#include "random_generator.h"
#include <memory>
#include <string>
#include <vector>

class DungeonEditor
{
private:
    int map_size;
    NpcFactory npc_factory;
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    std::vector<std::unique_ptr<Observer>> observers;
    RandomGenerator rng;
    void all_fight(void);

public:
    DungeonEditor(int map_size);
    void add_any_npc();
    void add_elf();
    void add_knight();
    void add_rogue();
    void save_to_file(std::string filename);
    void load_from_file(std::string filename);
    void print_npcs();
    void print_map();
    MyCoroutine start_battle(int battle_duration_seconds);
    void fight(BaseNPC& npc1, BaseNPC& npc2);
    void murder(BaseNPC& killer, BaseNPC& victim);

    const std::vector<std::shared_ptr<BaseNPC>>& getNPCs() { return npcs; }
};