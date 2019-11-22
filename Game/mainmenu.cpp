#include "mainmenu.hh"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu) {

    // Construct the UI and its style
    ui->setupUi(this);

    //this->setStyleSheet("background-color:black;");
    ui->playButton->setStyleSheet("background-color:green;" "color:white");
    //ui->loadButton->setStyleSheet("background-color:white;" "color:white");
    //ui->quitButton->setStyleSheet("background-color:darkRed;" "color:white");

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

void MainMenu::on_mapSizeComboBox_currentIndexChanged(int index) {

    if (index == 0) {
        emit mapSizeChanged(10, 10);
    } else if ( index == 1) {
        emit mapSizeChanged(20, 20);
    } else if ( index == 2) {
        emit mapSizeChanged(40, 40);
    } else if ( index == 3) {
        emit mapSizeChanged(60, 60);
    }

}
