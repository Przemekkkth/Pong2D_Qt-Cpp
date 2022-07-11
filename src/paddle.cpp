#include "paddle.h"
#include "ball.h"
#include "game.h"
Paddle::Paddle(PaddleType type, QSize size)
    : m_type(type), m_size(size)
{
    switch (m_type)
    {
    case Paddle::PaddleType::PLAYER1:
        setPosition(QPointF(0.95f*Game::RESOLUTION.width(), 0.5f*Game::RESOLUTION.height()));
        break;
    case Paddle::PaddleType::AI:
    case Paddle::PaddleType::PLAYER2:
        setPosition(QPointF(0.05f*Game::RESOLUTION.width(), 0.5f*Game::RESOLUTION.height()));
        break;
    }

}

QSize Paddle::size() const
{
    return m_size;
}

void Paddle::setSize(QSize newSize)
{
    if(newSize == m_size)
    {
        return;
    }
    m_size = newSize;
}

void Paddle::update(Ball &ball)
{
    if ( m_position.x() + m_size.width() > ball.position().x() &&
         m_position.x() < ball.position().x() &&
         m_position.y() + m_size.height() > ball.position().y() &&
         m_position.y() < ball.position().y())
    {
        if ( m_position.y() + (m_size.height() * 0.33f) > ball.position().y())
        {
            ball.setYDir(Ball::Y_DIRECTION::UP);
        }
        else if ( (m_position.y() + m_size.height() * 0.66f) < ball.position().y())
        {
            ball.setYDir(Ball::Y_DIRECTION::DOWN);
        }
    }
}

QPointF Paddle::position() const
{
    return m_position;
}

void Paddle::setPosition(QPointF newPoint)
{
    if(m_position == newPoint)
    {
        return;
    }
    m_position = newPoint;
}
