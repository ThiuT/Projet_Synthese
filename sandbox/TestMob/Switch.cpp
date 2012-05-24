#include "Switch.hpp"

Switch::Switch(float32 x, float32 y, StaticElement* elem) : InteractiveDecor(elem->GetBody()->GetWorld(),x,y,0.0f,0.0f,3)
{
    target = elem;
}

void Switch::Action()
{
    target->GetBody()->SetActive(false);
}
