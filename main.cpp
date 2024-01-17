#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace std;




vector<vector<bool>> createMineMap(int x, int y);
vector<vector<int>> checkForMinesMap(vector<vector<bool>> mineMap);

void centerTextOrigin(sf::Text &text);


int main() {
    auto test = createMineMap(15,10);

    for(auto a : test)
    {
        for (auto b : a)
        {
            cout << b << '\t';
        }
        cout << endl << endl;
    }
    auto test2 = checkForMinesMap(test);

    cout << endl << endl;
    for(auto a : test2)
    {
        for (auto b : a)
        {
            cout << b << '\t';
        }
        cout << endl << endl;
    }


    sf::RenderWindow display(sf::VideoMode(500,500),"Chuj");
    display.setFramerateLimit(10);

    sf::Event event;


    sf::RectangleShape box(sf::Vector2f(20,20));
    box.setFillColor(sf::Color::Blue);
    box.setOrigin(10,10);

    sf::Font font;
    if (!font.loadFromFile("../cmake-build-debug/Pixelboy.ttf")) {
        std::cerr << "Cannot load font" << std::endl;
        return 0;
    }
    font.setSmooth(false);

    sf::Text mineNumber("0", font, 20);
    centerTextOrigin(mineNumber);

    while(display.isOpen())
    {
        while(display.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) display.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                display.close();
                main();
            }
            
        }


        display.clear();

        for(int i = 0; i<test2.size(); i++)
        {
            for(int j = 0; j<test2[0].size(); j++)
            {
                if(test2[i][j]==0) box.setFillColor(sf::Color::Green);
                if(test2[i][j]> 0 && test2[i][j] < 20) box.setFillColor(sf::Color::Blue);
                if(test2[i][j] > 20) box.setFillColor(sf::Color::Red);

                box.setPosition(20 + j*22, 20 + i*22);

                if(test2[i][j] < 20) mineNumber.setString(to_string(test2[i][j]));
                if(test2[i][j] > 20) mineNumber.setString("X");

                mineNumber.setPosition(box.getPosition());
                display.draw(box);
                display.draw(mineNumber);
            }
        }









        display.display();



    }



    return 0;
}



vector<vector<bool>> createMineMap(int x, int y)
{
    vector<vector<bool>> map;
    srand(time(NULL));
    for(int i = 0; i < y ; i++)
    {
        vector<bool> row;
        for(int j = 0; j < x ; j++)
        {
            if(rand()%10==0) row.push_back(true);
            else row.push_back(false);
        }
        map.push_back(row);
    }
    return map;
}


vector<vector<int>> checkForMinesMap(vector<vector<bool>> mineMap)
{
    int x = mineMap[0].size();
    int y = mineMap.size();

    vector<vector<int>> solutionMap(y,vector<int>(x,0));

    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            if(mineMap[i][j]==false) continue;

            solutionMap[i][j]=90;


            if(i!=0 && j!=0)
            {
                solutionMap[i-1][j-1]++;
            }

            if(i!=0)
            {
                solutionMap[i-1][j]++;
            }

            if(j!=0)
            {
                solutionMap[i][j-1]++;
            }



            if(i!=y-1 && j!=x-1)
            {
                solutionMap[i+1][j+1]++;
            }

            if(i!=y-1)
            {
                solutionMap[i+1][j]++;
            }

            if(j!=x-1)
            {
                solutionMap[i][j+1]++;
            }



            if(i!=0 && j!=x-2)
            {
                solutionMap[i-1][j+1]++;
            }

            if(i!=y-1 && j!=0)
            {
                solutionMap[i+1][j-1]++;
            }





        }
    }





    return solutionMap;


}


void centerTextOrigin(sf::Text &text)
{
    text.setOrigin(round(text.getGlobalBounds().getSize().x / 2.f + text.getLocalBounds().getPosition().x)
            , round(text.getGlobalBounds().getSize().y / 2.f + text.getLocalBounds().getPosition().y));
}