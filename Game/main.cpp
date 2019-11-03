#include "mapwindow.hh"
#include "mainmenu.hh"

#include <QApplication>


int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    MapWindow mapWindow;
    MainMenu mainMenu;

    if (mainMenu.exec() == QDialog::Accepted) {
        mainMenu.close();
        mapWindow.show();
    } else {
        app.quit();
    }

    return app.exec();

}
