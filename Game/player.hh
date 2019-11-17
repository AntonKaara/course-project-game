#include "core/playerbase.h"
#include "core/basicresources.h"
#include "core/gameobject.h"

#include <vector>
#include <memory>
#include <string>

#ifndef PLAYER_HH
#define PLAYER_HH

namespace Aeta {

class Player : public Course::PlayerBase {

public:

    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects);
private:

    std::string name_ = "Unnamed player";
    Course::ResourceMapDouble resourceAmounts_ = {};
};

} // namespace Aeta
#endif // PLAYER_HH
