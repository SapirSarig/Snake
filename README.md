# Snake
This game is a competitive game between two players who need to solve math exercises. Each player has a snake.
One snake is controlled by the keys 'wxda' and the other by the keys 'imlj'.
In each level, a math exercise and numbers will be shown on the screen.
The goal is to collect a number that is the answer of the exercise.
The first player who collectes a correct number gets a point.
If a player collectes a wrong number - the other player gets a point.
The game ends when a player gains 12 points.

Instructions for sounds in the game:
-------------------------------------
In order to enable the sound, after creating a project in VS2015, press right click on the project and choose "Open folder in File Explorer".
Now add all the WAV files to the folder that opened.
   
Next, go to the open project in VS2015, press right click on the project again and follow the next instructions: 
Properties-> Linker -> Input-> on the first line "Additional Dependecies" click on edit-> add the next command: "winmm.lib"->press ok.
Now you can run the program with sounds. 
