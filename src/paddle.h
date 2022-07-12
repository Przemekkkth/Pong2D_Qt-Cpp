#ifndef PADDLE_H
#define PADDLE_H
#include <QSize>
#include <QPointF>

class Ball;

class Paddle
{
public:
    enum class PaddleType
    {
        PLAYER1, AI, PLAYER2
    };
    Paddle(PaddleType type, QSize size = QSize(1,1));

    QSize size() const;
    void setSize(QSize newSize);
    void update(Ball& ball);

    QPointF position() const;
    void setPosition(QPointF newPoint);

    void setMoveUp(bool val);
    void setMoveDown(bool val);

    PaddleType type() const;
    void setPaddleType(PaddleType type);

    void init();
private:
    void clampPaddle();
    PaddleType  m_type;
    float   m_baseSpeed;
    float   m_minSpeed;
    QSize m_size;
    QPointF m_position;

    bool m_moveUp, m_moveDown;
};

#endif // PADDLE_H
