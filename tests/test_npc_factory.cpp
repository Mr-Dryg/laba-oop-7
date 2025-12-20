#include <gtest/gtest.h>
#include "../include/npc_factory.h"
#include <memory>
#include <fstream>
#include <filesystem>

TEST(NpcFactoryTest, CreateRandomNPC) {
    NpcFactory factory(100, 100);
    auto npc = factory.create_npc();
    
    EXPECT_NE(npc, nullptr);
    EXPECT_TRUE(npc->is_alive());
    
    // Check that position is within bounds
    Position pos = npc->get_position();
    EXPECT_GE(pos.x, 0);
    EXPECT_LT(pos.x, 100);
    EXPECT_GE(pos.y, 0);
    EXPECT_LT(pos.y, 100);
}

TEST(NpcFactoryTest, CreateSpecificNPC) {
    NpcFactory factory(100, 100);
    
    auto elf = factory.create_npc(NpcType::elf);
    auto knight = factory.create_npc(NpcType::knight);
    auto rogue = factory.create_npc(NpcType::rogue);
    
    EXPECT_NE(elf, nullptr);
    EXPECT_NE(knight, nullptr);
    EXPECT_NE(rogue, nullptr);
    
    EXPECT_TRUE(elf->is_alive());
    EXPECT_TRUE(knight->is_alive());
    EXPECT_TRUE(rogue->is_alive());
}

TEST(NpcFactoryTest, SaveAndLoad) {
    NpcFactory factory(100, 100);
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    
    npcs.push_back(factory.create_npc(NpcType::elf));
    npcs.push_back(factory.create_npc(NpcType::knight));
    
    std::string filename = "test_save.txt";
    factory.save_to_file(npcs, filename);
    
    // Verify file was created
    std::ifstream file(filename);
    EXPECT_TRUE(file.good());
    file.close();
    
    auto loaded_npcs = factory.load_from_file(filename);
    EXPECT_EQ(loaded_npcs.size(), 2);
    
    // Verify loaded NPCs have correct properties
    EXPECT_TRUE(loaded_npcs[0]->is_alive());
    EXPECT_TRUE(loaded_npcs[1]->is_alive());
    
    // Clean up
    std::remove(filename.c_str());
}

TEST(NpcFactoryTest, SaveAndLoadEmptyVector) {
    NpcFactory factory(100, 100);
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    
    std::string filename = "test_empty.txt";
    factory.save_to_file(npcs, filename);
    
    auto loaded_npcs = factory.load_from_file(filename);
    EXPECT_EQ(loaded_npcs.size(), 0);
    
    std::remove(filename.c_str());
}

TEST(NpcFactoryTest, SaveAndLoadMultipleNPCs) {
    NpcFactory factory(100, 100);
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    
    // Create multiple NPCs of each type
    for (int i = 0; i < 3; ++i) {
        npcs.push_back(factory.create_npc(NpcType::elf));
        npcs.push_back(factory.create_npc(NpcType::knight));
        npcs.push_back(factory.create_npc(NpcType::rogue));
    }
    
    std::string filename = "test_multiple.txt";
    factory.save_to_file(npcs, filename);
    
    auto loaded_npcs = factory.load_from_file(filename);
    EXPECT_EQ(loaded_npcs.size(), 9);
    
    std::remove(filename.c_str());
}

TEST(NpcFactoryTest, LoadFromNonExistentFile) {
    NpcFactory factory(100, 100);
    
    // Try to load from non-existent file
    std::string filename = "nonexistent_file_12345.txt";
    auto loaded_npcs = factory.load_from_file(filename);
    
    // Should return empty vector or handle gracefully
    EXPECT_EQ(loaded_npcs.size(), 0);
}

TEST(NpcFactoryTest, DefaultConstructor) {
    NpcFactory factory; // Default constructor
    
    auto npc = factory.create_npc();
    EXPECT_NE(npc, nullptr);
    EXPECT_TRUE(npc->is_alive());
}