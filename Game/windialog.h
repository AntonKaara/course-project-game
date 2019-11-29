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

private slots:
    void on_quitButton_clicked();

    void on_menuButton_clicked();

private:
    Ui::WinDialog *ui;
};

#endif // WINDIALOG_H
