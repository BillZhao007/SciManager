#include "detailwidget.h"

DetailWidget::DetailWidget(QWidget *parent) : QWidget(parent) {
    int detailItemNum = 10;
    QString detailItem[] = {"题目", "作者", "关键词", "来源", "中图分类号", "日期", "被引", "下载", "文章编号", "摘要"};

    QFont detailFont;
    detailFont.setPointSize(14);

    detailButton = new QPushButton(tr("信息"));
    detailButton->setFont(detailFont);
    setButtonStyleSheet(detailButton);
    connect(detailButton, SIGNAL(clicked()), this, SLOT(showDetail()));

    tagButton = new QPushButton(tr("标签"));
    tagButton->setFont(detailFont);
    setButtonStyleSheet(tagButton);
    connect(tagButton, SIGNAL(clicked()), this, SLOT(showTag()));

    webButton = new QPushButton(tr("网络"));
    webButton->setFont(detailFont);
    setButtonStyleSheet(webButton);
    connect(webButton, SIGNAL(clicked()), this, SLOT(showWeb()));

    QHBoxLayout* rightButtonLayout = new QHBoxLayout;
    rightButtonLayout->addStretch();
    rightButtonLayout->addWidget(detailButton);
    rightButtonLayout->addWidget(tagButton);
    rightButtonLayout->addWidget(webButton);
    rightButtonLayout->addStretch();


    // detailTableHeaderLabel
    detailTableHeaderLabel = new QLabel(tr("期刊"));
    detailTableHeaderLabel->setAlignment(Qt::AlignCenter);
    detailTableHeaderLabel->setFixedHeight(30);
    detailTableHeaderLabel->setFont(detailFont);
    detailTableHeaderLabel->setStyleSheet("background-color:white");


    // detailTableView
    detailTableView = new QTableView(this);
    QFont detailTableFont;
    detailTableFont.setPointSize(14);
    detailTableView->setFont(detailTableFont);
    detailTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // detailTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // detailTableView->setShowGrid(false);
    detailTableView->setSelectionMode(QAbstractItemView::NoSelection);
    detailTableView->setFocusPolicy(Qt::NoFocus);
    detailTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    detailTableView->horizontalHeader()->hide();
    detailTableView->verticalHeader()->hide();
    detailTableView->setAlternatingRowColors(true);
    detailTableView->setStyleSheet("QTableView{border:0px;background-color:white;alternate-background-color:azure}");

    detailTableModel = new QStandardItemModel(detailTableView);
    detailTableModel->setColumnCount(2);
    detailTableModel->setRowCount(30);

    detailTableView->setModel(detailTableModel);

    QFont f;
    f.setWeight(QFont::Bold);
    for (int i = 0; i < detailItemNum; i++) {
        QStandardItem* a = new QStandardItem(detailItem[i]);
        a->setFont(f);
        detailTableModel->setItem(i, 0, a);
    }


    // tagView
    tagView = new QListView(this);
    tagView->setFont(detailFont);
    tagView->setSelectionMode(QAbstractItemView::NoSelection);
    tagView->setFocusPolicy(Qt::NoFocus);
    tagView->setStyleSheet("background-color:white;border:0px");
    tagView->hide();

    tagModel = new QStandardItemModel(tagView);
    tagView->setModel(tagModel);

    // example
    QStandardItem* tag = new QStandardItem(tr("Tag"));
    tagModel->appendRow(tag);
    // example


    // webView
    webView = new QListView(this);
    webView->setFont(detailFont);
    webView->setSelectionMode(QAbstractItemView::NoSelection);
    webView->setFocusPolicy(Qt::NoFocus);
    webView->setStyleSheet("background-color:white;border:0px");
    webView->hide();

    webModel = new QStandardItemModel(webView);
    webView->setModel(webModel);

    // example
    QStandardItem* web = new QStandardItem(tr("Web"));
    webModel->appendRow(web);
    // example


    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addLayout(rightButtonLayout, 0);
    mainLayout->addWidget(detailTableHeaderLabel, 0);
    mainLayout->addWidget(detailTableView, 1);
    mainLayout->addWidget(tagView);
    mainLayout->addWidget(webView);

    setLayout(mainLayout);
}

void DetailWidget::setButtonStyleSheet(QPushButton *b) {
    b->setStyleSheet("QPushButton{padding:2px 22px; background-color:white; color:black; border-radius:10px; border:2px groove gray; border-style:outset;}"
                     "QPushButton:hover{background-color:black; color: white;}"
                     "QPushButton:pressed{background-color:rgb(133, 133, 133); border-style: inset; }"
                     );
}

void DetailWidget::showDetail() {
    qDebug("showDetail");

    tagView->hide();
    webView->hide();

    detailTableHeaderLabel->show();
    detailTableView->show();
}

void DetailWidget::showTag() {
    qDebug("showTag");

    detailTableHeaderLabel->hide();
    detailTableView->hide();
    webView->hide();

    tagView->show();
}

void DetailWidget::showWeb() {
    qDebug("showWeb");

    detailTableHeaderLabel->hide();
    detailTableView->hide();
    tagView->hide();

    webView->show();
}
