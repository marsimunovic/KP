#ifndef PIANOKEY_H
#define PIANOKEY_H

#include <QGraphicsRectItem>
#include <QBrush>

class PianoKey : public QGraphicsRectItem
{
public:
    PianoKey(QGraphicsItem *parent = 0);
    PianoKey(QRectF const &rect, QBrush const &brush, short const note);
    PianoKey(QRectF const &rect, bool const black, short const note);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);


    void setPressed(bool pressed);
    bool isPressed() const {return m_pressed;}
    bool isKeyBlack() const { return m_black;}
    void setBrush(QBrush const &brush) {m_brush = brush;}
    void resetBrush();
    short getNote() const {return m_note;}
    void setPressedBrush(QBrush const &brush) {m_selectedBrush = brush;}

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool   m_pressed;
    bool   m_black;
    short  m_note;
    QBrush m_brush;
    QBrush m_selectedBrush;
};

#endif // PIANOKEY_H
