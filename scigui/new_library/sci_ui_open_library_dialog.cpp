#include "sci_ui_open_library_dialog.h"
#include "ui_sci_ui_open_library_dialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include "../scisl/sci_sl_file.h"

namespace scigui {

sci_ui_open_library_dialog::sci_ui_open_library_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sci_ui_open_library_dialog)
{
    ui->setupUi(this);

    ui->textEdit_library_path->setText(QDir::currentPath());
}

sci_ui_open_library_dialog::~sci_ui_open_library_dialog()
{
    delete ui;
}

}


void scigui::sci_ui_open_library_dialog::on_pushButton_browse_clicked()
{
    QString path = QFileDialog::getExistingDirectory(NULL,"选择路径",".")+"/";
    if(path.isEmpty())
        return;
    _file_path = path;
    ui->textEdit_library_path->setText(_file_path+ui->textEdit_library_name->toPlainText()+".sclb");
}

void scigui::sci_ui_open_library_dialog::on_textEdit_library_name_textChanged()
{
    ui->textEdit_library_path->setText(_file_path+ui->textEdit_library_name->toPlainText()+".sclb");
}

void scigui::sci_ui_open_library_dialog::on_buttonBox_accepted()
{
    QDir dir(_file_path);
    if(!dir.exists()){
        QMessageBox::warning(NULL,"错误：路径不正确","错误：所选择路径无效");
        return;
    }
    if(ui->textEdit_library_name->toPlainText().isEmpty()){
        QMessageBox::warning(NULL,"错误：无效命名","错误：文件命名无效");
        return;
    }

    //sci_sl_file file;
    //scicore::sci_folder* root = new scicore::sci_folder("root");
    //file.save(root,(_file_path+ui->textEdit_library_name->toPlainText()+".sclb").toStdString());
}
