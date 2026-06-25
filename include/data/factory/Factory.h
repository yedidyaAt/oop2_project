#pragma once

#include <map>
#include <functional>
#include <memory>

#include "Objects.h"
#include "ObjectDescriptor.h"
#include "GameObject.h"


namespace factory
{
  using Creator = std::function<std::unique_ptr<GameObject>(const ObjectDescriptor&)>;
  using CreatorRegistry = std::map<Objects, Creator>;

  bool registerCreator(Objects type,const Creator& func);

  std::unique_ptr<GameObject> create(const ObjectDescriptor& objD);
}
