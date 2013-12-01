A random assortment of info.

To compile:
	cd <path>
	make
To play:
	./The_Game
Note:
	Where <path> is the path to the code. You'll need ncurses.

The_Game is horribly unbalanced. Don't expect any fairness.

After naming your character, you will get to choose a species. This
determines your starting stats, but doesn't have that big of an
impact on the game.

You'll then get to choose a class. This affects how your stats will
grow as you level up. Again, not much impact here.

All stats cap at ((2 ^ 63) - 1) / 10  (922,337,203,685,477,580).
Except Wait, which has a range of 100-9999.

Every level, your stats will improve based on your class. You also get
to choose a bonus.

Damage formula: (R * D) - AP
R = STR / DEF. ranges from .01-100 (1%-10000%). This is shown in the menu
     after "Attack".
D = For each die, a random number between 1 and number of sides,
     inclusive. Add these numbers together.
     Ex: 2d5 means "2 dice with 5 sides", or 2-10. Bonus damage is added to the
     result, so 3d3+1 means "3 dice with 3 sides, plus 1", or 4-10.
AP= Armor Points
You can always do at least 1 damage.

Death is permanent!

Stat display (blue/white window) :
  Name: name
    HP: current HP
 MaxHP: maximum HP
    MP: current MP
 MaxMP: maximum MP
   STR: Strength
   DEF: Defense
   MAG: Magic
  Wait: current wait/max wait
 Staus: current status effect, if any
    AP: Armor Points
    LV: Level
    XP: experience
 NxtLv: experience needed for level up

Sidebar (green window) :
 Version of game being played
 Current time
 Turn number (time left in this turn)

 Summary of last three turns, displaying:
  Amount of damage dealt to enemy, HP/MP healed
  Amount of damage taken from enemy, HP/MP enemy healed
  If an enemy was killed
  
============================================================================

The_Game: A Game For Munchkins!

Copyright 2012,2013 William Patrick McFadden

If you make modifications to the code, make it explict and obvious, and do
not claim authorship of the original code. Other than that, you are free
to do whatever you wish with it.

============================================================================

contact info:
e-mail  : wbkm16@yahoo.com
 * Not checked often.
