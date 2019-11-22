#include "windialog.h"
#include "ui_windialog.h"

#include <QProcess>

WinDialog::WinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinDialog) {

    ui->setupUi(this);

}

WinDialog::~WinDialog() {

    delete ui;

}



void WinDialog::on_quitButton_clicked() {

    qApp->quit();

}

void WinDialog::on_menuButton_clicked() {

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}
