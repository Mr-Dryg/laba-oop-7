set(LIB_SOURCES
  dungeon_editor.cpp
  npc/base_npc.cpp
  npc/elf.cpp
  npc/knight.cpp
  npc/rogue.cpp
  npc_factory.cpp
  observer.cpp
  random_generator.cpp
)

add_library(lib ${LIB_SOURCES})