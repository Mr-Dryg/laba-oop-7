#include "../include/observer.h"
#include <iostream>

void Observer::log_kill_event(std::ostream& os, BaseNPC& killer, BaseNPC& victim)
{
    os << "\"" << killer << "\" killed \"" << victim << "\"\n";
}

void TerminalObserver::update(BaseNPC& killer, BaseNPC& victim)
{
    Observer::log_kill_event(std::cout, killer, victim);
}

LogObserver::LogObserver() : LogObserver("log.txt") {}

LogObserver::LogObserver(std::string filename) : file(filename) {}

void LogObserver::update(BaseNPC& killer, BaseNPC& victim)
{
    Observer::log_kill_event(file, killer, victim);
    file.flush();
}

LogObserver::~LogObserver()
{
    file.close();
}