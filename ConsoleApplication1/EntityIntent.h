#pragma once
#include "Position.h"
struct MoveIntent { Position target; bool hasIntent = false; bool approved = false; };