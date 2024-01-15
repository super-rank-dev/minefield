========================================================================
    CONSOLE APPLICATION : Minefield Project Overview

	ZOS Software Engineer Applicant Test 2.6.0
========================================================================

=================================================================================
Overview:
=================================================================================

This application consists of a large number of mine objects that have a unique identifier, a position,
a team and can be marked as active or invulnerable.

Each loop, all active mines find what other non-invulnerable mines are within their blast radius
(i.e. what other mines would be damaged if it exploded).  Then, for each team, the active mine with the most enemy targets is chosen and exploded.

Friendly fire is on (an exploding mine will damage both enemy and friendly targets within its destructive radius).

Inactive mines cannot be exploded, however they can be damaged by other mines. Invulnerable can be exploded, but not damaged by other mines.

This continues until a round occurs in which each team no longer has targetable enemy mines.

The team with the most remaining mines is declared the winner.


=================================================================================
Objectives:
=================================================================================


1) Make sure the code compiles cleanly
2) Get the code to run (it does not run successfully right off the bat)
3) Verify that the code is accomplishing its main goal correctly
4) Look to enforce defensive programming
5) Complete Additional Feature based on your surname
6) Look for ways to optimize the code for both performance and memory usage, there are significant gains that can be made in performance
7) Follow Submission Requirements listed below

In a real working environment, you'd be able to ask the design intent behind how certain things work. You don't
have that luxury doing this test. If there are certain things that really bug you or you're unsure how to proceed 
feel free to reach out to HR and ask for clarification. 

It's perfectly fine for you to identify the conundrum and pick what way you think it should be working. Again, document
your insight and choice.


=================================================================================
Additional Feature:
=================================================================================


Using the first letter of your surname as a key, implement one of the following feature additions:

A-F: Mines are now shielded.
		- Each mine starts with a shield that has 100 health. 
        - There is a 20% chance that a shield may begin with double health.
        - The shield will regenerate 50 health at the start of its team's turn, up to the initial starting health.  
        - A shield with no health remaining is destroyed and cannot regenerate.
 
G-L: A Random Hotspot will now appear on the minefield to give Losing teams an advantage.
        - The hotspot will appear in a random location within the minefield for 3 game turns before changing location and type. This repeats for the duration of the game.
		- Its center and type are determined randomly, however its radius is always 200 units. A hotspot can only be a single type at any given time.
		- Depending on the hotspot's type, it will modify and override the attributes of all mines contained within its radius for those game turns. The types are as follows:
			1) For all contained mines on a Losing team, they are made Invulnerable. The Winning team's mines are unaffected.
			2) For all contained mines that are on the Winning team, they are made Inactive. Losing team's mines are unaffected.
			3) For all contained mines on a Losing team, their destructive radius is doubled. The Winning team's mines are unaffected.
		-After a hotspot has expired and changed location/type, all mines no longer within its radius with modified and overridden attributes revert back to pre-hotspot values.
 
M-R: Mines can now provide stealth to other allied mines.
        - There is a 5% chance that a mine will provide stealth for allied mines within 200% of its destructive radius. 
        - Allied mines within the stealth radius will not be picked up in a targeting pass (similar to how invulnerable mines are ignored). 
        - While stealth mines aren’t targeted, they can still be damaged if within the destructive radius of an exploding mine.
        - Once a mine providing stealth is destroyed, allied mines within the radius are no longer provided with stealth.

S-Z: Mines now have a new type: Cluster Mines. 
        - Upon being exploded, cluster mines release 3 smaller mines, which are dispersed randomly within the mine’s blast radius. 
        - The submunitions are designed to explode and cause damage upon impact(during the same game turn) but have a 15% chance of misfiring and becoming inactive mines on the minefield. 
        - The cluster mine itself is always active but does not cause damage upon detonation, only it’s submunitions.
        - The submunitions' destructive range, explosive yield and health are 50% of that of the parent cluster mine.
        - Each team gets an equal amount, in which 5% of their total mines are cluster mines.



Feel free to design and implement this new feature in whatever way you deem most suitable.

Again, it's perfectly fine(and expected) for you to identify design conundrums and pick what way you think it should be working. 
There is no right or wrong design choices, as long as the technical implementation is correct, efficient and you document your choice.


=================================================================================
Submission Requirements:
=================================================================================


The C++ standard used in this project is currently C++14, however usage of C++17 or later is permitted. Look to use and update to Modern C++ best practices if that is something
you have experience in.

