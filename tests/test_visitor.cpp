#include <gtest/gtest.h>
#include "../include/npc.h"
#include "../include/visitor.h"
#include <memory>

class VisitorTest : public ::testing::Test {
protected:
    void SetUp() override {
        elf = std::make_shared<Elf>("Legolas", 0, 0);
        knight = std::make_shared<Knight>("Arthur", 10, 10);
        rogue = std::make_shared<Rogue>("Shadow", 5, 5);
        visitor = std::make_unique<Visitor>();
    }

    std::shared_ptr<Elf> elf;
    std::shared_ptr<Knight> knight;
    std::shared_ptr<Rogue> rogue;
    std::unique_ptr<Visitor> visitor;
};

TEST_F(VisitorTest, VisitElfReturnsCorrectType) {
    std::string type = elf->get_type(*visitor);
    EXPECT_EQ(type, "Elf");
}

TEST_F(VisitorTest, VisitKnightReturnsCorrectType) {
    std::string type = knight->get_type(*visitor);
    EXPECT_EQ(type, "Knight");
}

TEST_F(VisitorTest, VisitRogueReturnsCorrectType) {
    std::string type = rogue->get_type(*visitor);
    EXPECT_EQ(type, "Rogue");
}

TEST_F(VisitorTest, VisitorIdentifiesAllTypes) {
    Visitor v;
    
    EXPECT_EQ(elf->get_type(v), "Elf");
    EXPECT_EQ(knight->get_type(v), "Knight");
    EXPECT_EQ(rogue->get_type(v), "Rogue");
}

TEST_F(VisitorTest, MultipleNPCsWithVisitor) {
    Visitor v;
    
    std::vector<std::shared_ptr<BaseNPC>> npcs;
    npcs.push_back(std::make_shared<Elf>("Elf1", 1, 1));
    npcs.push_back(std::make_shared<Knight>("Knight1", 2, 2));
    npcs.push_back(std::make_shared<Rogue>("Rogue1", 3, 3));
    npcs.push_back(std::make_shared<Elf>("Elf2", 4, 4));
    
    std::vector<std::string> types;
    for (const auto& npc : npcs) {
        types.push_back(npc->get_type(v));
    }
    
    EXPECT_EQ(types[0], "Elf");
    EXPECT_EQ(types[1], "Knight");
    EXPECT_EQ(types[2], "Rogue");
    EXPECT_EQ(types[3], "Elf");
}