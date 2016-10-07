#include "ElectricTools.h"

#include <sstream>

#include "representation/Chat.h"
#include "Tile.h"
#include "../Game.h"

AtmosTool::AtmosTool(size_t id) : Item(id)
{
    SetSprite("icons/device.dmi");
    SetState("atmos");
    name = "Atmos tool";
}

std::string AtmosTool::GetInfo(AtmosHolder &holder)
{
    std::stringstream ss;
    ss << "Energy: " << holder.GetEnergy() << std::endl;
    ss << "Volume: " << holder.GetVolume() << std::endl;
    ss << "Temperature: " << holder.GetTemperature() << std::endl;
    ss << "Pressure: " << holder.GetPressure() << std::endl;
    for (size_t i = 0; i < GASES_NUM; ++i)
    {
        ss << GASES_NAME[i] << ": " << holder.GetGase(i) << std::endl;
    }
    return ss.str();
}

void AtmosTool::AttackBy(IdPtr<Item> item)
{
    if (item.Id() == GetId())
    {
        if (IdPtr<CubeTile> ct = GetOwner()->GetOwner())
        {
            GetGame().GetChat().PostTextFor(GetInfo(*ct->GetAtmosHolder()), GetOwner());
        }
    }
}

RemoteAtmosTool::RemoteAtmosTool(size_t id) : AtmosTool(id)
{
    name = "Remote atmos tool";
}
