#ifndef MAINMENU_HH
#define MAINMENU_HH

#include <QDialog>

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_HH
