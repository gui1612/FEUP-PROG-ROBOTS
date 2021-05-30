# Robots Game: Overview

## Important
>- 'H'/'h' -> Player (alive/dead)
>- 'R'/'r' -> Robot (alive/dead)
>- 'r' -> Several Robots collision 
>- '*' -> Fence/Post
>

| Right    | Middle   | Left     |
| -------- | -------- | -------- |
| Q        | W        | E        |
| A        | S (stay) | D        |
| Z        | X        | C        |



`Note: Both upper and lower cases work`


## MAZE (\*)
>- High voltage fences
>- High voltage posts

## PLAYER (H/h)
>#### Overview
>- Interceptor robots will try to destroy the player
>#### Movement
>- The player can move in any direction to an adjacent cell (horizontally, vertically, or diagonally)

## ROBOTS (R/r)
>#### Death
>- Robot touches the fences/posts or other robot
>#### Movement
>- For each player's cell movement the robot also moves one cell in the shortest path direction

## WIN CONDITION
>- All robots are destroyed

## GAME OVER
>- Player touches maze
>- Player touches robots

## Program flow
>#### Start
>- Show a menu (`1) Rules`, `2) Play`, `3) Exit`)
>- When a user decides to play the game:
>>- Ask the number (int) of the maze
>>- Build the maze with the name `MAZE_XX.TXT` (XX - maze no.) and verify if it exists
>>    - If the user input is 0 show the menu again
>>    - If the user input is not valid and not 0 asks the user again 
>#### Mid-Game
>- Each robot must have an ID (starting at 1) to be stored in the data structure
>- Ask the player where he wants to move to ([MORE ON THIS](#important))
>     - If the input is invalid repeats the question
>     - If the player tries to move to occupied places he gets `Warning: invalid movement` and the question is repeated
>- Move the player each round and, if necessary, his status ('H' -> 'h')
>- If the player is alive, move one robot after the other (according to their ID's)
>- If a Robot collides with a dead or alive Robot ('r'/'R') it gets stuck and is represented by 'r'
>- If a Robot collides with a fence it dies, still being represented as an 'r' and the fence looses its capability to eletrocute
>- If the player survives ask his name (15 CHARS MAX) and update the list of winners stored in the corresponding file (`MAZE_XX_WINNERS.TXT`)
>- Press EOF to exit the game whenever

## FILES (NAMES AND CONTENT)
>File containing Maze: `MAZE_XX.TXT` (XX represents the number of the maze)
>File containing the name and time (seconds) of the winners (sorted by ascending order): `MAZE_XX_WINNERS.TXT` 

#### MAP EXAMPLE
```
10 x 20
********************
*  R        R      *
*   R *  *  *      *
*        H  *      *
*   **     *   *   *  
*   *      *  *    *
*     * *   R  *   *
*  *          **   *
*     R     *      *
********************
```

#### WINNER FILE EXAMPLE
```
Player          – Time
----------------------
Antonio Santos  -  321
Guilherme A     -  512
```

## RULES
>- Program must execute in console
>- External libraries are not allowed
>- Must be compatible with Windows/Linux
>- Not allowed: Calls to `system()`, colored output


## TIPS
>- Use named constants instead of "Magic numbers"
>- Don't use global variables
>- Choose the best way to pass parameters to the functions
>- Comment code
>- Structure code
>- Efficient code
>- Robust code (the program should not stop working because of bad user input)
>- Separate data processing from I/O
>- Choose data structures, identifiers of type and functions well


# SUBMISSION
>- Create a folder `Txx_Gyy` (xx -> class; yy -> group no.)
>- Copy `.h` and `.cpp` files to that folder
>- Create a `ReadMe.txt` file 
>- Compress the folder into a `.zip`

#### README.TXT EXAMPLE
```
Txx_Gyy (in the first line, the class and group number, as specified above)
GROUP MEMBERS:
-student_1 name
-student_2 name
PROGRAM DEVELOPMENT STATE:
-(say here if all the objectives were accomplished or, otherwise, which ones were not achieved, and also what improvements were made, if any)
MAIN DIFFICULTIES:
-(describe here the main difficulties that you faced whendevelopping the program)
```
