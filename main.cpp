#include "include/dungeon_editor.h"
#include <iostream>
#include <string>

int main() {
    DungeonEditor editor;

    for (int i = 0; i < 50; i++)
        editor.add_any_npc();

    std::cout << "Before battle:\n";
    
    std::string s ("save.txt");
    editor.save_to_file("save.txt");
    editor.print_npcs();

    std::cout << "\nBattle...\n";
    editor.start_battle(250);

    std::cout << "\nAfter battle:\n";
    editor.print_npcs();

    return 0;
}
