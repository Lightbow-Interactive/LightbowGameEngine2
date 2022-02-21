# LightbowGameEngine2
Lightbow Game 2D Open-Source Game Engine built on SFML

- To get a good example have a look at "PongTemplate". This is the Ping Pong game created in LBGE2. 
- The Blank Template is currently not finished.

## Engine

### Engine Modules

- LBGE2 currently has 6 modules which can be included.

#### LBGECore

#include "LBGECore.h"

| Class         | Description                                                  |
| ------------- | ------------------------------------------------------------ |
| Game          | Static functions to start the game and manage core features  |
| Level         | A level is the root object for everything. There can only exist one level at the time. Each level has a state (m_state) and an object manager (m_manager). |
| EventDelegate | Used for creating events where you can bind functions to. See PongTemplate -> PongMenuLevel.cpp for button actions. |

#### LBGEObjects

#include "LBGEObjects.h"

| Class      | Description                                                  |
| ---------- | ------------------------------------------------------------ |
| LBGEObject | A visible object which can be added to the object manager in the level. The object is create with a texture. Support for multiple textures for animations is planned. |

#### LBGEStates

#include "LBGEStates.h"

| Class     | Description                                    |
| --------- | ---------------------------------------------- |
| GameState | GameState base class. Every level has a state. |

#### LBGETypes

#include "LBGETypes.h"

| Class    | Description                                                  |
| -------- | ------------------------------------------------------------ |
| KeyEvent | An input event which is passed into the "HandleInput" function of each LBGEObject. |
| Vector2  | Not really a vector. It just contains an x and y value and can be explicitly converted to an SFML Vector2. |

#### LBGEAudio

#include "LBGEAudio.h"

| Class | Description                        |
| ----- | ---------------------------------- |
| Sound | A sound object which can be played |
| Audio | Static functions to play sounds    |

#### LBGEUi

#include "LBGEUi.h"

| Class     | Description                                                  |
| --------- | ------------------------------------------------------------ |
| Fonts     | Static class to load and manage fonts.                       |
| TextBlock | A text block which can be added to the object manager in your level. It can display text. |

## Installation

### Installation with Engine Source

- To use and compile the Engine, SFML is required. 
- Download the correct SFML release here https://www.sfml-dev.org/download/sfml/2.5.1/ for your compiler.
- LBGE2 uses CMake as compiler.
- Make sure SFML is installed at "C:/Libs/SFML" or change the directory in "LBGE2->Engine->CMakeLists.txt" Line 33.
- On MacOS SFML needs to be installed at "/usr/local/include" or change the directory in "LBGE2->Engine->CMakeLists.txt" Line 22.
- Use the one of the templates to start with your project.

### Installation without Engine Source

- A packaged version of the Engine is currently not available, but will be in future.
