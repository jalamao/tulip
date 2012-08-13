/**
 *
 * This file is part of Tulip (www.tulip-software.org)
 *
 * Authors: David Auber and the Tulip development Team
 * from LaBRI, University of Bordeaux 1 and Inria Bordeaux - Sud Ouest
 *
 * Tulip is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * Tulip is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 */

#include "OutputPanelButton.h"
#include <QtGui/QPainter>
#include <QtGui/QApplication>

OutputPanelButton::OutputPanelButton(QWidget *parent): QToolButton(parent), _number(0) {
}

QSize OutputPanelButton::sizeHint() const {
  ensurePolished();

  QSize s = fontMetrics().size(Qt::TextSingleLine, _title);

  // Expand to account for border image set by stylesheet above
  s.rwidth() += 19 + 5 + 2;
  s.rheight() += 2 + 2;

  return s.expandedTo(QApplication::globalStrut());
}

void OutputPanelButton::paintEvent(QPaintEvent* event) {
  QToolButton::paintEvent(event);
  const QFontMetrics fm = fontMetrics();
  const int baseLine = (height() - fm.height() + 1) / 2 + fm.ascent();
  const int numberWidth = fm.width(QString::number(_number));

  QPainter p(this);
  p.setFont(font());
  p.setPen(Qt::white);
  p.drawText((20 - numberWidth) / 2, baseLine, QString::number(_number));

  if (!isChecked())
    p.setPen(Qt::black);

  int leftPart = 22;
  p.drawText(leftPart, baseLine, width()-leftPart, height()-baseLine*2, Qt::AlignCenter | Qt::AlignVCenter, fm.elidedText(_title, Qt::ElideMiddle, width() - leftPart - 1));
}
