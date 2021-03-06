#pragma once

#include <unordered_map>

#include "core/objects/Object.h"

using ItemCreator = kv::Object*(*)();
using VoidItemCreator = kv::Object*(*)();

std::unordered_map<QString, ItemCreator>* GetItemsCreators();

std::unordered_map<QString, VoidItemCreator>* GetVoidItemsCreators();

using VariableSetter = void(*)(kv::Object* ptr, FastDeserializer& str);

using SettersForType = std::unordered_map<QString, VariableSetter>;

std::unordered_map<QString, SettersForType>& GetSettersForTypes();

void InitRealTypes();
void InitCreators();
void InitSettersForTypes();
