set(LIB_SOURCES
  npc/base_npc.cpp
  npc/elf.cpp
  npc/knight.cpp
  npc/rogue.cpp
  dungeon_editor.cpp
  npc_factory.cpp
  observer.cpp
  random_generator.cpp
  visitor.cpp
)

add_library(lib ${LIB_SOURCES})