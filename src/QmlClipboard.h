// **************************************************************************
// class QmlClipboard
// 02.07.2021
// Clipboard access from QML
// **************************************************************************
// MIT License
// Copyright © 2021 Patrick Fial
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
// files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// **************************************************************************
// includes
// **************************************************************************

#ifndef QMLCLIPBOARD_H
#define QMLCLIPBOARD_H

#include <QApplication>
#include <QClipboard>
#include <QObject>

// **************************************************************************
// class QmlClipboard
// **************************************************************************

namespace qml
{
   class QmlClipboard : public QObject
   {
         Q_OBJECT

      public:
         QmlClipboard(QObject* parent = nullptr);
         Q_INVOKABLE void setText(QString text);

      private:
         QClipboard* clipboard;
   };
}

#endif // QMLCLIPBOARD_H
