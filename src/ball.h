#ifndef BALL_H
#define BALL_H
#include <QPointF>

class Ball
{
public:
    Ball(int diameter);
    enum class Y_DIRECTION
    {
        NONE, UP, DOWN
    };
    enum class X_DIRECTION
    {
        NONE, RIGHT, LEFT
    };

    X_DIRECTION xDir() const;
    Y_DIRECTION yDir() const;
    void setXDir(const X_DIRECTION newDir);
    void setYDir(const Y_DIRECTION newDir);

    QPointF position() const;
    void setPos(QPointF newPos);

    int diameter() const;

    void increaseSpeed();

    void update();
private:
    int m_diameter;
    float m_speed;
    const float m_maxSpeed;
    X_DIRECTION m_xDir;
    Y_DIRECTION m_yDir;

    QPointF m_position;
};

#endif // BALL_H
