# Baba Ghanoush: Education App for Fish
An educational app about things fish-rlated.

# Video Presentation
https://www.youtube.com/watch?v=7AQt-hzFX3A

## Getting box2d to work
Please run the following commands:   
`git submodule add https://github.com/tobanteGaming/Box2D-cmake.git box2d-src`

`git submodule update --init --recursive`

## Building
To import the project into QT Creator, just select the CMakeLists.txt and build. Please see the previous 
section on how to get box2d building.
If you want to build it outside of QT Creator, run `cmake .` followed by `make` to build an executable.

## Easter Egg
There is an easter egg in the project. For some reason it was driving us *bananas*

## Some cool things
This entire project contains its own game engine. Meaning that we can easily create new objects and quests.

## Credits
#### Gavin C. Pease (GT3CH1)
	- Git repository manager
	- Bug fixer
	- CMake(r)
	- Level design
	- Jack of all trades, master of all.
	- Game engine
	- CI/CD
	- Resident fish
#### William Erignac (werignac)
	- Sprites
	- Game engine design
	- Physics integration
	- GameObject handling
	- Level design
	- Mouse input
	- View controller
	- Debug mode
	- Unity copy-cater
#### Kenzie Evans (kenzie-evans)
	- Start/End screen
	- Quest implementation
	- UI design
	- Level design
	- Backbone of the project
#### Jon Vielstich (JVielstich)
	- Render area
	- Mouse input
	- Professional Mouse Charmer
#### Alex Richins (ajrichins)
	- Quest implementation/design
	- Callbacks
	- Level design
	- Instructions
	- View controller
	- Game engine
	- Stinky ADHD God
