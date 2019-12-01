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
    ~WinDialog() override;

public slots:

    /**
     * @brief setHighScore Adds the text and statistics to the victory
     * dialog window.
     * @param turn Turn amount in which the game has been won.
     * @param winPlayer Player who won.
     * @param losePlayer Player who lost.
     * @param player1Name User specified name for player 1.
     * @param player2Name User specified name for player 2.
     * @param p1Tiles Most tiles owned by player 1.
     * @param p2Tiles Most tiles owned by player 2.
     * @param p1Buildings Most buildings owned by player 1.
     * @param p2Buildings Most buildings owned by player 2.
     * @param p1ArmySize Most units owned by player 1.
     * @param p2ArmySize Most units owned by player 2.
     */
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

    /**
     * @brief on_quitButton_clicked quits the whole program.
     */
    void on_quitButton_clicked();

    /**
     * @brief on_menuButton_clicked starts the program again.
     */
    void on_menuButton_clicked();

    /**
     * @brief reject Overridden reject to close the whole program
     * when X-button is pressed.
     */
    void reject() override;

private:
    Ui::WinDialog *ui;

};

#endif // WINDIALOG_H
