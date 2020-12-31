#ifndef WELCOME_WIDGET_H
#define WELCOME_WIDGET_H

#include <QWidget>
#include <QThread>

namespace Ui {
class welcome_widget;
}

class welcome_widget : public QWidget
{
    Q_OBJECT
public:
    explicit welcome_widget(QWidget *parent = 0);
    ~welcome_widget();

private:
    Ui::welcome_widget *ui;

signals:

public slots:
};

class welcome_thread : public QThread
{
    Q_OBJECT
public:
    explicit welcome_thread(QObject *parent = 0);
    ~welcome_thread();

    void run();

signals:
    void finish();
};

#endif // WELCOME_WIDGET_H
