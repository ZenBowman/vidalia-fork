/*
**  This file is part of Vidalia, and is subject to the license terms in the
**  LICENSE file, found in the top level directory of this distribution. If you
**  did not receive the LICENSE file with this file, you may obtain it from the
**  Vidalia source package distributed by the Vidalia Project at
**  http://www.torproject.org/projects/vidalia.html. No part of Vidalia,
**  including this file, may be copied, modified, propagated, or distributed
**  except according to the terms described in the LICENSE file.
*/

/*
** \file VClickLabel.cpp
** \brief Custom widget to create a clickable label with both an image and text.
*/

#include "VClickLabel.h"
#include "Vidalia.h"

#include <QPainter>


/** Default constructor. */
VClickLabel::VClickLabel(QWidget *parent)
 : QWidget(parent)
{
  setCursor(Qt::PointingHandCursor);
  _flashToggle = false;
  _isPressed = false;
}

/** Returns the current size hint for this widget's current contents. */
QSize
VClickLabel::sizeHint() const
{
  int height = qMax(_pixmap.height(), fontMetrics().height())+2;
  int width = _pixmap.width() + fontMetrics().width(_text)+2;
  return QSize(width, height);
}

/** Returns the minimum size hint for this widget's current contents. */
QSize
VClickLabel::minimumSizeHint() const
{
  return sizeHint();
}

/** Overloaded paint event to draw a pixmap and a text label. */
void
VClickLabel::paintEvent(QPaintEvent *e)
{
  QPainter p(this);
  QRect rect = this->rect();

  if (_flashToggle || _isPressed) {
    p.setBrush(QColor(150,150,150));
    rect.setX(rect.x()+1);
    rect.setY(rect.y()+1);
    rect.setWidth(rect.width());
    rect.setHeight(rect.height());
    p.drawRect(rect);
  }

  rect = this->rect();
  
  // when label is in "pressed" state, we will translate the pixmap and text
  // a bit, just like regular buttons do
  const int d = _isPressed ? 2 : 0;

  if (vApp->isLeftToRight()) {
    if (!_pixmap.isNull())
      p.drawPixmap(d, qMax((rect.height()-_pixmap.height())/2+d, 0), _pixmap);
    if (!_text.isEmpty())
      p.drawText(_pixmap.width()+2+d, (rect.height()+fontInfo().pixelSize())/2+d, _text);
  } else {
    if (!_pixmap.isNull())
      p.drawPixmap(qMax(rect.right()-_pixmap.width()-d, d),
                   qMax((rect.height()-_pixmap.height())/2-d, d), _pixmap);
    if (!_text.isEmpty()) {
      int textWidth  = fontMetrics().width(_text);
      p.drawText(qMax(rect.right()-_pixmap.width()-textWidth-2-d, d),
                 (rect.height()+fontInfo().pixelSize())/2-d, _text);
    }
  }
  e->accept();
}

/** Overloaded mouse event to remember click state. */
void
VClickLabel::mousePressEvent(QMouseEvent * e)
{
  if (e->button() == Qt::LeftButton) {
    _isPressed = true;
    update();
  }
  e->accept();
}

/** Overloaded mouse event to catch left mouse button clicks. */
void
VClickLabel::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) {
    _isPressed = false;
    update();
    emit clicked();
  }
  e->accept();
}

/** Sets the label text to <b>text</b>. */
void
VClickLabel::setText(const QString &text)
{
  _text = text;
  update();
}

/** Sets the widget's image to <b>img</b>. */
void
VClickLabel::setPixmap(const QPixmap &pixmap)
{
  _pixmap = pixmap;
  update();
}

void
VClickLabel::enableFlashing()
{
  _flashToggle = true;
  repaint();
}

void
VClickLabel::disableFlashing()
{
  _flashToggle = false;
  repaint();
}
