#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

//  const defines an immutable compile-time value
const int WINDOW_WIDTH{800};
const int WINDOW_HEIGHT{600};

int main()
{
    // Creation of the game window
    RenderWindow window{{WINDOW_WIDTH, WINDOW_HEIGHT}, "Arkanoid - 1"};
    window.setFramerateLimit(60);
    
    // Game loop
    while(true)
    {
        //  "Clear" the window from the previously drawn graphics
        window.clear(Color::Black);
        
        //  if "Escape" is pressed, break out of the loop
        if(Keyboard::isKeyPressed(Keyboard::Key::Escape))
            break;
        
        //  show the window contents
        window.display();
    }
    return 0;
}