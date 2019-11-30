#include "windialog.h"
#include "ui_windialog.h"
#include "mapwindow.hh"

#include <QProcess>

WinDialog::WinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinDialog) {

    ui->setupUi(this);

    // Set window style

    this->setStyleSheet("background-color: black;" "color:white");
    ui->victoryLabel->setStyleSheet("color:white");
    ui->textBrowser->setStyleSheet("background-color: black;" "color:white");
    ui->menuButton->setStyleSheet("background-color: darkGreen;" "color:white");
    ui->quitButton->setStyleSheet("background-color: darkRed;" "color:white");

}

WinDialog::~WinDialog() {

    delete ui;

}

void WinDialog::setHighScore(int turn, QString winPlayer, QString losePlayer,
                             QString player1Name, QString player2Name,
                             int p1Tiles, int p2Tiles, int p1Buildings,
                             int p2Buildings, int p1ArmySize, int p2ArmySize) {

    QString highScoreText = "Congratulations " + winPlayer + "! \n \n"
            "It took " + QString::number(turn) + " turns for " + winPlayer + " to wipe out " + losePlayer +
            "! At its highest point, " + player1Name + " controlled a great number of " +
            QString::number(p1Tiles) + " tiles, " +
            player2Name + " on the other hand owned " + QString::number(p2Tiles) + " tiles at best. \n \n"

            "On those tiles, " + player1Name + " managed to maintain " + QString::number(p1Buildings) +
            " buildings at once, while " + player2Name + " managed " + QString::number(p2Buildings) + " buildings. \n \n" +

            player1Name + " was responsible for an army of " + QString::number(p1ArmySize) + " units. "
            + player2Name + "'s army was " + QString::number(p2ArmySize) + " units strong at best.";

    ui->textBrowser->setText(highScoreText);

}

void WinDialog::on_quitButton_clicked() {

    qApp->quit();

}

void WinDialog::on_menuButton_clicked() {

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}
