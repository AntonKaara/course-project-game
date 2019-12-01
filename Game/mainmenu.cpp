#include "mainmenu.hh"
#include "ui_mainmenu.h"
#include <QString>
#include <QPixmap>

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu) {

    // Construct the UI and its style
    ui->setupUi(this);
    ui->playButton->setStyleSheet("background-color:green;" "color:white");
    QString filePath = QString::fromStdString(":/pictures/pictures/Logo.png");
    QPixmap image(filePath);
    ui->gameNameLabel->setScaledContents(true);
    ui->gameNameLabel->setPixmap(image);


    //Tooltips
    ui->mapSizeComboBox->setToolTip("Select map size");

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
        emit mapSizeChanged(15, 15);
    } else if ( index == 2) {
        emit mapSizeChanged(20, 20);
    } else if ( index == 3) {
        emit mapSizeChanged(40, 40);
    }

}
