#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QVBoxLayout>

class LibraryWidget : public QWidget {
    Q_OBJECT
public:
    explicit LibraryWidget(QWidget *parent = 0);

    QTableView *libraryTable;
    QStandardItemModel *libraryTableModel;

signals:
    void openDocumentSignal(QString);

public slots:
    void openDocument(const QModelIndex&);
};

#endif // LIBRARYWIDGET_H
