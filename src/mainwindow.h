#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "backend.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Q_SLOT void buttonClicked();
    Q_SLOT void timeUpdate();
    Q_SLOT void usUpdate();

    Q_PROPERTY(int usX READ usX WRITE setUsX NOTIFY usXChanged)

    int usX() {
        return m_usX;
    }

    void setUsX(int _usX) {
        m_usX = _usX;
        emit usXChanged(m_usX);
    }

    // from gps
    Q_SLOT void positionUpdated(const QGeoPositionInfo &update);
    Q_SLOT void satellitesInUseUpdated(int count);

signals:
    void usXChanged(int);
protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QTimer *secondTimer;
    void setDPI(int _dpi);
    QGraphicsPixmapItem *pict;

    Backend *backend;


    int m_usX;
};

#endif // MAINWINDOW_H
