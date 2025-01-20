# Monopoly
This is a C++ implementation of the Monopoly board game by Hasbro. It features a university based variant on the properties but utilizes similar rules to the original game.

The game allows 2 to 7 players. Players take turns rolling two dice and moving around the 40 square board. As players move around the board, they have the ability to buy and improve properties, trade, mortgage, etc. Different squares on the board also have special features or penalties that a player may face. The aim of the game is to be the last player that has not gone bankrupt. 

A text-based display is provided in the console to view the board and players.  

## Building the game 
Prerequisites:
- A C++ compiler that supports C++14 or later (e.g. GCC or Clang). 
- The project uses a Makefile to simplify the build process, ensure that `make` is installed. 

Compiling the game: 
```
make
```
This creates an executable named `monopoly`. 

Run the game: 
```
./monopoly
```

Run the game in testing mode (players can customize their dice rolls):
```
./monopoly -testing
```

## Gameplay 
When the game begins, the players can follow on-screen prompts to configure the number of players, their names, and their characters on the board. 

Appropriate rent or other fees will be automatically calculated and deducted when a player lands on a square. 

The possible commands are performed in relation to the player whose turn it currently is. 

View all possible commands:
```
c
```

Roll dice (calculate movement):
```
roll
```

Give control to next player:
```
next
```

Trade:
```
trade <name> <give> <receive>
```
Where `name` is the player to trade with and `give` is offered by the current player in exchange for `receive`. 

Buy or sell an improvement on a property:
```
improve <property> buy/sell
```

Mortgage or unmortgage a property:
```
mortgage <property>
unmortgage <property>
```

Declare bankruptcy (leave the game):
```
bankrupt
```

View current assets of the current player:
```
assets
```

View current assets of all players:
```
all
```

Save the current game to resume later:
```
save <filename>
``` 
This will save the current game status to the given `filename`. To resume a game, run `./monopoly -load <file>`
