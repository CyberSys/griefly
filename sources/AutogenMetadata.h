#pragma once

#include <unordered_map>

#include "core/objects/MainObject.h"

typedef IMainObject* (*item_creator)(size_t id);
typedef IMainObject* (*item_creator_saved)();

std::unordered_map<std::string, item_creator>* items_creators();

std::unordered_map<std::string, item_creator_saved>* items_void_creators();

typedef void (*variable_setter)(IMainObject* ptr, std::stringstream& str);

typedef std::unordered_map<std::string, variable_setter> setters_for_type;

std::unordered_map<std::string, setters_for_type>& get_setters_for_types();

void InitRealTypes();
void InitCreators();
void InitSettersForTypes();
