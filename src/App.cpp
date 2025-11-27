#include "../include/App.hpp"
#include "../include/GroupSolver.hpp"
#include <iostream>

App::App() : m_window(sf::VideoMode(1200, 800), "SFML Team Builder") {
    m_window.setFramerateLimit(60);
    
    // Chargement des assets
    // NOTE: Assurez-vous que le fichier est dans le dossier assets/ à côté de l'exécutable
    if (!m_font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Erreur: Impossible de charger assets/arial.ttf" << std::endl;
        exit(-1);
    }

    initData();
    initUI();
}

void App::initData() {
    std::vector<std::string> names = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Heidi", "Ivan", "Judy", "Kevin", "Leo"};
    
    for (size_t i = 0; i < names.size(); ++i) {
        Student s;
        s.id = i;
        s.name = names[i];
        m_students.push_back(s);
        
        // Création de la carte graphique associée
        m_cards.emplace_back(i, names[i], m_font, sf::Vector2f(50, 50 + i * 50));
    }

    // Ajout de conflits pour tester l'algo
    m_students[0].enemies.push_back(1); m_students[1].enemies.push_back(0); // Alice <> Bob
    m_students[2].enemies.push_back(3); m_students[3].enemies.push_back(2); // Charlie <> David
}

void App::initUI() {
    // Bouton Générer
    m_btnGenerate.setSize(sf::Vector2f(200, 60));
    m_btnGenerate.setPosition(500, 700);
    m_btnGenerate.setFillColor(sf::Color(46, 204, 113));
    
    m_txtBtn.setFont(m_font);
    m_txtBtn.setString("MELANGER");
    m_txtBtn.setPosition(540, 715);

    // Zones de groupes
    float startX = 400;
    for (int i = 0; i < m_numGroups; i++) {
        sf::RectangleShape zone(sf::Vector2f(240, 500));
        zone.setPosition(startX + i * 260, 50);
        zone.setFillColor(sf::Color(50, 50, 50));
        zone.setOutlineThickness(2);
        zone.setOutlineColor(sf::Color::White);
        m_groupZones.push_back(zone);
    }
}

void App::run() {
    sf::Clock clock;
    while (m_window.isOpen()) {
        processEvents();
        update(clock.restart());
        render();
    }
}

void App::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            
            // Interaction Bouton
            if (m_btnGenerate.getGlobalBounds().contains(mousePos)) {
                if (GroupSolver::generateGroups(m_students, m_numGroups)) {
                    // Si succès, on met à jour les cibles des cartes
                    std::vector<int> countPerGroup(m_numGroups, 0);

                    for (auto& card : m_cards) {
                        // Trouver l'étudiant correspondant
                        auto it = std::find_if(m_students.begin(), m_students.end(), 
                            [&](const Student& s){ return s.id == card.getStudentId(); });
                        
                        if (it != m_students.end()) {
                            int gId = it->currentGroupId;
                            float x = m_groupZones[gId].getPosition().x + 20;
                            float y = m_groupZones[gId].getPosition().y + 50 + (countPerGroup[gId] * 50);
                            
                            card.setTargetPosition(sf::Vector2f(x, y));
                            countPerGroup[gId]++;
                        }
                    }
                }
            }
        }
    }
}

void App::update(sf::Time dt) {
    for (auto& card : m_cards) {
        card.update(dt.asSeconds());
    }
}

void App::render() {
    m_window.clear(sf::Color(30, 30, 30));

    // Dessin UI
    for (const auto& zone : m_groupZones) m_window.draw(zone);
    m_window.draw(m_btnGenerate);
    m_window.draw(m_txtBtn);

    // Dessin Debug (Lignes de conflits) si ESPACE appuyé
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        for (const auto& s : m_students) {
            for (int enemyId : s.enemies) {
                if (s.id < enemyId) { // Évite les doublons
                    auto it1 = std::find_if(m_cards.begin(), m_cards.end(), [&](const StudentCard& c){ return c.getStudentId() == s.id; });
                    auto it2 = std::find_if(m_cards.begin(), m_cards.end(), [&](const StudentCard& c){ return c.getStudentId() == enemyId; });

                    if (it1 != m_cards.end() && it2 != m_cards.end()) {
                        sf::Vertex line[] = {
                            sf::Vertex(it1->getCenter(), sf::Color::Red),
                            sf::Vertex(it2->getCenter(), sf::Color::Red)
                        };
                        m_window.draw(line, 2, sf::Lines);
                    }
                }
            }
        }
    }

    // Dessin des cartes (en dernier pour être au premier plan)
    for (auto& card : m_cards) {
        card.draw(m_window);
    }

    m_window.display();
}