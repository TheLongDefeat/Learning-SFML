#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowWidth{800};
constexpr int windowHeight{600};

constexpr float ballRadius{10.f};

//  Let's add the velocity
constexpr float ballVelocity{8.f};

struct Ball
{

    CircleShape shape;
    
    //  2D vector that stores the ball's velocity
    Vector2f velocity{-ballVelocity, -ballVelocity};
    
    Ball(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }
    
    //  Let's "update" the ball: move it's shape
    //  by the current velocity
    void update() { shape.move(velocity); }
    
};

int main()
{
    Ball ball {windowWidth/2, windowHeight/2};
    
    RenderWindow window{{windowWidth, windowHeight}, "Arkanoid - 3"};
    window.setFramerateLimit(60);
    
     while(true)
    {
       
        window.clear(Color::Black);
        
        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
        
        ball.update();
        
        window.draw(ball.shape);
        window.display();
    }
    
    return 0;
}