#pragma once

#include "engine/events/llevents.h"
#include <memory>

void processEvent(std::unique_ptr<ll::engine::events::AbstractEvent> event);
