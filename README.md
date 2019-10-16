# Corewar


*  Corewar is a game, a very special game. It consists in making small programs fight in a virtual machine.
*  The project is split in two main parts : 
    * <b>The assembler</b> : It will allow you to write programs destined to fight. It will need to understand the assembly language, and generate a binary programs that can be interpreted by the virtual machine.
    * <b>The virtual machine</b> :  It will house the binary programs (the champions) and provide them with a standard execution environment, It offers a lot of features useful to the fight.

## Dependencies
```
sdl2 sdl2_ttf sdl2_image sdl2_mixer
```

## Compilation & Usage

```
~ git clone https://gitlab.com/lperron/corewar.git
~ cd corewar/
~ make
```
Then to use asm :

```
~ cd ./asm/
~ ./asm champ.s
```

And to use the VM :

```
~ cd ./corewar/
~ ./corewar [-vg] [-d nbr_cycles] [[-n number] champion1.cor]
```
<p> Our VM offers various options : </p>

| option |  |
| :---   | :---:|
| -v     | activates the verbose mode |
| -g     | launches the graphical interface     |
| -d nbr\_cycles   | dumps the memory at nbr_cycles and exits the game|
| -n  number | manually assigns the number of the champ ID |


## Graphical Interface

Our project comes with a SDL-made tron-inspired glossy and classy GUI to fully enjoy the fights. Furthermore it has a memory and processes explorer which will allow you to understand what's really happening inside the VM.
It can be really helpful since one of the major difficulties of this project is to figure out how the virtual machine works. <br> Plus the GUI is kind of groovy. So, while you're working on corewar you can also develop your dance skills!
 💃🕺
<br>

| key |  |
| :---   | :---:|
| +     | speed up the game (limit at X64) |
| -     | slow down the game (limit at 1/64)     |
| space | pause the game and enter the explorer mode|
| esc | exit the game |
| mouse | the mouse is used to query informations about a memory location or a process |
| scroll | in the processes explorer, scroll is used to navigate through the different processes on the same memory location|
| mouse click | in the processes explorer, click is used to view the next page of informations about a process|
 
## Screenshots

 <figure>
  <img src="https://gitlab.com/lperron/corewar/raw/master/screenshots/CorewarInstr.png" alt="Memory explorer" style="width:100%">
  <figcaption>Memory explorer</figcaption>
</figure>

 <figure>
  <img src="https://gitlab.com/lperron/corewar/raw/master/screenshots/CorewarProc1.png" alt="Process explorer (general)" style="width:100%">
  <figcaption>Process explorer (general)</figcaption>
</figure> 

 <figure>
  <img src="https://gitlab.com/lperron/corewar/raw/master/screenshots/CorewarProc2.png" alt="Process explorer (registers)" style="width:100%">
  <figcaption>Process explorer (registers)</figcaption>
</figure> 

# Video

<figure>
  <img src="https://gitlab.com/lperron/files_for_other_projects/raw/master/DemoCorewar.mp4" alt="Corewar's graphical interface using SDL" style="width:100%">
</figure> 
