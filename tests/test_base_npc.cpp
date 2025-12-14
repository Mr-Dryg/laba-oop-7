#include <gtest/gtest.h>
#include "../include/npc.h"

TEST(BaseNPCTest, ConstructorAndBasicProperties) {
    Knight npc("TestNPC", 10, 20);
    
    EXPECT_TRUE(npc.is_alive());
}

TEST(BaseNPCTest, PositionCalculation) {
    Elf npc1("NPC1", 0, 0);
    Rogue npc2("NPC2", 0, 15);
    
    EXPECT_TRUE(npc1.is_near(npc2));
    EXPECT_FALSE(npc2.is_near(npc1));
}

TEST(BaseNPCTest, Death) {
    Elf npc("TestNPC", 10, 20);
    
    npc.dies();
    EXPECT_FALSE(npc.is_alive());
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