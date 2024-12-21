#include <SFML/Graphics.hpp>
#include <physfs.h>
int main()
{
    PHYSFS_init(NULL);
    PHYSFS_mount("assets.zip", "assets", 1); 
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);
    sf::Clock deltaClock; 
    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.display();
        sf::Time delta = deltaClock.restart(); 
    }

    PHYSFS_deinit();
}
