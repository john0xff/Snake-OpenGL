#include "map.h"
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>


Map::Map()
{
    this->_player.x = 0;
    this->_player.y = 0;

    this->_direction.x = 0;
    this->_direction.y = -1;

    this->_lenght.x = 10;
    this->_lenght.y = 10;

    this->_counter = 1;

    this->_point.x = 0;
    this->_point.y = -10;

    ::srand(::time( NULL ));

    this->initQueue();

    for(unsigned int i = 0; i < 100; ++i)
    {
        this->_tab[i].x = NULL;
        this->_tab[i].y = NULL;
    }
}

void Map::initQueue()
{
    if(this->_queue.empty())
    {
        this->_queue.push(this->_player);
    }
}

void Map::drawPlayer()
{
    unsigned int sizeTab = sizeof(this->_tab) / 8;

    for(unsigned int i = 0; i < sizeTab; ++i)
    {
        this->_tab[i].x = NULL;
        this->_tab[i].y = NULL;
    }

    unsigned int queueSize = this->_queue.size();

    for(unsigned int i = 0; i < queueSize; ++i)
    {
        this->_tab[i] = this->_queue.front();
        this->_player = this->_queue.front();

        ::glPushMatrix();

            ::glColor3f(0.0, 1.0, 0.0);
            ::glPointSize(30.0);
            ::glBegin(GL_POINTS);

            ::glVertex2d(this->_player.x, this->_player.y);

            ::glEnd();

        ::glPopMatrix();

        this->_queue.pop();
    }

    for(unsigned int i = 0; i < queueSize; ++i)
    {
        this->_queue.push(this->_tab[i]);
    }
}

void Map::updatePlayer(char keys[256])
{
    this->_queue.pop();

    if(keys['w'])
    {
        this->_direction.x = 0;
        this->_direction.y = 1;
    }

    if(keys['s'])
    {
        this->_direction.x = 0;
        this->_direction.y = -1;
    }

    if(keys['d'])
    {
        this->_direction.x = 1;
        this->_direction.y = 0;
    }

    if(keys['a'])
    {
        this->_direction.x = -1;
        this->_direction.y = 0;
    }

    this->_player.x += this->_direction.x;
    this->_player.y += this->_direction.y;

    this->playerCondition();

    this->_queue.push(this->_player);
}

bool Map::playerCondition()
{
   /* Player tmp = this->_queue.front();

    unsigned int queueSize = this->_queue.size();

    for(unsigned int i = 0; i < queueSize; ++i)
    {
        if(((this->_tab[i].x) == tmp.x)
           && ((this->_tab[i].y) == tmp.y))
                return false;
    }*/

    return true;
}

void Map::addPoint()
{
    for(int i = -1; i < 2; i = i + 2)
    {
        if(((this->_player.x) == (this->_point.x)) && ((this->_player.y + i) == (this->_point.y)))
        {
            --this->_counter;
            this->_queue.push(this->_player);
        }

        if(((this->_player.x + i) == (this->_point.x)) && ((this->_player.y) == (this->_point.y)))
        {
            --this->_counter;
            this->_queue.push(this->_player);
        }
    }
}

bool Map::mapContition()
{
    if(this->_player.y >= this->_lenght.y)
        return false;

    if(this->_player.y <= -this->_lenght.y)
        return false;

    if(this->_player.x >= this->_lenght.x)
       return false;

    if(this->_player.x <= -this->_lenght.x)
        return false;

    return true;
}

void Map::ortho2Dfunc()
{
    ::gluOrtho2D(-this->_lenght.x, this->_lenght.x, -this->_lenght.y, this->_lenght.y);
}

void Map::randomPoint()
{
    this->_point.x = (::rand() % (this->_lenght.x - 2)) - (this->_lenght.x -2); // obliczamy wartosc x losowanego punktu
    this->_point.y = (::rand() % (this->_lenght.y - 2)) - (this->_lenght.y - 2);

    ++this->_counter;
}

void Map::drawPoint()
{
    this->addPoint();

    if(this->_counter == 0)
    {
        this->randomPoint();
    }

    ::glPushMatrix();

        ::glColor3f(1.0, 0.0, 0.0);
        ::glPointSize(25.0);
        ::glBegin(GL_POINTS);

        ::glVertex2f(this->_point.x, this->_point.y);

        ::glEnd();

    ::glPopMatrix();
}

