#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

class Particle : public sf::Drawable{

private:
  sf::Vector2f pos;
  sf::Vector2f vel;
  sf::CircleShape shape;
  sf::VertexArray orbit;
  sf::Color color;
  static bool orbit_history;
  static sf::PrimitiveType orbit_style;

public:
  Particle(sf::Vector2f pos, float vel_x, float vel_y, sf::Color col) {
    this->pos.x = pos.x;
    this->pos.y = pos.y;
    vel.x = vel_x;
    vel.y = vel_y;
    shape.setPosition(pos);
    shape.setFillColor(col);
    shape.setRadius(5);
    this->color = col;
  }
  

     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
     {

        // Draw your custom shape, sprite, or whatever you want here
        // Example: Drawing a rectangle

        // Draw the rectangle to the render target
        target.draw(shape, states);
 };

};
