#include <gtest/gtest.h>
#include "../include/npc_factory.h"
#include <memory>

TEST(NpcFactoryTest, CreateRandomNPC) {
    NpcFactory factory(100, 100);
    auto npc = factory.create_npc();
    
    EXPECT_NE(npc, nullptr);
    EXPECT_TRUE(npc->is_alive());
}

TEST(NpcFactoryTest, CreateSpecificNPC) {
    NpcFactory factory(100, 100);
    
    auto elf = factory.create_npc(NpcType::elf);
    auto knight = factory.create_npc(NpcType::knight);
    auto rogue = factory.create_npc(NpcType::rogue);
    
    EXPECT_NE(elf, nullptr);
    EXPECT_NE(knight, nullptr);
    EXPECT_NE(rogue, nullptr);
}

TEST(NpcFactoryTest, SaveAndLoad) {
    NpcFactory factory(100, 100);
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    
    npcs.push_back(factory.create_npc(NpcType::elf));
    npcs.push_back(factory.create_npc(NpcType::knight));
    
    std::string filename = "test_save.txt";
    factory.save_to_file(npcs, filename);
    
    auto loaded_npcs = factory.load_from_file(filename);
    EXPECT_EQ(loaded_npcs.size(), 2);
}