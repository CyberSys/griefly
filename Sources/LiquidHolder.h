#pragma once
#include "MainInt.h"
#include "Liquid.h"
#include "HelperStructers.h"

std::iostream& operator<<(std::iostream& file, std::map<unsigned int, id_ptr_on<Liquid>>& liquids);
std::iostream& operator>>(std::iostream& file, std::map<unsigned int, id_ptr_on<Liquid>>& liquids);

class LiquidHolder: public IMainItem
{
public:
    static std::vector<Reaction> reactList;
    static bool LoadReaction();
    DECLARE_GET_TYPE_ITEM(liquidholder);
    DECLARE_SAVED(LiquidHolder, IMainItem);
    LiquidHolder();
    unsigned int addLiquid(unsigned int hash, unsigned int amount);
    unsigned int amountOf(unsigned int hash);
    unsigned int amountOfAll();
    unsigned int removeLiquid(unsigned int hash, unsigned int amount);//return removed amount
    
    std::list<HashAmount> removeLiquid(unsigned int amount);//return removed types and amounts
    std::list<HashAmount> addLiquid(std::list<HashAmount> what);

    int KV_SAVEBLE(size);
    virtual void delThis();
   // ~LiquidHolder(void);
    typedef std::map<unsigned int, id_ptr_on<Liquid>> LiquidMap;
    virtual void processImage(DrawType type);
private: 
    LiquidMap KV_SAVEBLE(liquids);
    void checkReaction(unsigned int hash);
    
};
ADD_TO_TYPELIST(LiquidHolder);
