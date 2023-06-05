cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)
project(Simulation) #numele proiectului este la alegere


set (Geant4_DIR "/home/oliviastefanoiu/Geant4-v2/install/lib/Geant4-11.0.2")
find_package(Geant4 REQUIRED ui_all vis_all) # includem(gasim) pachetele soft necesare sistemului grafic de vizualizare(GUI)

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})

file(GLOB MACRO_FILES "*.mac")

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB DATA_FILES  "*.dat")

file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_custom_target(Simulation DEPENDS sim)


