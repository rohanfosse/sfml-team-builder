#include "../include/GroupSolver.hpp"
#include <random>
#include <algorithm>
#include <iostream>
#include <map>

bool GroupSolver::generateGroups(std::vector<Student>& students, int numGroups) {
    std::random_device rd;
    std::mt19937 g(rd());
    
    const int MAX_TRIES = 10000;

    for (int i = 0; i < MAX_TRIES; ++i) {
        // 1. Mélange aléatoire
        std::shuffle(students.begin(), students.end(), g);

        // 2. Répartition séquentielle (Round Robin)
        std::vector<std::vector<int>> tempGroups(numGroups);
        for (size_t j = 0; j < students.size(); ++j) {
            tempGroups[j % numGroups].push_back(students[j].id);
            students[j].currentGroupId = j % numGroups;
        }

        // 3. Validation
        if (isValid(students, tempGroups)) {
            return true;
        }
    }
    return false;
}

bool GroupSolver::isValid(const std::vector<Student>& students, const std::vector<std::vector<int>>& groups) {
    // Map pour accès rapide ID -> Pointeur Étudiant
    std::map<int, const Student*> studentMap;
    for (const auto& s : students) studentMap[s.id] = &s;

    for (const auto& group : groups) {
        // Double boucle pour vérifier chaque paire dans le groupe
        for (size_t i = 0; i < group.size(); ++i) {
            for (size_t j = i + 1; j < group.size(); ++j) {
                const Student* s1 = studentMap[group[i]];
                int id2 = group[j];

                // Vérification de la liste noire
                for (int enemyId : s1->enemies) {
                    if (enemyId == id2) return false;
                }
            }
        }
    }
    return true;
}