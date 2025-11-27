#pragma once
#include <vector>
#include "Student.hpp"

/// @brief Classe utilitaire statique pour la gestion algorithmique des groupes.
class GroupSolver {
public:
    /**
     * @brief Tente de générer des groupes équitables en respectant les contraintes.
     * @param students Référence vers le vecteur d'étudiants (sera modifié).
     * @param numGroups Nombre de groupes souhaités.
     * @return true si une solution valide est trouvée, false sinon.
     */
    static bool generateGroups(std::vector<Student>& students, int numGroups);

private:
    /// @brief Vérifie si la répartition actuelle respecte toutes les contraintes "ennemis".
    static bool isValid(const std::vector<Student>& students, const std::vector<std::vector<int>>& groups);
};