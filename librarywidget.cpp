#include "librarywidget.h"

LibraryWidget::LibraryWidget(QWidget *parent) : QWidget(parent) {
    libraryTable = new QTableView(this);
    QFont libraryTableFont;
    libraryTableFont.setPointSize(14);
    libraryTable->setFont(libraryTableFont);
    libraryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    libraryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    libraryTable->setFocusPolicy(Qt::NoFocus);
    libraryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    libraryTable->verticalHeader()->hide();
    libraryTable->setAlternatingRowColors(true);
    libraryTable->setStyleSheet("QTableView{background-color:white;alternate-background-color:azure}");

    connect(libraryTable, SIGNAL(clicked(QModelIndex)), this, SLOT(openDocument(QModelIndex)));

    libraryTableModel = new QStandardItemModel(libraryTable);
    libraryTableModel->setColumnCount(3);
    libraryTableModel->setRowCount(32);

    libraryTableModel->setHeaderData(0, Qt::Horizontal, "标题");
    libraryTableModel->setHeaderData(1, Qt::Horizontal, "作者");
    libraryTableModel->setHeaderData(2, Qt::Horizontal, "关键词");

    libraryTable->setModel(libraryTableModel);

    // example
    QStandardItem* d11 = new QStandardItem(tr("\"第三条道路\"社会福利思想主张的发展"));
    d11->setData(tr("\"第三条道路\"社会福利思想主张的发展"), Qt::ToolTipRole);
    libraryTableModel->setItem(0, 0, d11);
    QStandardItem* d12 = new QStandardItem(tr("丁建定"));
    d12->setData(tr("丁建定"), Qt::ToolTipRole);
    libraryTableModel->setItem(0, 1, d12);
    QStandardItem* d13 = new QStandardItem(tr("社会市场经济"));
    d13->setData(tr("社会市场经济"), Qt::ToolTipRole);
    libraryTableModel->setItem(0, 2, d13);

    QStandardItem* d21 = new QStandardItem(tr("经济效率、刺激依赖与城投债规模"));
    d21->setData(tr("经济效率、刺激依赖与城投债规模"), Qt::ToolTipRole);
    libraryTableModel->setItem(1, 0, d21);
    QStandardItem* d22 = new QStandardItem(tr("卢进勇、李思静"));
    d22->setData(tr("卢进勇、李思静"), Qt::ToolTipRole);
    libraryTableModel->setItem(1, 1, d22);
    QStandardItem* d23 = new QStandardItem(tr("TFP、城投债"));
    d23->setData(tr("TFP、城投债"), Qt::ToolTipRole);
    libraryTableModel->setItem(1, 2, d23);
    // example


    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addWidget(libraryTable, 1);

    setLayout(mainLayout);

    libraryTable->setColumnWidth(0, this->width()/2);
    libraryTable->setColumnWidth(1, this->width()/4);
    libraryTable->setColumnWidth(2, this->width()/4);
}

void LibraryWidget::openDocument(const QModelIndex &index) {
    if (libraryTableModel->item(index.row(), 0)) {
        QString filename = libraryTableModel->item(index.row(), 0)->text();
        qDebug("openDocument, index: %d, filename: %s", index.row(), filename);

        this->hide();
        emit openDocumentSignal(filename);
    } else qDebug("invalid index");
}
