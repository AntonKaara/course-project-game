#include "mainmenu.hh"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    // Construct the UI and its style
    ui->setupUi(this);
    //this->setStyleSheet("");
    ui->playButton->setStyleSheet("background-color:green;" "color:white");

    //Tooltips
    ui->mapSizeComboBox->setToolTip("Cool tooltip");
}

MainMenu::~MainMenu()
{
    delete ui;
}
