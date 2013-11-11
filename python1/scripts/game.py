import PKFW
import grid
import kd

import time

tilegrid = None
tilesize = {'width':64, 'height':64}
def GameInit():#initialise game and globals
	PKFW.init(kd.sp['width'], kd.sp['height'])
	LevelGridInit()
	
def LevelGridInit():#initialises tile grid
	reload(grid)
	reload(kd)
	global tilegrid
	tilegrid = grid.LevelGrid(tilesize)
	
def GameUpdate():#main game loop 
	PKFW.upda()
	global tilegrid
	tilegrid.LevelGridUpdate()
	tilegrid.LevelGridDraw()

def c():
	global tilegrid
	tilegrid.cs()