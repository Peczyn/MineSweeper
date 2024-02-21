/*
 * One of my first projects ever and still learning SFML
 * You can highlight a field by right-clicking
 * By leftclicking you show the field
 * If you shown all the emty fields you win
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace std;

class Field{
public:
    int value;
    bool isMined;
    bool wasShown;
    bool wasHighlited;

    Field()= default;
    explicit Field(bool x): isMined(x),value(0),wasShown(false),wasHighlited(false){}
};

sf::RenderWindow display(sf::VideoMode(600,600),"Saper");
sf::Event event;


sf::Color color0(0x93A8ACFF);
sf::Color color1(0x918EF4FF);
sf::Color color2(0x1A936FFF);
sf::Color color3(0xB80C09FF);
sf::Color color4(0x2708A0FF);
sf::Color color5(0x653239FF);
sf::Color color6(0xB287A5FF);
sf::Color color7(0xF4442EFF);
sf::Color color8(0xF0E2A3FF);
sf::Color colorMine(0xA61C3CFF);

sf::Color colorHidden(0xFF);

vector<vector<Field>> createMineMap(int x, int y, int &mineCounter);
void checkForMinesMap(vector<vector<Field>> &mineMap);
void centerTextOrigin(sf::Text &text);
bool containsMouse(const sf::RectangleShape& box,sf::Vector2i coords);
void checkIfFieldShown(vector<vector<Field>> &test, int i, int j);

int main() {
    display.setFramerateLimit(240);

    int mapWidth = 15;
    int mapHeigth = 15;

    int spaceBetweenFields = 1;
    int fieldSize = min(display.getSize().x/(mapWidth+spaceBetweenFields*0.1*mapWidth),display.getSize().y/(mapHeigth+spaceBetweenFields*0.1*mapHeigth));

    int mineCounter = 0;

    vector<vector<Field>> mineField = createMineMap(mapWidth,mapHeigth,mineCounter);
    checkForMinesMap(mineField);


    sf::Font font;
    if (!font.loadFromFile("../cmake-build-debug/Pixelboy.ttf")) {
        std::cerr << "Cannot load font" << std::endl;
        return 1;
    }
    font.setSmooth(false);


    sf::RectangleShape box(sf::Vector2f(fieldSize,fieldSize));
    box.setFillColor(sf::Color::Blue);
    box.setOrigin(fieldSize/2,fieldSize/2);

    sf::Text mineNumber("0", font, fieldSize);
    centerTextOrigin(mineNumber);
    mineNumber.setOutlineThickness(1.5f);
    mineNumber.setOutlineColor(sf::Color::Black);

    sf::Text ZaminowanePoleText("X", font, fieldSize);
    ZaminowanePoleText.setFillColor(sf::Color::Red);
    centerTextOrigin(ZaminowanePoleText);
    ZaminowanePoleText.setOutlineThickness(0.5f);
    ZaminowanePoleText.setOutlineColor(sf::Color::Black);

    sf::Text CongratulationsText("Congratulations!", font, display.getSize().x / 8);
    centerTextOrigin(CongratulationsText);
    CongratulationsText.setPosition(display.getSize().x / 2, display.getSize().y / 2);
    CongratulationsText.setOutlineThickness(2.f);
    CongratulationsText.setOutlineColor(sf::Color::Black);

    sf::Text GameOverText("GAME OVER!", font, display.getSize().x/8);
    centerTextOrigin(GameOverText);
    GameOverText.setPosition(display.getSize().x/2, display.getSize().y/2);
    GameOverText.setOutlineThickness(2.f);
    GameOverText.setOutlineColor(sf::Color::Black);

    sf::Vector2i MouseCoordsLeftClick;
    sf::Vector2i MouseCoordsRightClick;

    bool GameOver = false;
    bool GameWin = false;

    bool Menu = true;
    bool Playing = false;

    int shownTilesCounter;
    while(display.isOpen())
    {
        display.clear();
        while(display.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) display.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) main();

            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) MouseCoordsLeftClick = sf::Mouse::getPosition(display);
            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) MouseCoordsRightClick = sf::Mouse::getPosition(display);
        }

        if(Menu)
        {



            Menu = false;
            Playing = true;
        }

        shownTilesCounter = 0;
        if(Playing) {
            //Checking fields value and showing them
            for (int i = 0; i < mineField.size(); i++) {
                for (int j = 0; j < mineField[0].size(); j++) {
                    auto a = &mineField[i][j];

                    box.setPosition((fieldSize + display.getSize().x -
                                     (fieldSize + spaceBetweenFields) * mineField[0].size()) / 2 +
                                    j * (fieldSize + spaceBetweenFields),
                                    (fieldSize + display.getSize().x -
                                     (fieldSize + spaceBetweenFields) * mineField.size()) / 2 +
                                    i * (fieldSize + spaceBetweenFields));
                    box.setFillColor(sf::Color(0x515151FF));

                    //Setting field color and text value
                    if (a->value == 0) {
                        mineNumber.setFillColor(color0);
                        box.setFillColor(color0);

                    }
                    else if (a->value == 1) {
                        mineNumber.setFillColor(color1);
                        box.setFillColor(color0);
                    }
                    else if (a->value == 2) {
                        mineNumber.setFillColor(color2);
                        box.setFillColor(color0);
                    }
                    else if (a->value == 3) {
                        mineNumber.setFillColor(color3);
                        box.setFillColor(color0);
                    }
                    else if (a->value == 4) {
                        mineNumber.setFillColor(color4);
                        box.setFillColor(color0);
                    }
                    else if (a->value == 5) {
                        mineNumber.setFillColor(color5);
                        box.setFillColor(color0);
                    }
                    else if (a->value == 6) {
                        mineNumber.setFillColor(color6);
                        box.setFillColor(color0);
                    }
                    else if (a->value == 7) {
                        mineNumber.setFillColor(color7);
                        box.setFillColor(color0);
                    }
                    else if (a->value == 8) {
                        mineNumber.setFillColor(color8);
                        box.setFillColor(color0);
                    }
                    else
                    {
                        mineNumber.setFillColor(sf::Color(0x555555FF));
                        box.setFillColor(colorMine);
                    }



                    //Setting value for field
                    if (a->value == 0) mineNumber.setString(" ");
                    else if (a->value > 0 && a->value < 20) mineNumber.setString(to_string(a->value));
                    else mineNumber.setString("*");


                    //Checking if field was shown
                    if (containsMouse(box, MouseCoordsLeftClick)) {
                        if (a->isMined) GameOver = true;

                        a->wasShown = true;
                        a->wasHighlited = false;
                    }

                    //Checking if field was highligthed
                    if (containsMouse(box, MouseCoordsRightClick) && !a->wasShown) {
                        a->wasHighlited = !a->wasHighlited;
                        MouseCoordsRightClick = sf::Vector2i();
                    }

                    //If field was shown and it's value is 0 then show all alied fields with value 0
                    if (mineField[i][j].value == 0 && mineField[i][j].wasShown) {
                        checkIfFieldShown(mineField, i, j);
                    }


                    //Drawing lower fields
                    mineNumber.setPosition(box.getPosition());
                    display.draw(box);
                    display.draw(mineNumber);


                    //Drawing over layer
                    ZaminowanePoleText.setPosition(box.getPosition());

                    //Over layer color set
                    box.setFillColor(sf::Color(0x222222FF));

                    //If field was shown then make it's over layer transparent
                    if (mineField[i][j].wasShown) box.setFillColor(sf::Color::Transparent);

                    //GameOver/Win
                    if (!GameOver) {
                        display.draw(box);
                    } else if (!GameWin) {
                        display.draw(GameOverText);
                    } else {
                        display.draw(CongratulationsText);
                    }

                    //Highligthing a field
                    if (mineField[i][j].wasHighlited) display.draw(ZaminowanePoleText);
                    if (mineField[i][j].wasShown) shownTilesCounter++;

                    //Check if game is won
                    if (shownTilesCounter == mineField.size() * mineField[0].size() - mineCounter && !GameOver)
                        GameWin = GameOver = true;
                }
            }
        }
        display.display();
    }
    return 0;
}



vector<vector<Field>> createMineMap(int x, int y, int &mineCounter)
{
    vector<vector<Field>> map;
    srand(time(nullptr));
    for(int i = 0; i < y ; i++)
    {
        vector<Field> row;
        for(int j = 0; j < x ; j++)
        {

            if(rand()%10==0)
            {
                row.push_back(Field(true));
                mineCounter++;
            }
            else row.push_back(Field(false));
        }
        map.push_back(row);
    }
    return map;
}


void checkForMinesMap(vector<vector<Field>> &mineMap)
{
    int x = mineMap[0].size();
    int y = mineMap.size();



    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            if(!mineMap[i][j].isMined) continue;


            mineMap[i][j].value=222;


            if(i!=0 && j!=0)
            {
                mineMap[i-1][j-1].value++;
            }

            if(i!=0)
            {
                mineMap[i-1][j].value++;
            }

            if(j!=0)
            {
                mineMap[i][j-1].value++;
            }



            if(i!=y-1 && j!=x-1)
            {
                mineMap[i+1][j+1].value++;
            }

            if(i!=y-1)
            {
                mineMap[i+1][j].value++;
            }

            if(j!=x-1)
            {
                mineMap[i][j+1].value++;
            }



            if(i!=0 && j!=x-1)
            {
                mineMap[i-1][j+1].value++;
            }

            if(i!=y-1 && j!=0)
            {
                mineMap[i+1][j-1].value++;
            }

        }
    }
}


void centerTextOrigin(sf::Text &text)
{
    text.setOrigin(round(text.getGlobalBounds().getSize().x / 2.f + text.getLocalBounds().getPosition().x)
            , round(text.getGlobalBounds().getSize().y / 2.f + text.getLocalBounds().getPosition().y));
}


bool containsMouse(const sf::RectangleShape& box,sf::Vector2i coords)
{
    if(sf::Rect(box.getGlobalBounds()).contains(coords.x, coords.y)) return true;
    return false;
}

void checkIfFieldShown(vector<vector<Field>> &test, int i, int j)
{
    if(i!=0 && j!=0 && !test[i-1][j-1].isMined)
    {
        test[i-1][j-1].wasShown = true;
    }

    if(i!=0  && !test[i-1][j].isMined)
    {
        test[i-1][j].wasShown = true;
    }

    if(j!=0  && !test[i][j-1].isMined)
    {
        test[i][j-1].wasShown = true;
    }



    if(i!=test.size()-1 && j!=test[0].size()-1  && !test[i+1][j+1].isMined)
    {
        test[i+1][j+1].wasShown = true;
    }

    if(i!=test.size()-1 && !test[i+1][j].isMined)
    {
        test[i+1][j].wasShown = true;
    }

    if(j!=test[0].size()-1 && !test[i][j+1].isMined)
    {
        test[i][j+1].wasShown = true;
    }



    if(i!=0 && j!=test[0].size()-1 && !test[i-1][j+1].isMined)
    {
        test[i-1][j+1].wasShown = true;
    }

    if(i!=test.size()-1 && j!=0 && !test[i+1][j-1].isMined)
    {
        test[i+1][j-1].wasShown = true;
    }
}