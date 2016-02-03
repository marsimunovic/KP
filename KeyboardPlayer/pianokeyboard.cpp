#include "pianokeyboard.h"
#include "pianoscene.h"

#include <QApplication>

static short const BASE_OCTAVE = 3;
static short const NUMBER_OF_KEYS = 61;
static short const STARTING_KEY = 0;

PianoKeyboard::PianoKeyboard(QWidget *parent)
    :QGraphicsView(parent)
    ,m_scene(NULL)
{
    initalize();
    initScene(BASE_OCTAVE, NUMBER_OF_KEYS, STARTING_KEY);
}

PianoKeyboard::PianoKeyboard(const short baseOctave, const short numKeys, const short startKey, QWidget *parent)
    :QGraphicsView(parent)
    ,m_scene(NULL)
{
    initalize();
    initScene(baseOctave, numKeys, startKey);
}

PianoKeyboard::~PianoKeyboard()
{

}

QSize PianoKeyboard::sizeHint() const
{
    return mapFromScene(sceneRect()).boundingRect().size();
}

void PianoKeyboard::initalize()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(MinimalViewportUpdate);
    setRenderHints(QPainter::Antialiasing |
                   QPainter::TextAntialiasing |
                   QPainter::SmoothPixmapTransform);
    setOptimizationFlags(DontSavePainterState |
                        DontAdjustForAntialiasing);
    setBackgroundBrush(QApplication::palette().background());
}

void PianoKeyboard::initScene(short baseOctave, short numKeys, short startKey, const QColor &c)
{
    m_scene = new PianoScene(baseOctave, numKeys, startKey, c, this);
    connect(m_scene, SIGNAL(noteOn(short, int)), SIGNAL(noteOn(short, int)));
    connect(m_scene, SIGNAL(noteOff(short, int)), SIGNAL(noteOff(short, int)));
        setScene(m_scene);
}

void PianoKeyboard::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}

