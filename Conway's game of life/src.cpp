#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <array>

const int grid_size = 400;
const int cell_size = 2;

bool isAlive(std::array<std::array<bool, grid_size>, grid_size>& game, const int x, const int y)
{
    int neighbour_count = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (!(i == 0 && j == 0))
            {
                if (game[y + i][x + j])
                {
                    neighbour_count++;
                }
            }
        }
    }



    if (game[y][x])
    {
        if (neighbour_count < 2)
        {
            return false;
        }
        else if (neighbour_count < 4)
        {
            return true;
        }
        else if (neighbour_count > 3)
        {
            return false;
        }
    }
    else
    {
        if (neighbour_count == 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}


int main()
{

    std::array<std::array<bool, grid_size>, grid_size> display{};
    std::array<std::array<bool, grid_size>, grid_size> swap{};

    for (auto& row : display)
    {
        std::generate(row.begin(), row.end(), []()
            {
            return rand() % 10 == 0 ? 1 : 0;
            });
    }

    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Insert Text Here");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {

        sf::Event event;
        std::srand(std::time(nullptr));
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            display[sf::Mouse::getPosition(window).y / cell_size][sf::Mouse::getPosition(window).x / cell_size] = true;
        }



        window.clear(sf::Color::Black);

        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                if(display[i][j])
                {
                    sf::RectangleShape drawer;
                    drawer.setPosition({ (float)(j * cell_size),(float)(i * cell_size) });
                    drawer.setSize({ (float)cell_size,(float)cell_size });
                    window.draw(drawer);
                }


            }
        }
        for (int i = 0; i < grid_size; i++)
        {
            for (int j = 0; j < grid_size; j++)
            {
                swap[i][j] = isAlive(display, j, i);
            }
        }
        std::copy(swap.begin(), swap.end(), display.begin());

        window.display();
    }
    return 0;
}
