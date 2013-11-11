import grid #tile class operations ## should have a seperate tile.py... needs fixing
import v2
from operator import attrgetter

def astar(start, end, levelTiles, levelSize):
		current = None
		openList = [start]
		closedList = []
		
		#sets all the tiles H scores to manhattan heuristic
		for x in range(len(levelTiles)):
			for y in range(len(levelTiles[x])):
				tile = levelTiles[x][y]
				tile.setH(10*(abs(tile.gpos['x']-end.gpos['x']) + abs(tile.gpos['y']-end.gpos['y'])))
				
		while len(openList):
			openList = sorted(openList, key=attrgetter('Fscore'))
			current = openList[0]
			openList.pop(0)
			closedList.append(current)
			#current is lowest F in open then removed from open then added to closed lists
			if(current.gpos['x']==end.gpos['x'] and current.gpos['y']==end.gpos['y']):
				return reconPath(current)
			for x in range(-1,2):
				for y in range(-1,2):
					if(x or y):
						gx=current.gpos['x']+x
						gy=current.gpos['y']+y
						if(gx<0) or (gy<0) or (gx>levelSize['x']-1) or (gy>levelSize['y']-1) or (levelTiles[gx][gy].reachable is not 1):
							continue
							
						tile = levelTiles[gx][gy]#each neighbour of the current
						
						if(tile.pos.x!=current.pos.x and tile.pos.y!=current.pos.y):
							tentativeGscore = current.Gscore + 14	#diagonal				
						else:
							tentativeGscore = current.Gscore + 10	#updownleftright
                        
						if (tile in closedList and tentativeGscore >= tile.Gscore):
							continue
						if (tile not in closedList or tentativeGscore < tile.Gscore):
							tile.setP(current)
							tile.setG(tentativeGscore)
							tile.setF(tile.Gscore + tile.Hscore)
							if(tile not in openList):
								openList.append(tile)

		print "astar fail"
		
def dijkstra(start, end, levelTiles, levelSize):
	current = None
	q = []

	#sets up the q with all the tiles G set to 
	for x in range(len(levelTiles)):
		for y in range(len(levelTiles[x])):
			levelTiles[x][y].Gscore = (levelSize['x'] * levelSize['x']) * (levelSize['y'] * levelSize['y']) 
			q.append(levelTiles[x][y])
	
	start.Gscore = 0
	
	while q:
		current = sorted(q, key=attrgetter('Gscore'))[0]
		q.remove(current)
		
		if(current in end):
			return reconPath(current)
		if(current.Gscore==(levelSize['x'] * levelSize['x']) * (levelSize['y'] * levelSize['y'])):
			print"dijkstra fail"
			return
		for x in range(-1,2):
			for y in range(-1,2):
				if(x or y):
					gx=current.gpos['x']+x
					gy=current.gpos['y']+y
					if(gx<0) or (gy<0) or (gx>levelSize['x']-1) or (gy>levelSize['y']-1) or (levelTiles[gx][gy].reachable is not 1):
						continue
					tile = levelTiles[gx][gy]	
					alt = current.Gscore + current.pos.distance(levelTiles[gx][gy].pos)
					if(alt<levelTiles[gx][gy].Gscore):
						levelTiles[gx][gy].Gscore = alt
						levelTiles[gx][gy].parent = current
						q = sorted(q, key=attrgetter('Gscore'))
	print"dijkstra fail"
	return
		
def reconPath(tile):
	path = []
	while(tile.parent is not None):
		path.append(tile)
		tile = tile.parent
	return path
	