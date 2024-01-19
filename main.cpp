#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace std;

class Pole{
public:
    int wartosc;
    bool czyJestMina;
    bool czyByloOdsloniete;
    bool czyZaznaczonaMina;

    Pole(){}
    Pole(bool x): czyJestMina(x),wartosc(0),czyByloOdsloniete(false),czyZaznaczonaMina(false){}
};

sf::RenderWindow display(sf::VideoMode(600,600),"Saper");
sf::Event event;


sf::Color color0(0x93A8ACFF);
sf::Color color1(0x918EF4FF);
sf::Color color2(0x1A936FFF);
sf::Color color3(0xB80C09FF);
sf::Color color4(0x2708A0FF);
sf::Color color5(0x653239FF);
sf::Color color6(0xB287A3FF);
sf::Color color7(0xF4442EFF);
sf::Color color8(0xF0E2A3FF);
sf::Color colorMine(0xA61C3CFF);

sf::Color colorZasloniete(0xFF);




vector<vector<Pole>> createMineMap(int x, int y, int &licznik);
void checkForMinesMap(vector<vector<Pole>> &mineMap);

void centerTextOrigin(sf::Text &text);
bool containsMouse(sf::RectangleShape box,sf::Vector2i coords);

void sprawdzCzyOdsloniete(vector<vector<Pole>> &test, int i, int j);





int main() {
    display.setFramerateLimit(240);


    int mapaSzerokosc = 15;
    int mapaWysokosc = 15;

    int odstep_miedzy_kratkami = 1;
    int szerokosc_kratki = min(display.getSize().x/(mapaSzerokosc+odstep_miedzy_kratkami*0.1*mapaSzerokosc),display.getSize().y/(mapaWysokosc+odstep_miedzy_kratkami*0.1*mapaWysokosc));


    int licznikMin = 0;




    vector<vector<Pole>> test = createMineMap(mapaSzerokosc,mapaWysokosc,licznikMin);
    checkForMinesMap(test);



    sf::Font font;
    if (!font.loadFromFile("../cmake-build-debug/Pixelboy.ttf")) {
        std::cerr << "Cannot load font" << std::endl;
        return 0;
    }
    font.setSmooth(false);



    sf::RectangleShape box(sf::Vector2f(szerokosc_kratki,szerokosc_kratki));
    box.setFillColor(sf::Color::Blue);
    box.setOrigin(szerokosc_kratki/2,szerokosc_kratki/2);

    sf::Text mineNumber("0", font, szerokosc_kratki);
    centerTextOrigin(mineNumber);
    mineNumber.setOutlineThickness(1.5f);
    mineNumber.setOutlineColor(sf::Color::Black);

    sf::Text ZaminowanePoleText("X", font, szerokosc_kratki);
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


    sf::Clock zegar;
    bool GameOver = false;
    bool GameWin = false;

    bool Menu = true;
    bool Playing = false;

    int licznikOdslonietychPol;
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


        licznikOdslonietychPol = 0;

        if(Menu)
        {



            Menu = false;
            Playing = true;
        }

        if(Playing) {
            //Sprawdzanie wartosci pol oraz wypisywanie ich
            for (int i = 0; i < test.size(); i++) {
                for (int j = 0; j < test[0].size(); j++) {
                    auto a = &test[i][j];

                    box.setPosition((szerokosc_kratki + display.getSize().x -
                                     (szerokosc_kratki + odstep_miedzy_kratkami) * test[0].size()) / 2 +
                                    j * (szerokosc_kratki + odstep_miedzy_kratkami),
                                    (szerokosc_kratki + display.getSize().x -
                                     (szerokosc_kratki + odstep_miedzy_kratkami) * test.size()) / 2 +
                                    i * (szerokosc_kratki + odstep_miedzy_kratkami));
                    box.setFillColor(sf::Color(0x515151FF));


                    //Ustawianie koloru boxa i tekstu w zaleznosci od numeru pola
                    if (a->wartosc == 0) {
                        mineNumber.setFillColor(color0);
                        box.setFillColor(color0);

                    }
                    else if (a->wartosc == 1) {
                        mineNumber.setFillColor(color1);
                        box.setFillColor(color0);
                    }
                    else if (a->wartosc == 2) {
                        mineNumber.setFillColor(color2);
                        box.setFillColor(color0);
                    }
                    else if (a->wartosc == 3) {
                        mineNumber.setFillColor(color3);
                        box.setFillColor(color0);
                    }
                    else if (a->wartosc == 4) {
                        mineNumber.setFillColor(color4);
                        box.setFillColor(color0);
                    }
                    else if (a->wartosc == 5) {
                        mineNumber.setFillColor(color5);
                        box.setFillColor(color0);
                    }
                    else if (a->wartosc == 6) {
                        mineNumber.setFillColor(color6);
                        box.setFillColor(color0);
                    }
                    else if (a->wartosc == 7) {
                        mineNumber.setFillColor(color7);
                        box.setFillColor(color0);
                    }
                    else if (a->wartosc == 8) {
                        mineNumber.setFillColor(color8);
                        box.setFillColor(color0);
                    }
                    else
                    {
                        mineNumber.setFillColor(sf::Color(0x555555FF));
                        box.setFillColor(colorMine);
                    }


                    //Ustawianie wypisywanej wartosci dla danego pola
                    if (a->wartosc == 0) mineNumber.setString(" ");
                    else if (a->wartosc > 0 && a->wartosc < 20) mineNumber.setString(to_string(a->wartosc));
                    else mineNumber.setString("*");


                    //Sprawdzenie czy pole zostalo odsloniete
                    if (containsMouse(box, MouseCoordsLeftClick)) {
                        if (a->czyJestMina) GameOver = true;

                        a->czyByloOdsloniete = true;
                        a->czyZaznaczonaMina = false;
                    }

                    //Sprawdzenie czy pole zsotalo zaznaczone jako mina
                    if (containsMouse(box, MouseCoordsRightClick) && !a->czyByloOdsloniete) {
                        a->czyZaznaczonaMina = !a->czyZaznaczonaMina;
                        MouseCoordsRightClick = sf::Vector2i();
                    }


                    //Jezeli odsloniete pole == 0 to wtedy sasiednie pola tez zostaja odsloniete
                    if (test[i][j].wartosc == 0 && test[i][j].czyByloOdsloniete) {
                        sprawdzCzyOdsloniete(test, i, j);
                    }


                    //Wypisywanie dolnej warstwy
                    mineNumber.setPosition(box.getPosition());
                    display.draw(box);
                    display.draw(mineNumber);


                    //Wypisywanie gornej warstwy
                    ZaminowanePoleText.setPosition(box.getPosition());




                    //Ustawiamy bazowy kolor gornej warstwy
                    box.setFillColor(sf::Color(0x222222FF));

                    //Jesli pole bylo odsloniete to kolor boxa transparentny
                    if (test[i][j].czyByloOdsloniete) box.setFillColor(sf::Color::Transparent);




                    //Wyswietlanie Game Over/ Game Win
                    if (!GameOver) {
                        display.draw(box);
                    } else if (!GameWin) {
                        display.draw(GameOverText);
                    } else {
                        display.draw(CongratulationsText);
                    }

                    //Jezeli zaznaczona mina to wypisze znaczek zaznaczonej miny
                    if (test[i][j].czyZaznaczonaMina) display.draw(ZaminowanePoleText);
                    if (test[i][j].czyByloOdsloniete) licznikOdslonietychPol++;

                    //Sprawdzamy czy wszystkie wymagane pola zostaly odkryte
                    if (licznikOdslonietychPol == test.size() * test[0].size() - licznikMin && !GameOver)
                        GameWin = GameOver = true;
                }
            }
        }


        display.display();
    }

    return 0;
}



