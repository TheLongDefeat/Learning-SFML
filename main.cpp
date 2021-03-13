#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//  const defines an immutable compile-time value
constexpr int WINDOW_WIDTH{800};
constexpr int WINDOW_HEIGHT{600};
constexpr float BALL_RADIUS{10.f};

//  Let's create a class for our Ball
//  'struct' == 'class' in c++
struct Ball
{
    //  CircleShape is an SFML class that
    //  defines a renderable circle
    CircleShape shape;
    
    //  Ball Constructor
    //  argument mX -> starting x coordinate
    //  argument mY -> starting y coordinate
    Ball(float mX, float mY)
    {
        //  Apply position, radius, color and origin
        //  to the CircleShape 'shape'
        shape.setPosition(mX, mY);
        shape.setRadius(BALL_RADIUS);
        shape.setFillColor(Color::Red);
        shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    }
};

int main()
{
    
    //  Create ball instance
    //  positioned at the center of the window
    Ball ball {WINDOW_WIDTH/2, WINDOW_HEIGHT/2};
    
    // Creation of the game window
    RenderWindow window{{WINDOW_WIDTH, WINDOW_HEIGHT}, "Arkanoid - 2"};
    window.setFramerateLimit(60);
    
    // Game loop
    while(true)
    {
        //  "Clear" the window from the previously drawn graphics
        window.clear(Color::Black);
        
        //  if "Escape" is pressed, break out of the loop
        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        
        //  show the window contents
        window.draw(ball.shape);
        window.display();
    }
    return 0;
}