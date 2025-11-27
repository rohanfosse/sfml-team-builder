cmake_minimum_required(VERSION 3.10)
project(SFML-Team-Builder VERSION 1.0)

# --- CONFIGURATION WINDOWS (Indispensable) ---
# On dit à CMake où trouver le fichier de config de la SFML
set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
# ---------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# On charge la SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# On inclut tes dossiers
include_directories(include)

# On trouve tous tes fichiers .cpp
file(GLOB SOURCES "src/*.cpp")

# On crée l'exécutable
add_executable(TeamBuilder ${SOURCES})

# On lie les bibliothèques
target_link_libraries(TeamBuilder sfml-graphics sfml-window sfml-system)

# Copie automatique du dossier assets à côté de l'exécutable
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)