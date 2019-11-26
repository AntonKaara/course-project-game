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

    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects);

    Course::ResourceMap getResources();
    Course::ResourceMapDouble getResourcesDouble();
    void setResources(Course::ResourceMap map);
    void setResources(Course::ResourceMapDouble map);
    double getMoney();
    double getFood();
    double getWood();
    double getStone();
    double getOre();

private:

    Course::ResourceMapDouble resourceAmounts_ = {};

};

} // namespace Aeta
#endif // PLAYER_HH
