# PS4: Sokoban

## Contact
Name: Mark Daoud
Section: 201
Time to Complete: 4 hour


## Description
Th project reads in from a level file the layout of the board using the overloaded >> operator to read it into a board matrix. The draw function then goes through the board matrix and loads in the proper sprite to match the symbol at that part of the board. The player then uses the arrow keys or WASD to move along the board and get the boxes in storage spots. If the player succeds then a victory screen appears and music starts playing. 
The player can press R at any time to restart the level and reset level back to original drawing state. 

### Features
Describe what your major decisions were and why you did things that way.

#### Part a
For the board, I used a vector of a vector of chars to represent it which allowed for dynamic resizing and easy access to each cell on the board. The choice of `char` was made to simplify the mapping of board symbols to sprites.
#### Part b
Basic movement was handled using first in main sf::Event::KeyPressed and then passing that key to the move function which handled movement by decrementing or incrementing the players nextloc.x and nextloc.y 
based on the direction that was passed in from main. 
Collisions with player going out of bounds were handled by checking if the nextloc.y was >= height and if nextloc.x was >= width. 
Collisions with walls were handled in the case of the player by checking if that position at nextlo.x, nextloc.y on the board was equal to '#'. In the case of box and wall or another box, the collision was handled
by checking if that next location on the board was equal to a 'A' or '1' then if the nextloc that the box was being pushed to was equal to 'A', '1', or '#' then the function returns.
Box out of bounds check is handled same as player by cheking if the next location exceeds the width or height. 

### Memory
I decided to store the level data using a vector of vectors of chars, which allows for dynamic resizing and easy access to each cell on the board. I didn't use smart pointers for the sprites and textures but instead just had the game object control those. 

### Lambdas
In my isWin function I used the count_if and count algorithms from the algorithm function and then implemented a lambda when counting the total boxes to check for both 'A' and '1' for boxes.
        

### Issues
At first I had trouble with their being black outlines under the character and boxes but fixed this by drawing the ground first to make sure everything else is drawn above it. 
Handling win conditions when boxes where greater or less than storage spots was difficult at first but implemented counts to handle it. 

### Extra Credit
Serenade Victory Screen where it displays text and plays sound and still allows for player to restart.
Character sprite updates based on direction character is moving impemented in move function.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Trumpets.wav - https://www.jamendo.com/start
Roboto.txt - https://fonts.google.com/
image.png - https://i.ytimg.com/vi/R8qqu3laqO4/maxresdefault.jpg

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
