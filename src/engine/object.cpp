#include "engine/object.hpp"

#include <atomic>
#include <memory>
#include <unordered_map>

namespace ll::engine {

static std::atomic_uint64_t uniqueId = 100;

static std::unordered_map<ObjectId, EngineObject*> globalObjects;

EngineObject::EngineObject() {
  _id = uniqueId.fetch_add(1);
  globalObjects.insert(std::pair(_id, this));
}

EngineObject::~EngineObject() {
  globalObjects.erase(_id);
}

bool EngineObject::objectExists(ObjectId id) {
  return globalObjects.contains(id);
}

EngineObject& EngineObject::findObject(ObjectId id) {
  return *globalObjects.at(id);
}

}// namespace ll::engine
