# The O-Engine
The O-Engine is a game engine made for 2D arcade games. It follows design philosophies similar to unity which will be explained later. This engine was made as part of my major course Programming-4. It the third party libraries SDL2 for images, sounds and fonts as well as glm for math and nlohmanns Json library for storing data. Its build as a static library that can be implemented in a C++ project. The download includes a bomberman for the nes as a demo project.
## Design Philosophy
The engine is made with Unity in mind making it easy to use for people with experience in that engine. It is focussed on keeping the API simple to use for new C++ users. It uses an object component system where the user can create gameobjects that are placed in a hierarchy in a scene allowing for easy parenting of objects. These gameobjects by themselves have no functionality except for a position, but the user can attach components to them to give them a use. All objects created within the framework of the engine are memory safe and deallocate without any input from the user.
## Documentation
### Implementing the engine
Before starting the user has to create an object of Minigin which is the core of the engine the engine takes a string as argument. The string is the path from the current directory to the data folder. After that call Run() on the engine object which takes a reference to a function which loads the first scene.
```C++
dae::Minigin engine{"../Data/"};
engine.Run(load);
```
### Creating a scene
In the load function the user can inititialize their scene. To start the user has to create a scene object and submit it to the scene manager. The new scene requires a name to later be loaded when switching scenes.
```C++
dae::Scene* pScene {dae::SceneManager::GetInstance().CreateScene("StartScreen")};
```
### Creating gameobjects
After creating a scene the user can now add an arbitrary number of gameobjects to design their own game. To do this the user needs to create a GameObject object and add it to the scene. The game objects take a pointer to scene as a constructor parameter.
```C++
GameObject* go{std::make_shared<GameObject>(pScene)};
pScene->Add(go);
```
### Adding Components
To add a component the user needs a pointer to a gameobject. Adding a component uses a template function the type in angular brackets is the added component in this example it is a SpriteComponent
```C++
SpriteComponent* spriteComp {go->AddComponent<SpriteComponent>();
```
With this a component is added to the gameobject. Some components require some further setup like our SpriteComponent. This can be easily done since the creation of the Component returns a pointer to it. In this example we are going to add a sprite to the gameobject.
```C++
spriteComp->AddSprite(3,1,"Character/LeftWalkCycle","WalkLeft");
```
The sprites are added by providing the amount of sprites per column and row then a path to the Sprite from the engines Data Directory. Last but not least the sprite needs a name to allow easy switchting between sprites.
### Handling Inputs
The engine supports Mouse and Keyboard as well as Xbox Controllers. This utilizes the Command pattern in which you bind certain action classes to the input.
There are 2 different types of inputs: 
1. Boolean inputs  
2. 2D-Axis inputs  
```C++
dae::Singleton<dae::InputManager>::GetInstance().AddControllerCompoundAction<dae::Move>(
  dae::Controller::ButtonInputs::DPadUp,
  dae::Controller::ButtonInputs::DPadDown,
  dae::Controller::ButtonInputs::DPadLeft,
  dae::Controller::ButtonInputs::DPadRight,
  go.get()
);
```
This is a 2D-Axis input that calls the MoveCommand on a gameobject. The function takes the command as the template class. The parameters of the function are The different inputs that should get bound and a pointer to the gameobject. For this example to work the gameobject needs to implement a MovementComponent since the move command depends on it.
```C++
dae::Singleton<dae::InputManager>::GetInstance().AddControllerActionMapping<dae::BombCommand>(
  dae::ControllerAction::ActionType::ButtonMap,
  go.get(),
  dae::Controller::ButtonInputs::XButton,
  dae::ControllerAction::InputType::ButtonUp
);
```
This is a boolean input that takes the BombCommand as template argument. The parameters for this function are the type of input the user needs e.g. button or trigger and it needs a pointer to the gameobject. The last two parameters are the specific button and the input type e.g. ButtonDown,ButtonUp and IsPressed

For any further information feel free to browse the engine and game code or contact me on discord @dezerted

