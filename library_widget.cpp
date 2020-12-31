#include "library_widget.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include "ui_library_widget.h"
#include "scicore/sci_folder.h"
#include "scicore/sci_pdf_paper.h"

#include "scigui/sci_file_visitor_adaptor.h"

#include "empty_detail_widget.h"
//#include "scigui/open_library/sci_ui_open_library_dialog.h"

#include "scisl/sci_sl_lib.h"
#include "sciinternet/download.h"
#include "sciinternet/get_title.h"
#include "scicore/set_info.h"

#include <scigui/pdf_paper/sci_pdf_detail_widget.h>

const char* null_c_ = "&";
const int len_author_ = 6;

library_widget::library_widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::library_widget),
    _library_buffer("rf.scll"),
    mdialog(new MultiInputDialog(7, true, this))
{
    ui->setupUi(this);

    this->model = new scigui::sci_file_model(this);

    _lib = scisl::sci_sl_lib("",model);

    //读取最近使用的文件
    _library_buffer.load();
    _library_buffer.set_lib_menu();
    connect(&_library_buffer,SIGNAL(library_selected(QString)),this,SLOT(load_lib(QString)));

    this->set_up_menu_bar();

    this->set_up_tab_widget();

    this->set_up_tree_view();

    this->set_up_layout();

    this->setWindowTitle("图书馆："+QString::fromStdString(_lib.get_path()));

}

library_widget::~library_widget()
{
    delete ui;
}

void library_widget::set_up_menu_bar(){
    //设置主页菜单栏--------------------------------------------------------------------------------------------
    menuBar = ui->menubar;//new QMenuBar(this);
    // fileMenu
    fileMenu = new QMenu(tr("文件"), this);

    QAction* newLibAction = new QAction(tr("新建图书馆"));
    newLibAction->setShortcut(Qt::CTRL | Qt::Key_N);
    connect(newLibAction, SIGNAL(triggered()), this, SLOT(newLibrary()));
    fileMenu->addAction(newLibAction);

    QAction* openLibAction = new QAction(tr("打开图书馆"));
    openLibAction->setShortcut(Qt::CTRL | Qt::Key_O);
    connect(openLibAction, SIGNAL(triggered()), this, SLOT(openLibrary()));
    fileMenu->addAction(openLibAction);

    QAction* parseDocumentAction = new QAction(tr("解析文档"));
    parseDocumentAction->setShortcut(Qt::CTRL | Qt::Key_P);
    connect(parseDocumentAction, SIGNAL(triggered()), this, SLOT(parseDocument()));
    fileMenu->addAction(parseDocumentAction);

    QMenu* importDocumentMenu = new QMenu(tr("导入文献"));
    QAction* localImportAction = new QAction(tr("本地导入"));
    localImportAction->setShortcut(Qt::CTRL | Qt::Key_L);
    connect(localImportAction, SIGNAL(triggered()), this, SLOT(localImportDocument()));
    importDocumentMenu->addAction(localImportAction);
    QAction* onlineImportAction = new QAction(tr("在线导入"));
    onlineImportAction->setShortcut(Qt::CTRL | Qt::Key_I);
    connect(onlineImportAction, SIGNAL(triggered()), this, SLOT(onlineImportDocument()));
    importDocumentMenu->addAction(onlineImportAction);
    fileMenu->addMenu(importDocumentMenu);

    QAction* exportDocumentAction = new QAction(tr("导出文献"));
    exportDocumentAction->setShortcut(Qt::CTRL | Qt::Key_K);
    connect(exportDocumentAction, SIGNAL(triggered()), this, SLOT(exportDocument()));
    fileMenu->addAction(exportDocumentAction);

    fileMenu->addSeparator();

    QAction* saveAction = new QAction(tr("保存"));
    saveAction->setShortcut(Qt::CTRL | Qt::Key_S);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    fileMenu->addAction(saveAction);
    //最近浏览的图书馆菜单
    fileMenu->addMenu(_library_buffer.get_lib_menu());

    fileMenu->addSeparator();
    fileMenu->addAction(tr("退出"), exit, QKeySequence("Ctrl+Q"));

    menuBar->addMenu(fileMenu);

    // editMenu---------------------------------------------------------
    editMenu = new QMenu(tr("编辑"), this);

    QAction* undoAction = new QAction(tr("撤销"));
    undoAction->setShortcut(Qt::CTRL | Qt::Key_Z);
    connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));
    editMenu->addAction(undoAction);

    QAction* redoAction = new QAction(tr("重做"));
    redoAction->setShortcut(Qt::CTRL | Qt::Key_Y);
    connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));
    editMenu->addAction(redoAction);

    editMenu->addSeparator();

    QAction* editAction = new QAction(tr("编辑"));
    editAction->setShortcut(Qt::CTRL | Qt::Key_E);
    connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));
    editMenu->addAction(editAction);

    QAction* deleteAction = new QAction(tr("删除"));
    deleteAction->setShortcut(Qt::CTRL | Qt::Key_D);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(_delete()));
    editMenu->addAction(deleteAction);

    editMenu->addSeparator();

    QAction* searchAction = new QAction(tr("搜索"));
    searchAction->setShortcut(Qt::CTRL | Qt::Key_F);
    connect(searchAction, SIGNAL(triggered()), this, SLOT(search()));
    editMenu->addAction(searchAction);

    QAction* filterAction = new QAction(tr("筛选"));
    filterAction->setShortcut(Qt::CTRL | Qt::Key_G);
    connect(filterAction, SIGNAL(triggered()), this, SLOT(filter()));
    editMenu->addAction(filterAction);

    QAction* selectAllAction = new QAction(tr("全选"));
    selectAllAction->setShortcut(Qt::CTRL | Qt::Key_A);
    connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));
    editMenu->addAction(selectAllAction);

    menuBar->addMenu(editMenu);

    // webMenu--------------------------------------------------------------------------------------
    webMenu = new QMenu(tr("关联网络"), this);

    QAction* newWebDatabaseAction = new QAction(tr("协助创建关系网络"));
    newWebDatabaseAction->setShortcut(Qt::CTRL | Qt::Key_R);
    connect(newWebDatabaseAction, SIGNAL(triggered()), this, SLOT(newWebDatabase()));
    webMenu->addAction(newWebDatabaseAction);

    QAction* openWebDatabaseAction = new QAction(tr("关系网络论文推荐"));
    openWebDatabaseAction->setShortcut(Qt::CTRL | Qt::Key_T);
    connect(openWebDatabaseAction, SIGNAL(triggered()), this, SLOT(openWebDatabase()));
    webMenu->addAction(openWebDatabaseAction);

    menuBar->addMenu(webMenu);

    // SciManager
    sciManagerMenu = new QMenu(tr("SciManager"), this);

    QAction* aboutSciManagerAction = new QAction(tr("关于SciManager"));
    connect(aboutSciManagerAction, SIGNAL(triggered()), this, SLOT(aboutSciManager()));
    sciManagerMenu->addAction(aboutSciManagerAction);

    QAction* instructionAction = new QAction(tr("使用说明书"));
    connect(instructionAction, SIGNAL(triggered()), this, SLOT(instruction()));
    sciManagerMenu->addAction(instructionAction);

    menuBar->addMenu(sciManagerMenu);

    this->setMenuBar(menuBar);
    //-----------------------------------------------------------------------------------------------
}

