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
    //setScene(m_menuScene);
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
