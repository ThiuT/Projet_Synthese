#include "Weapon.hpp"

Weapon::Weapon(Mob* mob)
{
    user = mob;
    b2Vec2 userPos = user->GetBody()->GetWorldCenter();
    sf::FloatRect userBounds = user->GetSprite().GetLocalBounds();
    float dir = user->GetSprite().GetScale().x;

    // Création du sprite
    texture.LoadFromFile("src/ressources/sword.png");
    sprite.SetTexture(texture);
    sprite.SetOrigin(sprite.GetLocalBounds().Width/2.0f,sprite.GetLocalBounds().Height/2.0f);
    sprite.SetScale(dir,1);

    // Definition d'un corps dynamique à la position initiale x,y
    bodydef.type = b2_dynamicBody;
    bodydef.position.Set(userPos.x - dir*(userBounds.Width + sprite.GetLocalBounds().Width)/200.0f,userPos.y);
    bodydef.fixedRotation = true;

    // Création du corps
    body = user->GetBody()->GetWorld()->CreateBody(&bodydef);
    destroyed = false;

    box.SetAsBox(sprite.GetLocalBounds().Width/200.0f,sprite.GetLocalBounds().Height/200.0f);
    fixturedef.shape = &box;
    fixturedef.density = 1.0f;
    fixturedef.friction = 1.0f;
    fixturedef.isSensor = true;
    fixturedef.filter.categoryBits = Element::WEAPON;
    fixturedef.filter.maskBits = Element::ENEMY;
    body->CreateFixture(&fixturedef);

    jointdef.bodyA = user->GetBody();
    jointdef.bodyB = body;
    jointdef.collideConnected = false;
    jointdef.localAnchorA.Set(-dir*userBounds.Width/200.0f,0.0f);
    jointdef.localAnchorB.Set(dir*sprite.GetLocalBounds().Width/200.0f,0.0f);
    jointdef.localAxisA.Set(1,0);
    jointdef.enableLimit = true;
    jointdef.lowerTranslation = 0;
    jointdef.upperTranslation = 0;
    joint = (b2PrismaticJoint*)user->GetBody()->GetWorld()->CreateJoint(&jointdef);

    body->SetUserData(this);
    timer=0;
}

bool Weapon::IsDone()
{
    if(timer++ > 50)
        return true;
    return false;
}

Weapon::~Weapon()
{
}

