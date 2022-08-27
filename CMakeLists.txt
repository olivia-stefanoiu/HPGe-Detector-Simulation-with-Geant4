#What is that? 
#    - In software development, CMake is cross-platform free and open-source software for build automation, testing, packaging and installation of software by using a compiler-independent method. *CMake is not a build system itself; it generates another system's build files.

############################################################################

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)
project(Simulation) #numele proiectului este la alegere


set (Geant4_DIR "/home/oliviastefanoiu/Geant4-v2/install/lib/Geant4-11.0.2")
find_package(Geant4 REQUIRED ui_all vis_all) # includem(gasim) pachetele soft necesare sistemului grafic de vizualizare(GUI)

# Setup Geant4 include directories and compile definitions
include(${Geant4_USE_FILE})

#includem directoarele necesare in build;
include_directories(${PROJECT_SOURCE_DIR}/include)


# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
# separam cele doua tipuri in doua categorii;

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


#dorim sa executam fiecare sursa precum si fiecare header 

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES}) #permitem accesarea librariilor din G4


#identifica si copiaza toate filele de tip ".mac" intr-un folder build
file(GLOB MACRO_FILES
  "*.mac" 
)

file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

#la fel si pentru data-files
file(GLOB DATA_FILES
  "*.dat"
)

file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

#final
add_custom_target(Simulation DEPENDS sim)

# *pentru alte detalii; https://cmake.org/cmake/help/latest/index.html
