#include "gamescene.h"
#include <QPixmap>
#include <QDebug>
#include <QGraphicsPixmapItem>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_deltaTime(0.0f), m_loopTime(0.0f), m_loopSpeed(15.0f),
      m_rightPaddle(Paddle::PaddleType::PLAYER1), m_leftPaddle(Paddle::PaddleType::AI)
{
    loadPixmap();

    m_rightPaddle.setSize(QSize(m_paddlePixmap.width(), m_paddlePixmap.height()));
    m_leftPaddle.setSize(QSize(m_paddlePixmap.width(), m_paddlePixmap.height()));
    m_ball.setDiameter(m_ballPixmap.width());

    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(Game::ITERATION_VALUE);
    m_elapsedTimer.start();
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed )
    {
        m_loopTime -= m_loopSpeed;
        render();
        updateLoop();
    }
}

void GameScene::loadPixmap()
{
    if(m_paddlePixmap.load(Game::PATH_TO_PADDLE_PIXMAP))
    {
        qDebug() << "PaddlePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "PaddlePixmap is not loaded successfully";
    }

    if(m_ballPixmap.load(Game::PATH_TO_BALL_PIXMAP))
    {
        qDebug() << "BallPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BallPixmap is not loaded successfully";
    }
}

void GameScene::render()
{
    clear();
    setBackgroundBrush(QBrush(Qt::black));
    QGraphicsPixmapItem* paddle1 = new QGraphicsPixmapItem(m_paddlePixmap);
    paddle1->setPos(m_leftPaddle.position());
    addItem(paddle1);

    QGraphicsPixmapItem* paddle2 = new QGraphicsPixmapItem(m_paddlePixmap);
    paddle2->setPos(m_rightPaddle.position());
    addItem(paddle2);

    QGraphicsPixmapItem* ball = new QGraphicsPixmapItem(m_ballPixmap);
    ball->setPos(m_ball.position());
    addItem(ball);


}

void GameScene::updateLoop()
{
    m_ball.update();
    m_leftPaddle.update(m_ball);
    m_rightPaddle.update(m_ball);
}
