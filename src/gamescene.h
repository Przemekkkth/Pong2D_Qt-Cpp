#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>

#include "game.h"
#include "ball.h"
#include "paddle.h"
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private slots:
    void loop();
private:
    void loadPixmap();
    void render();
    void updateLoop();
    float m_deltaTime, m_loopTime;
    const float m_loopSpeed;
    Game m_game;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    QPixmap m_paddlePixmap;
    QPixmap m_ballPixmap;

    Paddle	m_rightPaddle;
    Paddle	m_leftPaddle;
    Ball	m_ball;
};

#endif // GAMESCENE_H
