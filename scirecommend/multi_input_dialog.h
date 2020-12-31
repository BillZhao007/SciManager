#ifndef MULTI_INPUT_DIALOG_H
#define MULTI_INPUT_DIALOG_H

#include <QtGui>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QStringList>
#include <QBoxLayout>

class MultiInputDialog : public QDialog
{
    Q_OBJECT
private:
    const int m_GroupCount;
    QLabel **m_Labels;
    QPushButton *m_OKButton;
    QPushButton *m_CancelButton;

public:
    bool MultiInputDialogFinish;
    QStringList MultiInputDialogReturn;

    QLineEdit **m_LineEdits;
    MultiInputDialog(int count, bool num=false, QWidget *parent = 0);
    virtual ~MultiInputDialog();
    void SetLabelTexts(const QStringList &listText);
    void SetOneLabelText(int index, const QString &text);
    QString GetOneText(int index);
    QStringList GetAllTexts();
    void SetLabelsWidth(int width);
    void SetLineEditRegExp(int index, QRegExp regExp);

    virtual void accept() { QDialog::accept(); }
    virtual void reject() { QDialog::reject(); }
};

#endif // MULTI_INPUT_DIALOG_H
