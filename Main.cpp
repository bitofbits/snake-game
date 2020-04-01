#include <SFML/Graphics.hpp>
#include<bits/stdc++.h>
//functions..

void move();
void setBorder();
bool checksafety(int x,int y);
void drawsnakegame();
void food();
bool clearfood(int x,int y);
void checkcollision();
void clearData();
//variables..

sf::Font font;
sf::Text endtext;
sf::Text score_text;
sf::Text final_score;
sf::Text replay_text;
std::string final_string="Final Score : ";
std::string score_string = "Score: ";
std::string replay_string = "(Replay: r)";
int score=0;
int game_over=0;
char direction=' ';
int top=0;
std::pair<int,int> foodpos={-16,-16};
std::pair<int,int> position[2500]={};
sf::RenderWindow window(sf::VideoMode(800,800), "Snake!");
sf::RectangleShape rectangle(sf::Vector2f(16,16));
sf::RectangleShape line(sf::Vector2f(800,5));
sf::RectangleShape line2(sf::Vector2f(5,800));
int main()
{
    position[0]={392,392};
    window.setFramerateLimit(25);
    sf::Event event;
    if(!font.loadFromFile("OpenSans-ExtraBold.ttf"))
    {
      std::cout<<"Error in loading the font"<<std::endl;
    }
    line.setFillColor(sf::Color(96,96,96));
    line2.setFillColor(sf::Color(96,96,96));

    endtext.setFont(font);
    endtext.setFillColor(sf::Color::White);
    endtext.setCharacterSize(128);
    endtext.setPosition(13,200);

    final_score.setFont(font);
    final_score.setFillColor(sf::Color::White);
    final_score.setCharacterSize(64);
    final_score.setPosition(175,400);

    score_text.setFont(font);
    score_text.setFillColor(sf::Color::White);
    score_text.setCharacterSize(30);
    score_text.setPosition(350,0);

    replay_text.setFont(font);
    replay_text.setFillColor(sf::Color::White);
    replay_text.setCharacterSize(25);
    replay_text.setPosition(325,475);
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed)
            {
              if(event.key.code == sf::Keyboard::Escape)
                window.close();
              else if(event.key.code == sf::Keyboard::Up)
              {
                direction='U';
                //move();
              }
              else if(event.key.code == sf::Keyboard::Down)
              {
                direction='D';
                //move();
              }
              else if(event.key.code == sf::Keyboard::Left)
              {
                direction='L';
                //move();
              }
              else if(event.key.code == sf::Keyboard::Right)
              {
                direction='R';
                //move();
              }
              else if(event.key.code == sf::Keyboard::R)
              {
                clearData();
              }
              else if(event.key.code == sf::Keyboard::P)
              {
                direction=' ';
                //move();
              }

            }
        }
        if(game_over!=1)
        {
          if(foodpos.first==-16 && foodpos.second==-16)
          {
            food();
          }
          move();
          checkcollision();
          drawsnakegame();
        }
        else
        {
          window.clear(sf::Color::Red);

          endtext.setString("Game Over!");
          final_score.setString(final_string + std::to_string(score));
          replay_text.setString(replay_string);

          window.draw(endtext);
          window.draw(final_score);
          window.draw(replay_text);

          window.display();
        }
    }
    return 0;
}

void move()
{
  char tmp = direction;
  int pause=0;
  std::pair<int,int> head = position[top];
  if(tmp == 'U')
  {
    pause=0;
    head.second-=16;
  }
  else if(tmp == 'D')
  {
    pause=0;
    head.second+=16;
  }
  else if(tmp == 'L')
  {
    pause=0;
    head.first-=16;
  }
  else if(tmp == 'R')
  {
    pause=0;
    head.first+=16;
  }
  else if(tmp == ' ')
  {
    pause=1;
  }
  if(pause!=1)
  {
    for(int i=0;i<top;i++)
    {
      position[i]=position[i+1];
    }
    position[top] = head;
  }
}

bool checksafety(int x,int y)
{
  if(x<=0 || x>=779 || y<=0 || y>=779)
    return false;
  else
  {
    return true;
  }
}

void drawsnakegame()
{
  window.clear(sf::Color::Black);
  rectangle.setFillColor(sf::Color::White);
  setBorder();
  for(int i=0;i<=top;i++)
  {
    rectangle.setPosition(position[i].first,position[i].second);
    window.draw(rectangle);
  }
  if(foodpos.first!=-16 && foodpos.second!=-16)
  {
    rectangle.setFillColor(sf::Color::Yellow);
    rectangle.setPosition(foodpos.first,foodpos.second);
    window.draw(rectangle);
  }
  score_text.setString(score_string);
  window.draw(score_text);
  window.display();
}

void food()
{
  srand(time(0));
  int a=((rand())%740) + 30;
  int b=((rand())%740) + 30;
  while(!clearfood(a,b))
  {
    a=((rand())%740) + 30;
    b=((rand())%740) + 30;
  }
  foodpos.first = a;
  foodpos.second= b;
}

bool clearfood(int x, int y)
{
  for(int i=0;i<=top;i++)
  {
    if(abs(position[i].first -x)<16 && abs(position[i].second-y)<16)
      return false;
  }
  return true;
}

void checkcollision()
{
  char t = direction;
  if(abs(position[top].first - foodpos.first)<16 && abs(position[top].second - foodpos.second)<16)
  {
    ++score;
    score_string="Score: ";
    score_string+=std::to_string(score);
    int tmp=top+1;
    if(t=='U')
    {
      position[tmp].first=position[top].first;
      position[tmp].second=position[top].second-16;
    }
    else if(t=='D')
    {
      position[tmp].first=position[top].first;
      position[tmp].second=position[top].second+16;
    }
    else if(t=='L')
    {
      position[tmp].first=position[top].first-16;
      position[tmp].second=position[top].second;
    }
    else if(t=='R')
    {
      position[tmp].first=position[top].first+16;
      position[tmp].second=position[top].second;
    }
    foodpos.first=-16;
    foodpos.second=-16;
    top++;
  }
  for(int i=0;i<top;i++)
  {
    if((abs(position[top].first - position[i].first)<15 && abs(position[top].second - position[i].second)<15))
    {
      game_over=1;
      break;
    }
  }
  if(!checksafety(position[top].first,position[top].second))
  {
    game_over=1;
  }
}
void setBorder()
{
  line.setPosition(0,0);
  window.draw(line);
  line.setPosition(0,795);
  window.draw(line);
  line2.setPosition(0,0);
  window.draw(line2);
  line2.setPosition(795,0);
  window.draw(line2);
}
void clearData()
{
  game_over=0;
  top=0;
  score=0;
  std::memset(position,0,2500);
  position[0]={392,392};
  direction=' ';
  final_string="Final Score : ";
  score_string = "Score: ";
}
