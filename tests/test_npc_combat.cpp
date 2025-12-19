#include <gtest/gtest.h>
#include "../include/npc.h"
#include <memory>

class NPCCombatTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаем NPC с разными координатами для тестов расстояния
        // С учетом радиусов атаки: Elf=50, Knight=10, Rogue=10
        elf_near = std::make_shared<Elf>("ElfNear", 0, 0);
        elf_far = std::make_shared<Elf>("ElfFar", 100, 100);
        
        // Knight в радиусе атаки эльфа (50 единиц)
        knight_near = std::make_shared<Knight>("KnightNear", 30, 30);
        knight_far = std::make_shared<Knight>("KnightFar", 100, 100);
        
        // Rogue в радиусе атаки Knight (10 единиц)
        rogue_near = std::make_shared<Rogue>("RogueNear", 8, 8);
        rogue_far = std::make_shared<Rogue>("RogueFar", 100, 100);
    }

    std::shared_ptr<Elf> elf_near;
    std::shared_ptr<Elf> elf_far;
    std::shared_ptr<Knight> knight_near;
    std::shared_ptr<Knight> knight_far;
    std::shared_ptr<Rogue> rogue_near;
    std::shared_ptr<Rogue> rogue_far;
};

// Тест 1: Разбойник убивает эльфов (при близком расстоянии)
TEST_F(NPCCombatTest, RogueKillsElfWhenNear) {
    // Разбойник достаточно близко к эльфу (расстояние √(8²+8²) ≈ 11.3 > 10)
    // Разбойник должен быть в пределах 10 единиц
    auto rogue_very_near = std::make_shared<Rogue>("RogueVeryNear", 5, 5);
    EXPECT_TRUE(rogue_very_near->can_kill(*elf_near));
    
    // Разбойник далеко от эльфа
    EXPECT_FALSE(rogue_far->can_kill(*elf_near));
    
    // Эльф далеко от разбойника
    EXPECT_FALSE(rogue_near->can_kill(*elf_far));
}

// Тест 2: Эльф убивает рыцарей (при близком расстоянии)
TEST_F(NPCCombatTest, ElfKillsKnightWhenNear) {
    // Эльф достаточно близко к рыцарю (расстояние √(30²+30²) ≈ 42.4 < 50)
    EXPECT_TRUE(elf_near->can_kill(*knight_near));
    
    // Эльф далеко от рыцаря
    EXPECT_FALSE(elf_far->can_kill(*knight_near));
    
    // Рыцарь далеко от эльфа
    EXPECT_FALSE(elf_near->can_kill(*knight_far));
}

// Тест 3: Рыцарь убивает разбойников (при близком расстоянии)
TEST_F(NPCCombatTest, KnightKillsRogueWhenNear) {
    // Knight в (30,30), Rogue в (8,8) - расстояние слишком большое (>10)
    auto knight_very_near = std::make_shared<Knight>("KnightVeryNear", 5, 5);
    EXPECT_TRUE(knight_very_near->can_kill(*rogue_near));
    
    // Рыцарь далеко от разбойника
    EXPECT_FALSE(knight_far->can_kill(*rogue_near));
    
    // Разбойник далеко от рыцаря
    EXPECT_FALSE(knight_near->can_kill(*rogue_far));
}

// Тест 4: NPC не могут убивать себе подобных
TEST_F(NPCCombatTest, SameTypeCannotKillEachOther) {
    // Эльфы не могут убивать друг друга
    auto elf2 = std::make_shared<Elf>("Elf2", 1, 1);
    EXPECT_FALSE(elf_near->can_kill(*elf2));
    
    // Рыцари не могут убивать друг друга
    auto knight2 = std::make_shared<Knight>("Knight2", 31, 31);
    EXPECT_FALSE(knight_near->can_kill(*knight2));
    
    // Разбойники не могут убивать друг друга
    auto rogue2 = std::make_shared<Rogue>("Rogue2", 9, 9);
    EXPECT_FALSE(rogue_near->can_kill(*rogue2));
}

