#pragma once
#include "npc.h"
#include <fstream>
#include <string>

class Observer
{
protected:
    void log_kill_event(std::ostream& os, BaseNPC& killer, BaseNPC& victim);

public:
    virtual void update(BaseNPC& killer, BaseNPC& victim) =0;
};

class TerminalObserver : public Observer
{
public:
    void update(BaseNPC& killer, BaseNPC& victim) override;
};

class LogObserver : public Observer
{
private:
    std::ofstream file;

public:
    LogObserver();
    LogObserver(std::string filename);
    void update(BaseNPC& killer, BaseNPC& victim) override;
    ~LogObserver();
};