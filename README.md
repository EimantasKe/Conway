# Conway's Game of Life
## Assignment
Conway's Game of Life: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

Write Conway's Game of life:
- [ ] It should be multithreaded application with QT5 based graphical interface.
- [x] User should be able to change execution speed.
- [x] User should be able to change game field size.
- [x] Game field size should not be limited by drawn view.
- [ ] There should be unit tests
## Development
* Initial decision to use Qt Quick (QML) rather than QtWidget
* Using TableView to represent the board

## Program structure
* `Conways.pro`
* Headers
  * `conways.h`
* Sources
  * `conways.cpp`
  * `main.cpp`
* QML
  * `main.qml`
* Remnant and build files from development 
  * `qmldir`
  * `qml.qrc`
  * `qtquickcontrols.conf`
  * `Conways.pro.user`

## TODO
* Multithreading - requires developing function to split the board into section that then are operated upon by separate threads (each section will have edge columns(or rows) that won't be changed in the section but are required to look at, in order to properly operate on the remainder of the section)
* Unit testing

## Other potential features
* Presets for starting live cells
* Changing cell colors based on recognized patterns (https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Examples_of_patterns)
