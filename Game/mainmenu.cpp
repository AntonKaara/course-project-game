#include "mainmenu.hh"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu) {

    // Construct the UI and its style
    ui->setupUi(this);

    //this->setStyleSheet("");
    ui->playButton->setStyleSheet("background-color:green;" "color:white");

    //Tooltips
    ui->mapSizeComboBox->setToolTip("Cool tooltip"); 

}

MainMenu::~MainMenu() {

    delete ui;

}

void MainMenu::on_player1NameEdit_textEdited(const QString &name) {
    emit playerNameChanged(name, 1);
}

void MainMenu::on_player2NameEdit_textEdited(const QString &name) {
    emit playerNameChanged(name, 2);
}
