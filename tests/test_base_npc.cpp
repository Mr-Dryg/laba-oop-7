#include <gtest/gtest.h>
#include "../include/npc.h"

TEST(BaseNPCTest, ConstructorAndBasicProperties) {
    Knight npc("TestNPC", 10, 20);
    
    EXPECT_TRUE(npc.is_alive());
    EXPECT_EQ(npc.get_name(), "TestNPC");
    Position pos = npc.get_position();
    EXPECT_EQ(pos.x, 10);
    EXPECT_EQ(pos.y, 20);
}

TEST(BaseNPCTest, PositionCalculation) {
    Elf npc1("NPC1", 0, 0);
    Rogue npc2("NPC2", 0, 15);
    
    // Elf has attack range 50, so can reach npc2 at distance 15
    EXPECT_TRUE(npc1.is_near(npc2));
    // Rogue has attack range 10, so cannot reach npc1 at distance 15
    EXPECT_FALSE(npc2.is_near(npc1));
}

TEST(BaseNPCTest, Death) {
    Elf npc("TestNPC", 10, 20);
    
    EXPECT_TRUE(npc.is_alive());
    npc.dies();
    EXPECT_FALSE(npc.is_alive());
    // Death should be permanent
    npc.dies();
    EXPECT_FALSE(npc.is_alive());
}

TEST(BaseNPCTest, ExactAttackRangeBoundary) {
    // Test exact boundary of attack range
    Elf elf("Elf", 0, 0);
    Knight knight("Knight", 50, 0); // Exactly at attack range (50)
    
    EXPECT_TRUE(elf.is_near(knight)); // Should be true (<= 50)
    
    Knight knight_far("KnightFar", 51, 0); // Just beyond attack range
    EXPECT_FALSE(elf.is_near(knight_far)); // Should be false (> 50)
}

TEST(BaseNPCTest, DiagonalDistance) {
    // Test diagonal distance calculation
    Elf elf("Elf", 0, 0);
    Knight knight("Knight", 30, 40); // Distance = sqrt(30²+40²) = 50, exactly at range
    
    EXPECT_TRUE(elf.is_near(knight));
    
    Knight knight_far("KnightFar", 31, 40); // Distance > 50
    EXPECT_FALSE(elf.is_near(knight_far));
}

TEST(BaseNPCTest, SamePosition) {
    Elf npc1("NPC1", 10, 20);
    Rogue npc2("NPC2", 10, 20); // Same position
    
    // Both should be able to see each other (distance = 0)
    EXPECT_TRUE(npc1.is_near(npc2));
    EXPECT_TRUE(npc2.is_near(npc1));
}

TEST(ElfTest, CreationAndAccept) {
    Elf elf("Legolas", 5, 5);
    testing::internal::CaptureStdout();
    std::cout << elf;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("[Elf]") != std::string::npos);
    EXPECT_TRUE(output.find("Legolas") != std::string::npos);
}

TEST(KnightTest, CreationAndAccept) {
    Knight knight("Arthur", 10, 10);
    testing::internal::CaptureStdout();
    std::cout << knight;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("[Knight]") != std::string::npos);
    EXPECT_TRUE(output.find("Arthur") != std::string::npos);
}

TEST(RogueTest, CreationAndAccept) {
    Rogue rogue("Shadow", 15, 15);
    testing::internal::CaptureStdout();
    std::cout << rogue;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("[Rogue]") != std::string::npos);
    EXPECT_TRUE(output.find("Shadow") != std::string::npos);
}