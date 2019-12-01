#ifndef MAINMENU_HH
#define MAINMENU_HH

#include <QDialog>

namespace Ui {
    class MainMenu;
}

/**
 * @brief The MainMenu class represents the menu dialog.
 */
class MainMenu : public QDialog {

    Q_OBJECT

public:

    /**
     * @brief Class constructor
     */
    explicit MainMenu(QWidget *parent = nullptr);

    /**
     * @brief Default destructor
     */
    ~MainMenu();

signals:

    /**
     * @brief Signal to MapWindow
     * @param Player name
     * @param Player number (not used yet)
     */
    void playerNameChanged(const QString &name, const int &number);

    /**
     * @brief Signal to MapWindow
     * @param Mapsize x
     * @param Mapsize y
     */
    void mapSizeChanged(const int &mapSizeX, const int &mapSizeY);

public slots:

    /**
     * @brief Calls playerNameChanged when text input detected
     */
    void on_player1NameEdit_textEdited(const QString &name);

    /**
     * @brief Calls playerNameChanged when text input detected
     */
    void on_player2NameEdit_textEdited(const QString &name);

private slots:

    /**
     * @brief Calls mapSizeChanged when input detected
     */
    void on_mapSizeComboBox_currentIndexChanged(int index);

private:

    Ui::MainMenu *ui;

};

#endif // MAINMENU_HH
