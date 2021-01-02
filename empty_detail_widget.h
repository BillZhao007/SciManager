#ifndef EMPTY_DETAIL_WIDGET_H
#define EMPTY_DETAIL_WIDGET_H

#include <QWidget>

namespace Ui {
class empty_detail_widget;
}

class empty_detail_widget : public QWidget
{
    Q_OBJECT

public:
    explicit empty_detail_widget(QWidget *parent = nullptr);
    ~empty_detail_widget();

private:
    Ui::empty_detail_widget *ui;
};

#endif // EMPTY_DETAIL_WIDGET_H
