#ifndef CHILDREN_H
#define CHILDREN_H

#include <list>
#include <memory>
#include <iostream>

#include "../component.h"
#include "../accessor/accessor.h"

namespace game
{
  template <class T>
  class Child
  {
  public:
    Child(std::string type, std::shared_ptr<T> ptr)
    {
      this->type = type;
      this->ptr = ptr;
    }

    ~Child()
    {
    }

    std::string type;
    std::shared_ptr<T> ptr;
  };

  template <class T>
  class Children
  {
  private:
    std::list<std::shared_ptr<Child<T>>> children = {};

  public:
    Children(){};
    ~Children()
    {
      children.clear();
    };

    template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr, class... Args>
    Accessor<R> attach(Args... args)
    {
      std::string typeName = typeid(R).name();
      std::shared_ptr<R> rawComponent = std::make_shared<R>(args...);
      std::shared_ptr<T> castedComponent = std::static_pointer_cast<T>(rawComponent);
      std::shared_ptr<Child<T>> child = std::make_shared<Child<T>>(typeName, castedComponent);

      this->children.push_back(child);

      return Accessor<R>(rawComponent);
    }

    template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr>
    Accessor<R> attach(std::shared_ptr<R> instance)
    {
      std::string typeName = typeid(R).name();
      std::shared_ptr<T> castedComponent = std::static_pointer_cast<T>(instance);
      std::shared_ptr<Child<T>> child = std::make_shared<Child<T>>(typeName, castedComponent);

      this->children.push_back(child);

      return Accessor<R>(instance);
    }

    template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr>
    void destroy(Accessor<R> accessor)
    {
      try
      {
        std::shared_ptr<T> castedComponent = std::static_pointer_cast<T>(accessor.toSharedPointer());

        for (auto it = children.begin(); it != children.end(); ++it)
        {
          Child<T> *child = (*it).get();
          if (child->ptr == castedComponent)
          {
            children.remove((*it));
            return;
          }
        }
      }
      catch (game::ComponentAccessException e)
      {
        std::cout << "Can't destroy accessor - " << e.toString() << " as it's not exists." << std::endl;
      }
    }

    template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr>
    Accessor<R> findFirst()
    {
      std::string type = typeid(R).name();

      for (auto it = children.begin(); it != children.end(); ++it)
      {
        Child<T> *child = (*it).get();
        if (child->type == type)
        {
          return Accessor<R>(std::static_pointer_cast<R>(child->ptr));
        }
      }

      return Accessor<R>();
    }

    template <class R, typename std::enable_if<std::is_base_of<T, R>::value>::type * = nullptr>
    std::list<Accessor<R>> findAll()
    {
      std::list<Accessor<R>> childrenOfR = {};
      std::string type = typeid(R).name();

      for (auto it = children.begin(); it != children.end(); ++it)
      {
        Child<T> *child = (*it).get();
        if (child->type == type)
        {
          childrenOfR.push_back(Accessor<R>(std::static_pointer_cast<R>(child->ptr)));
        }
      }

      return childrenOfR;
    }
  };
};

#endif