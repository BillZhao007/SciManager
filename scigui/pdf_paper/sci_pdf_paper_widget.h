#ifndef SCI_PDF_PAPER_WIDGET_H
#define SCI_PDF_PAPER_WIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>

#include "scicore/sci_pdf_paper.h"
#include "sci_pdf_reader.h"
#include "sci_pdf_detail_widget.h"
namespace Ui {
class sci_pdf_paper_widget;
}

class sci_pdf_paper_widget : public QWidget
{
    Q_OBJECT

public:
    explicit sci_pdf_paper_widget(scicore::sci_pdf_paper* paper,QWidget *parent = nullptr);
    ~sci_pdf_paper_widget();

private:
    Ui::sci_pdf_paper_widget *ui;

    scicore::sci_pdf_paper* _paper;

    sci_pdf_reader* _pdf_reader;

    sci_pdf_detail_widget* _detail_widget;

    QSplitter* _splitter;

    QVBoxLayout* _layout;

};

#endif // SCI_PDF_PAPER_WIDGET_H
