#App printing randonm scenes
add_executable(genscene genscene.cpp)
target_link_libraries(genscene dsl)

add_executable(area area.cpp)
target_link_libraries(area dsl)

add_executable(translate translate.cpp)
target_link_libraries(translate dsl)

add_executable(enlarge enlarge.cpp)
target_link_libraries(enlarge dsl)
