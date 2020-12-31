#ifndef SCI_UI_TOTAL_LIBRARY_WIDGET_H
#define SCI_UI_TOTAL_LIBRARY_WIDGET_H

#include <QDialog>
#include <QStandardItemModel>

#include "scisl/sci_sl_lib_buffer.h"

namespace Ui {
class sci_ui_total_library_widget;
}

/**
 * @brief 一个显示所有图书馆的表单，选中图书馆将发送library_selected(int)信号
 */
class sci_ui_total_library_widget : public QDialog
{
    Q_OBJECT

public:
    explicit sci_ui_total_library_widget(scisl::sci_sl_lib_buffer* buffer,QWidget *parent = nullptr);
    ~sci_ui_total_library_widget();

private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_accept_clicked();

    void on_pushButton_cancel_clicked();

signals:
    void library_selected(int);
private:
    Ui::sci_ui_total_library_widget *ui;

    QStandardItemModel *_model;
    scisl::sci_sl_lib_buffer* _buffer;
};

#endif // SCI_UI_TOTAL_LIBRARY_WIDGET_H
