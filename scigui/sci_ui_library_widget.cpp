#include "sci_ui_library_widget.h"
#include "ui_sci_ui_library_widget.h"

#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

#include "../scicore/sci_folder.h"
#include "sci_file_visitor_adaptor.h"

#include "../scisl/sci_sl_file.h"

namespace scigui {

sci_ui_library_widget::sci_ui_library_widget(QString filename,QWidget *parent) :
    QMainWindow(parent),_filename(filename),
    ui(new Ui::sci_ui_library_widget)
{
    ui->setupUi(this);

    //设置右键能弹出自定义菜单
    this->ui->treeView_library_file_tree->setContextMenuPolicy(Qt::CustomContextMenu);

    model = new sci_file_model(this);//创建模型

    //sci_sl_file save;

    //scicore::sci_file* file = save.load(_filename.toStdString());

    //model->set_root(file);

    ui->treeView_library_file_tree->setModel(model);


}

sci_ui_library_widget::~sci_ui_library_widget()
{
    delete ui;
}

void sci_ui_library_widget::on_treeView_library_file_tree_doubleClicked(const QModelIndex &index)
{

    //获取选取文件的指针
    scicore::sci_file* file = model->file_from_index(index);
    scigui::sci_ui_file* ui_file = scigui::ui_of_file(file, model);
    //右边打开编辑窗口，这里是随便加的
    QWidget* edit_widget = ui_file->edit_widget(this);
    this->ui->tabWidget_file_edit->addTab(edit_widget,index.data().toString());
}

void sci_ui_library_widget::on_treeView_library_file_tree_clicked(const QModelIndex &index)
{
    qDebug()<<"library file tree right clicked";
    qDebug()<<ui->treeView_library_file_tree->currentIndex();
    if(qApp->mouseButtons() == Qt::RightButton){
        //右键点击
        this->hide();
    }

}

void sci_ui_library_widget::mousePressEvent(QMouseEvent *event){
    //获取点击的下标
    qDebug() << event->x() << ":" << event->y();
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "左键" ;
    }
    else if(event->button() == Qt::RightButton)
    {
        qDebug() << "右键" ;
    }
}



void sci_ui_library_widget::on_treeView_library_file_tree_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index=ui->treeView_library_file_tree->currentIndex();
    scicore::sci_file* file = this->model->file_from_index(index);

    scigui::sci_ui_file* ui_file = scigui::ui_of_file(file, model);
    QMenu* menu=ui_file->context_menu(this);
    menu->exec(QCursor::pos()); //在鼠标点击的位置显示鼠标右键菜单
}

void sci_ui_library_widget::closeEvent(QCloseEvent * event){
    switch( QMessageBox::information( this, tr("保存"),tr("您即将离开本图书馆，是否保存并退出？"),tr("确定"), tr("取消"),0, 1 ) )
     {
        case 0:{
        //sci_sl_file save;
        //save.save(model->get_root(),this->_filename.toStdString());
        event->accept();
              break;
        }

    case 1:{
        event->ignore();
        break;
        }
     default:
        event->ignore();
        break;
        }
}

}
