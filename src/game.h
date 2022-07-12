#ifndef GAME_H
#define GAME_H
#include <QSize>

class Game
{
public:
    Game();
    static const QSize RESOLUTION;
    static const float ITERATION_VALUE;
    static const QString PATH_TO_PADDLE_PIXMAP;
    static const QString PATH_TO_BALL_PIXMAP;
    static const QString PATH_TO_CURSOR_PIXMAP;
    static int SCORE_1, SCORE_2;
};

#endif // GAME_H