It is preferred that Visual Studio 2022 is used as your development environment.  Visual Studio
Community 2022 can be downloaded free from:
http://www.visualstudio.com/en-us/downloads/
A makefile is provided if you are compiling on linux.
If another development environment is used, please provide details.

Note any and all performance tools and techniques used.

When returning your completed test, please make sure to remove any compiled binary files to allow the test to be attached in the return email.
If any supporting documentation cannot be attached to an email, please provide a link to a secure storage space online.

Please comment changes and alterations to the code. Feel free to document your work and progress in the comment
notes section at the top of Minefield.cpp. In general, the more insight you provide into your work the better.
If you try alternative approaches, even if they don't work out the way you hope, be sure to document the decision making
you made along the way.

Make sure that your name, the date you did this test and the amount of time taken are marked in Minefield.cpp.

Try to stick to the code convention that you find in the existing code.  Feel free to fix any inconsistencies.

=================================================================================
Result Examples:
=================================================================================


The results below are provided as a guide, not as something you need to ultimately match. Saying that, you should be able to replicate them after initially getting the code to compile 
and fixing any crashes. When you start to refactor or make significant changes to the code, then the results will NOT match up. 
So if you consider matching the results below to be an important first step, focus on that early before making any major changes. 

Getting the exact results provided below is not a requirement to ‘pass’ the test. We are far more interested in code fixes, cleanup, style, improvements, issues uncovered, performance considerations, etc.
Focus on things that you are unhappy with in the code, its layout and structure, then explain your rationale for making those changes.

Do not modify the existing four command line input parameters used.  Feel free to add additional command line
inputs if needed, but make sure they are not required.

The four command line parameters are: <random seed> <number of worker threads> <number of teams> <number of mines per team>

With the following input parameters: 987654 1 3 500
Object id 1071 position (-755.938, 93.133, -556.052) active Y invulnerable N
Object id 275 position (266.852, -32.735, 970.941) active Y invulnerable N
Object id 934 position (570.726, -275.077, -346.969) active N invulnerable N
Object id 1863 position (903.713, -300.514, 338.788) active Y invulnerable Y
Object id 3885 position (331.019, 376.530, 101.836) active Y invulnerable N
Object id 1470 position (-924.728, 20.487, -262.222) active Y invulnerable N
Object id 3201 position (379.957, 81.881, 458.886) active Y invulnerable N
Object id 2538 position (-119.712, -5.246, -345.135) active Y invulnerable N
Object id 455 position (-610.912, -547.901, -254.453) active Y invulnerable N
Object id 2465 position (429.587, -295.623, -74.395) active Y invulnerable N
Turn 1: Team 0 picks Mine with object id 2540 (with 2 targets) to explode
Turn 1: Team 1 picks Mine with object id 1104 (with 3 targets) to explode
Turn 1: Team 2 picks Mine with object id 553 (with 2 targets) to explode
Turn 2: Team 0 picks Mine with object id 2223 (with 2 targets) to explode
Turn 2: Team 1 picks Mine with object id 358 (with 3 targets) to explode
Turn 2: Team 2 picks Mine with object id 581 (with 2 targets) to explode
Turn 3: Team 0 picks Mine with object id 2466 (with 1 targets) to explode
Turn 3: Team 1 picks Mine with object id 4973 (with 2 targets) to explode
Turn 3: Team 2 picks Mine with object id 4548 (with 2 targets) to explode
Turn 4: Team 0 picks Mine with object id 53 (with 1 targets) to explode
Turn 4: Team 1 picks Mine with object id 4247 (with 2 targets) to explode
Turn 4: Team 2 picks Mine with object id 3923 (with 1 targets) to explode
Team 0 has 357 mines remaining
Team 1 has 385 mines remaining
Team 2 has 424 mines remaining
Team 2 WINS after 41 turns!!

