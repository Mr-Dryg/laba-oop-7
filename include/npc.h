#pragma once
#include "npc_coroutine.h"
#include "random_generator.h"
#include "visitor.h"
#include <cmath>
#include <ostream>
#include <random>
#include <string>
#include <system_error>

#define ELF_ATTACK_RANGE 50
#define KNIGHT_ATTACK_RANGE 10
#define ROGUE_ATTACK_RANGE 10

#define ELF_TRAVEL_RANGE 10
#define KNIGHT_TRAVEL_RANGE 30
#define ROGUE_TRAVEL_RANGE 10

struct Position{
    int x;
    int y;
};

enum NpcType {elf, knight, rogue};

class Visitor;

class Elf;
class Knight;
class Rogue;

class BaseNPC
{
private:
    static double distance(Position pos1, Position pos2);
    bool alive;
    RandomGenerator rng;
    int travel_range;

protected:
    Position position;
    std::string name;
    double attack_range;
    bool can_fight_with(BaseNPC& other);

public:
    BaseNPC() = default;
    BaseNPC(std::string name, int x, int y, double attack_range, int travel_range);
    bool is_near(BaseNPC& other);
    bool is_alive(void);
    void dies(void);
    std::string get_name(void);
    Position get_position(void);
    MyCoroutine start_move(int map_size);
    // void move_by(int dx, int dy);
    friend std::ostream& operator<<(std::ostream& os, const Position& position);
    virtual void print(std::ostream& os) const;
    virtual bool can_kill(BaseNPC& other) =0;
    virtual bool can_be_defeated_by(Elf& other) =0;
    virtual bool can_be_defeated_by(Knight& other) =0;
    virtual bool can_be_defeated_by(Rogue& other) =0;
    virtual std::string get_type(Visitor& visitor) =0;
};

std::ostream& operator<<(std::ostream& os, const BaseNPC& npc);

class Elf : public BaseNPC
{
public:
    Elf(std::string name, int x, int y);
    void print(std::ostream& os) const override;
    bool can_kill(BaseNPC& other) override;
    bool can_be_defeated_by(Elf& other) override;
    bool can_be_defeated_by(Knight& other) override;
    bool can_be_defeated_by(Rogue& other) override;
    std::string get_type(Visitor& visitor) override;
};

class Knight : public BaseNPC
{
public:
    Knight(std::string name, int x, int y);
    void print(std::ostream& os) const override;
    bool can_kill(BaseNPC& other) override;
    bool can_be_defeated_by(Elf& other) override;
    bool can_be_defeated_by(Knight& other) override;
    bool can_be_defeated_by(Rogue& other) override;
    std::string get_type(Visitor& visitor) override;
};

class Rogue : public BaseNPC
{
public:
    Rogue(std::string name, int x, int y);
    void print(std::ostream& os) const override;
    bool can_kill(BaseNPC& other) override;
    bool can_be_defeated_by(Elf& other) override;
    bool can_be_defeated_by(Knight& other) override;
    bool can_be_defeated_by(Rogue& other) override;
    std::string get_type(Visitor& visitor) override;
};
