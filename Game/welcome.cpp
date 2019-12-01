#include "welcome.h"
#include "ui_welcome.h"

#include <QTextCursor>
#include <QString>

Welcome::Welcome(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Welcome)
{
    ui->setupUi(this);
    ui->acceptButton->setStyleSheet("background-color:darkGreen;" "color:white");
    QString filePath = QString::fromStdString(":/pictures/pictures/Logo.png");
    QPixmap image(filePath);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(image);
}

Welcome::~Welcome() {

    delete ui;

}

void Welcome::setText(const QString &player1Name,
                      const QString &player2Name) {


   QString story =
           "Long, a very long time ago, during the Middle Ages two magnificent "
           "armies started to form up. The race to be the most glorious empire "
           "of the era started.\n\n"

           "The northerners, a clan named Frostfall, mustered a mighty horde of "
           "supporters as their to-be commander, Everard of the Snow, started "
           "to gain the trust of the northern people. The clan was soon "
           "described to be the savior of the Northeners. During the fierce "
           "winters in the North, people wanted something to believe to. \n\n"

           "With his talented speech skills Everard won the peoples trust by "
           "providing them with a vision of a peaceful, large and mighty "
           "empire providing food, shelter, riches and more favourable weather "
           "conditions.\n\n"

           "Soon enough, a very powerful army had emerged. Frostfall's leader, "
           "Everard, commanded the army on a mission to conquer the areas south "
           "in Pirkanmaa, a region described to be filled to the brim with much "
           "needed resources and land.\n\n"

           "Everard promoted " + player1Name + " to commanders position in "
           "the army. " + player1Name + " commanded the army to attack. "
           "Battlecry echoed in the air as the northern warriors charged "
           "towards Pirkanmaa..\n\n"

           "At the same time, in the South, King Cerill 'The Colossus', the "
           "ruler of the Kingdom of Essumos, was upon an inevitable fate of "
           "being dethroned. The southern people demanded acts from the King, "
           "as the kingdom was facing a major starvation due to the lack of "
           "fertile land.\n\n"

           "King Cerill was desperate. During his reign, a mysterious man "
           "named Iowerth had told tales about this land full of riches called "
           "Pirkanmaa.  Iowerth had unfortunately died a few years before the "
           "Great Starvation. Despite the fact that he didn't know if the "
           "land existed for sure, he had to act.\n\n"

           "King Cerill gathered his Royal Guard. He spoke to his people, and "
           "laid a spark of hope to the peoples' minds. The Great Starvation "
           "can be ended.  He reqruited every man capable to arms.\n\n"

           "The newly formed army was weak. King Cerill used all his power and "
           "resources to reinvigorate the soldiers. He managed to build the "
           "army up to a point where it was ready to save the kingdom from the "
           "inevitable doom.\n\n"

           "Cerill promoted " + player2Name + " as his army's commander. " +
           player2Name + " commanded his army to march north, to conquer the "
           "mysterious land of Pirkanmaa..\n\n";

           ui->textBrowser->append(story);
           ui->textBrowser->setFontWeight(QFont::Bold);
           ui->textBrowser->append("Conquest of Pirkanmaa\n\n");
           ui->textBrowser->setFontWeight(QFont::Normal);

           QString general =
           "You play as the commander of your army. The battle for the "
           "Pirkanmaa's riches has started. The survival of your people is "
           "in your hands! Lead your forces to victory by conquering areas "
           "and wiping out any rival forces who stand against your path!\n\n";

           ui->textBrowser->append(general);
           ui->textBrowser->setFontWeight(QFont::Bold);
           ui->textBrowser->append("Turn your village into a thriving "
                                   "empire!\n\n");
           ui->textBrowser->setFontWeight(QFont::Normal);


           QString buildings =
           "Conquer new territory by building outposts on the outskirts "
           "of your faction. Use the newly aqcuired region to your advantage "
           "and build buildings to produce more resources.\n\n";

           ui->textBrowser->append(buildings);
           ui->textBrowser->setFontWeight(QFont::Bold);
           ui->textBrowser->append("Recruit new units to make your empire "
                                   "stronger!\n\n");
           ui->textBrowser->setFontWeight(QFont::Normal);



           QString unitGeneral =
           "Respond to the ever changing landscape of the Pirkanmaa region "
           "and make sure you don't let your enemies become too strong! One "
           "needs money and food to sustain a large army.\n\n";

           ui->textBrowser->append(unitGeneral);
           ui->textBrowser->setFontWeight(QFont::Bold);
           ui->textBrowser->append("Engage in battle!\n\n");
           ui->textBrowser->setFontWeight(QFont::Normal);


           QString units =
           "Plan out your attack strategy and outsmart your enemy. Archers may "
           "prove useful due to their ranged attacks. Cavalry units are the "
           "fastest and make the most damage.\n\n";

           ui->textBrowser->append(units);
           ui->textBrowser->setFontWeight(QFont::Bold);

           QString winnerAndGl =
           "The ultimate winner is the first player to destroy the enemy "
           "headquarters.\n\n"
           "Good luck on your Conquest of Pirkanmaa!\n\n";

           ui->textBrowser->append(winnerAndGl);

           // lastly set the scrollbar back up after appending all the text

           QTextCursor cursor = ui->textBrowser->textCursor();
           cursor.setPosition(0);
           ui->textBrowser->setTextCursor(cursor);

}
