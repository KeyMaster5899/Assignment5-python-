import PKFW 		#petekeys framework
import pathfinding 	#astar and dijkstra
import v2 			#vector2
import ai 			#steering behaviours 
import kd 			#key definitions / global module
import random
import math

start = None
finish = []
walls = []
#sprites = {'startSID':None, 'finishSID':None, 'tileSID':None, 'wallSID':None, 'pathSID':None, 'boidSID':None }
sprites = []
class LevelGrid:
	def __init__(self, tileSize):
		reload(pathfinding)
		reload(ai)
		reload(v2)
		reload(kd)
		
		#sprites['tileSID'] = PKFW.spcr("./images/grey.png", tileSize['width'], tileSize['height'])
		#sprites['startSID'] = PKFW.spcr("./images/blue.png", tileSize['width'], tileSize['height'])
		#sprites['finishSID'] = PKFW.spcr("./images/green.png", tileSize['width'], tileSize['height'])
		#sprites['wallSID'] = PKFW.spcr("./images/red.png", tileSize['width'], tileSize['height'])
		#sprites['pathSID'] = PKFW.spcr("./images/purple.png",tileSize['width'], tileSize['height'])
		#sprites['boidSID'] = PKFW.spcr("./images/reds.png", 32,32)
		sprites.append(PKFW.spcr("./images/grey.png", tileSize['width'], tileSize['height']))
		sprites.append(PKFW.spcr("./images/blue.png", tileSize['width'], tileSize['height']))
		sprites.append(PKFW.spcr("./images/green.png", tileSize['width'], tileSize['height']))
		sprites.append(PKFW.spcr("./images/red.png", tileSize['width'], tileSize['height']))
		sprites.append(PKFW.spcr("./images/purple.png",tileSize['width'], tileSize['height']))
		sprites.append(PKFW.spcr("./images/reds.png", 32,32))
		
		self.wanderers = []
		self.flock = None
		self.path = None
		
		self.buttonpressed = [False]*5
		self.screenProps = kd.sp
		self.tileSize = tileSize
		self.levelSize = {'x':self.screenProps['width']/self.tileSize['width'], 'y':self.screenProps['height']/self.tileSize['height']}
		self.levelTiles = [[None]*self.levelSize['y'] for i in range(self.levelSize['x'])]
		
		#initialising levelTiles grid with new tiles
		#small random portion of tiles set to walls 
		#outer edges of tiles set to wall (not needed but included to avoid boid boundries)
		for x in range(len(self.levelTiles)):
			for y in range(len(self.levelTiles[x])):
				self.levelTiles[x][y] = Tile()
				if(random.random()>0.20) or ((x>10 and x<14) and (y>4 and y<9)):
					self.levelTiles[x][y].setS(sprites[0])
				else:		
					self.levelTiles[x][y].setS(sprites[3])
					
				self.levelTiles[x][y].pos.x = (self.tileSize['width']) * x%self.screenProps['width']+ (tileSize['width']*0.5)
				self.levelTiles[x][y].pos.y = (self.tileSize['height']) * y%self.screenProps['height']+ (tileSize['width']*0.5)
				self.levelTiles[x][y].gpos['x'] = x
				self.levelTiles[x][y].gpos['y'] = y
				if(not x or not y) or (x is self.levelSize['x']-1 or y is self.levelSize['y']-1):
					self.levelTiles[x][y].setS(sprites[3])
		
		#initialising 10 boid wanderers 
		for i in range(10):
			rx = random.randint(kd.sp['width']*0.5-64,kd.sp['width']*0.5+64)
			ry = random.randint(kd.sp['height']*0.5-72,kd.sp['height']*0.5+72)
			self.wanderers.append(ai.boid(rx, ry, 32, sprites[5]))
			
	def LevelGridDraw(self):
		for x in range(len(self.levelTiles)):
			for y in range(len(self.levelTiles[x])):
				if(self.levelTiles[x][y].Sid != -1):
					PKFW.spmo(self.levelTiles[x][y].Sid,self.levelTiles[x][y].pos.x, self.levelTiles[x][y].pos.y )
					PKFW.spdr(self.levelTiles[x][y].Sid)	
		
		for i in range(len(self.wanderers)):
			self.wanderers[i].obstacleAvoid(walls)
			self.wanderers[i].update()
			self.wanderers[i].draw()
			if(math.isnan(self.wanderers[i].position.x) or math.isnan(self.wanderers[i].position.y)):
				# on rare occasions the boid position and steering becomes NAN due to being too close to too many 
				# walls... I am not sure why this is happening and have implemented a half fix which just
				# re initialises the boid if this happens
				self.wanderers[i] = ai.boid(kd.sp['width']*0.5, kd.sp['height']*0.5, 64, sprites[5])
		
		if(self.flock is not None):
			self.flock.update()
		
	def LevelGridUpdate(self):
		mx, my = PKFW.gtmp() #mouse x and y
		tx = int(mx/self.tileSize['width'])
		ty = int(my/self.tileSize['height'])	#current tile mouse is over

		if(tx<0):tx=0
		if(ty<0):ty=0
		if(tx>self.levelSize['x']-1):
			tx = self.levelSize['x']-1
		if(ty>self.levelSize['y']-1):
			ty = self.levelSize['y']-1	#current tile mouse is over window clamp	
				

		#left mouse button sets tile to start
		#right mouse button sets tile to wall
		#middle mouse button sets tile to blank				
		if(PKFW.gmpr(0) and self.buttonpressed[0] is False):
			self.buttonpressed[0] = True
			self.levelTiles[tx][ty].setS(sprites[1])
		self.buttonpressed[0] = not PKFW.gtmr(0)
		if(PKFW.gmpr(1)):
			self.levelTiles[tx][ty].setS(sprites[3])
		if(PKFW.gmpr(2)):
			self.levelTiles[tx][ty].setS(sprites[0])
		

		#if the start exists and there is only one finish and the 'a' key is pressed
		#astar runs and sets the tiles in the returned path to the path sprite	
		if isinstance(start, Tile) and len(finish)==1 and PKFW.gtkp(65) and self.buttonpressed[1] is False: 
			self.buttonpressed[1] = True
			self.path = pathfinding.astar(start, finish[0], self.levelTiles, self.levelSize)
			if(isinstance(self.path, list)):
				for i in range(len(self.path)):
					self.path[i].setS(sprites[4])
		self.buttonpressed[1] = not PKFW.gtkr(65)
		
		#if the start exists and there is at least 1 finish and the 'd' key is pressed
		#dijkstra runs (path tiles sprite set to path)
		if isinstance(start, Tile) and len(finish)>0 and PKFW.gtkp(68) and self.buttonpressed[2] is False:
			self.buttonpressed[2] = True
			self.path = pathfinding.dijkstra(start, finish, self.levelTiles, self.levelSize)
			if(isinstance(self.path,list)):
				for i in range(len(self.path)):
					self.path[i].setS(sprites[4])
		self.buttonpressed[2] = not PKFW.gtkr(68)

		#checks if path is a list
		#if so then delete all the elements and set to None
		#in case previous tiles from previous paths are left over when attempting new path
		
		if(isinstance(self.path,list)):
			for i in range(len(self.path)):
				self.path[i].resetTile()
			del self.path[:]
			self.path = None
			
		
		#when the 'c' button is pressed all the tiles that are not walls are set to blank tiles
		if(PKFW.gtkp(67)):
			for x in range(len(self.levelTiles)):
				for y in range(len(self.levelTiles[x])):
					if(self.levelTiles[x][y].Sid != sprites[3]):
						self.levelTiles[x][y].resetTile()
						self.levelTiles[x][y].setS(sprites[0])


		#the f1 button clears all the wanderes and tiles and initialises the flock class
		#to return to the wanderers and tiles press ESC
		if(PKFW.gtkp(kd.keys['F1']) and self.buttonpressed[3] is False):
			self.buttonpressed[3] = True
			self.flock = ai.flock(30, sprites[5])
			for i in range (len(self.wanderers)):
				del self.wanderers[:]
			for x in range(len(self.levelTiles)):
				for y in range(len(self.levelTiles[x])):
					self.levelTiles[x][y].setS(sprites[0])
		self.buttonpressed[3] = not PKFW.gtkr(kd.keys['F1'])


		#pressing f12 sets debug to !debug
		#used when creating boid steering behaviours
		if(PKFW.gtkp(kd.keys['F12']) and self.buttonpressed[4] is False):
			self.buttonpressed[4] = True
			kd.debug = not kd.debug
		self.buttonpressed[4] = not PKFW.gtkr(kd.keys['F12'])
		
	def cs(self):
		global sprites
		PKFW.spde(sprites[0])
		PKFW.spde(sprites[1])
		PKFW.spde(sprites[2])
		PKFW.spde(sprites[3])
		PKFW.spde(sprites[4])
		PKFW.spde(sprites[5])
		
		del sprites[:]
		
