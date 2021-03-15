#include <iostream>
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

//  constants for the bricks
constexpr float blockWidth{60.f};
constexpr float blockHeight{20.f};
constexpr int countBlocksX{11};
constexpr int countBlocksY{4};

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
         {
            velocity.x = -paddleVelocity;
         }
         else if (Keyboard::isKeyPressed(Keyboard::Key:: Right) && right() < windowWidth)
         {
            velocity.x = paddleVelocity;
         }
         else
         {
            velocity.x = 0;
         }
    }
    
    float x()       { return shape.getPosition().x; }
    float y()       { return shape.getPosition().y; }
    float left()    { return x() - shape.getSize().x / 2.f; }
    float right()   { return x() + shape.getSize().x / 2.f; }
    float top()     { return y() - shape.getSize().y / 2.f; }
    float bottom()  { return x() + shape.getSize().y / 2.f; }
    
};

//  Brick "class"
struct Brick
{
    RectangleShape shape;
    
    //  This boolean value will be used to check
    //  whether a brick has been hit or not.
    bool destroyed{false};
    
    //  The constructor is almost identical to the 'paddle' one.
    Brick(float mX, float mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({blockWidth, blockHeight});
        shape.setFillColor(Color::Yellow);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }
    
    float x()       { return shape.getPosition().x; };
    float y()       { return shape.getPosition().y; };
    float left()    { return x() - shape.getSize().x / 2.f; }
    float right()   { return x() + shape.getSize().x / 2.f; }
    float top()     { return y() - shape.getSize().y / 2.f; }
    float bottom()  { return y() + shape.getSize().y / 2.f; }
};

//  Dealing with collisions: Let's define a generic function
//  to check if two shapes are intersecting (colliding).
template <class T1, class T2> 
bool isIntersecting(T1& mA, T2& mB)
{
    return  mA.right() >= mB.left() && mA.left() <= mB.right() && 
            mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

//  Let's define a function that deals with paddle/ball collision.
void testCollision(Paddle& mPaddle, Ball& mBall)
{
    //  Exits function if there's no intersection.
    if(!isIntersecting(mPaddle, mBall)) return;

    mBall.velocity.y = -ballVelocity;
    if(mBall.x() < mPaddle.x())
        mBall.velocity.x = -ballVelocity;
    else
        mBall.velocity.x = ballVelocity;
}

int main()
{
    //  ball instance
    Ball ball {windowWidth/2, windowHeight/2};
    
    //  paddle starting position
    Paddle paddle {windowWidth / 2, windowHeight - 50};
    
    //  We will use a 'std::vector' to contain any number
    //  of "brick' instances.
    vector<Brick> bricks;
    
    //  we fill up our vector via a 2D for loop, creating
    //  bricks in a grid-like pattern.
    for(int iX{0}; iX < countBlocksX; ++iX)
        for(int iY{0}; iY < countBlocksY; ++iY)
            bricks.emplace_back(
                (iX + 1) * (blockWidth + 3) + 22, (iY + 2) * (blockHeight + 3));
    
    RenderWindow window{{windowWidth, windowHeight}, "Arkanoid - 7"};
    window.setFramerateLimit(60);
    
     while (window.isOpen())
    {
       
        Event event;
        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        
        window.clear(Color::Black);
        ball.update();
        
        //  paddle update
        paddle.update();
        
        //  collision test
        testCollision(paddle, ball);
        
        //  draw ball shape on the window
        window.draw(ball.shape);
        
        //  draw paddle shape on the window
        window.draw(paddle.shape);
        
        //  We must draw every brick on the window!
        //  Let's use a modern C++11 for-each loop, that allows
        //  us to intuitively say: "Draw every 'brick' in 'bricks'".
        for(auto& brick : bricks) window.draw(brick.shape);
        
        window.display();
    }
    
    return 0;
}