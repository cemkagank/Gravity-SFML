#include "Particle.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>


class ParticleController {
private:
  std::vector<Particle> particles;
public:

  void add_particles(sf::Vector2f pos, int amount){
    for (int i = 0; i < amount; i++) {
      particles.push_back(Particle(pos, 0.2f, 0 , sf::Color::White));
    }
  }
  void toggle_orbit_history(){}
  void toggle_orbit_style(){}
  void clear(){}
  void render(sf::RenderWindow &window){
    for (Particle &p : particles) {
      window.draw(p);
    }

  }
};
