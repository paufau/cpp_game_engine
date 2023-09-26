#ifndef ACCESSOR_H
#define ACCESSOR_H

#include <memory>
#include <string>

namespace game
{
  class ComponentAccessException : public std::exception
  {
  private:
    const char *componentTypeName;

  public:
    ComponentAccessException(const char *componentTypeName)
        : componentTypeName(componentTypeName){};

    std::string toString()
    {
      return std::string("Unable to access component: ") + std::string(this->componentTypeName);
    }
  };

  template <class T>
  class Accessor
  {
  private:
    bool is_initialized = false;

  public:
    std::weak_ptr<T> ptr;
    Accessor(){};
    Accessor(std::shared_ptr<T> _ptr)
    {
      is_initialized = true;
      ptr = _ptr;
    };

    std::shared_ptr<T> toSharedPointer()
    {
      if (std::shared_ptr<T> instance_ptr = ptr.lock())
      {
        return instance_ptr;
      }

      throw ComponentAccessException(typeid(T).name());
    }

    T *get()
    {
      return toSharedPointer().get();
    };

    bool exists()
    {
      return is_initialized && !ptr.expired();
    }
  };
};

#endif