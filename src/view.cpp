#include "view.h"
#include <QKeyEvent>
#include <QApplication>

View::View()
    : QGraphicsView{}, m_gameScene(new GameScene(this)), m_menuScene(new MenuScene(this))
{
    setScene(m_gameScene);
    resize(sceneRect().width() + 2, sceneRect().height() + 2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(m_menuScene);

    connect(m_menuScene, &MenuScene::pVSpcActivated, [this](){
       m_gameScene->reset(Paddle::PaddleType::AI, Paddle::PaddleType::PLAYER1);
       setScene(m_gameScene);
    });

    connect(m_menuScene, &MenuScene::pVSpActivated, [this](){
       m_gameScene->reset(Paddle::PaddleType::PLAYER2, Paddle::PaddleType::PLAYER1);
       setScene(m_gameScene);
    });

    connect(m_menuScene, &MenuScene::pcVSpcActivated, [this](){
       m_gameScene->reset(Paddle::PaddleType::AI, Paddle::PaddleType::AI1);
       setScene(m_gameScene);
    });

    connect(m_gameScene, &GameScene::menuActivated, [this](){
        setScene(m_menuScene);
    });
}

void View::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:
            QApplication::instance()->quit();
        break;
    }
    QGraphicsView::keyPressEvent(event);
}
