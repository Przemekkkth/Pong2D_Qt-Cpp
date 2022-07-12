#include "menuscene.h"
#include "game.h"
#include <QGraphicsSceneMouseEvent>
#include <QFontDatabase>
#include <QDebug>

MenuScene::MenuScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    setBackgroundBrush(QBrush(Qt::black));
    int id = QFontDatabase::addApplicationFont(":/res/college.ttf");
    m_familyName = QFontDatabase::applicationFontFamilies(id).at(0);

    m_titleText = new QGraphicsSimpleTextItem("Pong2D");
    m_titleText->setFont(QFont(m_familyName, 50, 50, false));
    m_titleText->setBrush(QBrush(Qt::white));
    m_titleText->setPen(QPen(Qt::NoPen));
    m_titleText->setPos(0.40f*Game::RESOLUTION.width(), 0.05f*Game::RESOLUTION.height());
    addItem(m_titleText);

    m_playerVsPCText = new QGraphicsSimpleTextItem("Player vs PC");
    m_playerVsPCText->setFont(QFont(m_familyName, 30, 50, false));
    m_playerVsPCText->setBrush(QBrush(Qt::white));
    m_playerVsPCText->setPen(QPen(Qt::NoPen));
    m_playerVsPCText->setPos(0.38f*Game::RESOLUTION.width(), 0.25f*Game::RESOLUTION.height());
    addItem(m_playerVsPCText);

    m_playerVSPlayerText = new QGraphicsSimpleTextItem("Player vs Player");
    m_playerVSPlayerText->setFont(QFont(m_familyName, 30, 50, false));
    m_playerVSPlayerText->setBrush(QBrush(Qt::white));
    m_playerVSPlayerText->setPen(QPen(Qt::NoPen));
    m_playerVSPlayerText->setPos(0.33f*Game::RESOLUTION.width(), 0.45f*Game::RESOLUTION.height());
    addItem(m_playerVSPlayerText);

    m_pcVsPCText = new QGraphicsSimpleTextItem("PC vs PC");
    m_pcVsPCText->setFont(QFont(m_familyName, 30, 50, false));
    m_pcVsPCText->setBrush(QBrush(Qt::white));
    m_pcVsPCText->setPen(QPen(Qt::NoPen));
    m_pcVsPCText->setPos(0.42f*Game::RESOLUTION.width(), 0.65f*Game::RESOLUTION.height());
    addItem(m_pcVsPCText);


}

void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF clickedPoint = event->scenePos();

    if (
         clickedPoint.x() > m_playerVsPCText->pos().x()                                            &&
         clickedPoint.x() < m_playerVsPCText->pos().x() + m_playerVsPCText->boundingRect().width() &&
         clickedPoint.y() > m_playerVsPCText->pos().y()                                            &&
         clickedPoint.y() < m_playerVsPCText->pos().y() + m_playerVsPCText->boundingRect().height()
       )
    {
        emit pVSpcActivated();
    }

    if (
         clickedPoint.x() > m_playerVSPlayerText->pos().x()                                                &&
         clickedPoint.x() < m_playerVSPlayerText->pos().x() + m_playerVSPlayerText->boundingRect().width() &&
         clickedPoint.y() > m_playerVSPlayerText->pos().y()                                                &&
         clickedPoint.y() < m_playerVSPlayerText->pos().y() + m_playerVSPlayerText->boundingRect().height()
       )
    {
         emit pVSpActivated();
    }

    if (
         clickedPoint.x() > m_pcVsPCText->pos().x()                                                &&
         clickedPoint.x() < m_pcVsPCText->pos().x() + m_pcVsPCText->boundingRect().width() &&
         clickedPoint.y() > m_pcVsPCText->pos().y()                                                &&
         clickedPoint.y() < m_pcVsPCText->pos().y() + m_pcVsPCText->boundingRect().height()
       )
    {
         emit pcVSpcActivated();
    }
}
