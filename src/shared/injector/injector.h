#ifndef INJECTOR_H
#define INJECTOR_H

#include <functional>
#include <map>
#include "injectable.h"
#include "builder.h"

class Injector
{
private:
  std::map<const char *, Injectable *> instances = {};
  std::map<const char *, Builder<Injectable *> *> builders = {};

public:
  Injector(){};

  template <typename T>
  T *injectSingleton()
  {
    const char *type = typeid(T).name();
    Injectable *instance = instances[type];

    if (instance)
    {
      return static_cast<T *>(instance);
    }

    T *newInstance = this->injectNew<T>();
    instances[type] = newInstance;

    return newInstance;
  }

  template <typename T>
  T *injectNew()
  {
    Builder<Injectable *> *fabricator = this->builders[typeid(T).name()];
    T *instance = static_cast<T *>(fabricator->build());
    return instance;
  }

  template <typename T, typename std::enable_if<std::is_base_of<Injectable, T>::value>::type * = nullptr>
  void setBuilder(std::function<T *(void)> fabFn)
  {
    this->builders[typeid(T).name()] = new Builder<Injectable *>(fabFn);
  }
};

#endif