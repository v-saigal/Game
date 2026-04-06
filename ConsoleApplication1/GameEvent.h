#pragma once

#include <variant>
#include "EventType.h"
#include "MoveEvent.h"
#include "AttackEvent.h"
#include "DamageEvent.h"
#include "DeathEvent.h"

using EventData = std::variant<
    MoveEvent,
    AttackEvent,
    DamageEvent,
    DeathEvent
>;

struct GameEvent
{
    EventType type;
    EventData data;
};