void library_widget::set_up_tree_view(){
    // treeView--------------------------------------------------------------------------------
//    this->model->set_root(new scicore::sci_folder("root"));
//    this->model->add_file(new scicore::sci_folder("我的图书馆",NULL),model->get_root());
//    this->model->add_file(new scicore::sci_folder("网络下载",NULL),model->get_root());

//    scicore::sci_pdf_paper* paper = new scicore::sci_pdf_paper("单片机应用");
//    paper->set_path("F://SciManager//ex_pdf//a.pdf");
//    this->model->add_file(paper,model->get_root()->get_child(0));

    _tree_view = new scigui::sci_ui_file_tree_view(this);
    _tree_view->set_model(this->model);
    connect(_tree_view, SIGNAL(request_show_widget(QWidget*,QString)), _tab_widget, SLOT(add_page(QWidget*,QString)));
}

void library_widget::set_up_tab_widget(){
    this->_tab_widget = new scigui::sci_ui_display_tab_widget(this);
    this->_tab_widget->addTab(new empty_detail_widget,"welcome");
}

void library_widget::set_up_layout(){

    splitter = new QSplitter(Qt::Orientation::Horizontal, this);//水平
    splitter->setStyleSheet("QSplitter:handle{background-color:grey}");

    splitter->addWidget(_tree_view);
    splitter->addWidget(_tab_widget);

    splitter->setStretchFactor(0,4);
    splitter->setStretchFactor(1,16);
    splitter->setHandleWidth(1);
    // mainLayout
    QHBoxLayout* mainLayout = new QHBoxLayout(ui->centralwidget);
    mainLayout->addWidget(splitter);

    ui->centralwidget->setLayout(mainLayout);
}



void library_widget::load_lib(QString path){
    _lib.set_path(path.toStdString());
    _lib.load();

    _library_buffer.add_library(path.toStdString());


}


