#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
#include "game.h"
class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = nullptr);

signals:

private slots:
    void loop();
private:
    float m_deltaTime, m_loopTime;
    const float m_loopSpeed;
    Game m_game;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;

};

#endif // GAMESCENE_H