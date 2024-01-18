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

sf::RenderWindow display(sf::VideoMode(600,600),"Chuj");
sf::Event event;

vector<vector<Pole>> createMineMap(int x, int y, int &licznik);
void checkForMinesMap(vector<vector<Pole>> &mineMap);

void centerTextOrigin(sf::Text &text);
bool containsMouse(sf::RectangleShape box,sf::Vector2i coords);






int main() {
    display.setFramerateLimit(60);


    int liczba_kratek = 5;

    int odstep_miedzy_kratkami = 1;
    int szerokosc_kratki = display.getSize().x/(liczba_kratek+odstep_miedzy_kratkami*0.1*liczba_kratek);




    int licznikMin = 0;
    auto test = createMineMap(liczba_kratek,liczba_kratek,licznikMin);
    checkForMinesMap(test);



//    vector<vector<bool>> hasBeenTouched(test.size(),vector<bool>(test[0].size(),false));


//    vector<vector<Pole>> Mapa = createMineMap(10,10,licznikMin);





    sf::RectangleShape box(sf::Vector2f(szerokosc_kratki,szerokosc_kratki));
    box.setFillColor(sf::Color::Blue);
    box.setOrigin(szerokosc_kratki/2,szerokosc_kratki/2);

    sf::Font font;
    if (!font.loadFromFile("../cmake-build-debug/Pixelboy.ttf")) {
        std::cerr << "Cannot load font" << std::endl;
        return 0;
    }
    font.setSmooth(false);

    sf::Text mineNumber("0", font, szerokosc_kratki);
    centerTextOrigin(mineNumber);
    mineNumber.setOutlineThickness(0.5f);
    mineNumber.setOutlineColor(sf::Color::Black);

    sf::Vector2i coords;
    sf::Vector2i coords2;



    bool GameOver = false;
    while(display.isOpen())
    {
        while(display.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) display.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) main();


            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                coords = sf::Mouse::getPosition(display);
            }
            if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) coords2 = sf::Mouse::getPosition(display);

        }



        display.clear();

        int licznikOdslonietychPol = 0;
        for(int i = 0; i<test.size(); i++)
        {
            for(int j = 0; j<test[0].size(); j++)
            {
                auto a = &test[i][j];

                box.setPosition((szerokosc_kratki+display.getSize().x-(szerokosc_kratki+odstep_miedzy_kratkami)*test[0].size())/2+j*(szerokosc_kratki+odstep_miedzy_kratkami),(szerokosc_kratki+display.getSize().x-(szerokosc_kratki+odstep_miedzy_kratkami)*test.size())/2+ i*(szerokosc_kratki+odstep_miedzy_kratkami));
                box.setFillColor(sf::Color(0x515151FF));
                if(a->wartosc == 0) mineNumber.setFillColor(sf::Color::Green);
                if(a->wartosc >  0 && a->wartosc < 20) mineNumber.setFillColor(sf::Color::Blue);
                if(a->wartosc > 20)
                {
                    mineNumber.setFillColor(sf::Color::Red);
                    box.setFillColor(sf::Color(0x580C1FFF));
                }

                if(a->wartosc < 20) mineNumber.setString(to_string(a->wartosc));
                if(a->wartosc > 20) mineNumber.setString("X");



                if(containsMouse(box,coords))
                {
                    if(a->czyJestMina) GameOver=true;
                    a->czyByloOdsloniete=true;
                    if(a->czyZaznaczonaMina)
                    {
                        a->czyZaznaczonaMina = false;
                    }

                }

                if(containsMouse(box,coords2) && !a->czyByloOdsloniete)
                {
                    a->czyZaznaczonaMina = !a->czyZaznaczonaMina;
                    coords2 = sf::Vector2i();
                }



                if(test[i][j].wartosc==0 && test[i][j].czyByloOdsloniete)
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



                mineNumber.setPosition(box.getPosition());
                display.draw(box);
                display.draw(mineNumber);


                box.setFillColor(sf::Color(0x222222FF));
                if(test[i][j].czyZaznaczonaMina) box.setFillColor(sf::Color(0xBD1E1EFF));
                if(test[i][j].czyByloOdsloniete) box.setFillColor(sf::Color::Transparent);


                if(!GameOver) display.draw(box);
                if(test[i][j].czyByloOdsloniete) licznikOdslonietychPol++;
            }
        }

        if(licznikOdslonietychPol==test.size()*test[0].size() - licznikMin) display.draw(sf::RectangleShape(sf::Vector2f(5,5)));

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

            if(rand()%10==0)
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