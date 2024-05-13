#include "ParticleController.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720
#define FPS 60
#define CENTER_W (float)WIDTH / 2
#define CENTER_H (float)HEIGHT / 2

// NOTE: Add imgui if possible if none add own gui

class Game {

public:
  Game() { init_context(); }

  void run() {
    while (window.isOpen()) {
      sf::Event event;

      while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
          window.close();
        } else if (event.type == sf::Event::Resized) {
          sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
          window.setView(sf::View(visibleArea));
        } else if (event.type == sf::Event::MouseButtonPressed) {
          sf::Vector2i mouse = sf::Mouse::getPosition(window);
          pc.add_particles(sf::Vector2f{(float)mouse.x, (float)mouse.y}, 20);
          break;
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::P:
              std::cout << "DBG\n" << std::endl;
              break;
            default:
            break;
            }
        }

        window.clear();
        pc.render(window);
        window.draw(text);
        window.display();
      }
    }
  }

private:
  sf::Font font;
  sf::Text text;
  sf::Text fps;
  sf::ContextSettings settings;
  sf::RenderWindow window;
  ParticleController pc;

  void init_context() {
    font.loadFromFile("./res/fx.ttf");
    text.setFont(font);
    text.setString(
        "s - toggle orbit\nl - toggle orbit style\nr - clear all\nleft click - "
        "spawn source\nright click - spawn particles");
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(16);
    settings.antialiasingLevel = 8;
    window.setFramerateLimit(FPS);
    window.setVerticalSyncEnabled(true);
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Gravityv2", sf::Style::Default,
                  settings);
  }
};
