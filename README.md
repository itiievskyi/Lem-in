# Lem-in

The program receives the data describing the ant farm from the standard output in the following format:
* number_of_ants
* the_rooms
* the_links

```
##start
1 23 3
2 16 7
#comment
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
#another comment
```
which corresponds to the following representation:
![Farm](/images/2.png)

The goal of this project is to **find the quickest way to get n ants across the farm**. Quickest way means the solution with the least number of lines, respecting the
output format requested below:
```
number_of_ants
the_rooms
the_links

Lx-y Lz-w Lr-o ...
```
x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y, w, o represents the rooms’ names.

### How to use
* git clone https://github.com/itiievskyi/Lem-in.git ~/lem-in/
* cd ~/lem-in/
* make
* ./lem-in [< file]

If you use standard input, press Ctrl+D after the last instruction.

Use "color" as the last argument to produce the colored output:

![Valid output with colors](/images/1.png)

### Enjoy!
