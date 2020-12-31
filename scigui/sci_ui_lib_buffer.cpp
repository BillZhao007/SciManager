#include "sci_ui_lib_buffer.h"


#include "lib_buffer/sci_ui_total_library_widget.h"


namespace scigui {

sci_ui_lib_buffer::sci_ui_lib_buffer()
{
    _menu = new QMenu("最近使用的图书馆");
    _mapper = new QSignalMapper(_menu);
    connect(_mapper, SIGNAL(mapped(int)), this, SLOT(select_library(int)));

    set_lib_menu();
}

sci_ui_lib_buffer::sci_ui_lib_buffer(QString path):scisl::sci_sl_lib_buffer(path.toStdString()){
    _menu = new QMenu("最近使用的图书馆");
    _mapper = new QSignalMapper(_menu);
    connect(_mapper, SIGNAL(mapped(int)), this, SLOT(select_library(int)));

    set_lib_menu();
}

QMenu* sci_ui_lib_buffer::get_lib_menu(){
    return _menu;
}


void sci_ui_lib_buffer::set_lib_menu(){
    //清除旧菜单
    QList<QAction*> actions = _menu->actions();
    for(QList<QAction*>::iterator iter = actions.begin(); iter!=actions.end(); iter++){
        disconnect(*iter, SIGNAL(triggered()), _mapper, SLOT(map()));
        _menu->removeAction(*iter);
    }

    //设置历史图书馆条目
    for(int i=get_library_count()-1; i>=0; i--){
        QAction* select_action = new QAction(QString::fromStdString(get_library_path(i)),_menu);
        _menu->addAction(select_action);
        _mapper->setMapping(select_action, i);
        connect(select_action, SIGNAL(triggered()), _mapper, SLOT(map()));
    }

    //设置清除条目
    QAction* clear_action = new QAction("清除记录",_menu);
    _menu->addAction(clear_action);
    connect(clear_action, SIGNAL(triggered()), this, SLOT(clear_menu()));

    //设置详细信息条目
    QAction* total_action = new QAction("完整记录",_menu);
    _menu->addAction(total_action);
    connect(total_action, SIGNAL(triggered()), this, SLOT(show_total_widget()));

}

QDialog* sci_ui_lib_buffer::get_lib_list(QWidget* parent){
    sci_ui_total_library_widget* widget = new sci_ui_total_library_widget(this,parent);
    connect(widget,SIGNAL(library_selected(int)),this,SLOT(select_library(int)));
    return  widget;
}

void sci_ui_lib_buffer::show_total_widget(){
    QDialog* widget = get_lib_list(NULL);
    widget->exec();
}

void sci_ui_lib_buffer::clear_menu(){
    clear_all();
    save();
    set_lib_menu();
}

bool sci_ui_lib_buffer::add_library(std::string path, int index){
    scisl::sci_sl_lib_buffer::add_library(path,index);
    set_lib_menu();
    save();
}

void sci_ui_lib_buffer::select_library(int index){
    emit library_selected(QString::fromStdString(get_library_path(index)));
}

void sci_ui_lib_buffer::delete_library(int){

}

}

