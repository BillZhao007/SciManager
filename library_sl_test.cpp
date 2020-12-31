#include "library_sl_test.h"

#include "scicore/sci_library.h"
#include "scicore/sci_folder.h"
#include "scisl/sci_sl_file.h"

#include <QString>
/*
void new_library_window_test::case1_add_folder(){
    scicore::sci_library* lib = new scicore::sci_library();

    scicore::sci_file* fd = new scicore::sci_folder("root");

    lib->set_root(fd);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int a = qrand()%9;
    QFETCH(int,fileCount);
    for(int i = 0; i< fileCount; i++){
        fd->add_file(new scicore::sci_folder((QString("fd")+i).toStdString(),NULL));
        int choice = fd->child_count()+2;

        int choose = qrand()%choice;
        if(choose == choice-1){
            if(fd->get_parent()){
                fd = fd->get_parent();
            }
        }
        else if(choose == choice-2){

        }
        else {
            fd = fd->get_child(choose);
        }
    }

    QCOMPARE(fileCount+1,lib->total_file(lib->get_root()));
    lib->get_root()->delete_self();
}

void new_library_window_test::case1_add_folder_data(){
    QTest::addColumn<int>("fileCount");
    //QTest::newRow("little")<<100;
    //QTest::newRow("medium")<<1000;
    //QTest::newRow("large")<<10000;
    //QTest::newRow("very large")<<100000;
    QTest::newRow("million")<<140000;
}
//void new_library_window_test::case2_add_and_remove_folder();
//void new_library_window_test::case3_abitrary_expand_10000();
void new_library_window_test::case2_remove_folder(){
    scicore::sci_library* lib = new scicore::sci_library();

    scicore::sci_file* fd = new scicore::sci_folder("root");

    lib->set_root(fd);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int a = qrand()%9;
    QFETCH(int,fileCount);
    for(int i = 0; i< fileCount; i++){
        fd->add_file(new scicore::sci_folder((QString("fd")+i).toStdString(),NULL));
        int choice = fd->child_count()+2;

        int choose = qrand()%choice;
        if(choose == choice-1){
            if(fd->get_parent()){
                fd = fd->get_parent();
            }
        }
        else if(choose == choice-2){

        }
        else {
            fd = fd->get_child(choose);
        }
    }

    QCOMPARE(fileCount+1,lib->total_file(lib->get_root()));

    QFETCH(int,movetime);

    int count = fileCount+1;

    for(int i = 0; i<movetime; i++){
        int choice = fd->child_count()+1;

        int choose = qrand()%choice;
        if(choose == choice - 1){
            if(fd->get_parent()){
                fd = fd->get_parent();
            }
        }
        else{
            if(qrand()%2==0)
                fd = fd->get_child(choose);
            else{
                count-=lib->total_file(fd->get_child(choose));
                fd->delete_file(choose);
            }
        }
    }

    QCOMPARE(count,lib->total_file(lib->get_root()));
    lib->get_root()->delete_self();
}

void new_library_window_test::case2_remove_folder_data(){
    QTest::addColumn<int>("fileCount");QTest::addColumn<int>("movetime");
    QTest::newRow("little")<<100<<30;
    QTest::newRow("medium")<<1000<<300;
    QTest::newRow("large")<<10000<<1000;
    QTest::newRow("very large")<<100000<<5000;
    QTest::newRow("million")<<140000<<10000;
}

void new_library_window_test::random_act(scicore::sci_library* lib,int step){
    //scicore::sci_file* fd = new scicore::sci_folder("root");
    int count=1;
    //lib->set_root(fd);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    scicore::sci_file* fd = lib->get_root();
    for(int i = 0; i< step; i++){
        fd->add_file(new scicore::sci_folder((QString("fd")+i).toStdString(),NULL));
        int choice = fd->child_count()*3+2;

        int choose = qrand()%choice;

        if(choose == choice - 1){//前往父节点
            if(fd->get_parent()){
                fd = fd->get_parent();
            }
        }
        else if(choose == choice - 2){
            //什么也不做
        }
        else {
            if(choose==-1){
                //qDebug()<<count<<endl;
                count-=lib->total_file(fd->get_child(choose/3));
                fd->delete_file(choose/3);
                //前往子节点
            }
            else if(choose%3==1){
                fd->insert_file(new scicore::sci_folder((QString("fd")+i).toStdString()),choose/3);
                count++;
            }
            else{
                fd = fd->get_child(choose/3);
            }
        }
    }

    QCOMPARE(count+step,lib->total_file(lib->get_root()));

    //return count;
}


void new_library_window_test::case3_serial_random_act(){
    QFETCH(int,step1);QFETCH(int,step2);QFETCH(int,step3);QFETCH(int,step4);
    scicore::sci_library* lib = new scicore::sci_library;
    lib->set_root(new scicore::sci_folder);
    random_act(lib,step1);
    lib->get_root()->delete_self();
    lib->set_root(new scicore::sci_folder);
    random_act(lib,step2);
    lib->get_root()->delete_self();
    lib->set_root(new scicore::sci_folder);
    random_act(lib,step3);
    lib->get_root()->delete_self();
    lib->set_root(new scicore::sci_folder);
    random_act(lib,step4);
    lib->get_root()->delete_self();
}

void new_library_window_test::case3_serial_random_act_data(){
    QTest::addColumn<int>("step1");QTest::addColumn<int>("step2");QTest::addColumn<int>("step3");
    QTest::addColumn<int>("step4");
    QTest::newRow("little")<<100<<300<<500<<700;
    QTest::newRow("medium")<<1000<<3000<<2000<<6000;
    QTest::newRow("large")<<10000<<1000<<10000<<1;
    QTest::newRow("very large")<<100000<<5000<<50000<<30000;
    QTest::newRow("million")<<140000<<100000<<10000<<20000;
}

void new_library_window_test::case4_save_load(){

    QFETCH(int,step1);QFETCH(int,step2);

    scicore::sci_library* lib = new scicore::sci_library;
    lib->set_root(new scicore::sci_folder);
    random_act(lib,step1);

    sci_sl_file file;


    qDebug()<<lib->total_file(lib->get_root());
    file.save(lib->get_root(),"Auto.sclb");
    scicore::sci_file* fd = file.load("Auto.sclb");
    //qDebug()<<lib->total_file(lib->get_root());
    scicore::sci_file* fd2 = lib->get_root();
    qDebug()<<lib->total_file(lib->get_root());
    for(int i = 0; i<step2; i++){
        int choice = fd->child_count()+1;

        int choose = qrand()%choice;
        if(choose == choice - 1){
            if(fd->get_parent()){
                fd = fd->get_parent();
                fd2 = fd2->get_parent();
            }
        }
        else{
            if(qrand()%2==0){
                fd = fd->get_child(choose);
                fd2 = fd2->get_child(choose);
            }
            else{

            }
        }

        QCOMPARE(fd->get_name(),fd2->get_name());
    }
    fd->delete_self();
    fd2->delete_self();
}

void new_library_window_test::case4_save_load_data(){
    QTest::addColumn<int>("step1");QTest::addColumn<int>("step2");
    QTest::newRow("little")<<100<<300;
    QTest::newRow("medium")<<1000<<3000;
    QTest::newRow("large")<<10000<<1000;
    QTest::newRow("very large")<<100000<<5000;
    QTest::newRow("million")<<140000<<100000;
}
*/
