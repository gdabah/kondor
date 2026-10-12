/*
 __________________________
/       |  CHECK  |        \
+---+-------------+--------+
| N |    FNAME    | MALLOC |
+---+-------------+--------+
| 1	|	AI          |   V    |
| 2	|	FONT        |   V    |
| 3	|	LAYERS			|  X-WAS |
| 4	|	LOADMAP			|   V    |
| 5	|	*GETVIRSCR* |   V    |
| 6	|	SCROLL			|   V    |
| 7	|	SOUND			  |   V    |
+---+-------------+--------+
| - |    -----    | IMAGES |
|---+-------------+--------+
| 1 | FTIMAGES    | X-NO_N |
| 2 | IMAGES      |   V    |
| 3 | MEUNPIX     |   V    |
+---+-------------+--------+
| - |    -----    |  I/O   |
+---+-------------+--------+
| 1 | FONT        |   V    | "qsoft.fnt"
| 2 | LOADMAP     |   V    | *.maps
| 3 | OPTIONS     |   V    | "FUNTANK.CFG"
| 4 | PAL         |   V    | "pal.dat"
| 5 | SCROLL      |   V    | "images.dat" "menu.dat"
| 6 | SOUND       |   V    |  *.wavs
+-----------------+--------+