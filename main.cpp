#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <vector>
#include <iostream>
#include <cmath>

const sf::Color VECTOR_COLOR = sf::Color::White;
const int SCREEN_X = 300;
const int SCREEN_Y = 300;
const int SCALING_FACTOR = 15;
typedef struct vector2{
  float x;
  float y;

  vector2(float x = 0, float y = 0) : x(x), y(y) {}

  void draw(sf::RenderWindow* window){
    sf::Vertex line[] =
    {
    sf::Vertex(sf::Vector2f(SCREEN_X, SCREEN_Y)),
    sf::Vertex(sf::Vector2f(SCREEN_X + x * SCALING_FACTOR, SCREEN_Y - y * SCALING_FACTOR))
    };

    sf::CircleShape point(2.f);
    point.setFillColor(sf::Color::Blue);
    point.setPosition(SCREEN_X + x * SCALING_FACTOR - 3, SCREEN_Y - y * SCALING_FACTOR - 3);
    window->draw(line, 2, sf::Lines);
    window->draw(point);
  }

    // Scalar multiplication
    vector2 operator*(int scalar) const {
        return vector2{x * scalar, y * scalar};
    }

    // Friend function to enable commutative property for scalar multiplication
    friend vector2 operator*(int scalar, const vector2& vec) {
        return vec * scalar;
    }

    // Vector multiplication
    /* vector2 operator*(vector2 vector) const { */
    /* } */
} vector2;

typedef struct vector3{
  int x;
  int y;
  int z;
} vector3;

typedef struct r2{
  std::vector<vector2> vectors;

  void draw(sf::RenderWindow* window){
    for (vector2& vector : vectors){
      vector.draw(window);
    }
  }

  void reset(){
    vectors.clear();
    populate_grid();

  }

  void linear_transformation(vector2 i, vector2 j){
    for (vector2& vector : vectors){
      vector.x = (vector.x*i.x) + (vector.y*j.x);
      vector.y = (vector.x*i.y) + (vector.y*j.y);
    }
  }

  void x_inc(){
    for (vector2& vector : vectors){
      vector.x++;
    }
  }

  void x_dec(){
    for (vector2& vector : vectors){
      vector.x--;
    }
  }

  void y_inc(){
    for (vector2& vector : this->vectors){
      vector.y++;
    }
  }

  void y_dec(){
    for (vector2& vector : this->vectors){
      vector.y--;
    }
  }

  void add(int x, int y){
    vectors.push_back(vector2(x, y));
  }
 
  void populate_grid(){
    for (int x = -10; x < 10; x++){
      for (int y = -10; y < 10; y++){
        this->add(x, y);
      }
    }
  }

  void print(){
    for (vector2& vector : vectors){
      std::cout << "(" << vector.x << "," << vector.y << ") ";
    }
    std::cout << std::endl;
  }

} r2;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(SCREEN_X*2, SCREEN_Y*2), "My window");
    window.setFramerateLimit(10);

    r2 space;
    space.populate_grid();
    space.print();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
          space.reset();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
          space.x_inc();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
          space.x_dec();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
          space.y_inc();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
          space.linear_transformation({1,0}, {0.2,1});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
          space.linear_transformation({0.8,0}, {0,1});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
          space.linear_transformation(vector2(0.8,0), vector2(0,1/0.8));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
          space.linear_transformation(vector2(cos(0.5), -sin(0.5)), vector2(sin(0.5),cos(0.5)));
        }
        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        space.print();

        space.draw(&window);
        // end the current frame
        window.display();
    }

    return 0;
}
