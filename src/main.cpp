#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "gravity.hpp"
#include <cmath>
#include <vector>



#define WIDTH 1280
#define HEIGHT 720
#define FPS 120
#define CENTER_W (float)WIDTH/2
#define CENTER_H (float)HEIGHT/2


// TODO: add mouse event to add particle or power source 
// NOTE: new system to detect and attach particles to power sources.
// TODO: add sliders to change str of power source


sf::Color interpolate(float val){
  int r,g,b = 0;
  val = fmod(val, 1.0);
  if (val < 0.5f ) {
    b = 255 * (1.0f - 2 * val);
    g = 255 * 2 * val; 
  } else {
    g = 255 * (2.0f - 2 * val);
    r = 255 * (2 * val -1);
  }
  return sf::Color(r,g,b);
}

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity" , sf::Style::Default, settings);
  window.setFramerateLimit(FPS);
  GravitySource s1 = GravitySource(CENTER_W - 500, CENTER_H,9000);
  GravitySource s2 = GravitySource(CENTER_W + 500,CENTER_H,3000);
  GravitySource s3 = GravitySource(CENTER_W,160,3000);
  

  std::vector<GravitySource> sources;
  sources.push_back(s1);
  //sources.push_back(s2);
  //sources.push_back(s3);

  const int num_particle = 200;
  std::vector<Particle> particles;


  for (int i =0 ; i < num_particle; i++) {
    particles.push_back(Particle(CENTER_W + 3,260,4, 0.2 + (0.1/ num_particle) * i ));
    float val = (float)i / (float)num_particle;
    sf::Color col = interpolate(val);
    particles[i].set_color(col);

  }

  float fps = 0;
  sf::Clock clock;
  sf::Time prev = clock.getElapsedTime();
  sf::Time curr;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i pos = sf::Mouse::getPosition(window);
          sources.push_back(GravitySource(pos.x, pos.y, 3000));
        }
      } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::S) {
          Particle::toggle_orbit_history();
        }
      }
      

    }

    window.clear();

    for (int i=0 ; i < sources.size(); i++) {
      for (int j = 0; j < particles.size(); j++) {
        particles[j].update_pyhsics(sources[i]);
      }
    
    }

    for (auto s: sources) s.render(window);
    for (auto p: particles) p.render(window);

    window.display();

    curr = clock.getElapsedTime();
    fps = 1.0f / (curr.asSeconds() - prev.asSeconds());
    prev = curr;
    window.setTitle("Gravity - FPS: " + std::to_string(fps));

    
  }
}
