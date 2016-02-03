#include "pianoscene.h"
#include "pianokey.h"

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QPalette>
#include <QtMath>

int const KEY_WIDTH = 18;
int const KEY_HEIGHT = 72;

static qreal sceneWidth(int keys) {
    return KEY_WIDTH * qCeil(keys * 7.0 / 12.0);
}

PianoScene::PianoScene(const short baseOctave,
                       const short numKeys,
                       const short startKey, const QColor &keyPressedColor,
                       QObject *parent)
    :QGraphicsScene(QRectF(0, 0, sceneWidth(numKeys), KEY_HEIGHT), parent)
    ,m_baseOctave(baseOctave)
    ,m_numKeys(numKeys)
    ,m_startKey(startKey)
    ,m_transpose(0)
    ,m_minNote(0)
    ,m_maxNote(127)
    ,m_mouseEnabled(true)
    ,m_mousePressed(false)
    ,m_velocityTint(true)
    ,m_velocity(100)
    ,m_handler(NULL)
    ,m_keyPressedColor(keyPressedColor)
{
    QFont lblFont(QApplication::font());
    int upperLimit = m_numKeys + m_startKey;

    int adj = m_startKey % 12;
    if(adj >= 5) ++adj;
    for(short i = m_startKey; i < upperLimit; ++i)
    {
        PianoKey *key = NULL;

        short ocs = i/12*7;
        short j = i%12;
        if(j >= 5)
            ++j;
        if(j%2 == 0){
            float x = (ocs + qFloor((j-adj) / 2.0)) * KEY_WIDTH;
            key = new PianoKey(QRectF(x, 0, KEY_WIDTH, KEY_HEIGHT), false, i);
        } else {
            float x = (ocs + qFloor((j-adj) / 2.0)) * KEY_WIDTH + KEY_WIDTH * 0.6 + 1;
            key = new PianoKey(QRectF(x, 0, KEY_WIDTH * 0.8 - 1, KEY_HEIGHT * 0.6), true, i);
            key->setZValue(1); //pull black keys on top
        }
        m_keys.insert(i, key);
        addItem(key);
    }
    hideOrShowKeys();
}

QSize PianoScene::sizeHint() const
{
    return QSize(sceneWidth(m_numKeys), KEY_HEIGHT);
}

void PianoScene::keyOn(const short note)
{
    if(m_keys.contains(note))
        keyOn(m_keys.value(note));
    else
        triggerNoteOn(note, m_velocity);
}

void PianoScene::keyOff(const short note)
{
    if(m_keys.contains(note))
        keyOn(m_keys.value(note));
    else
        triggerNoteOff(note, m_velocity);
}

void PianoScene::showNoteOn(const short note, QColor color, int velocity)
{

}


void PianoScene::showKeyOn(PianoKey *key, QColor color, int velocity, bool setFromPol)
{
    if (velocity >= 0) {
        if (m_velocityTint && color.isValid()) {
            QBrush hilightBrush(color.lighter(200 - velocity));
            key->setPressedBrush(hilightBrush);
        } else if(setFromPol){
            setColorFromPolicy(key, velocity);
        }
    }
    key->setPressed(true);
}

void PianoScene::showKeyOn(PianoKey *key, int vel)
{
    showKeyOn(key, m_keyPressedColor, vel, true);
}

void PianoScene::showKeyOff(PianoKey *key, int)
{
    key->setPressed(false);
}

void PianoScene::keyOn(PianoKey *key)
{
    triggerNoteOn(key->getNote(), m_velocity);
    showKeyOn(key, m_velocity);
}

void PianoScene::keyOff(PianoKey *key)
{
    triggerNoteOff(key->getNote(), 0);
    showKeyOff(key, 0);
}

void PianoScene::keyOn(PianoKey *key, qreal pressure)
{
    int velocity = m_velocity * pressure;
    triggerNoteOn(key->getNote(), velocity);
    showKeyOn(key, velocity);
}

void PianoScene::keyOff(PianoKey *key, qreal pressure)
{
    int velocity = m_velocity * pressure;
    triggerNoteOff(key->getNote(), velocity);
    showKeyOff(key, velocity);
}

void PianoScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_mouseEnabled) {
        PianoKey *key = getKeyFromCoordinate(event->scenePos());
        if(key != NULL && !key->isPressed()) {
            keyOn(key);
            m_mousePressed = true;
            event->accept();
            return;
        }
    }
}

void PianoScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_mouseEnabled) {
        if(m_mousePressed) {
            PianoKey *key = getKeyFromCoordinate(event->scenePos());
            PianoKey *lastKey = getKeyFromCoordinate(event->lastScenePos());
            if(lastKey != NULL && lastKey != key && lastKey->isPressed()){
                keyOff(lastKey);
            }
            if(key != NULL && !key->isPressed()) {
                keyOn(key);
            }
            event->accept();
            return;
        }
    }
}

void PianoScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_mouseEnabled) {
        m_mousePressed = false;
        PianoKey *key = getKeyFromCoordinate(event->scenePos());
        if(key != NULL && key->isPressed()) {
            keyOff(key);
            event->accept();
            return;
        }
    }
}

PianoKey *PianoScene::getKeyFromCoordinate(const QPointF &point) const
{
    PianoKey *key = NULL;
    QList<QGraphicsItem*> keyItems = this->items(point,
                                                 Qt::IntersectsItemShape,
                                                 Qt::DescendingOrder);
    foreach(QGraphicsItem *itm, keyItems) {
        key = dynamic_cast<PianoKey*>(itm);
        if(key != NULL)
            break;
    }
    return key;
}

void PianoScene::hideOrShowKeys()
{
    foreach(PianoKey *key, m_keys){
        short n = m_baseOctave*12 + key->getNote() + m_transpose;
        bool visible = (n >= m_minNote) && (n <= m_maxNote);
        key->setVisible(visible);
    }
}

void PianoScene::triggerNoteOn(const short note, const int velocity)
{
    short n = m_baseOctave*12 + note + m_transpose;
    if((n >= m_minNote) && (n <= m_maxNote)) {
        if(m_handler != NULL) {
            m_handler->noteOn(n, velocity);
        } else {
            emit noteOn(n, velocity);
        }
    }
}

void PianoScene::triggerNoteOff(const short note, const int velocity)
{
    short n = m_baseOctave*12 + note + m_transpose;
    if((n >= m_minNote) && (n <= m_maxNote)) {
        if(m_handler != NULL) {
            m_handler->noteOn(n, velocity);
        } else {
            emit noteOff(n, velocity);
        }
    }
}

void PianoScene::setColorFromPolicy(PianoKey *key, const int velocity)
{
    QColor c;
#if defined(PALETTE_SUPPORT)
    switch (m_palette->paletteId()) {
    case PAL_SINGLE:
        c = m_palette->getColor(0);
        break;
    case PAL_DOUBLE:
        c = m_palette->getColor(key->getType());
        break;
    case PAL_CHANNELS:
        c = m_palette->getColor(m_channel);
        break;
    case PAL_SCALE:
        c = m_palette->getColor(key->getDegree());
    }
#else
    c = QApplication::palette().highlight().color();
#endif
    if (m_velocityTint && c.isValid()) {
        QBrush h(c.lighter(200 - velocity));
        key->setPressedBrush(h);
    }
}

