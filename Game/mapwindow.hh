#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include "graphics/simplegamescene.h"
#include "core/coordinate.h"

#include "gamescene.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "player.hh"
#include "mainmenu.hh"
#include "windialog.h"
#include "welcome.h"
#include "headquarters.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QListWidget>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <map>
#include <QObject>

namespace Ui {

class MapWindow;

}

namespace Aeta {

class MapWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MapWindow(QWidget *parent = nullptr);
    ~MapWindow() override;

    // Scene

    void setSize(int width, int height);
    void setScale(int scale);
    void drawTile(std::shared_ptr<Course::TileBase> obj);
    void removeItem(std::shared_ptr<Course::GameObject> obj);

    // Map generation

    void addPixmaps();
    void generateMap();
    void drawMap();
    void initializePlayer1();
    void initializePlayer2();

    // Map view

    void centerViewtoHQ();

    // Buildings

    void buildOnTile();
    void demolishBuilding(std::shared_ptr<Course::BuildingBase> building,
                          std::shared_ptr<Course::TileBase> tile);

    // Units

    void recruitUnit();
    void onMoveModeActivate();
    void drawMovementMarkers(std::vector<std::shared_ptr<Course::TileBase>> tiles);
    void drawAttackMarkers(std::vector<std::shared_ptr<Course::TileBase>> tiles);
    bool moveUnit(const std::shared_ptr<Course::TileBase> &tile);
    bool attackHQ(const std::shared_ptr<Course::TileBase> &tile,
                  const std::shared_ptr<UnitBase> &attacker);
    void cutForest(const std::shared_ptr<Course::TileBase> &tile);

    // Other mechanics

    void endTurn();
    void addProduction();
    void updateUI();
    void updateResourceLabels();
    void gameOver();
    bool checkIfEnoughResources(const Course::ResourceMap &resourcesRequired,
                                const std::shared_ptr<Player> &player);
    bool showMessageBox(QWidget *parent,
                        const QString &windowTitle,
                        const QString &windowMessage,
                        const bool &cancelButtonMode);

    void showTextAnimation(const QString &text,
                           const Course::Coordinate &startPosition,
                           const QColor &color);

    void updateHighScores();

    // Events

    bool eventFilter(QObject *object, QEvent *event) override;

signals:

    /**
     * @brief Signal high scores to winDialog
     */
    void highScore(int turn,
                      QString winPlayer,
                      QString losePlayer,
                      QString player1Name,
                      QString player2Name,
                      int p1TileNumber,
                      int p2TileNumber,
                      int p1Buildings,
                      int p2Buildings,
                      int p1ArmySize,
                      int p2ArmySize);

    /**
     * @brief playerNames signal chosen names to welcome dialog
     */

    void playerNames(const QString &player1Name,
                     const QString &player2Name);

public slots:

    // Signals from main menu

    void setPlayerName(const QString &name, const int &playerNumber);
    void setMapSize(const int &sizeX, const int &sizeY);

private slots:

    // Buttons and other clickables

    void on_zoomInButton_clicked();
    void on_zoomOutButton_clicked();
    void on_endTurnButton_clicked();
    void on_unitTextBox_editingFinished();
    void on_moveButton_clicked();
    void on_buildPanelButton_clicked();
    void on_confirmBuildButton_clicked();
    void on_recruitButton_clicked();
    void on_confirmRecruitButton_clicked();
    void on_buildList_itemDoubleClicked(QListWidgetItem *item);
    void on_recruitList_doubleClicked(const QModelIndex &index);
    void on_buildList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_recruitList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:

    Ui::MapWindow* ui_;
    std::shared_ptr<GameScene> scene_ = nullptr;
    std::shared_ptr<GameEventHandler> gameEventHandler_ = nullptr;
    std::shared_ptr<ObjectManager> objectManager_ = nullptr;
    std::shared_ptr<MainMenu> mainMenu_ = nullptr;
    std::shared_ptr<WinDialog> winDialog_ = nullptr;
    std::shared_ptr<Welcome> welcomeDialog_ = nullptr;

    std::map<std::string, QPixmap> pixmaps_ = {};

    int mapsizeX_ = 10; // Tile count
    int mapsizeY_ = 10;
    int mapScale_ = 60; // Tile pixmap size in px
    int zoomLevel_ = 0; // Normal view = 0

    int turn_ = 1; // Turn for playerInTurn pointer
    int turnCount_ = 1; // Turn for UI
    bool moveMode_ = false;

    // Important GameObjects

    std::shared_ptr<Course::TileBase> selectedTile_ = nullptr;
    std::shared_ptr<UnitBase> selectedUnit_ = nullptr;
    std::shared_ptr<Headquarters> player1HQ_ = nullptr;
    std::shared_ptr<Headquarters> player2HQ_ = nullptr;
    std::vector<std::shared_ptr<Course::TileBase>> viableTilesForMove_ = {};
    std::vector<std::shared_ptr<Course::TileBase>> viableTilesForAttack_ = {};

    // Attributes for storing players' information

    std::shared_ptr<Player> playerInTurn_ = nullptr;
    QString player1UiName_ = "Player 1";
    QString player2UiName_ = "Player 2";

    std::vector<std::shared_ptr<Player>> players_ = {};
    std::vector<std::shared_ptr<Course::TileBase>> tilesToGiveBack_ = {};

    // High score info

    int player1TilesMax_ = 0;
    int player2TilesMax_ = 0;
    int player1BuildingsMax_ = 0;
    int player2BuildingsMax_ = 0;
    int player1ArmyMax_ = 0;
    int player2ArmyMax_ = 0;

};

} // namespace Aeta

#endif // MapWINDOW_HH

