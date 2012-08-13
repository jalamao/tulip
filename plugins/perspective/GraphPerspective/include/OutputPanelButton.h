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

#ifndef OUTPUTPANELBUTTON_H
#define OUTPUTPANELBUTTON_H

#include <QtGui/QToolButton>

class OutputPanelButton : public QToolButton {
  Q_OBJECT

  Q_PROPERTY(int number READ number WRITE setNumber)
  int _number;

  Q_PROPERTY(QString title READ title WRITE setTitle)
  QString _title;

public:
  explicit OutputPanelButton(QWidget *parent = 0);
  int number() const {
    return _number;
  }
  QString title() const {
    return _title;
  }

  QSize sizeHint() const;

protected:
  void paintEvent(QPaintEvent *);

public slots:
  void setNumber(int number) {
    _number = number;
  }
  void setTitle(QString title) {
    _title = title;
  }

};

#endif // OUTPUTPANELBUTTON_H
