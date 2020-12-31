#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QLabel>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QString>
#include <QPushButton>
#include <QListView>

#include "scicore/sci_pdf_paper.h"

class sci_pdf_detail_widget : public QWidget {
    Q_OBJECT
public:
    explicit sci_pdf_detail_widget(scicore::sci_pdf_paper* paper, QWidget *parent = 0);
    ~sci_pdf_detail_widget();
    QPushButton *detailButton;
    QPushButton *tagButton;
    QPushButton *webButton;

    QTableView *detailTableView;
    QStandardItemModel *detailTableModel;

    QListView *tagView;
    QStandardItemModel *tagModel;

    QTableView *webView;
    QStandardItemModel *webModel;

    QStringList detailItem;
    QStringList detialItemData;
    QStringList webItemData;

    void webUpdateSlot();

signals:

public slots:
    void showDetail();
    void showTag();
    void showWeb();
    void change_info(QStandardItem*);

private:
    void setButtonStyleSheet(QPushButton*);

    scicore::sci_pdf_paper* _paper;
};

#endif // DETAILWIDGET_H
