#ifndef SCI_PDF_WIDGET_H
#define SCI_PDF_WIDGET_H

#include <QWidget>

#include "sci_pdf_canvas.h"

namespace Ui {
class sci_pdf_widget;
}

class sci_pdf_reader : public QWidget
{
    Q_OBJECT

public:
    explicit sci_pdf_reader(QString path, QWidget *parent = nullptr);

    ~sci_pdf_reader();

public slots:

    /**
     * @brief 设置pdf文件的缩放因子
     * @param ratio
     */
    void set_display_ratio(double ratio);
    /**
     * @brief 将当前pdf置于显示窗口的合适位置，需要在本函数后调用绘制函数，才能显示
     */
    void suit_page();
    /**
     * @brief 将滚动条的大小和位置与当前窗口匹配
     */
    void set_scroll_bar();
private slots:

    void on_verticalScrollBar_valueChanged(int value);

    void on_lineEdit_scale_ratio_returnPressed();

    void on_pushButton_enlarge_pdf_clicked();

    void on_pushButton_shrink_pdf_clicked();

private:
    Ui::sci_pdf_widget *ui;

};

#endif // SCI_PDF_WIDGET_H
