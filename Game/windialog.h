#ifndef WINDIALOG_H
#define WINDIALOG_H

#include <QDialog>

namespace Ui {
class WinDialog;
}

/**
 * @brief WinDialog class represents the victory dialog at the end
 */
class WinDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Class constructor
     */
    explicit WinDialog(QWidget *parent = nullptr);

    /**
     * @brief Class destructor
     */
    ~WinDialog();

public slots:

    void setHighScore(int turn,
                          QString winPlayer,
                          QString losePlayer,
                          QString player1Name,
                          QString player2Name,
                          int p1Tiles,
                          int p2Tiles,
                          int p1Buildings,
                          int p2Buildings,
                          int p1ArmySize,
                          int p2ArmySize);

private slots:

    void on_quitButton_clicked();
    void on_menuButton_clicked();

private:
    Ui::WinDialog *ui;

};

#endif // WINDIALOG_H
