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
  using CreatorRegistry = std::map<objects, Creator>;

  bool registerCreator(objects type,const Creator& func);

  std::unique_ptr<GameObject> create(const ObjectDescriptor& objD);
}
