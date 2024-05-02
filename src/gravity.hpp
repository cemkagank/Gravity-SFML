#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

class GravitySource {
  sf::Vector2f pos;
  float str;
  sf::CircleShape s;

  public:
    GravitySource(float pos_x, float pos_y, float str) {
      pos.x = pos_x;
      pos.y = pos_y;
      this->str = str;
      s.setPosition(pos);
      s.setFillColor(sf::Color::White);
    }

    
  private:
};
