#ifndef DISPLAY_WIDGET_H
#define DISPLAY_WIDGET_H

#include <QTabWidget>

namespace Ui {
class display_widget;
}

class display_widget : public QTabWidget
{
    Q_OBJECT

public:
    explicit display_widget(QWidget *parent = nullptr);
    ~display_widget();

private:
    Ui::display_widget *ui;

public slots:
    /**
     * @brief 关闭index处的展示窗口
     * @param index
     */
    void close_page(int index);
};

#endif // DISPLAY_WIDGET_H
