#include <QDialog>

#ifndef MAINMENU_HH
#define MAINMENU_HH

namespace Ui {

class MainMenu;

}

class MainMenu : public QDialog {

    Q_OBJECT

public:

    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

signals:
    void playerNameChanged(const QString &name, const int &number);
    void mapSizeChanged(const int &mapSizeX, const int &mapSizeY);

public slots:
    void on_player1NameEdit_textEdited(const QString &arg1);
    void on_player2NameEdit_textEdited(const QString &arg1);

private slots:
    void on_mapSizeComboBox_currentIndexChanged(int index);

private:

    Ui::MainMenu *ui;

};

#endif // MAINMENU_HH