// Тест 5: Обратные правила не работают
TEST_F(NPCCombatTest, ReverseRulesDoNotWork) {
    // Эльф не может убить разбойника
    EXPECT_FALSE(elf_near->can_kill(*rogue_near));
    
    // Разбойник не может убить рыцаря
    auto rogue_very_near = std::make_shared<Rogue>("RogueVeryNear", 5, 5);
    auto knight_very_near = std::make_shared<Knight>("KnightVeryNear", 5, 5);
    EXPECT_FALSE(rogue_very_near->can_kill(*knight_very_near));
    
    // Рыцарь не может убить эльфа
    EXPECT_FALSE(knight_near->can_kill(*elf_near));
}

// Тест 6: Проверка метода can_be_defeated_by
TEST_F(NPCCombatTest, CanBeDefeatedByRules) {
    // Эльф может быть побежден разбойником
    EXPECT_TRUE(elf_near->can_be_defeated_by(*rogue_near));
    
    // Рыцарь может быть побежден эльфом
    EXPECT_TRUE(knight_near->can_be_defeated_by(*elf_near));
    
    // Разбойник может быть побежден рыцарем
    EXPECT_TRUE(rogue_near->can_be_defeated_by(*knight_near));
    
    // Обратные правила
    EXPECT_FALSE(elf_near->can_be_defeated_by(*knight_near));
    EXPECT_FALSE(knight_near->can_be_defeated_by(*rogue_near));
    EXPECT_FALSE(rogue_near->can_be_defeated_by(*elf_near));
}

// Тест 7: Проверка граничных значений расстояния
TEST_F(NPCCombatTest, EdgeCaseDistances) {
    // Эльф на граничной дистанции (ровно 50 единиц)
    auto elf_edge = std::make_shared<Elf>("ElfEdge", 35, 35); // √(35²+35²) ≈ 49.5 < 50
    auto knight_edge = std::make_shared<Knight>("KnightEdge", 0, 0);
    EXPECT_TRUE(elf_edge->can_kill(*knight_edge));
    
    // Эльф чуть дальше границы
    auto elf_too_far = std::make_shared<Elf>("ElfTooFar", 36, 36); // √(36²+36²) ≈ 50.9 > 50
    EXPECT_FALSE(elf_too_far->can_kill(*knight_edge));
}

// Тест 8: Мертвые NPC не могут убивать
TEST_F(NPCCombatTest, DeadNPCsCannotKill) {
    auto rogue = std::make_shared<Rogue>("Rogue", 1, 1);
    rogue->dies();
    EXPECT_FALSE(rogue->is_alive());
    EXPECT_FALSE(rogue->can_kill(*elf_near));
}

// Тест 9: Мертвые NPC не могут быть убиты
TEST_F(NPCCombatTest, DeadNPCsCannotBeKilled) {
    elf_near->dies();
    EXPECT_FALSE(elf_near->is_alive());
    EXPECT_FALSE(rogue_near->can_kill(*elf_near));
}

// Тест 10: Цепочка убийств
TEST_F(NPCCombatTest, KillChain) {
    // Создаем NPC близко друг к другу
    auto elf_chain = std::make_shared<Elf>("ElfChain", 0, 0);
    auto knight_chain = std::make_shared<Knight>("KnightChain", 5, 5);
    auto rogue_chain = std::make_shared<Rogue>("RogueChain", 3, 3);
    
    // Рыцарь убивает разбойника (расстояние √(2²+2²) ≈ 2.8 < 10)
    EXPECT_TRUE(knight_chain->can_kill(*rogue_chain));
    
    // Эльф убивает рыцаря (расстояние √(5²+5²) ≈ 7.1 < 50)
    EXPECT_TRUE(elf_chain->can_kill(*knight_chain));
    
    // Разбойник убивает эльфа (расстояние √(3²+3²) ≈ 4.2 < 10)
    EXPECT_TRUE(rogue_chain->can_kill(*elf_chain));
}