vector<vector<Pole>> createMineMap(int x, int y, int &licznik)
{
    vector<vector<Pole>> map;
    srand(time(NULL));
    for(int i = 0; i < y ; i++)
    {
        vector<Pole> row;
        for(int j = 0; j < x ; j++)
        {

            if(rand()%2==0)
            {
                row.push_back(Pole(true));
                licznik++;
            }
            else row.push_back(Pole(false));
        }
        map.push_back(row);
    }
    return map;
}


void checkForMinesMap(vector<vector<Pole>> &mineMap)
{
    int x = mineMap[0].size();
    int y = mineMap.size();



    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++)
        {
            if(!mineMap[i][j].czyJestMina) continue;


            mineMap[i][j].wartosc=222;


            if(i!=0 && j!=0)
            {
                mineMap[i-1][j-1].wartosc++;
            }

            if(i!=0)
            {
                mineMap[i-1][j].wartosc++;
            }

            if(j!=0)
            {
                mineMap[i][j-1].wartosc++;
            }



            if(i!=y-1 && j!=x-1)
            {
                mineMap[i+1][j+1].wartosc++;
            }

            if(i!=y-1)
            {
                mineMap[i+1][j].wartosc++;
            }

            if(j!=x-1)
            {
                mineMap[i][j+1].wartosc++;
            }



            if(i!=0 && j!=x-1)
            {
                mineMap[i-1][j+1].wartosc++;
            }

            if(i!=y-1 && j!=0)
            {
                mineMap[i+1][j-1].wartosc++;
            }

        }
    }
    return;
}


void centerTextOrigin(sf::Text &text)
{
    text.setOrigin(round(text.getGlobalBounds().getSize().x / 2.f + text.getLocalBounds().getPosition().x)
            , round(text.getGlobalBounds().getSize().y / 2.f + text.getLocalBounds().getPosition().y));
}


bool containsMouse(sf::RectangleShape box,sf::Vector2i coords)
{
    if(sf::Rect(box.getGlobalBounds()).contains(coords.x, coords.y)) return true;
    return false;
}

void sprawdzCzyOdsloniete(vector<vector<Pole>> &test, int i, int j)
{
    if(i!=0 && j!=0 && !test[i-1][j-1].czyJestMina)
    {
        test[i-1][j-1].czyByloOdsloniete = true;
    }

    if(i!=0  && !test[i-1][j].czyJestMina)
    {
        test[i-1][j].czyByloOdsloniete = true;
    }

    if(j!=0  && !test[i][j-1].czyJestMina)
    {
        test[i][j-1].czyByloOdsloniete = true;
    }



    if(i!=test.size()-1 && j!=test[0].size()-1  && !test[i+1][j+1].czyJestMina)
    {
        test[i+1][j+1].czyByloOdsloniete = true;
    }

    if(i!=test.size()-1 && !test[i+1][j].czyJestMina)
    {
        test[i+1][j].czyByloOdsloniete = true;
    }

    if(j!=test[0].size()-1 && !test[i][j+1].czyJestMina)
    {
        test[i][j+1].czyByloOdsloniete = true;
    }



    if(i!=0 && j!=test[0].size()-1 && !test[i-1][j+1].czyJestMina)
    {
        test[i-1][j+1].czyByloOdsloniete = true;
    }

    if(i!=test.size()-1 && j!=0 && !test[i+1][j-1].czyJestMina)
    {
        test[i+1][j-1].czyByloOdsloniete = true;
    }
}