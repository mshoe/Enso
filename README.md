# Enso
[![Alt text](https://img.youtube.com/vi/OimTkWG0jM8/0.jpg)](https://www.youtube.com/watch?v=OimTkWG0jM8)

Enso is a game where you use the power of gravity to solve puzzles. I originally made the game in Unity back in 2016 for the UofT Game Making Deathmatch, where the game got 3rd place as well as the creativity award. It was my first ever game, but instead of continuing it, I got sucked into the desire of making my dream game (an action party-based rpg rogue-like dungeon crawler with minecraft mechanics), which I have tried to make on and off since the summer of 2016. Now I have decided to remake it since it is a simple yet powerful concept, and I hope that in making this game I will gain enough experience to try and tackle my dream game again in the future.

Languages used:
C++

Libraries used:
glm, SIGIL

Rules for the arcade mode:
-White circle (player controlled) has a gravitational pull on the other circles
-we want to get the red circles into our goals (the yellow box in the center is one example of a goal), those increase our score
-we want to avoid getting the green circles into our goals (like the 8 ball in pool until the very end), those will result in game over

Next steps:
-Improve the real-time collision engine to be more realistic (fix overlapping objects, sinking objects, etc.)
-more ideas to arcade mode (power-ups or power-downs that affect things such as reversing the white ball's gravitational pull, enlarging the goal size, shrinking all the circles, etc.)

Long-term goals:
-puzzle mode: a series of levels designed around the concept of the white ball using its gravitational pull to navigate red and green (and other color) circles through obstacles to their destinations
-level editor: a GUI that allows users to make their own levels for the game
-music: electronic/chillhop bgm