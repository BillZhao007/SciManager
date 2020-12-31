#include "sci_pdf_paper_widget.h"
#include "ui_sci_pdf_paper_widget.h"


sci_pdf_paper_widget::sci_pdf_paper_widget(scicore::sci_pdf_paper* paper,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sci_pdf_paper_widget)
{
    ui->setupUi(this);

    this->_paper = paper;

    this->_pdf_reader = new sci_pdf_reader(QString::fromStdString(paper->get_path()),this);

    this->_detail_widget = new sci_pdf_detail_widget(paper,this);

    this->_splitter = new QSplitter(this);
    _splitter->setStyleSheet("QSplitter:handle{background-color:grey}");

    _splitter->addWidget(_pdf_reader);
    _splitter->addWidget(_detail_widget);

    _splitter->setStretchFactor(0,12);
    _splitter->setStretchFactor(1,1);

    _layout = new QVBoxLayout;
    _layout->addWidget(_splitter);
    this->setLayout(_layout);

    this->_pdf_reader->suit_page();
    this->_pdf_reader->set_scroll_bar();
}

sci_pdf_paper_widget::~sci_pdf_paper_widget()
{
    delete ui;
}

