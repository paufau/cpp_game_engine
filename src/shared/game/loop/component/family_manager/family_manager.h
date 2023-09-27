#ifndef FAMILY_MANAGER
#define FAMILY_MANAGER

#include "../children/children.h"

#include <memory>
#include <string>
#include <iostream>

namespace game
{
  class AssignParentToItself : public std::exception
  {
  private:
    const char *componentTypeName;

  public:
    AssignParentToItself(const char *componentTypeName)
        : componentTypeName(componentTypeName){};

    std::string toString()
    {
      return std::string("Attempt to assign parent to itself: ") + std::string(this->componentTypeName);
    }
  };

  template <class T>
  class FamilyManager
  {
  private:
    FamilyManager<T> *parent_manager = nullptr;
    Children<T> children = Children<T>();

    FamilyManager<T> *findChildrenHolder()
    {
      // Connect to current manager
      if (isChildrenHolder)
      {
        return this;
      }

      // Find parent to connect to
      if (parent_manager != nullptr)
      {
        return parent_manager->findChildrenHolder();
      }

      // Has no parent, so should become global children holder
      isChildrenHolder = true;
      return this;
    }

  public:
    bool isChildrenHolder = true;

    T *getParent()
    {
      if (parent_manager == nullptr)
      {
        return nullptr;
      }

      return static_cast<T *>(parent_manager);
    }

    void checkNotToBeItself(FamilyManager *family_manager)
    {
      if (family_manager == this)
      {
        throw game::AssignParentToItself(typeid(T).name());
      }
    }

    void bindParent(T *parent_component)
    {
      FamilyManager *maybe_family_manager = dynamic_cast<FamilyManager *>(parent_component);
      checkNotToBeItself(maybe_family_manager);

      if (maybe_family_manager)
      {
        parent_manager = maybe_family_manager;
      }
    }

    void bindParent(FamilyManager *family_manager)
    {
      checkNotToBeItself(family_manager);

      parent_manager = family_manager;
    }

    template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr, class... Args>
    Accessor<R> attach(Args... args)
    {
      // Searching for component in current
      FamilyManager *current_holder = findChildrenHolder();
      Accessor<R> maybe_r = current_holder->children.template findFirst<R>();

      if (maybe_r.exists())
      {
        // Existing component was found
        return maybe_r;
      }

      // Component wasn't found, creating new one
      std::shared_ptr<R> instance = std::make_shared<R>(args...);
      FamilyManager *maybe_family_manager = dynamic_cast<FamilyManager *>(instance.get());

      if (maybe_family_manager)
      {
        // Binding parent
        maybe_family_manager->bindParent(this);
      }

      return current_holder->children.template attach(instance);
    }

    template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr>
    void destroy(Accessor<R> accessor)
    {
      FamilyManager<T> *holder = findChildrenHolder();

      holder->children.template destroy<R>(accessor);
    }

    template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr>
    Accessor<R> findFirst()
    {
      FamilyManager<T> *holder = findChildrenHolder();

      return holder->children.template findFirst<R>();
    }

    // template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr>
    // std::list<Accessor<R>> findAll()
    // {
    //   std::list<Accessor<R>> childrenOfR = {};
    //   std::string type = typeid(R).name();

    //   for (auto it = children.begin(); it != children.end(); ++it)
    //   {
    //     Child<T> *child = (*it).get();
    //     if (child->type == type)
    //     {
    //       childrenOfR.push_back(Accessor<R>(std::static_pointer_cast<R>(child->ptr)));
    //     }
    //   }

    //   return childrenOfR;
    // }
  };
};

#endif