#include <gtest/gtest.h>
#include "visitor.h"
#include "npc.h"
#include "observer.h"
#include <vector>
#include <memory>

class BattleRulesTest : public ::testing::Test {
protected:
    void SetUp() override {
        observers.push_back(std::make_unique<TerminalObserver>());
    }

    std::vector<std::unique_ptr<Observer>> observers;
    TypeVisitor type_visitor;
};

TEST_F(BattleRulesTest, RogueKillsElf) {
    BattleVisitor battle_visitor(10.0, &observers);
    
    auto elf = std::make_shared<Elf>("ElfVictim", 0, 0);
    auto rogue = std::make_shared<Rogue>("RogueKiller", 1, 1); // Close enough
    
    battle_visitor.set_current_npc(elf);
    
    rogue->accept(battle_visitor);
    
    EXPECT_FALSE(elf->is_alive());
    EXPECT_TRUE(rogue->is_alive());
}

TEST_F(BattleRulesTest, ElfKillsKnight) {
    BattleVisitor battle_visitor(10.0, &observers);
    
    auto knight = std::make_shared<Knight>("KnightVictim", 0, 0);
    auto elf = std::make_shared<Elf>("ElfKiller", 1, 1); // Close enough
    
    battle_visitor.set_current_npc(knight);
    
    elf->accept(battle_visitor);
    
    EXPECT_FALSE(knight->is_alive());
    EXPECT_TRUE(elf->is_alive());
}

TEST_F(BattleRulesTest, KnightKillsRogue) {
    BattleVisitor battle_visitor(10.0, &observers);
    
    auto rogue = std::make_shared<Rogue>("RogueVictim", 0, 0);
    auto knight = std::make_shared<Knight>("KnightKiller", 1, 1); // Close enough
    
    battle_visitor.set_current_npc(rogue);
    
    knight->accept(battle_visitor);
    
    EXPECT_FALSE(rogue->is_alive());
    EXPECT_TRUE(knight->is_alive());
}

TEST_F(BattleRulesTest, NoCombatBetweenSameType) {
    BattleVisitor battle_visitor(10.0, &observers);
    
    auto elf1 = std::make_shared<Elf>("Elf1", 0, 0);
    auto elf2 = std::make_shared<Elf>("Elf2", 1, 1);
    
    battle_visitor.set_current_npc(elf1);
    
    elf2->accept(battle_visitor);
    
    EXPECT_TRUE(elf1->is_alive());
    EXPECT_TRUE(elf2->is_alive());
}

TEST_F(BattleRulesTest, NoCombatWhenTooFar) {
    BattleVisitor battle_visitor(5.0, &observers);
    
    auto elf = std::make_shared<Elf>("Elf", 0, 0);
    auto knight = std::make_shared<Knight>("Knight", 100, 100);
    
    battle_visitor.set_current_npc(elf);
    
    knight->accept(battle_visitor);
    
    EXPECT_TRUE(elf->is_alive());
    EXPECT_TRUE(knight->is_alive());
}

TEST_F(BattleRulesTest, ReverseRulesDoNotWork) {
    BattleVisitor battle_visitor(10.0, &observers);
    
    auto rogue = std::make_shared<Rogue>("Rogue", 0, 0);
    auto elf = std::make_shared<Elf>("Elf", 1, 1);
    
    battle_visitor.set_current_npc(rogue);
    elf->accept(battle_visitor);
    
    EXPECT_TRUE(rogue->is_alive());
    
    auto elf2 = std::make_shared<Elf>("Elf2", 0, 0);
    auto knight = std::make_shared<Knight>("Knight", 1, 1);
    
    battle_visitor.set_current_npc(elf2);
    knight->accept(battle_visitor);
    
    EXPECT_TRUE(elf2->is_alive());
    
    auto knight2 = std::make_shared<Knight>("Knight2", 0, 0);
    auto rogue2 = std::make_shared<Rogue>("Rogue2", 1, 1);
    
    battle_visitor.set_current_npc(knight2);
    rogue2->accept(battle_visitor);
    
    EXPECT_TRUE(knight2->is_alive());
}

TEST_F(BattleRulesTest, MultipleAttacks) {
    BattleVisitor battle_visitor(10.0, &observers);
    
    auto elf = std::make_shared<Elf>("Elf", 0, 0);
    auto knight = std::make_shared<Knight>("Knight", 1, 1);
    auto rogue = std::make_shared<Rogue>("Rogue", 2, 2);
    
    battle_visitor.set_current_npc(knight);
    elf->accept(battle_visitor);
    EXPECT_FALSE(knight->is_alive());
    
    battle_visitor.set_current_npc(elf);
    rogue->accept(battle_visitor);
    EXPECT_FALSE(elf->is_alive());
    
    EXPECT_TRUE(rogue->is_alive());
}

TEST_F(BattleRulesTest, DeadNPCsDoNotFight) {
    BattleVisitor battle_visitor(10.0, &observers);
    
    auto dead_elf = std::make_shared<Elf>("DeadElf", 0, 0);
    auto knight = std::make_shared<Knight>("Knight", 1, 1);
    
    dead_elf->dies();
    
    battle_visitor.set_current_npc(dead_elf);
    
    knight->accept(battle_visitor);
    
    EXPECT_FALSE(dead_elf->is_alive());
    EXPECT_TRUE(knight->is_alive());
}