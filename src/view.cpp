#include "view.h"

View::View()
    : QGraphicsView{}, m_gameScene(new GameScene(this))
{
    setScene(m_gameScene);
    resize(sceneRect().width() + 2, sceneRect().height() + 2);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
