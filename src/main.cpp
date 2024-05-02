#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Gravity");
  window.setFramerateLimit(120);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear();
    window.display();
  }
}
