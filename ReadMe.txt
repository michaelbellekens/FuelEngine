LINK TO GITHUB: https://github.com/michaelbellekens/FuelEngine

Description of FuelEngine:

Command pattern: Used in the InputManager to link specific functions of the PlayerController to it.
Although it is possible to overwrite this function with a new function by passing a function pointer.
Commands will be triggered through KeyBindings or ControllerBindings that keep track of the status of
the binded key.

Game Loop: The engine can run on multiple predetermined framerates. The gameloop has an update and render
function that will be ran every frame but also has a FixedUpdate function that runs on a fixed speed.
This is where all the physics will run on.

Components: Although you can create childs of GameObject classes it's possible to keep extending an
gameobject by simply adding components that will extend its functionality. The engine comes with a 
set of default components that can be used to extend your gameobjects. But it's possible to create
your own components and add them to the gameObjects. So it's easy to extend you objects.

States: (Not build in engine feature) States are used to for the behaviour of the enemies. An AIController
component has control over the states. With a Physics Callback the states are able to detect when
a collision or trigger happened and are able to extract information from it.

FileManager: ALl the levels can be saved and loaded from/to binary files for optimal performance and speed.
Through an enum will be determined which type of object will be saved. Afterwards all it's components will 
be saved (also with an enum as componentType). Each component has a virtual Save en Load function that
will take care of the important datamembers.

SoundManager: Used Fmod to play sounds in the engine, the soundManager will allow you to add, play, pause, 
stop, mute,... sounds and more. Since it's a singletone you will have easy access to it from each class 
where you would need it.

