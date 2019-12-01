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

/**
 * @brief The MapWindow class is the main window in the application
 */
class MapWindow : public QMainWindow {

    Q_OBJECT

public:

    /**
     * @brief Class constructor
     */
    explicit MapWindow(QWidget *parent = nullptr);

    /**
     * @brief Class destructor
     */
    ~MapWindow() override;

    // Scene

    /**
     * @brief Set the scene size to mapsize
     * @param x-size
     * @param y-size
     */
    void setSize(int width, int height);

    /**
     * @brief Set tilesize in px in scene
     * @param size in px
     */
    void setScale(int scale);

    /**
     * @brief Draw map object as MapItem in scene
     * @param Tile object
     */
    void drawTile(std::shared_ptr<Course::TileBase> obj);

    /**
     * @brief Remove tile from scene
     * @param Tile object
     */
    void removeItem(std::shared_ptr<Course::GameObject> obj);

    // Map generation

    /**
     * @brief Helper function for adding picture filepaths to map structure
     */
    void addPixmaps();

    /**
     * @brief Passes class constructors to Course::WorldGenerator to generate the tiles
     */
    void generateMap();

    /**
     * @brief Builds the map taking the tile objects from objectManager
     */
    void drawMap();

    /**
     * @brief Adds player 1 starting buildings and units
     */
    void initializePlayer1();

    /**
     * @brief Adds player 2 starting buildings and units
     */
    void initializePlayer2();

    // Map view

    /**
     * @brief Focuses the camera above player_in_turn HQ
     */
    void centerViewtoHQ();

    // Buildings

    /**
     * @brief Creates building object and adds to the tile object
     */
    void buildOnTile();

    /**
     * @brief Removes given building
     * @param selected building object
     * @param tile where building is located
     */
    void demolishBuilding(std::shared_ptr<Course::BuildingBase> building,
                          std::shared_ptr<Course::TileBase> tile);

    // Units

    /**
     * @brief Creates unit object and adds to recruiter HQ
     */
    void recruitUnit();

    /**
     * @brief Determines tiles where the selected unit can move to
     */
    void onMoveModeActivate();

    /**
     * @brief Draws blue indicator rectangles to tiles the selected unit can move to
     */
    void drawMovementMarkers(std::vector<std::shared_ptr<Course::TileBase>> tiles);

    /**
     * @brief Draws red indicator rectangles to tiles the selected unit can move to
     */
    void drawAttackMarkers(std::vector<std::shared_ptr<Course::TileBase>> tiles);

    /**
     * @brief Move/Attack handling - Move unit from to given tile and attack if enemy unit on that tile
     */
    bool moveUnit(const std::shared_ptr<Course::TileBase> &tile);

    /**
     * @brief Attack handling for HQ separately
     */
    bool attackHQ(const std::shared_ptr<Course::TileBase> &tile,
                  const std::shared_ptr<UnitBase> &attacker);

    /**
     * @brief Produces wood resource when walking over forest
     */
    void cutForest(const std::shared_ptr<Course::TileBase> &tile);

    // Other mechanics

    /**
     * @brief Executed at the end of the turn, change turns, add resources..
     */
    void endTurn();

    /**
     * @brief Called from endTurn, adds resources
     */
    void addProduction();

    /**
     * @brief Update UI elements to match to new data
     */
    void updateUI();

    /**
     * @brief Does production calculation and updates resource labels
     *
     * @note Can be called separately from UpdateUI, recaulculating on every click is unnecessary
     */
    void updateResourceLabels();

    /**
     * @brief Executed when HQ destroyed, ends the game, sends high scores
     */
    void gameOver();

    /**
     * @brief Resource amount check to prevent resources from plummeting to negatives when buying
     * @param amount of resources required as ResourceMap
     * @param playerInTurn
     */
    bool checkIfEnoughResources(const Course::ResourceMap &resourcesRequired,
                                const std::shared_ptr<Player> &player);

    /**
     * @brief function to show different alerts
     */
    bool showMessageBox(QWidget *parent,
                        const QString &windowTitle,
                        const QString &windowMessage,
                        const bool &cancelButtonMode);

    /**
     * @brief Draws animation on attack/forest wood collect
     */
    void showTextAnimation(const QString &text,
                           const Course::Coordinate &startPosition,
                           const QColor &color);

    /**
     * @brief Compares current values to saved high scores
     */
    void updateHighScores();

    // Events

    /**
     * @brief Kidnaps events going to scene to make the movement system possible
     */
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

    /**
     * @brief Set player UI names inputted in main menu
     */
    void setPlayerName(const QString &name, const int &playerNumber);

    /**
     * @brief Set mapsize selected in main menu
     */
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

