#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

constexpr int windowWidth{800};
constexpr int windowHeight{600};

//  Constants for ball
constexpr float ballRadius{10.f};   //  This define the size of the ball
constexpr float ballVelocity{8.f};  //  This defines the speed the ball will travel at

//  Constants for the paddle
constexpr float paddleWidth{60.f}; 
constexpr float paddleHeight{20.f};
constexpr float paddleVelocity{8.f};

struct Ball
{

    CircleShape shape;    
    Vector2f velocity{-ballVelocity, -ballVelocity}; // stores the ball's velocity
    
    Ball(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setRadius(ballRadius);
        shape.setFillColor(Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }
    
    void update() // update location of the ball by using the current velocity
    { 
        shape.move(velocity); 
        
        /*
         * The if loop will keep the ball within boundaries of the window.
         * If it hits one of the "walls" the ball will bounce back and travel
         * in the opposite direction.
         * 
         * This is determined by measuring whether the radius of the ball exceeds
         * the height and the width of the window.
         */ 
        
        if (left() < 0) 
            velocity.x = ballVelocity;
        else if (right() > windowWidth) 
            velocity.x = -ballVelocity;
                    
        if (top() < 0)
            velocity.y = ballVelocity;
        else if (bottom() > windowHeight)
            velocity.y = -ballVelocity;
    } 
    
    //  We can also create "property" methods to easily
    //  get commonly used values
    float x()       { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getRadius(); }
    float right()   { return x() + shape.getRadius(); }
    float top()     { return y() - shape.getRadius(); }
    float bottom()  { return y() + shape.getRadius(); }
};

//  Paddle "class"
struct Paddle
{
    //  RectangleShape is an SFML class that defines
    //  a renderable rectangular shape.
    RectangleShape shape;
    Vector2f velocity;
    
    //  As with the ball, we construct the paddle with
    //  arguments for initial position and pass the values
    //  to the SFML 'shape'
    Paddle(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(Color::Red);
        shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }
    
    void update()
    {
        shape.move(velocity);
        
        /*
         * To move the paddle, we check if the user is pressing
         * the left or right arrow key: if so, we change the velocity.
         * 
         * To keep the paddle "inside the window", we change the velocity
         * only if its position is inside the window.
         */ 
         
         if (Keyboard::isKeyPressed(Keyboard::Key:: Left) && left() > 0)
            velocity.x = -paddleVelocity;
         else if (Keyboard::isKeyPressed(Keyboard::Key:: Right) && right() < windowWidth)
            velocity.x = paddleVelocity;
        else
            velocity.x = 0;
    }
    
    float x()       { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getSize().x / 2.f; }
    float right()   { return x() + shape.getSize().x / 2.f; }
    float top()     { return y() - shape.getSize().y / 2.f; }
    float bottom()    { return x() + shape.getSize().y / 2.f; }
    
};

int main()
{
    //  ball instance
    Ball ball {windowWidth/2, windowHeight/2};
    
    //  paddle starting position
    Paddle paddle {windowWidth / 2, windowHeight - 50};
    
    RenderWindow window{{windowWidth, windowHeight}, "Arkanoid - 5"};
    window.setFramerateLimit(60);
    
     while (window.isOpen())
    {
        window.clear(Color::Black);
       
        Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        ball.update();
        
        //  paddle update
        paddle.update();
        
        window.draw(ball.shape);
        
        //  draw paddle shape on the window
        window.draw(paddle.shape);
        
        window.display();
    }
    
    return 0;
}