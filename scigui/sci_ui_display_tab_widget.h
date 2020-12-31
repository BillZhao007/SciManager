#ifndef SCI_LIBRARY_DISPLAY_WIDGET_H
#define SCI_LIBRARY_DISPLAY_WIDGET_H

#include <QTabWidget>

namespace scigui {

class sci_ui_display_tab_widget: public QTabWidget
{
    Q_OBJECT

public:
    explicit sci_ui_display_tab_widget(QWidget *parent = nullptr);
    ~sci_ui_display_tab_widget();


public slots:
    /**
     * @brief 关闭index处的展示窗口
     * @param index
     */
    void close_page(int index);

    /**
     * @brief 展示窗口
     */
    void add_page(QWidget* widget, QString title);
};


}



#endif // SCI_LIBRARY_DISPLAY_WIDGET_H
