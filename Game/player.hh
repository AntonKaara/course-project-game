#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/gameobject.h"
#include "core/basicresources.h"

#include <vector>
#include <memory>
#include <string>

namespace Aeta {

class Player : public Course::PlayerBase {

public:

    /**
     * @brief Player Constructor for the Player class.
     * @param name Specifies the constructed player object's name.
     * @param objects A vector of player's owned GameObjects.
     */
    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects);

    /**
     * @brief getResources Returns player's resource amounts
     * @return Map containing player's resource amount values as integer-type
     */
    Course::ResourceMap getResources();

    /**
     * @brief getResourcesDouble Returns player's resource amounts
     * @return Map containing player's resource amount values as double-type
     */
    Course::ResourceMapDouble getResourcesDouble();

    /**
     * @brief setResources Sets player's resources to match the map given as
     * a parameter.
     * @param map Map to change the player's resource amounts to.
     */
    void setResources(Course::ResourceMap map);

    /**
     * @brief setResources Sets player's resources to match the map given as
     * a parameter.
     * @param map Map to change the player's resource amounts to.
     */
    void setResources(Course::ResourceMapDouble map);

    /**
     * @brief getMoney A helper method to access the player's money amount.
     * @return The amount of money the player has.
     */
    double getMoney();

    /**
     * @brief getFood A helper method to access the player's food amount.
     * @return The amount of food the player has.
     */
    double getFood();

    /**
     * @brief getWood A helper method to access the player's wood amount.
     * @return The amount of wood the player has.
     */
    double getWood();

    /**
     * @brief getStone A helper method to access the player's stone amount.
     * @return The amount of stone the player has.
     */
    double getStone();

    /**
     * @brief getOre A helper method to access the player's ore amount.
     * @return The amount of ore the player has.
     */
    double getOre();

private:

    Course::ResourceMapDouble resourceAmounts_ = {};

};

} // namespace Aeta

#endif // PLAYER_HH
