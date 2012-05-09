#include "Game.hpp"

Game::Game()
{
    this->Initialize();
}

void Game::Initialize()
{
    // Création d'une fenêtre SFML de 800*600px et 32bits par pixel
    window = new sf::RenderWindow(sf::VideoMode(800,600,32),"Test");
    window->EnableKeyRepeat(false);

    // Attribution d'une position fixe à la fenêtre
    window->SetPosition(74,155);

    // Définition des propriétés d'un monde Box2D
    gravity.Set(0.0f, -0.98f);
    velocityIterations = 6;
    positionIterations = 2;
    timeStep = 1.0f/60.0f; // = 60Hz

    // Création d'un monde Box2D
    world = new b2World(gravity);
    world->SetAllowSleeping(true);

    // Création du niveau
    CreateLevel();

    // Création d'un mob
    player = new Character(world,1.0f,4.0f);
    mobs.push_back(player);
    mobs.push_back(new Enemy (world,5.0f,3.0f));

    // Création et assignation d'un renderer pour les objets Box2D
    DebugDraw* debugDraw;
    debugDraw = new DebugDraw(window);
    debugDraw->AppendFlags(b2Draw::e_shapeBit);
    world->SetDebugDraw(debugDraw);

    // Assignation d'un gestionnaire de collision
    world->SetContactListener(new CollisionManager());
}

void Game::CreateLevel()
{
    // Création du "plancher"
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(4.0f, 0.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(5.0f, 0.5f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Création d'une plate forme
    b2BodyDef platformDef;
    platformDef.position.Set(4.5f,1.5f);
    b2Body* platformBody = world->CreateBody(&platformDef);
    b2PolygonShape platformBox;
    platformBox.SetAsBox(1.0f,0.2f);
    b2FixtureDef platformFixtureDef;
    platformFixtureDef.shape = &platformBox;
    platformFixtureDef.friction = 0.0f;
    platformBody->CreateFixture(&platformFixtureDef);
}

void Game::Run()
{
    // Boucle principale : tant que la fenêtre est ouverte
    while(window->IsOpen()) {
        window->Clear();
        // Traitement des événements
        while(window->PollEvent(sfmlEvent)) {
            if(sfmlEvent.Type == sf::Event::Closed) window->Close();
            if(sfmlEvent.Type == sf::Event::KeyPressed) {
                switch(sfmlEvent.Key.Code) {
                    case sf::Keyboard::Up:
                        player->Jump(b2Vec2(0.0f,0.05f));
                        break;
                    default:
                        break;
                }
            }
        }

        // Traitement des entrées clavier autres que évennements
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
            player->Move(Mob::LEFT);
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
            player->Move(Mob::RIGHT);

        // Itération dans le monde
        world->Step(timeStep,velocityIterations,positionIterations);

        // Dessin des hitbox
        world->DrawDebugData();

        // Parcours de la liste des mobs, effacement des morts, affichage des vivants
        std::vector<Mob*>::iterator mobsIterator = mobs.begin();
        while(mobsIterator != mobs.end()) {
            if((*mobsIterator)->IsDestroyed()) {
                Mob* dyingEnemy = *mobsIterator;
                delete dyingEnemy;
                mobsIterator = mobs.erase(mobsIterator);
            }
            else {
                (*mobsIterator)->Render(window);
                mobsIterator++;
            }
        }


        window->Display();
        usleep(3000);
    }

}
