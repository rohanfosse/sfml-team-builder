#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/// @brief Composant graphique représentant un étudiant à l'écran.
class StudentCard {
public:
    /**
     * @brief Constructeur de la carte.
     * @param id ID de l'étudiant lié.
     * @param name Nom à afficher.
     * @param font Police d'écriture chargée.
     * @param startPos Position initiale.
     */
    StudentCard(int id, const std::string& name, const sf::Font& font, sf::Vector2f startPos);

    /// @brief Met à jour l'animation de déplacement.
    /// @param dt Temps écoulé depuis la dernière frame (Delta Time).
    void update(float dt);

    /// @brief Dessine la carte dans la fenêtre.
    void draw(sf::RenderWindow& window);

    /// @brief Définit la nouvelle destination de la carte.
    void setTargetPosition(sf::Vector2f target);

    /// @brief Récupère le centre géométrique de la carte (pour les lignes de conflit).
    sf::Vector2f getCenter() const;

    /// @brief ID de l'étudiant associé (lecture seule).
    int getStudentId() const { return m_studentId; }

private:
    int m_studentId;
    sf::RectangleShape m_shape;
    sf::Text m_text;
    
    sf::Vector2f m_currentPos;
    sf::Vector2f m_targetPos;
    
    const float ANIMATION_SPEED = 5.0f;
};