void library_widget::newLibrary() {
    qDebug("newLibrary");

    _lib.set_path("");
    model->set_root(new scicore::sci_folder("root"));

    this->setWindowTitle("新建图书馆："+QString::fromStdString(_lib.get_path()));
}

void library_widget::openLibrary() {
    qDebug("openLibrary");
    QString file_name = QFileDialog::getOpenFileName(NULL,"打开图书馆",".","*.sclb");

    if(file_name.isEmpty()){
        return;//QMessageBox::critical(this,"")
    }

    load_lib(file_name);
    this->setWindowTitle("图书馆："+QString::fromStdString(_lib.get_path()));
}

void library_widget::parseDocument() {
    qDebug("parseDocument");
    std::string cache_root = "./cache/";
    if (access(cache_root.c_str(), 0) == -1) {
        _mkdir(cache_root.c_str());
    }
//    paper->title = get_title(path.toStdString());
//    set_info(*paper, cache_root);

}

void library_widget::onlineImportDocument() {
    bool ok;
    qDebug("onlineImportDocument");
    QString title = QInputDialog::getText(this, tr("请输入文献名称"),
                                         tr("文献名称："),
                                         QLineEdit::Normal,
                                          "", &ok);
    if (ok && !title.isEmpty()){
        QString save_path = QFileDialog::getExistingDirectory(
                       this, "选择保存路径", "/");
        if(!save_path.isEmpty()){
            download(title.toStdString(), save_path.toStdString());
            QModelIndex index = _tree_view->currentIndex();
            scicore::sci_file* parent = model->file_from_index(index);

            if(!parent){
                QMessageBox::critical(this,"错误","错误：未打开图书馆");
                return;
            }

            scicore::sci_pdf_paper* paper = new scicore::sci_pdf_paper(title.toStdString(),parent);
            paper->title = title.toStdString();
            std::string cache_root = "./cache/";
            if (access(cache_root.c_str(), 0) == -1) {
                _mkdir(cache_root.c_str());
            }
            set_info(*paper, cache_root);
            paper->set_path(save_path.toStdString());
            model->add_file(paper, parent);

        }

    }
}

void library_widget::localImportDocument() {
    qDebug("localImportDocument");

    QString path = QFileDialog::getOpenFileName(this,"导入文件",".","*.pdf");
    if(!path.isEmpty()){
        QModelIndex index = _tree_view->currentIndex();
        scicore::sci_file* parent = model->file_from_index(index);

        if(!parent){
            QMessageBox::critical(this,"错误","错误：未打开图书馆");
            return;
        }

        QDir dir(path);

        scicore::sci_pdf_paper* paper = new scicore::sci_pdf_paper(dir.dirName().toStdString(),parent);
        paper->set_path(path.toStdString());
        model->add_file(paper,parent);
    }
}

void library_widget::exportDocument() {
    qDebug("exportDocument");
}

void library_widget::save() {
    qDebug("save");
    if(_lib.get_path().empty()){
        //如果该图书馆没有路径，说明需要保存
        QString path = QFileDialog::getSaveFileName(this,"另存为",".","*.sclb");
        qDebug()<<"new lib path: "<<path;
        if(!path.isEmpty()){
            _lib.set_path(path.toStdString());
            _lib.save();
        }
    }
    else{
        _lib.save();
    }
    _library_buffer.add_library(_lib.get_path());
    this->setWindowTitle("图书馆："+QString::fromStdString(_lib.get_path()));
}


void library_widget::edit() {
    qDebug("edit");
}


void library_widget::undo() {
    qDebug("undo");
}

void library_widget::redo() {
    qDebug("redo");
}

void library_widget::_delete() {
    qDebug("_delete");
}


void library_widget::search() {
    qDebug("search");
}

void library_widget::filter() {
    qDebug("filter");
}

void library_widget::selectAll() {
    qDebug("selectAll");
}

void library_widget::newWebDatabase() {
    qDebug("newWebDatabase");
    QModelIndex index = _tree_view->currentIndex();
    scicore::sci_file* pt = model->file_from_index(index);
    if(!pt){
        QMessageBox::critical(this,"错误","错误：未打开图书馆");
        return;
    }
    else if(typeid(*pt) != typeid(scicore::sci_pdf_paper)) {
        QMessageBox::critical(this,"错误","错误：请打开一个具体的论文文件");
        return;
    }

    QMessageBox * mBox = new QMessageBox(this);
    mBox->setWindowTitle(QString("协助创建论文关系网络"));
    mBox->setText(QString("是否上传本论文内容，\n协助创建论文关系网络？"));
    mBox->setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
    mBox->setButtonText(QMessageBox::StandardButton::Ok, QString("确定"));
    mBox->setButtonText(QMessageBox::StandardButton::Cancel, QString("取消"));
    mBox->exec();
    QMessageBox::StandardButton ret = mBox->standardButton(mBox->clickedButton());
    if(ret == QMessageBox::Ok) {
        scicore::sci_pdf_paper *pt1 = (scicore::sci_pdf_paper*)pt;
        bool flag = sci_r::upload_single(*pt1);
        if(flag) QMessageBox::information(this, "成功", "成功上传");
        else QMessageBox::critical(this,"错误","错误：上传失败");
    }
    if (mBox != nullptr) {
        delete mBox;
        mBox = nullptr;
    }
}

