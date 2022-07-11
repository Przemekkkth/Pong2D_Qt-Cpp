#include "ball.h"
#include "game.h"

Ball::Ball(int diameter)
    : m_diameter(diameter), m_speed(4.0f), m_maxSpeed(8.0f), m_xDir(X_DIRECTION::LEFT), m_yDir(Y_DIRECTION::NONE)
{
    setPos(QPointF(Game::RESOLUTION.width()/2-m_diameter, Game::RESOLUTION.height()/2-m_diameter));
}

Ball::X_DIRECTION Ball::xDir() const
{
    return m_xDir;
}

Ball::Y_DIRECTION Ball::yDir() const
{
    return m_yDir;
}

void Ball::setXDir(const X_DIRECTION newDir)
{
    if(m_xDir == newDir)
    {
        return;
    }
    m_xDir = newDir;
}

void Ball::setYDir(const Y_DIRECTION newDir)
{
    if(m_yDir == newDir)
    {
        return;
    }
    m_yDir = newDir;
}

QPointF Ball::position() const
{
    return m_position;
}

void Ball::setPos(QPointF newPos)
{
    if(m_position == newPos)
    {
        return;
    }
    m_position = newPos;
}

int Ball::diameter() const
{
    return m_diameter;
}

void Ball::setDiameter(int newVal)
{
    if(newVal == m_diameter)
    {
        return;
    }
    m_diameter = newVal;
}

void Ball::increaseSpeed()
{
    m_speed += m_speed * 0.1f;
}

void Ball::update()
{
    //top wall
    if (0.f > m_position.y())
    {
        m_yDir = Y_DIRECTION::DOWN;
        increaseSpeed();
    }
    //botom wall
    else if (Game::RESOLUTION.height() < m_position.y()+m_diameter)
    {
        m_yDir = Y_DIRECTION::UP;
        increaseSpeed();
    }
    //left wall
    if (0.f > m_position.x())
    {
        Game::SCORE_2++;
        reset(X_DIRECTION::RIGHT);
    }
    else if ( Game::RESOLUTION.width() < m_position.x()+m_diameter)
    {
        Game::SCORE_1++;
        reset(X_DIRECTION::LEFT);
    }

    m_speed = m_speed > m_maxSpeed ? m_maxSpeed : m_speed;

    switch (m_xDir)
    {
    case Ball::X_DIRECTION::RIGHT:
        switch (m_yDir)
        {
        case Ball::Y_DIRECTION::DOWN:
            setPos(position()+QPointF(m_speed, m_speed));
            break;
        case Ball::Y_DIRECTION::UP:
            setPos(position()+QPointF(m_speed, -m_speed));
            break;
        case Ball::Y_DIRECTION::NONE:
            setPos(position()+QPointF(m_speed, 0));
            break;
        }
        break;
    case Ball::X_DIRECTION::LEFT:
        switch (m_yDir)
        {
        case Ball::Y_DIRECTION::DOWN:
            setPos(position()+QPointF(-m_speed, m_speed));
            break;
        case Ball::Y_DIRECTION::UP:
            setPos(position()+QPointF(-m_speed, -m_speed));
            break;
        case Ball::Y_DIRECTION::NONE:
            setPos(position()+QPointF(-m_speed, 0));
            break;
        }
        break;
    case Ball::X_DIRECTION::NONE:
    {}
        break;
    }
}

void Ball::reset(X_DIRECTION dir)
{
    setPos(QPointF(Game::RESOLUTION.width()/2-m_diameter, Game::RESOLUTION.height()/2-m_diameter));
    setXDir(dir);
    setYDir(Y_DIRECTION::NONE);
}

