#include <gtest/gtest.h>
#include "../include/dungeon_editor.h"
#include <cstdio>
#include <fstream>

TEST(DungeonEditorTest, AddNPCs) {
    DungeonEditor editor(25);
    
    editor.add_elf();
    editor.add_knight();
    editor.add_rogue();
    editor.add_any_npc();
    
    EXPECT_GE(editor.getNPCs().size(), 3);
}

TEST(DungeonEditorTest, PrintNPCs) {
    DungeonEditor editor(25);
    editor.add_elf();
    
    testing::internal::CaptureStdout();
    editor.print_npcs();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_FALSE(output.empty());
}

TEST(DungeonEditorTest, BattleMechanics) {
    DungeonEditor editor(25);
    
    editor.add_elf();
    editor.add_knight();
    editor.add_rogue();
    
    EXPECT_EQ(editor.getNPCs().size(), 3);
    
    auto battle_coro = editor.start_battle(30);
    
    // Запускаем корутину несколько раз
    int iterations = 0;
    while (battle_coro.resume() && iterations < 5) {
        iterations++;
    }
    
    // После битвы должно остаться хотя бы 0 NPC (могут все погибнуть)
    EXPECT_GE(editor.getNPCs().size(), 0);
    EXPECT_LE(editor.getNPCs().size(), 3);
    
    // Очищаем файлы
    std::remove("log.txt");
}

TEST(DungeonEditorTest, EmptyBattle) {
    DungeonEditor editor(25);
    
    // Battle with no NPCs should complete immediately
    auto battle_coro = editor.start_battle(30);
    EXPECT_FALSE(battle_coro.resume()); // Should return false immediately
    
    std::remove("log.txt");
}

TEST(DungeonEditorTest, BattleWithSingleNPC) {
    DungeonEditor editor(25);
    editor.add_elf();
    
    EXPECT_EQ(editor.getNPCs().size(), 1);
    
    auto battle_coro = editor.start_battle(30);
    
    // Single NPC should survive (no one to fight)
    int iterations = 0;
    while (battle_coro.resume() && iterations < 3) {
        iterations++;
    }
    
    // Should still have 1 NPC (no combat possible)
    EXPECT_EQ(editor.getNPCs().size(), 1);
    
    std::remove("log.txt");
}

TEST(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor(25);
    editor.add_elf();
    editor.add_knight();
    
    std::string filename = "test_dungeon.txt";
    editor.save_to_file(filename);
    
    // Verify file was created
    std::ifstream file(filename);
    EXPECT_TRUE(file.good());
    file.close();
    
    DungeonEditor editor2(25);
    editor2.load_from_file(filename);
    
    EXPECT_EQ(editor2.getNPCs().size(), 2);
    
    // Verify loaded NPCs are alive
    for (const auto& npc : editor2.getNPCs()) {
        EXPECT_TRUE(npc->is_alive());
    }
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
    std::remove("log.txt");
}

TEST(DungeonEditorTest, LoadFromNonExistentFile) {
    DungeonEditor editor(25);
    
    // Try to load from non-existent file
    std::string filename = "nonexistent_dungeon_12345.txt";
    editor.load_from_file(filename);
    
    // Should handle gracefully (empty vector)
    EXPECT_EQ(editor.getNPCs().size(), 0);
    
    std::remove("log.txt");
}

TEST(DungeonEditorTest, PrintMap) {
    DungeonEditor editor(25);
    editor.add_elf();
    editor.add_knight();
    
    testing::internal::CaptureStdout();
    editor.print_map();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_FALSE(output.empty());
    // Map should contain grid representation
    EXPECT_TRUE(output.find("METKA") != std::string::npos || output.length() > 100);
    
    std::remove("log.txt");
}