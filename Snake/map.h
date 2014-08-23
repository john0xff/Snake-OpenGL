#ifndef MAP_H
#define MAP_H
#include <queue>
#include <vector>

struct Player
{
    int x;
    int y;
};

struct Direction
{
    int x;
    int y;
};

struct Point2D
{
    int x;
    int y;
};

struct Lenght
{
    int x;
    int y;
};

class Map
{
private:
    Lenght _lenght;

    Player _player;
    Direction _direction;

    std::queue<Player> _queue;
    Point2D _point;

    Player _tab[100];
    int _counter;

public:
    Map();

    void drawPlayer();

    void initQueue();
    void motionPlayer();
    void updatePlayer(char keys[256]);
    void addPoint();
    bool mapContition();
    bool playerCondition();

    void keyDowns();
    void keyUp();

    void ortho2Dfunc();

    void randomPoint();
    void drawPoint();
};

#endif // MAP_H
