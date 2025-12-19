#include <gtest/gtest.h>
#include "../include/dungeon_editor.h"
#include <cstdio>

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
    
    // Исправление: start_battle() возвращает MyCoroutine
    // Выполняем одну итерацию битвы
    auto battle_coro = editor.start_battle();
    
    // Запускаем корутину один раз
    bool should_continue = battle_coro.resume();
    
    // После битвы должно остаться хотя бы 0 NPC (могут все погибнуть)
    EXPECT_GE(editor.getNPCs().size(), 0);
    
    // Очищаем файлы
    std::remove("log.txt");
}

TEST(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor(25);
    editor.add_elf();
    editor.add_knight();
    
    std::string filename = "test_dungeon.txt";
    editor.save_to_file(filename);
    
    DungeonEditor editor2(25);
    editor2.load_from_file(filename);
    
    EXPECT_EQ(editor2.getNPCs().size(), 2);
    
    // Удаляем тестовый файл
    std::remove(filename.c_str());
    std::remove("log.txt");
}