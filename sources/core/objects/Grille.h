#pragma once

#include "Structure.h"

class Grille: public Structure
{
public:
    DECLARE_SAVED(Grille, Structure);
    DECLARE_GET_TYPE_ITEM(Grille);
    Grille(size_t id);
    virtual void AttackBy(IdPtr<Item> item) override;
private:
    bool KV_SAVEBLE(cutted_);
};
ADD_TO_TYPELIST(Grille);
