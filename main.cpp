/*
 * Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
 *
 */

#include "src/MainWindow/mainwindow.h"
#include <QtSingleApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QScreen>
#include <QTranslator>
#include <QLocale>
#include <KWindowEffects>
#include <X11/Xlib.h>
#include <syslog.h>

void centerToScreen(QWidget* widget) {
    if (!widget)
      return;
    QDesktopWidget* m = QApplication::desktop();
    QRect desk_rect = m->screenGeometry(m->screenNumber(QCursor::pos()));
    int desk_x = desk_rect.width();
    int desk_y = desk_rect.height();
    int x = widget->width();
    int y = widget->height();
    widget->move(desk_x / 2 - x / 2 + desk_rect.left(), desk_y / 2 - y / 2 + desk_rect.top());
}

int main(int argc, char *argv[])
{
    qRegisterMetaType<QVector<QStringList>>("QVector<QStringList>");

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QtSingleApplication app("ukui-menu-search", argc, argv);
    app.setQuitOnLastWindowClosed(false);


    if(app.isRunning())
    {
        app.sendMessage("raise_window_noop");
        return EXIT_SUCCESS;
    }

    QTranslator translator;
    if (translator.load(QLocale(), "ukui-menu", "_", QM_FILES_INSTALL_PATH))
        app.installTranslator(&translator);
    else
        qDebug() << "Load translations file" << QLocale() << "failed!";

    MainWindow *w=new MainWindow;
    w->setFrameStyle();
    centerToScreen(w);
    w->show();
    w->raise();
    w->activateWindow();
    w->loadMainWindow();
    app.setActivationWindow(w);

    KWindowEffects::enableBlurBehind(w->winId(),true);

    return app.exec();
}
