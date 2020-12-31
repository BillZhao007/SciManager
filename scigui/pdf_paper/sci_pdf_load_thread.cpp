#include "sci_pdf_load_thread.h"

sci_pdf_load_thread::sci_pdf_load_thread(QString path, int cache_size,QObject *parent):QThread(parent){
    _util = new sci_pdf_utils();
    _locker = new QMutex();

    _cache_size = cache_size;

    load_pdf(path);
}

sci_pdf_load_thread::~sci_pdf_load_thread(){
    delete _locker;
    delete _util;
}


void sci_pdf_load_thread::load_pdf(QString path){

    _locker->lock();

    _cached_page_map.clear();
    _cached_page.clear();

    _load_queue.clear();

    _util->load(path);

    _locker->unlock();
}

int sci_pdf_load_thread::get_page_num(){
    return _util->get_num_pages();
}

QSize sci_pdf_load_thread::get_page_size(){
    return _util->get_page_size();
}

void sci_pdf_load_thread::run(){
    while(1){
        _locker->lock();

        if(!_load_queue.isEmpty()){
            int page = _load_queue.front();
            _load_queue.pop_front();
            _locker->unlock();

            add_to_cache(page);
        }
        else{
            _locker->unlock();
        }


    }

}


void sci_pdf_load_thread::clear_load_queue(){
    _locker->lock();
    _load_queue.clear();
    _locker->unlock();
}

void sci_pdf_load_thread::load_page(int page){
    _locker->lock();
    _load_queue.push_back(page);
    _locker->unlock();
}

bool sci_pdf_load_thread::page_loaded(int page){
    return _cached_page_map.contains(page);
}

QImage* sci_pdf_load_thread::get_page(int page){
    _locker->lock();
    QImage* ptr = NULL;
    if(page_loaded(page)){
        ptr = &_cached_page_map[page];
    }
    _locker->unlock();
    return ptr;
}

void sci_pdf_load_thread::set_cache_size(int size){
    _cache_size = size;
}

void sci_pdf_load_thread::add_to_cache(int page){
    _locker->lock();
    if(_cached_page_map.contains(page)){
        _locker->unlock();
        return;
    }
    _locker->unlock();

    _cached_page_map[page] = _util->get_pdf_image(page);//其实这里可以设置精度

    _cached_page.push_back(page);

    if(_cached_page.size()>_cache_size){
        _locker->lock();
        int outpage = _cached_page.front();
        _cached_page.pop_front();
        _cached_page_map.remove(outpage);
        _locker->unlock();
    }
    qDebug()<<"add page "<<page<<" to cache";
    emit load_new_image();
}
