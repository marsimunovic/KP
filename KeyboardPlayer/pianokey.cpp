#include "pianokey.h"

#include <QApplication>
#include <QPainter>
#include <QPalette>
#include <QtSvg/QSvgRenderer>

static QBrush const blackBrush = QBrush(Qt::black);
static QBrush const whiteBrush = QBrush(Qt::white);

PianoKey::PianoKey(QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
    ,m_pressed(false)
    ,m_black(false)
    ,m_note(0)
{
    //setAcceptedMouseButtons(Qt::NoButton);
    setAcceptedMouseButtons(Qt::LeftButton);

}

PianoKey::PianoKey(const QRectF &rect, const QBrush &brush, const short note)
    :QGraphicsRectItem(rect)
    ,m_pressed(false)
    ,m_black(brush == blackBrush)
    ,m_note(note)
    ,m_brush(brush)
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

PianoKey::PianoKey(const QRectF &rect, const bool black, const short note)
    :QGraphicsRectItem(rect)
    ,m_pressed(false)
    ,m_black(black)
    ,m_note(note)
    ,m_brush(black? blackBrush: whiteBrush)
{
   // setAcceptedMouseButtons(Qt::NoButton);
    setAcceptedMouseButtons(Qt::LeftButton);

}

void PianoKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    static QSvgRenderer keyRenderer(QString(":/data/blkey.svg"));
    static QPen const blackPen(Qt::black, 1);
    static QPen const grayPen(QBrush(Qt::gray), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    if(m_pressed){
        if(m_selectedBrush.style() != Qt::NoBrush) {
            painter->setBrush(m_selectedBrush);
        } else {
            painter->setBrush(QApplication::palette().highlight());
        }
    } else {
        painter->setBrush(m_brush);
    }

    painter->setPen(blackPen);
    painter->drawRoundRect(rect(), 10, 10);
    if(m_black){
        keyRenderer.render(painter, rect());
    } else {
        QPointF points[3] = {
            QPointF(rect().left() + 1.5, rect().bottom() - 1),
            QPointF(rect().right() - 1, rect().bottom() - 1),
            QPointF(rect().right() - 1, rect().top() + 1)
        };
        painter->setPen(grayPen);
        painter->drawPolyline(points, 3);
    }
}

void PianoKey::setPressed(bool pressed)
{
   if(pressed != m_pressed){
       m_pressed = pressed;
       update();
   }
}

void PianoKey::resetBrush()
{
    m_brush = m_black? blackBrush: whiteBrush;
}







