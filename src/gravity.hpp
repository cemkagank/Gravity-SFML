#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

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
      s.setRadius(8);
    }
  
    void render(sf::RenderWindow &window) {
      window.draw(s);
    }

    sf::Vector2f get_pos() {
      return pos;  
    }

    float get_str(){
      return str;  
    }

    
  private:
};

class Particle {
  sf::Vector2f pos;
  sf::Vector2f vel;
  sf::CircleShape s;

  public:
    Particle(float pos_x, float pos_y, float vel_x , float vel_y) {
      pos.x = pos_x;
      pos.y = pos_y;
      vel.x = vel_x;
      vel.y = vel_y;
      s.setPosition(pos);
      s.setFillColor(sf::Color::Green);
      s.setRadius(5);
    }
  
    void render(sf::RenderWindow &window) {
      s.setPosition(pos);
      window.draw(s);
    }

    sf::Vector2f get_pos() {
      return pos;  
    }

    sf::Vector2f get_vel(){
      return vel;  
    }

    void update_pyhsics(GravitySource &gs) {
      float dx = gs.get_pos().x - pos.x;
      float dy = gs.get_pos().y - pos.y;
      float dc = sqrt(dx * dx + dy * dy);
      
      float ic = 1.f / dc;
      float ic2 = ic * ic;

      float nx = dx * ic;
      float ny = dy * ic;

      float acc_x = nx * gs.get_str() * ic2 ;
      float acc_y = ny * gs.get_str() * ic2 ;

      vel.x += acc_x;
      vel.y += acc_y;

      pos.x += vel.x;
      pos.y += vel.y;
    }
    
    void set_color(sf::Color c) {
      s.setFillColor(c);
    }

    
  private:
};