void library_widget::openWebDatabase() {
    qDebug("openWebDatabase");
    QModelIndex index = _tree_view->currentIndex();
    scicore::sci_file* pt = model->file_from_index(index);
    if(!pt){
        QMessageBox::critical(this,"错误","错误：未打开图书馆");
        return;
    }
    else if(typeid(*pt) != typeid(scicore::sci_pdf_paper)) {
        QMessageBox::critical(this,"错误","错误：请打开一个具体的论文文件");
        return;
    }
    QMessageBox * mBox = new QMessageBox(this);
    mBox->setWindowTitle(QString("运用论文关系网络"));
    mBox->setText(QString("是否寻找本论文的推荐阅读？"));
    mBox->setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
    mBox->setButtonText(QMessageBox::StandardButton::Ok, QString("确定"));
    mBox->setButtonText(QMessageBox::StandardButton::Cancel, QString("取消"));
    mBox->exec();
    QMessageBox::StandardButton ret = mBox->standardButton(mBox->clickedButton());
    if(ret == QMessageBox::Ok) {
        scicore::sci_pdf_paper *pt1 = (scicore::sci_pdf_paper*)pt;

        QStringList list;
        list << "推荐论文数目: " << "同数据库权值: " << "同作者权值: " << "同关键词权值: " << "同期刊/会议权值: "\
             << "引用关系权值: " << "同领域权值: ";
        mdialog->m_LineEdits[0]->setPlaceholderText("5");
        mdialog->m_LineEdits[1]->setPlaceholderText("1");
        mdialog->m_LineEdits[2]->setPlaceholderText("5");
        mdialog->m_LineEdits[3]->setPlaceholderText("15");
        mdialog->m_LineEdits[4]->setPlaceholderText("7");
        mdialog->m_LineEdits[5]->setPlaceholderText("20");
        mdialog->m_LineEdits[6]->setPlaceholderText("5");
        mdialog->SetLabelTexts(list);
        mdialog->SetLabelsWidth(200);
        mdialog->exec();

        sci_r::weight wt;
        list = mdialog->GetAllTexts();
        int rec_n = (list[0] == ""? 1 : list[0].toInt());
        wt.database = (list[1] == ""? 0 : list[1].toDouble());
        wt.author = (list[2] == ""? 0 : list[2].toDouble());
        wt.keyword = (list[3] == ""? 0 : list[3].toDouble());
        wt.origin = (list[4] == ""? 0 : list[4].toDouble());
        wt.ref = (list[5] == ""? 0 : list[5].toDouble());
        wt.field = (list[6] == ""? 0 : list[6].toDouble());

        std::vector<scicore::sci_pdf_paper> res = sci_r::recommend(*pt1, wt, rec_n);
        if(res.size() == rec_n) QMessageBox::information(this, "成功", "成功：请至右方菜单查看");
        else QMessageBox::critical(this,"错误","错误：搜索失败");
        
		pt1->recommend.clear();
        for(int i=0; i<rec_n; i++){
            if(res[i].title != null_c_){
                pt1->recommend.push_back(res[i].title);

                std::string authors = res[i].authors[0];
                for(int j=1; j<len_author_; j++){
                    if(res[i].authors[j] != null_c_)
                        authors += ', ';
                        authors += res[i].authors[j];
                }
                pt1->recommend.push_back(authors);
                pt1->recommend.push_back(res[i].date);
                std::cout<<res[i].title<<" "<<authors<<std::endl;
            }
        }
        for(int i=0; i<pt1->page_list.size(); i++){
            pt1->page_list[i]->webUpdateSlot();
        }
    }
    if (mBox != nullptr) {
        delete mBox;
        mBox = nullptr;
    }
}

void library_widget::aboutSciManager() {
    qDebug("aboutSciManager");
}

void library_widget::instruction() {
    qDebug("instruction");
}

void library_widget::searchLine() {
    qDebug("searchLine");
}
