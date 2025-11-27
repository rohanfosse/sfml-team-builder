#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Student.hpp"
#include "StudentCard.hpp"

/// @brief Classe principale gérant la fenêtre et la boucle de jeu.
class App {
public:
    App();
    
    /// @brief Lance la boucle principale de l'application.
    void run();

private:
    // Méthodes internes
    void processEvents();
    void update(sf::Time dt);
    void render();
    void initData();    ///< Initialise les étudiants de test
    void initUI();      ///< Initialise les zones et boutons

    // Membres SFML
    sf::RenderWindow m_window;
    sf::Font m_font;

    // Données & UI
    std::vector<Student> m_students;
    std::vector<StudentCard> m_cards;
    std::vector<sf::RectangleShape> m_groupZones;
    sf::RectangleShape m_btnGenerate;
    sf::Text m_txtBtn;

    // État
    int m_numGroups = 3;
};