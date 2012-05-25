/**
 * @author Benoit DJERIGIAN
 * @author Nicolas LE NUE
 * @file Game.cpp
 * @brief Implémentation du jeu
 *
 * Ce fichier implémente les méthodes de la classe Game
 */

#include "Game.hpp"

/** @brief Constructeur
 *
 * Initialise le nombre de vies à 3, crée un thread pour l'IA
 *
 */
Game::Game() : mobsIA(&Game::UpdateMobs,this)
{
    lives = 3;
}

/** @brief Initialisation
 *
 * L'initialisation comporte les étapes suivantes
 *
 * 1. Créer une fenêtre de rendu
 * 2. Créer le monde physique
 * 3. Appeler la méthode de création du niveau
 * 4. Créer le personnage
 * 5. Assigner un objet pour le dessin des hitbox (pour le debug)
 * 6. Créer la vue
 * 7. Dessiner le fond
 *
 */
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
    player = new Character(world,1.0f,6.0f);

    // Création et assignation d'un renderer pour les objets Box2D
    DebugDraw* debugDraw;
    debugDraw = new DebugDraw(window);
    debugDraw->AppendFlags(b2Draw::e_shapeBit);
    world->SetDebugDraw(debugDraw);

    // Assignation d'un gestionnaire de collision
    world->SetContactListener(new CollisionManager());

    view.SetCenter(100,300);
    view.SetSize(800,600);
    window->SetView(view);

    bgtexture.LoadFromFile("src/ressources/background.jpg");
    bgtexture.SetRepeated(true);
    background.SetTexture(bgtexture);
    background.SetTextureRect(sf::IntRect(0,0,7200,600));
    background.SetPosition(-600,0);
}

/** @brief Création du niveau
 *
 * Cette méthode crée les plates-formes, les décors et les ennemis
 *
 */
void Game::CreateLevel()
{
    // Création des sols
    map.push_back(new Platform(world,2.5f,0.0f,2.5f,0.5f,"src/ressources/metal.jpeg",false));
    map.push_back(new Platform(world,8.2f,0.0f,2.0f,0.5f,"src/ressources/metal.jpeg",false));
    map.push_back(new Platform(world,20.0f,0.0f,5.0f,0.5f,"src/ressources/metal.jpeg",false));
    map.push_back(new Platform(world,23.5f,1.0f,0.5f,0.5f,"src/ressources/box.png",false));
    map.push_back(new Platform(world,24.5f,1.0f,0.5f,0.5f,"src/ressources/box.png",false));
    map.push_back(new Platform(world,24.5f,2.0f,0.5f,0.5f,"src/ressources/box.png",false));
    map.push_back(new Platform(world,32.0f,0.0f,6.0f,0.5f,"src/ressources/metal.jpeg",false));
    map.push_back(new Platform(world,36.0f,2.4f,0.2f,3.0f,"src/ressources/wall.png",false));
    map.push_back(new Platform(world,56.2f,0.0f,2.5f,0.5f,"src/ressources/metal.jpeg",false));

    // Création des plate forme
    map.push_back(new Platform(world,2.9f,1.3f,0.6f,0.1f,"src/ressources/metal.jpeg",false));
    map.push_back(new Platform(world,4.9f,2.0f,0.9f,0.1f,"src/ressources/metal.jpeg",false));
    map.push_back(new Platform(world,12.0f,4.0f,2.0f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,34.8f,5.4f,1.0f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,34.3f,1.1f,1.5f,0.1f,"src/ressources/metal.jpeg",false));
    map.push_back(new Platform(world,31.8f,1.9f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,33.3f,2.7f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,34.8f,3.5f,0.5f,0.1f,"src/ressources/cloud.png",true));

    map.push_back(new Platform(world,39.0f,0.8f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,40.0f,1.6f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,41.0f,2.0f,0.25f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,41.8f,1.3f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,42.0f,2.8f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,43.6f,2.6f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,44.0f,0.8f,0.25f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,46.2f,3.0f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,45.0f,2.6f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,47.9f,3.7f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,48.6f,4.5f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,50.4f,5.2f,0.5f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,52.65f,0.5f,0.25f,0.1f,"src/ressources/cloud.png",true));
    map.push_back(new Platform(world,56.2f,5.0f,1.0f,0.1f,"src/ressources/cloud.png",true));

    // Création des décors interactifs
    map.push_back(new InteractiveDecor(world,10.1f,2.3f,0.1f,1.8f,InteractiveDecor::LADDER));
    map.push_back(new InteractiveDecor(world,33.9f,5.0f,0.1f,0.5f,InteractiveDecor::LADDER));
    map.push_back(new InteractiveDecor(world,56.2f,2.8f,0.1f,2.3f,InteractiveDecor::LADDER));
    map.push_back(new InteractiveDecor(world,56.9f,5.2f,0.1f,2.3f,InteractiveDecor::FINISH));

    // Création des mobs
    enemies.push_back(new Enemy (world,8.2f,1.0f,1));
    enemies.push_back(new FlyingEnemy(world,15.0f,2.5f));
    enemies.push_back(new Enemy (world,19.0f,1.0f,1));
    enemies.push_back(new Enemy (world,23.5f,1.8f,2));
    enemies.push_back(new Enemy (world,30.5f,1.8f,1));
    enemies.push_back(new Enemy (world,33.3f,3.0f,2));
    enemies.push_back(new Enemy (world,42.0f,3.1f,2));
    enemies.push_back(new Enemy (world,50.4f,5.5f,2));
    enemies.push_back(new FlyingEnemy(world,56.2f,2.0f));
    enemies.push_back(new FlyingEnemy(world,56.6f,4.0f));
}

