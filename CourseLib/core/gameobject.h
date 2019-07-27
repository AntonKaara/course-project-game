#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "coordinate.h"

namespace Course {

// Forward declarations
class PlayerBase;
class iObjectManager;
class iGameEventHandler;

// Some aliases to make things easier
using ObjectId = unsigned int;
using DescriptionMap = std::map<std::string, std::string>;

/**
 * @brief The GameObject class acts as a datastructure for different data
 * that can be stored in GameObjects and as a BaseClass for easier
 * resource-management.
 * @note The functions consist mainly of get and set -functions that don't do
 * any checking on wheter some actions are legal or not. This is supposed to be
 * handled by inherited classes.
 */
class GameObject
{
public:
    /**
     * @brief ID is a constant value that can be used to identify
     * GameObjects through ID numbers.
     */
    const ObjectId ID;

    /**
     * @brief GameObject copy-constructor
     * @param original GameObject
     */
    GameObject(const GameObject& original);

    /**
     * @brief GameObject constructor that requires optional map of descriptions.
     * @param descriptions A map of strings referring to strings
     */
    GameObject(const std::shared_ptr<iGameEventHandler>& eventhandler={nullptr},
               const std::shared_ptr<iObjectManager>& objectmanager={nullptr},
               const DescriptionMap& descriptions={});

    /**
     * @brief GameObject constructor that can create objects with owner
     * @param owner A weak-pointer to "owner" player
     * @param descriptions A map of strings referring to strings
     */
    GameObject(const std::shared_ptr<PlayerBase>& owner,
               const std::shared_ptr<iGameEventHandler>& eventhandler={nullptr},
               const std::shared_ptr<iObjectManager>& objectmanager={nullptr},
               const DescriptionMap& descriptions={});

    /**
     * @brief GameObject constructor that can create objects with
     * owner and coordinate
     * @param coordinate A Coordinate-Object that is being stored.
     * @param owner A weak-pointer to "owner" player
     * @param descriptions A map of strings referring to strings
     */
    GameObject(const Coordinate& coordinate,
               const std::shared_ptr<PlayerBase>& owner,
               const std::shared_ptr<iGameEventHandler>& eventhandler={nullptr},
               const std::shared_ptr<iObjectManager>& objectmanager={nullptr},
               const DescriptionMap& descriptions={});

    /**
     *
     *
     *
     */
    GameObject(const Coordinate& coordinate,
               const std::shared_ptr<iGameEventHandler>& eventhandler={nullptr},
               const std::shared_ptr<iObjectManager>& objectmanager={nullptr},
               const DescriptionMap& descriptions={});


    /**
     * @brief ~GameObject Default destructor.
     */
    virtual ~GameObject() = default;

    /**
     * @brief Change GameObject's "owner".
     * @param owner Weak-pointer to the new "owner".
     * @post Exception guarantee: No-throw
     */
    virtual void setOwner(const std::shared_ptr<PlayerBase>& owner) final;
    /**
     * @brief Change GameObject's coordinate with shared pointer to a
     * coordinate.
     * @param coordinate A shared-pointer to the new coordinate.
     * @post Exception guarantee: No-throw
     * @note This creates new Coordinate based on the coordinate
     * @note Can be used to unset coordinate with null-shared-pointer.
     */
    virtual void setCoordinate(
            const std::shared_ptr<Coordinate>& coordinate) final;

    /**
     * @brief Change GameObject's coordinate.
     * @param coordinate The new coordinate.
     * @post Exception guarantee: No-throw
     */
    virtual void setCoordinate(const Coordinate& coordinate) final;

    /**
     * @brief Removes the coordinate from GameObject.
     * @post Exception guarantee: No-throw
     */
    virtual void unsetCoordinate() final;

    /**
     * @brief Change GameObject's "descriptions"-map.
     * @param desciptions The new "descriptions"-map of strings referring
     * to strings
     * @post Exception guarantee: No-throw
     */
    virtual void setDescriptions(const DescriptionMap& descriptions) final;

    /**
     * @brief Adds a new description to description map.
     * @param key Key for the content
     * @param content Content being stored
     * @post Exception guarantee: Strong
     * @exception
     * KeyError - If the key is already in use in the description-map.
     */
    virtual void addDescription(const std::string& key,
                                const std::string& content) final;
    /**
     * @brief Sets a description for the specified key
     * @param key Key for the content
     * @param content Content being stored
     * @post Exception guarantee: Strong
     * @exceptions  See std::map::operator[]
     */
    virtual void setDescription(const std::string& key,
                                const std::string& content) final;
    /**
     * @brief Returns the content with specified key from the
     * descriptions.
     * @param key Key for the content
     * @post Exception guarantee: Strong
     * @exceptions KeyError - if the description for the key is not found.
     */
    virtual std::string getDescription(const std::string& key) const final;
    /**
     * @brief Removes the content with specified key from the
     * descriptions.
     * @param key Key for the content
     * @post Exception guarantee: Strong
     * @exceptions KeyError - if the description for the key is not found.
     */
    virtual void removeDescription(const std::string& key) final;

    /**
     * @brief Removes all content from descriptions.
     * @post Exception guarantee: No-throw
     */
    virtual void removeDescriptions() final;

    /**
     * @brief Returns GameObject's owner.
     * @return A shared-pointer to GameObject's owner
     * @post Exception guarantee: No-throw
     */
    virtual std::shared_ptr<PlayerBase> getOwner() const final;

    /**
     * @brief Returns a pointer to a copy of GameObject's coordinate.
     * @return Shared-pointer copy of the GameObject's coordinate,
     * if the GameObject has a coordinate.
     * Null-shared-pointer if the GameObject has no coordinate.
     * @post Exception guarantee: No-throw
     * @note To change GameObject's coordinate you must use setCoordinate.
     * This prevent unwanted alterations by accident.
     */
    virtual std::shared_ptr<Coordinate> getCoordinate() const final;

    /**
     * @brief Returns the map of descriptions in GameObject.
     * @return std::map of strings referring to strings.
     * @post Exception guarantee: No-throw
     */
    virtual std::map<std::string, std::string> getDescriptions() const final;

    /**
     * @brief getType Returns a string describing objects type.
     * This should be overriden in each inherited class.
     * Makes checking object's type easier for students.
     * @return std::string that represents Object's type.
     * @post Exception guarantee: No-throw
     */
    virtual std::string getType() const;

    /**
     * @brief Function to compare if objects have same owner.
     * * @param other The other GameObject
     * @return True - If owners match or both are null
     * False - If owners don't match
     * @post Excepetion guarantee: Strong
     * @exception ExpiredPointer - If any owner weak_ptr has expired.
     */
    virtual bool has_same_owner_as(
            const std::shared_ptr<GameObject>& other) const final;

    /**
     * @brief has_same_coordinate
     * @param other The other GameObject
     * @return True - If coordinates match or both are null
     * False - If the coordinates don't match
     * @post Exception guarantee: Strong
     */
    virtual bool has_same_coordinate_as(
            const std::shared_ptr<GameObject>& other) const final;

protected:

    virtual std::shared_ptr<iGameEventHandler> lockEventHandler() const final;
    virtual std::shared_ptr<iObjectManager> lockObjectManager() const final;

private:
    const std::weak_ptr<iGameEventHandler> EVENTHANDLER;
    const std::weak_ptr<iObjectManager> OBJECTMANAGER;

    std::weak_ptr<PlayerBase> m_owner;
    std::unique_ptr<Coordinate> m_coordinate;
    std::map<std::string, std::string> m_descriptions;

    static ObjectId c_next_id;
};

}
#endif // GAMEOBJECT_H
