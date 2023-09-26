#ifndef BUILDER_H
#define BUILDER_H

#include <functional>

template <typename T>
class Builder
{
public:
  std::function<T(void)> fab;

  Builder(std::function<T(void)> fab)
  {
    this->fab = fab;
  }

  T build()
  {
    return this->fab();
  }
};

#endif