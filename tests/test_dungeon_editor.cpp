#include <gtest/gtest.h>
#include "../include/dungeon_editor.h"

TEST(DungeonEditorTest, AddNPCs) {
    DungeonEditor editor;
    
    editor.add_elf();
    editor.add_knight();
    editor.add_rogue();
    editor.add_any_npc();
    
    EXPECT_GE(editor.getNPCs().size(), 3);
}

TEST(DungeonEditorTest, PrintNPCs) {
    DungeonEditor editor;
    editor.add_elf();
    
    testing::internal::CaptureStdout();
    editor.print_npcs();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_FALSE(output.empty());
}

TEST(DungeonEditorTest, BattleMechanics) {
    DungeonEditor editor;
    
    editor.add_elf();
    editor.add_knight();
    editor.add_rogue();
    
    EXPECT_EQ(editor.getNPCs().size(), 3);
    
    editor.start_battle(1000.0);
    
    EXPECT_GE(editor.getNPCs().size(), 1);
}

TEST(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor;
    editor.add_elf();
    editor.add_knight();
    
    std::string filename = "test_dungeon.txt";
    editor.save_to_file(filename);
    
    DungeonEditor editor2;
    editor2.load_from_file(filename);
    
    EXPECT_EQ(editor2.getNPCs().size(), 2);
}