class Tile:
	def __init__(self):
		self.Sid = -1
		self.pos = v2.vector2(0,0)
		self.gpos = {'x':0,'y':0} #was using dictionaries before i created a vector2 py script ## should replace with vector
		self.reachable = 1
		self.parent=None
		self.Gscore=0
		self.Fscore=0
		self.Hscore=0
	def __repr__(self):
		return 'tile: %s, %s' % (self.pos.x, self.pos.y)
	def resetTile(self):
		self.reachable=1
		self.parent=None
		self.Gscore=0
		self.Fscore=0
		self.Hscore=0
	def setH(self, h):
		self.Hscore = h
	def setG(self, g):
		self.Gscore = g
	def setF(self, f):
		self.Fscore = f
	def setP(self, p):
		self.parent = p
	def setS(self, sid):
		global sprites
		global start
		if (sid==sprites[1] and start==None):
			start=self
		elif (sid==sprites[1] and start!=None):
			sid = sprites[2]
		if(self.Sid == sprites[1] and sid!=sprites[1] and start!=None):
			start = None	
			
		global finish
		if(sid==sprites[2]):
			if(self not in finish):
				finish.append(self)
		elif(sid!=sprites[2]): 
			if(self.Sid==sprites[2]):
				finish.remove(self)
				
		global walls
		if(sid==sprites[3]):
			if(self not in walls):
				walls.append(self)
			self.reachable = 0
		else:
			if(self in walls):
				walls.remove(self)
			self.reachable = 1
		self.Sid = sid