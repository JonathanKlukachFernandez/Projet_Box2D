# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

# Solution
project ("Projet_Box2D")
message("SOLUTION/PROJECT CMAKING " ${CMAKE_PROJECT_NAME})

# Each sub-project
set(EXECUTABLE_CUSTOM_NAME "Projet_Box2D")
add_subdirectory ("Projet_Box2D")
