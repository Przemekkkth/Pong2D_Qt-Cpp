#include "menuscene.h"
#include "game.h"
#include <QGraphicsSceneMouseEvent>
#include <QFontDatabase>

MenuScene::MenuScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    setBackgroundBrush(QBrush(Qt::black));
    int id = QFontDatabase::addApplicationFont(":/res/college.ttf");
    m_familyName = QFontDatabase::applicationFontFamilies(id).at(0);

    m_titleText = new QGraphicsSimpleTextItem("Pong2D");
    addItem(m_titleText);

    m_playerVsPCText = new QGraphicsSimpleTextItem("Player vs PC");
    addItem(m_playerVsPCText);

    m_playerVSPlayerText = new QGraphicsSimpleTextItem("Player vs Player");
    addItem(m_playerVSPlayerText);

    m_pcVsPCText = new QGraphicsSimpleTextItem("PC vs PC");
    addItem(m_pcVsPCText);
}

void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}
