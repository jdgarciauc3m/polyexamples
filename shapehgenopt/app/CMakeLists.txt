#App printing randonm scenes
add_executable(genscene genscene.cpp)
target_link_libraries(genscene dsl)

add_executable(area area.cpp)
target_link_libraries(area dsl)

add_executable(move move.cpp)
target_link_libraries(move dsl)

add_executable(resize resize.cpp)
target_link_libraries(resize dsl)
