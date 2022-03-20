#ifndef PG_SMARTTYPEPTR_H
#define PG_SMARTTYPEPTR_H

#include <memory>
#include<GL/glew.h>
#include<glm.hpp>
#include "gtc/matrix_transform.hpp"
#include "gtx/quaternion.hpp"


#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define MAKE_SHARED(TYPENAME) \
class TYPENAME; \
    typedef std::shared_ptr<TYPENAME> TYPENAME ## SharedPtr;

#define MAKE_UNIQUE(TYPENAME) \
class TYPENAME; \
    typedef std::unique_ptr<TYPENAME> TYPENAME ## UniquePtr;
// namespace PG
#endif // PG_SMARTTYPEPTR_H
