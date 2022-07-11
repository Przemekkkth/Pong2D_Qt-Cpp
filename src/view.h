#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "gamescene.h"
#include "menuscene.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View();

signals:

private:
    GameScene* m_gameScene;
    MenuScene* m_menuScene;
    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