/** @brief Boucle principale
 *
 * Cette méthode lance l'IA et entre dans la boucle de jeu :
 *
 * 1. Traiter les évènements clavier
 * 2. Traiter les appuis longs clavier
 * 3. Itérer le monde physique
 * 4. Dessiner le fond
 * 5. Dessiner les plates-formes
 * 6. Parcourir les ennemis, détruire ceux qui doivent l'être, afficher les autres
 * 7. Tester si le personnage a gagné ou est détruit, l'afficher sinon
 * 8. Ajuster la vue sur le personnage et afficher
 *
 */
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
                    case sf::Keyboard::A:
                        player->Attack();
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

        window->Draw(background);

        // Dessin des hitbox
        //world->DrawDebugData();

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
        if(player->IsDestroyed() || player->GetBody()->GetWorldCenter().y<-3.0f) {
            delete player;
            return Terminate(1);
        }
        else if(player->HasWon())
            return Terminate(2);
        else
            player->Render(window);

        view.SetCenter(player->GetBody()->GetWorldCenter().x*100,300);
        window->SetView(view);
        window->Display();
        usleep(3000);
    }
    return Terminate(0);
}

/** @brief Gestion de l'IA
 *
 * Cette méthode lancée dans un thread permet d'appeler,
 * pour chaque ennemi, leur méthode d'IA.
 *
 */
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

/** @brief Terminaison
 *
 * Cette méthode permet de traiter un code de terminaison du jeu
 * et de renvoyer une valeur adéquate à la fonction principale.
 *
 * @param cause : le code de terminaison
 */
int Game::Terminate(int cause)
{
    switch(cause) {
        case 0:     // Le code 0 correspond à la fermeture de la fenêtre de jeu
            mobsIA.Terminate();
            enemies.clear();
            window->Clear();
            window->Close();
            return 0;
        case 1:     // Le code 1 correspond à la mort du personnage
            lives--;
            printf("%i lives remaining !",lives);
            mobsIA.Terminate();
            enemies.clear();
            window->Clear();
            window->Close();
            return lives;
        case 2:     // Le code 2 correspond à la victoire
            printf("Congrats!!!!\n");
            player->Render(window);
            window->Display();
            usleep(3000000);
            mobsIA.Terminate();
            enemies.clear();
            window->Clear();
            window->Close();
            return 0;
        default:
            return 0;
    }
}

