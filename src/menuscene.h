#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>

class MenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MenuScene(QObject *parent = nullptr);

signals:
    void pVSpcActivated();
    void pVSpActivated();
    void pcVSpcActivated();
private:
    QGraphicsSimpleTextItem *m_titleText;
    QGraphicsSimpleTextItem *m_playerVsPCText;
    QGraphicsSimpleTextItem *m_playerVSPlayerText;
    QGraphicsSimpleTextItem *m_pcVsPCText;

    QString m_familyName;
    // QGraphicsScene interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MENUSCENE_H
