#include "Game.hpp"

Game::Game() : mobsIA(&Game::UpdateMobs,this)
{
    //this->Initialize();
    lives = 3;
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

    enemies.push_back(new Enemy (world,5.0f,3.0f));

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
    map.push_back(new Platform(world,4.0f,0.0f,5.0f,0.5f,false));

    // Création d'une plate forme
    map.push_back(new Platform(world,4.5f,2.0f,1.0f,0.1f,true));

    map.push_back(new InteractiveDecor(world,4.0f,1.25f,0.1f,1.5f,InteractiveDecor::LADDER));
}

int Game::Run()
{
    mobsIA.Launch();
    // Boucle principale : tant que la fenêtre est ouverte
    while(window->IsOpen()) {
        window->Clear();

        // Traitement des événements
        while(window->PollEvent(sfmlEvent)) {
            if(sfmlEvent.Type == sf::Event::Closed) window->Close();
            if(sfmlEvent.Type == sf::Event::KeyPressed) {
                switch(sfmlEvent.Key.Code) {
                    case sf::Keyboard::Space:
                        player->Jump(b2Vec2(0.0f,0.05f));
                        break;
                    default:
                        break;
                }
            }
        }

        // Traitement des entrées clavier autres que évennements
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
            player->Move(Mob::LEFT,0.3f);
        else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
            player->Move(Mob::RIGHT,0.3f);
        //else
            //player->Move(Mob::STOP);

        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Up))
            player->Climb(Mob::UP);
        else if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
            player->Climb(Mob::DOWN);
        //else
            //player->Climb(Mob::STOP);


        // Itération dans le monde
        world->Step(timeStep,velocityIterations,positionIterations);

        // Dessin des hitbox
        world->DrawDebugData();

        // Affichage des plates formes
        std::vector<StaticElement*>::iterator mapIterator = map.begin();
        while(mapIterator != map.end()) {
            (*mapIterator)->Render(window);
            mapIterator++;
        }

        // Parcours de la liste des mobs, effacement des morts, affichage des vivants
        std::vector<Enemy*>::iterator enemiesIterator = enemies.begin();
        while(enemiesIterator != enemies.end()) {
            if((*enemiesIterator)->IsDestroyed()) {
                delete *enemiesIterator;
                enemiesIterator = enemies.erase(enemiesIterator);
            }
            else {
                (*enemiesIterator)->Render(window);
                enemiesIterator++;
            }

        }

        // Affichage du personnage
        if(player->IsDestroyed()) {
            delete player;
            return Terminate(1);
        }
        else player->Render(window);

        window->Display();
        usleep(3000);
    }
    return Terminate(0);
}

void Game::UpdateMobs()
{
    while(1) {
        std::vector<Enemy*>::iterator enemiesIterator = enemies.begin();
        while(enemiesIterator != enemies.end()) {
            (*enemiesIterator)->IA(player->GetPosition());
            enemiesIterator++;
        }
        usleep(3000);
    }
}

int Game::Terminate(int cause)
{
    mobsIA.Terminate();
    enemies.clear();
    window->Clear();
    window->Close();

    switch(cause) {
        case 0:
            return 0;
        case 1:
            lives--;
            printf("%i lives remaining !",lives);
            return lives;
        default:
            return 0;
    }
}