With the following input parameters: 456 16 3 1000
Object id 5241 position (-502.488, 960.968, -673.866) active Y invulnerable N
Object id 8308 position (-429.672, 251.257, -690.690) active Y invulnerable N
Object id 9649 position (518.235, 635.312, -637.790) active Y invulnerable N
Object id 5054 position (-410.384, -226.540, -217.858) active Y invulnerable Y
Object id 2728 position (373.186, -937.465, -62.392) active Y invulnerable N
Object id 8632 position (-651.196, 446.681, 638.653) active Y invulnerable N
Object id 5008 position (893.620, 164.387, 108.439) active Y invulnerable N
Object id 7782 position (-93.770, -602.303, 213.354) active Y invulnerable Y
Object id 4858 position (-599.576, 697.088, -730.733) active Y invulnerable N
Object id 507 position (698.314, 716.660, 750.904) active Y invulnerable N
Turn 1: Team 0 picks Mine with object id 3398 (with 3 targets) to explode
Turn 1: Team 1 picks Mine with object id 2609 (with 4 targets) to explode
Turn 1: Team 2 picks Mine with object id 5427 (with 3 targets) to explode
Turn 2: Team 0 picks Mine with object id 6725 (with 3 targets) to explode
Turn 2: Team 1 picks Mine with object id 8415 (with 3 targets) to explode
Turn 2: Team 2 picks Mine with object id 9307 (with 3 targets) to explode
Turn 3: Team 0 picks Mine with object id 4314 (with 3 targets) to explode
Turn 3: Team 1 picks Mine with object id 4372 (with 3 targets) to explode
Turn 3: Team 2 picks Mine with object id 5106 (with 3 targets) to explode
Turn 4: Team 0 picks Mine with object id 4800 (with 3 targets) to explode
Turn 4: Team 1 picks Mine with object id 553 (with 3 targets) to explode
Turn 4: Team 2 picks Mine with object id 8917 (with 3 targets) to explode
Team 0 has 623 mines remaining
Team 1 has 722 mines remaining
Team 2 has 773 mines remaining
Team 2 WINS after 115 turns!!

With the following input parameters: 654321 12 5 1500
Object id 8591 position (-898.894, -290.149, 50.030) active Y invulnerable N
Object id 7110 position (-303.245, 718.965, -516.425) active Y invulnerable N
Object id 1466 position (637.269, -285.511, -88.674) active Y invulnerable N
Object id 10286 position (-312.755, -866.798, -53.850) active Y invulnerable N
Object id 10766 position (316.465, 415.601, 571.089) active Y invulnerable N
Object id 3469 position (956.990, -160.174, -141.135) active Y invulnerable N
Object id 44 position (447.428, -995.504, 571.503) active N invulnerable N
Object id 14905 position (-256.135, -394.987, -613.572) active Y invulnerable N
Object id 14267 position (-446.510, -544.947, 657.727) active Y invulnerable N
Object id 7000 position (-123.204, -670.820, 631.414) active Y invulnerable N
Turn 1: Team 0 picks Mine with object id 1920 (with 6 targets) to explode
Turn 1: Team 1 picks Mine with object id 1678 (with 6 targets) to explode
Turn 1: Team 2 picks Mine with object id 7753 (with 6 targets) to explode
Turn 1: Team 3 picks Mine with object id 7578 (with 5 targets) to explode
Turn 1: Team 4 picks Mine with object id 11024 (with 8 targets) to explode
Turn 2: Team 0 picks Mine with object id 947 (with 5 targets) to explode
Turn 2: Team 1 picks Mine with object id 801 (with 6 targets) to explode
Turn 2: Team 2 picks Mine with object id 7181 (with 6 targets) to explode
Turn 2: Team 3 picks Mine with object id 1515 (with 4 targets) to explode
Turn 2: Team 4 picks Mine with object id 3190 (with 6 targets) to explode
Turn 3: Team 0 picks Mine with object id 13719 (with 5 targets) to explode
Turn 3: Team 1 picks Mine with object id 5827 (with 6 targets) to explode
Turn 3: Team 2 picks Mine with object id 9530 (with 6 targets) to explode
Turn 3: Team 3 picks Mine with object id 8955 (with 4 targets) to explode
Turn 3: Team 4 picks Mine with object id 9682 (with 5 targets) to explode
Turn 4: Team 0 picks Mine with object id 14543 (with 5 targets) to explode
Turn 4: Team 1 picks Mine with object id 10092 (with 6 targets) to explode
Turn 4: Team 2 picks Mine with object id 1466 (with 4 targets) to explode
Turn 4: Team 3 picks Mine with object id 13093 (with 4 targets) to explode
Turn 4: Team 4 picks Mine with object id 10741 (with 5 targets) to explode
Team 0 has 565 mines remaining
Team 1 has 574 mines remaining
Team 2 has 738 mines remaining
Team 3 has 814 mines remaining
Team 4 has 949 mines remaining
Team 4 WINS after 278 turns!!

These results were obtained on a Windows 10 PC, using the VS2022 toolsets.


////////////////////////////////End of ReadMe.txt, Good Luck!////////////////////////////////////////////
