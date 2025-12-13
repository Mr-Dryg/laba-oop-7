#pragma once
#include <cmath>
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <system_error>

enum NpcType {elf, knight, rogue};

class Visitor;

class BaseNPC
{
private:
    struct Position{
        int x;
        int y;
    };
    static double distance(Position pos1, Position pos2);
    bool alive;

protected:
    Position position;
    std::string name;

public:
    BaseNPC() = default;
    BaseNPC(std::string name, int x, int y);
    bool is_near(BaseNPC& other, double attack_range);
    bool is_alive(void);
    void dies(void);
    std::string get_name(void);
    friend std::ostream& operator<<(std::ostream& os, const Position& position);
    virtual void print(std::ostream& os) const;
    virtual void accept(Visitor& visitor) {;}
};

std::ostream& operator<<(std::ostream& os, const BaseNPC& npc);

class Elf : public BaseNPC
{
public:
    Elf(std::string name, int x, int y);
    void print(std::ostream& os) const override;
    void accept(Visitor& visitor) override;
};

class Knight : public BaseNPC
{
public:
    Knight(std::string name, int x, int y);
    void print(std::ostream& os) const override;
    void accept(Visitor& visitor) override;
};

class Rogue : public BaseNPC
{
public:
    Rogue(std::string name, int x, int y);
    void print(std::ostream& os) const override;
    void accept(Visitor& visitor) override;
};
