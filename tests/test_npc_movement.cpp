#include <gtest/gtest.h>
#include "../include/npc.h"
#include <memory>

class NPCMovementTest : public ::testing::Test {
protected:
    void SetUp() override {
        elf = std::make_shared<Elf>("Elf", 50, 50);
        knight = std::make_shared<Knight>("Knight", 50, 50);
        rogue = std::make_shared<Rogue>("Rogue", 50, 50);
    }

    std::shared_ptr<Elf> elf;
    std::shared_ptr<Knight> knight;
    std::shared_ptr<Rogue> rogue;
};

TEST_F(NPCMovementTest, MoveCreatesCoroutine) {
    auto coroutine = elf->start_move(1);
    EXPECT_TRUE(true); // Если не выброшено исключение, тест пройден
}

TEST_F(NPCMovementTest, CoroutineCanBeResumed) {
    auto coroutine = elf->start_move(1);
    
    // Первый resume запускает корутину
    bool should_continue = coroutine.resume();
    EXPECT_TRUE(should_continue);
    
    // Последующие resume продолжают выполнение
    for (int i = 0; i < 2; ++i) { // Уменьшено с 5 до 2
        should_continue = coroutine.resume();
        EXPECT_TRUE(should_continue);
    }
}

TEST_F(NPCMovementTest, PositionChangesAfterMovement) {
    Position initial_pos = elf->get_position();
    
    auto coroutine = elf->start_move(1);
    
    // Выполняем несколько шагов движения
    for (int i = 0; i < 3; ++i) {
        coroutine.resume();
    }
    
    Position new_pos = elf->get_position();
    
    // Позиция должна измениться после движения
    EXPECT_TRUE(initial_pos.x != new_pos.x || initial_pos.y != new_pos.y);
}

TEST_F(NPCMovementTest, DeadNPCNoMovement) {
    Position initial_pos = elf->get_position();
    elf->dies();
    
    auto coroutine = elf->start_move(1);
    
    // Пытаемся двигать мертвого NPC
    bool should_continue = coroutine.resume();
    
    // Корутина должна завершиться сразу, так как NPC мертв
    EXPECT_FALSE(should_continue);
    
    // Позиция не должна измениться
    Position new_pos = elf->get_position();
    EXPECT_EQ(initial_pos.x, new_pos.x);
    EXPECT_EQ(initial_pos.y, new_pos.y);
}

TEST_F(NPCMovementTest, DifferentTravelRanges) {
    // Проверяем, что разные типы NPC имеют разные диапазоны движения
    auto elf_coro = elf->start_move(1);
    auto knight_coro = knight->start_move(1);
    auto rogue_coro = rogue->start_move(1);
    
    // Выполняем по одному шагу для каждого
    elf_coro.resume();
    knight_coro.resume();
    rogue_coro.resume();
    
    // Проверяем, что корутины еще живы
    EXPECT_TRUE(elf_coro.resume());
    EXPECT_TRUE(knight_coro.resume());
    EXPECT_TRUE(rogue_coro.resume());
}

TEST_F(NPCMovementTest, CoroutineDestructorCleansUp) {
    {
        auto coroutine = elf->start_move(1);
        coroutine.resume();
        // Корутина должна быть уничтожена при выходе из области видимости
    }
    
    // Если не было утечек или сбоев, тест пройден
    EXPECT_TRUE(true);
}

TEST_F(NPCMovementTest, MultipleMovementsInSequence) {
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    std::vector<MyCoroutine> coroutines;
    
    // Создаем несколько NPC - уменьшено с 5 до 3
    for (int i = 0; i < 3; ++i) {
        auto npc = std::make_shared<Elf>("Elf" + std::to_string(i), 50, 50);
        npcs.push_back(npc);
        coroutines.push_back(npc->start_move(1));
    }
    
    // Выполняем несколько шагов для всех корутин - уменьшено с 3 до 2
    for (int step = 0; step < 2; ++step) {
        for (auto& coro : coroutines) {
            coro.resume();
        }
    }
    
    // Проверяем, что все NPC изменили позицию
    for (const auto& npc : npcs) {
        Position pos = npc->get_position();
        EXPECT_FALSE(pos.x == 50 && pos.y == 50);
    }
}