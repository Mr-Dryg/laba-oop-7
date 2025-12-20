include(FetchContent)

# Оптимизация: кэшируем GoogleTest
# FetchContent автоматически кэширует загруженные зависимости
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

# Настраиваем опции перед загрузкой
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Отключаем сборку gmock после загрузки (если возможно)
if(TARGET gmock)
  set_target_properties(gmock PROPERTIES EXCLUDE_FROM_ALL TRUE)
endif()

set(TEST_SOURCES
  test_main.cpp
  test_base_npc.cpp
  test_npc_factory.cpp
  test_dungeon_editor.cpp
  test_npc_combat.cpp
  test_visitor.cpp
  test_npc_movement.cpp
)

add_executable(tests ${TEST_SOURCES})
# Убираем gmock, так как он не используется в тестах - это ускорит сборку
target_link_libraries(tests gtest_main lib)

include(GoogleTest)
gtest_discover_tests(tests)