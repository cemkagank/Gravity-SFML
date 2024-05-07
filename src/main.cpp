#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "gravity.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <vector>

#define WIDTH 1280
#define HEIGHT 720
#define FPS 120
#define CENTER_W (float)WIDTH/2
#define CENTER_H (float)HEIGHT/2

bool Particle::orbitHistory = false;
sf::PrimitiveType Particle::ltype = sf::LinesStrip;

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


void populate(std::vector<Particle> &arr){
  int num_particle = 200;
  for (int i =0 ; i < num_particle; i++) {
      float val = (float)i / (float)num_particle;
      sf::Color col = interpolate(val);
      arr.push_back(Particle(CENTER_W + 3,260,4, 0.2 + (0.1/ num_particle) * i , col) );

    }
}

void add_particles(std::vector<Particle> &arr, float x , float y){
  for (int i =0 ; i < 200; i++) {
      float val = (float)i  / (float)200;
      sf::Color col = interpolate(val);
      arr.push_back(Particle( x ,y  ,4, 0.2 + (0.1/ 200) * i, col ));

    }
}

void reset(std::vector<Particle> &arr, std::vector<GravitySource> &gr) {
  arr.clear();
  gr.clear();
}


int main() {
  // Font loading
  sf::Font font;
  font.loadFromFile("./res/font.ttf");

  // Text
  sf::Text text;
  text.setFont(font);
  text.setString("s - toggle orbit\nl - toggle orbit style\nr - clear all\nleft click - spawn source\nright click - spawn particles");
  text.setFillColor(sf::Color::White);
  text.setCharacterSize(16);

  // Create window and set options
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Gravity" , sf::Style::Default, settings);
  window.setFramerateLimit(FPS);
  window.setVerticalSyncEnabled(true);

  // Gravity source creation
  GravitySource s1 = GravitySource(CENTER_W - 500, CENTER_H,9000);
  std::vector<GravitySource> sources;
  sources.push_back(s1);

  // Particle creation
  std::vector<Particle> particles;
  populate(particles);
  
  // Needed to display fps in title
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
        } else if(event.mouseButton.button == sf::Mouse::Right){
          sf::Vector2i pos = sf::Mouse::getPosition(window);
          add_particles(particles, pos.x,pos.y);
          

        }
      } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::S) {
          Particle::toggle_orbit_history();
        } else if (event.key.code == sf::Keyboard::L) {
          Particle::switch_ltype();
        } else if (event.key.code == sf::Keyboard::R) {
          reset(particles,sources);
        }
          
      } else if (event.type == sf::Event::Resized) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
    }
      

    }

    window.clear();
    window.draw(text);
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
