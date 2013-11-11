import math
class vector2:
	def __init__(self, x, y):
		self.x = float(x)
		self.y = float(y)
	
	def __repr__(self):
		return '%s, %s' % (self.x, self.y)
	def mag(self):
		return math.sqrt((self.x * self.x)+(self.y*self.y))
		
	def norm(self):
		m=self.mag()
		if(m<1):m=1
		nx = self.x/m
		ny = self.y/m
		return vector2(nx,ny)
		
	def distance(self, other):
		nv = self-other
		return nv.mag()
	
	def __add__(self, other):
		if(isinstance(other, vector2)):
			nx = self.x + other.x
			ny = self.y + other.y
		elif isinstance(other, (int, float, long)):
			nx = self.x + other
			ny = self.y + other
		return vector2(nx,ny)
	
	def __sub__(self, other):
		if(isinstance(other, vector2)):
			nx = self.x - other.x
			ny = self.y - other.y
		elif isinstance(other, (int, float, long)):
			nx = self.x - other
			ny = self.y - other
		return vector2(nx,ny)
		
	def __mul__(self, other):
		if(isinstance(other, vector2)):
			nx = self.x * other.x
			ny = self.y * other.y
		elif isinstance(other, (int, float, long)):
			nx = self.x * other
			ny = self.y * other
		return vector2(nx,ny)
			
	def __div__(self, other):
		nx = self.x
		ny = self.y
		if(isinstance(other, vector2)):
			if(other.x!=0):
				nx = self.x / other.x
			if(other.y!=0):
				ny = self.y / other.y
		elif isinstance(other, (int, float, long)):
			if(other!=0):
				nx = self.x / other
				ny = self.y / other
		return vector2(nx,ny)
				
	def __neg__(self):
		return vector2(-self.x, -self.y)