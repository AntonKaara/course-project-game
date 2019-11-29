#ifndef WELCOME_H
#define WELCOME_H

#include <QDialog>

namespace Ui {
class Welcome;
}

/**
 * @brief Welcome class represents the pop up welcome dialog
 */
class Welcome : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the class.
     */
    explicit Welcome(QWidget *parent = nullptr);

    /**
     * @brief Class destructor
     **/
    ~Welcome();

private:
    Ui::Welcome *ui;
};

#endif // WELCOME_H
