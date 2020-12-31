#ifndef SCI_PDF_CANVAS_H
#define SCI_PDF_CANVAS_H

#include <QWidget>
#include <QVector>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QQueue>

#include <QPalette>
#include <QResizeEvent>
#include <QMutex>

#include "sci_pdf_utils.h"
#include "sci_pdf_load_thread.h"

class sci_pdf_canvas: public QWidget
{

    Q_OBJECT
public:
    explicit sci_pdf_canvas(QString path = "", QWidget *parent = 0);
    sci_pdf_canvas(QWidget *parent = 0);

    ~sci_pdf_canvas();

    void load(QString path);

    void paintEvent(QPaintEvent *e) override;

    void resizeEvent(QResizeEvent *event) override;

    void mousePressEvent(QMouseEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

    void mouseMoveEvent(QMouseEvent *e) override;

    bool page_to(int page);

    void set_handle_width(int width);

    int get_page_step();

    int get_total_height();

    int get_total_y();

    double get_scale_ratio();

signals:
    void page_size_changed(double);

    void canvas_size_changed();

public slots:
    void set_canvas_size(int width,int height);

    void scale_page(double ratio);

    void suit_page_to_canvas();

    void _suit_page_to_canvas();

    void set_y_value(int y);

    void change_y_value(int y);

    void set_x_value(int x);

    void change_x_value(int x);

    void paint();

private:

    sci_pdf_load_thread* _thread;

    QString _path;

    int _page_width;
    int _page_height;

    int _current_page;
    int _current_page_y;
    int _current_page_x;

    int _canvas_width;
    int _canvas_height;

    int _handle_width;

    bool _is_clicked;
    int _last_x;
    int _last_y;

    bool _to_suit_page_to_canvas;
};

#endif // SCI_PDF_CANVAS_H
