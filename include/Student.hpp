#pragma once
#include <string>
#include <vector>

/// @brief Représente un étudiant et ses contraintes.
struct Student {
    int id;                         ///< Identifiant unique
    std::string name;               ///< Nom affiché
    std::vector<int> enemies;       ///< Liste des IDs des étudiants incompatibles
    int currentGroupId = -1;        ///< ID du groupe assigné (-1 si aucun)
};