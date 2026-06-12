#include "Factory.h"


// to get familer whit the using have at .h
namespace factory
{
// static: internal linkage — private to this file, not part of the API
 static CreatorRegistry& getCreatorRegistry()
  {
    static CreatorRegistry map;

    return map;
  }

 bool registerCreator(Objects type,const Creator& func)
 {
   getCreatorRegistry()[type] = func;
 
   return true;
 }

 std::unique_ptr<GameObject> create(const ObjectDescriptor& objD)
 {
   auto it = getCreatorRegistry().find(objD.m_type);
   
   if (it != getCreatorRegistry().end())
   {
     return it->second(objD);
   }

   throw std::runtime_error(
     std::string("not found type num: ") + 
     std::to_string( static_cast<int>(objD.m_type)));
 }
}
