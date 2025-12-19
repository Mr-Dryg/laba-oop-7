#include "include/dungeon_editor.h"
#include "include/npc_coroutine.h"
#include <iostream>
#include <string>

int main() {
    DungeonEditor editor(100);

    for (int i = 0; i < 50; i++)
        editor.add_any_npc();

    editor.save_to_file("save.txt");
    std::cout << "Before battle:\n";
    editor.print_npcs();
    // editor.print_map();

    std::cout << "\nBattle...\n";
    MyCoroutine coro = editor.start_battle();
    while (coro.resume())
    {
        // editor.print_map();
    }

    std::cout << "\nAfter battle:\n";
    editor.print_npcs();
    // editor.print_map();

    return 0;
}
