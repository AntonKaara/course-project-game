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

public slots:

    /**
     * @brief setText Adds a story/help text to the welcome dialog
     * window's textbrowser.
     * @param player1Name User specified player name to use in the story.
     * @param player2Name User specified player name to use in the story.
     */
    void setText(const QString &player1Name,
                 const QString &player2Name);

private:

    Ui::Welcome *ui;

};

#endif // WELCOME_H
