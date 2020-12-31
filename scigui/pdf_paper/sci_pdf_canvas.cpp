#include "sci_pdf_canvas.h"

#include <QDebug>
sci_pdf_canvas::sci_pdf_canvas(QString path, QWidget *parent):QWidget(parent)
{
    _thread = new sci_pdf_load_thread();
    //读取设置
    load(path);
    connect(_thread,SIGNAL(load_new_image()),this,SLOT(paint()));

    //显示设置
    _current_page = 0;
    _current_page_y = 0;
    _current_page_x = 0;

    _canvas_width = this->width();
    _canvas_height = this->height();

    _handle_width = 5;
    //运行读取线程
    _thread->start();
}

sci_pdf_canvas::sci_pdf_canvas(QWidget *parent):QWidget(parent)
{
    _thread = new sci_pdf_load_thread();
    //读取设置
    load("");
    connect(_thread,SIGNAL(load_new_image()),this,SLOT(paint()));

    //显示设置
    _current_page = 0;
    _current_page_y = 0;
    _current_page_x = 0;

    _canvas_width = this->width();
    _canvas_height = this->height();

    _handle_width = 5;
    //运行读取线程
    _thread->start();
}

void sci_pdf_canvas::load(QString path){
    _thread->load_pdf(path);
    _page_width = _thread->get_page_size().width();
    qDebug()<<"load pdf file, each page width: "<<_page_width;
    _page_height = _thread->get_page_size().height();
    paint();
}

sci_pdf_canvas::~sci_pdf_canvas(){
    _thread->terminate();
    delete _thread;
}

void sci_pdf_canvas::paintEvent(QPaintEvent *e){
    if(_to_suit_page_to_canvas){
        _to_suit_page_to_canvas=0;
        _suit_page_to_canvas();
    }


    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::darkGray);

    int display_page = this->_current_page;
    int display_page_x = this->_current_page_x;
    int display_page_y = this->_current_page_y;
    //qDebug()<<_page_width;
    do{
        if(_thread->page_loaded(display_page)){
            painter.drawImage(display_page_x,display_page_y, _thread->get_page(display_page)->scaled(this->_page_width,this->_page_height));
        }
        else{
            _thread->load_page(display_page);
            painter.fillRect(display_page_x,display_page_y,_page_width,_page_height,Qt::white);
        }

        display_page_y+= this->_handle_width+this->_page_height;
        display_page++;
    }
    while(display_page_y<this->_canvas_height);

}

void sci_pdf_canvas::mousePressEvent(QMouseEvent *e){
    _is_clicked = true;
    _last_x = e->x();
    _last_y = e->y();
}

void sci_pdf_canvas::mouseReleaseEvent(QMouseEvent *e){
    _is_clicked = false;
}

void sci_pdf_canvas::mouseMoveEvent(QMouseEvent *e){
    if(_is_clicked){
        int y_offset = e->y()-_last_y;
        int x_offset = e->x()-_last_x;
        _last_x = e->x();
        _last_y = e->y();

        change_y_value(-y_offset);
        change_x_value(x_offset);
        paint();
    }
}

void sci_pdf_canvas::resizeEvent(QResizeEvent *event){

    //_current_page_x *= this-> width()/_canvas_width;

    _canvas_width = this->width();
    _canvas_height = this->height();
    qDebug()<<"resize"<<_canvas_width;
    if(_canvas_width>_page_width+2*_handle_width){
        _current_page_x = (_canvas_width-_page_width)/2;
    }

    int cache_size = _canvas_height/get_page_step()+5;
    cache_size = cache_size>5?cache_size:5;
    _thread->set_cache_size(cache_size);

    emit canvas_size_changed();
    //this->paint();
}

bool sci_pdf_canvas::page_to(int page){
    this->_current_page=page;
    this->_thread->load_page(page);
    return true;
}

void sci_pdf_canvas::set_handle_width(int width){
    this->_handle_width = width;
}

int sci_pdf_canvas::get_page_step(){
    return this->_page_height+this->_handle_width;
}

int sci_pdf_canvas::get_total_height(){
    return (this->_thread->get_page_num()-1) * get_page_step();
}

int sci_pdf_canvas::get_total_y(){
    return _current_page * get_page_step() + _current_page_y;
}

double sci_pdf_canvas::get_scale_ratio(){
    return (_page_width+0.0)/(_thread->get_page_size().width());
}

void sci_pdf_canvas::set_canvas_size(int width,int height){
    _canvas_width = width;
    _canvas_height = height;
}

void sci_pdf_canvas::scale_page(double ratio){
    _page_width = ratio*_thread->get_page_size().width();
    _page_height = ratio*_thread->get_page_size().height();

    if(_canvas_width>_page_width+2*_handle_width){
        _current_page_x = (_canvas_width-_page_width)/2;
    }

    int cache_size = _canvas_height/get_page_step()+5;
    cache_size = cache_size>5?cache_size:5;
    _thread->set_cache_size(cache_size);

    emit page_size_changed(ratio);
    //paint();
}

void sci_pdf_canvas::suit_page_to_canvas(){
    _to_suit_page_to_canvas = 1;
}

void sci_pdf_canvas::_suit_page_to_canvas(){
    qDebug()<<"Now suit page to canvas";
    double ratio = (_canvas_width-2*_handle_width+0.0)/_thread->get_page_size().width();
    qDebug()<<"ratio"<<ratio;
    if(ratio>0)
        scale_page(ratio);
}

void sci_pdf_canvas::set_y_value(int y){
    this->_thread->clear_load_queue();

    page_to(y/get_page_step());
    this->_current_page_y = -y%get_page_step();
    //qDebug()<<_current_page_y;

}

void sci_pdf_canvas::change_y_value(int y){
    int npage;
    int ny;
    //qDebug()<<_current_page<<" "<<_current_page_y<<" "<<y;
    if(-_current_page_y+y>=0){
        npage = _current_page+(-_current_page_y+y)/get_page_step();
        ny = - (-_current_page_y+y)%get_page_step();
    }
    else{
        npage = _current_page+(-_current_page_y+y)/get_page_step()-1;
        ny = - get_page_step() - (-_current_page_y+y)%get_page_step();
    }

    if(npage>=0&&npage<this->_thread->get_page_num()){
        this->_thread->clear_load_queue();

        page_to(npage);
        this->_current_page_y = ny;
    }

}


void sci_pdf_canvas::set_x_value(int x){
    this->_current_page_x = x;
}

void sci_pdf_canvas::change_x_value(int x){
    int nx = this->_current_page_x + x;

    if(_canvas_width>=_page_width+2*_handle_width){
        return;
    }

    if(nx<0){
        set_x_value(0);
    }
    if(nx+_page_width+_handle_width<_canvas_width){
        nx = _canvas_width-_page_width-_handle_width;
    }
    else if(nx>_handle_width){
        nx = _handle_width;
    }
    qDebug()<<"nx"<<nx;
    set_x_value(nx);
}

void sci_pdf_canvas::paint(){
    this->repaint();
}
