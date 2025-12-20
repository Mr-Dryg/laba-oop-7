#include "include/dungeon_editor.h"
#include "include/npc_coroutine.h"
#include <iostream>
#include <string>
#include <thread>

int main() {
    DungeonEditor editor(100);

    for (int i = 0; i < 50; i++)
        editor.add_any_npc();

    editor.save_to_file("save.txt");
    std::cout << "Before battle:\n";
    editor.print_npcs();

    std::cout << "\nBattle...\n";
    MyCoroutine battle = editor.start_battle(30);

    while (true)
    {
        editor.print_map();
        if (!battle.resume())
            break;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\nAfter battle:\n";
    editor.print_map();
    editor.print_npcs();

    return 0;
}
