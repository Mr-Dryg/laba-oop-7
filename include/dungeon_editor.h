#pragma once
#include "npc.h"
#include "observer.h"
#include "npc_factory.h"
#include <memory>
#include <string>
#include <vector>

class DungeonEditor
{
private:
    NpcFactory npc_factory;
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    std::vector<std::unique_ptr<Observer>> observers;

public:
    DungeonEditor();
    void add_any_npc();
    void add_elf();
    void add_knight();
    void add_rogue();
    void save_to_file(std::string filename);
    void load_from_file(std::string filename);
    void print_npcs();
    void start_battle(double attack_range);
    void fight(BaseNPC& npc1, BaseNPC& npc2);
    void murder(BaseNPC& killer, BaseNPC& victim);

    const std::vector<std::shared_ptr<BaseNPC>>& getNPCs() { return npcs; }
};