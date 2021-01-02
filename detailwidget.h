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

class DetailWidget : public QWidget {
    Q_OBJECT
public:
    explicit DetailWidget(QWidget *parent = 0);

    QPushButton *detailButton;
    QPushButton *tagButton;
    QPushButton *webButton;

    QLabel *detailTableHeaderLabel;
    QTableView *detailTableView;
    QStandardItemModel *detailTableModel;

    QListView *tagView;
    QStandardItemModel *tagModel;

    QListView *webView;
    QStandardItemModel *webModel;

signals:

public slots:
    void showDetail();
    void showTag();
    void showWeb();

private:
    void setButtonStyleSheet(QPushButton*);
};

#endif // DETAILWIDGET_H
