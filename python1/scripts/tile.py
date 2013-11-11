import grid
class Tile:
	def __init__(self):
		self.state = 1
		self.pos = {'x':0,'y':0}
		self.gpos = {'x':0,'y':0}
		self.parent=None
		self.Gscore=0
		self.Fscore=0
		self.Hscore=0
		
	def setState(self, st):
		if(self.state==2 and st!=2): 
			start = None
		if(st==2 and start==None):
			grid.start = self
		elif(st==2 and start!=None):
			st=st+1
			
		global finish
		if(st==3):
			finish.append(self)
		if(self.state==3 and (st!=3 or st!=5)): 
			finish.remove(self)
		if(self.state==3 and st==4):
			st=6
		if(self.state==4 and st!=4):
			st=1
		if(st>5):
			st = 1
		self.state = st