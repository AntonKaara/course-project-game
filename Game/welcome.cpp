#include "welcome.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
    ui->acceptButton->setStyleSheet("background-color:darkGreen;" "color:white");
}

Welcome::~Welcome() {

    delete ui;

}
