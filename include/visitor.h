#pragma once
#include "npc.h"
#include "observer.h"
#include <memory>
#include <vector>

class Visitor
{
public:
    virtual void visit(Elf& elf) = 0;
    virtual void visit(Knight& knight) = 0;
    virtual void visit(Rogue& rogue) = 0;
};

class TypeVisitor : public Visitor
{
private:
    NpcType npc_type;

public:
    TypeVisitor() = default;
    NpcType& get_npc_type(void);
    void visit(Elf& elf);
    void visit(Knight& knight);
    void visit(Rogue& rogue);
};

class BattleVisitor : public Visitor
{
private:
    double attack_range;
    std::shared_ptr<BaseNPC> cur_npc;
    NpcType cur_npc_type;
    std::vector<std::unique_ptr<Observer>>* observers;
    TypeVisitor type_visitor;
    bool are_alive(BaseNPC& npc1, BaseNPC& npc2);
    bool possibility_of_battle(BaseNPC& npc1, BaseNPC& npc2);
    void murder(BaseNPC& killer, BaseNPC& victim);

public:
    BattleVisitor(double attack_range, std::vector<std::unique_ptr<Observer>>* observers);
    void set_current_npc(std::shared_ptr<BaseNPC> npc);
    void visit(Elf& killer) override;
    void visit(Knight& killer) override;
    void visit(Rogue& killer) override;
};