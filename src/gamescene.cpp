#include "gamescene.h"
#include <QPixmap>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QFontDatabase>
#include <QGraphicsSimpleTextItem>
#include <QDir>
#include <QPainter>

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

    int id = QFontDatabase::addApplicationFont(":/res/college.ttf");
    m_familyName = QFontDatabase::applicationFontFamilies(id).at(0);

}

void GameScene::reset(Paddle::PaddleType leftPaddleMode, Paddle::PaddleType rightPaddleMode)
{
    m_leftPaddle.setPaddleType(leftPaddleMode);
    m_rightPaddle.setPaddleType(rightPaddleMode);

    m_ball.setPos(QPointF(Game::RESOLUTION.width()/2-m_ball.diameter(), Game::RESOLUTION.height()/2-m_ball.diameter()));
    m_ball.setXDir(Ball::X_DIRECTION::LEFT);
    m_ball.setYDir(Ball::Y_DIRECTION::NONE);

    m_leftPaddle.init();
    m_rightPaddle.init();

    Game::SCORE_1 = Game::SCORE_2 = 0;

    m_game.m_isPause = false;
}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    while( m_loopTime > m_loopSpeed && !m_game.m_isPause)
    {
        m_loopTime -= m_loopSpeed;
        renderGame();
        updateLoop();
    }
    drawPauseText();
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

void GameScene::renderGame()
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

    QGraphicsLineItem *lItem = new QGraphicsLineItem();
    lItem->setPen(QColor(Qt::red));
    lItem->setLine(0,0,0, Game::RESOLUTION.height());
    addItem(lItem);

    QGraphicsLineItem *rItem = new QGraphicsLineItem();
    rItem->setPen(QColor(Qt::red));
    rItem->setLine(Game::RESOLUTION.width()-1,0, Game::RESOLUTION.width()-1, Game::RESOLUTION.height());
    addItem(rItem);

    QGraphicsLineItem *tItem = new QGraphicsLineItem();
    tItem->setPen(QColor(Qt::green));
    tItem->setLine(0,0, Game::RESOLUTION.width(), 0);
    addItem(tItem);

    QGraphicsLineItem *bItem = new QGraphicsLineItem();
    bItem->setPen(QColor(Qt::green));
    bItem->setLine(0,Game::RESOLUTION.height()-1, Game::RESOLUTION.width(), Game::RESOLUTION.height()-1);
    addItem(bItem);

    drawScores();

}

void GameScene::updateLoop()
{
    m_ball.update();
    m_leftPaddle.update(m_ball);
    m_rightPaddle.update(m_ball);
}

void GameScene::drawScores()
{
    QGraphicsSimpleTextItem* text1 = new QGraphicsSimpleTextItem(QString::number(Game::SCORE_1));
    text1->setFont(QFont(m_familyName, 24, 50, false));
    text1->setBrush(QBrush(Qt::white));
    text1->setPen(QPen(Qt::NoPen));
    text1->setPos(0.40f*Game::RESOLUTION.width(), 0.05f*Game::RESOLUTION.height());
    addItem(text1);

    QGraphicsSimpleTextItem* text2 = new QGraphicsSimpleTextItem(QString::number(Game::SCORE_2));
    text2->setFont(QFont(m_familyName, 24, 50, false));
    text2->setBrush(QBrush(Qt::white));
    text2->setPen(QPen(Qt::NoPen));
    text2->setPos(0.60f*Game::RESOLUTION.width(), 0.05f*Game::RESOLUTION.height());
    addItem(text2);
}

void GameScene::drawPauseText()
{
    if(m_game.m_isPause)
    {
        QGraphicsSimpleTextItem* pauseText = new QGraphicsSimpleTextItem("Pause");
        pauseText->setFont(QFont(m_familyName, 50, 50, false));
        pauseText->setBrush(QBrush(Qt::red));
        pauseText->setPen(QPen(Qt::NoPen));
        pauseText->setPos(0.40f*Game::RESOLUTION.width(), 0.45f*Game::RESOLUTION.height());
        addItem(pauseText);
    }
}

void GameScene::renderScene()
{
    static int index = 0;
    QString fileName = QDir::currentPath() + QDir::separator() + "screen" + QString::number(index++) + ".png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    {
        if(m_rightPaddle.type() == Paddle::PaddleType::PLAYER1)
        {
            m_rightPaddle.setMoveUp(true);
        }
    }
        break;
    case Qt::Key_Down:
    {
        if(m_rightPaddle.type() == Paddle::PaddleType::PLAYER1)
        {
            m_rightPaddle.setMoveDown(true);
        }
    }
        break;
    case Qt::Key_W:
    {
        if(m_leftPaddle.type() == Paddle::PaddleType::PLAYER2)
        {
            m_leftPaddle.setMoveUp(true);
        }
    }
        break;
    case Qt::Key_S:
    {
        if(m_leftPaddle.type() == Paddle::PaddleType::PLAYER2)
        {
            m_leftPaddle.setMoveDown(true);
        }
    }
        break;
    }


    if(!event->isAutoRepeat())
    {
        if(event->key() == Qt::Key_P)
        {
            if(m_game.m_isPause == false)
            {
                m_game.m_isPause = true;
            }
            else
            {
                m_game.m_isPause = false;
            }
        }
        else if(event->key() == Qt::Key_Backspace)
        {
            emit menuActivated();
        }
        else if(event->key() == Qt::Key_Z)
        {
            //renderScene();
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
    {
        m_rightPaddle.setMoveUp(false);
    }
        break;
    case Qt::Key_Down:
    {
        m_rightPaddle.setMoveDown(false);
    }
        break;
    case Qt::Key_W:
    {
        if(m_leftPaddle.type() == Paddle::PaddleType::PLAYER2)
        {
            m_leftPaddle.setMoveUp(false);
        }
    }
        break;
    case Qt::Key_S:
    {
        if(m_leftPaddle.type() == Paddle::PaddleType::PLAYER2)
        {
            m_leftPaddle.setMoveDown(false);
        }
    }
        break;
    }
    QGraphicsScene::keyReleaseEvent(event);
}
