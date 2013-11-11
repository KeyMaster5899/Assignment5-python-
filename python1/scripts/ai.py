import PKFW
import v2
import math
import random
import kd
import time

MAXVEL = 1
MAXFOR = 0.6
MAXSPD = MAXVEL
CIRCDIS = 20
CIRCRAD = 10
ANGLECHANGE = 0.35
MAXAVOIDAHEAD = 32
AVOIDFOR = 0.15 ###!!!### CANNOT BE ABOVE 0.3 ###!!!###

class boid:
	def __init__(self, x, y, m, s):
		self.position = v2.vector2(x,y)
		self.velocity = v2.vector2(0,0)
		self.target = v2.vector2(0,0)
		self.desired = None
		self.steering = v2.vector2(0,0)
		self.avoidance = v2.vector2(0,0)
		self.mass = m
		self.sprite = s
		
		self.wanderAngle = random.randint(-4,4)
		
	def update(self):
	
		self.steering = self.mintrunc(self.steering + self.avoidance, MAXFOR)
		self.steering = self.steering / self.mass
		self.velocity = self.maxtrunc(self.velocity + self.steering, MAXSPD)
		
		self.position = self.position + self.velocity
	
		if(self.position.x < 0):self.position.x = kd.sp['width']
		if(self.position.x > kd.sp['width']):self.position.x = 0
		if(self.position.y < 0):self.position.y = kd.sp['height'] 
		if(self.position.y > kd.sp['height']):self.position.y = 0
		
		PKFW.spmo(self.sprite,self.position.x, self.position.y)
		
	def draw(self):
		PKFW.spdr(self.sprite)
		
	def maxtrunc(self, v, max):
		i = v.mag() / max
		if(i<1.0):i=1.0 
		else:i=1/i
		v = v * i	
		return v
	def mintrunc(self, v, max):
		i =v.mag()/ max
		if(i<1.0):i=1.0 
		v = v * i	
		return v
		
	def seek(self, target):	
		self.target = target
				
		self.desired = (self.target - self.position).norm() * MAXVEL
		
		self.steering = self.desired - self.velocity
		
	def flee(self, target):
		self.target = target
				
		self.desired = (self.position - self.target).norm() * MAXVEL
		
		self.steering = self.desired - self.velocity
				
	def arrive(self, target):
		self.target = target
		slowingrad = 256
		self.desired = (self.target - self.position)
		dist = self.desired.mag()
		
		if(dist<=slowingrad):
			self.desired = (self.desired).norm() * MAXVEL * dist / slowingrad
		else:
			self.desired = (self.desired).norm() * MAXVEL
		
		self.steering = self.desired - self.velocity
	
	def PursueEvade(self, target, pursuit):
		toTarget = target.position - self.position
		updatesNeeded = toTarget.mag() / MAXVEL
		futurePosition = target.position + target.velocity * updatesNeeded
		if(pursuit):
			self.seek(futurePosition)
		else:
			self.flee(futurePosition)
		
	def wander(self):
		circCent = self.velocity
		cricCent = circCent.norm()
		circCent = circCent * CIRCDIS
			
		displac = v2.vector2(1,1)
		displac = displac * CIRCRAD
		len = displac.mag()
		
		displac.x = math.cos(self.wanderAngle) * len  * 0.1
		displac.y = math.sin(self.wanderAngle) * len  * 0.1
		
		r = random.random() 
		
		self.wanderAngle = self.wanderAngle + r * ANGLECHANGE - ANGLECHANGE * 0.5
		print(self.wanderAngle);
		self.steering = circCent + displac
		
	def obstacleAvoid(self, obstacles):
		self.avoidance = v2.vector2(0,0)
		tv = self.velocity
		tv.norm()
		tv = tv * MAXAVOIDAHEAD
		ahead = self.position + tv
		mostThreatening = None
		
		for i in range(len(obstacles)):
			obstacle = obstacles[i]
			
			if((obstacle.pos - self.position).mag()>96):
				continue
			else:
				if(kd.debug):
					PKFW.drln(self.position.x, self.position.y, obstacle.pos.x, obstacle.pos.y, 0,0,1)
				
			coll = self.lineIntersection(self.position, ahead, obstacle)
			if(coll and ((mostThreatening is None) or (self.position.distance(obstacle.pos) < self.position.distance(mostThreatening.pos)))):
				mostThreatening = obstacle
		
		if(mostThreatening is not None):
			self.avoidance = ahead - mostThreatening.pos
			self.avoidance.norm()
			self.avoidance = self.avoidance * AVOIDFOR
		else:
			self.wander()
				

	def lineIntersection(self, pos, ahead, obstacle):
		tv = self.velocity
		tv.norm()
		tv = tv * MAXAVOIDAHEAD * 0.75
		
		ahead2 = self.position + tv
		if(kd.debug):
			PKFW.drln(self.position.x, self.position.y, ahead.x, ahead.y, 1,0,1)
			PKFW.drln(self.position.x, self.position.y, ahead2.x, ahead2.y, 1,1,0)
		n = 52
		if(kd.debug):
			for t in range(n)[::3]:
				th = 2* math.pi * t/n
				th1 = 2* math.pi * (t+1)/n
				v = v2.vector2(n*math.cos(th), n*math.sin(th))
				v1 = v2.vector2(n*math.cos(th1), n*math.sin(th1))
				if(obstacle.gpos['x']>0 and obstacle.gpos['y']>0):
					PKFW.drln(obstacle.pos.x+v.x, obstacle.pos.y+v.y, obstacle.pos.x+v1.x, obstacle.pos.y+v1.y, 1,1,1)
		return (obstacle.pos.distance(ahead)<=n) or (obstacle.pos.distance(ahead2)<=n)

class flock:
	def __init__(self, numBoids, bs):
		self.boids = []
		for i in range(numBoids):
			rx = random.randint(100, 1500)
			ry = random.randint(50, 850)
			self.boids.append(boid(rx, ry, 100, bs))
		
	def update(self):
		for i in range(len(self.boids)):
			v1 = self.rule1(self.boids[i])
			v2 = self.rule2(self.boids[i])
			v3 = self.rule3(self.boids[i])
			
			self.boids[i].velocity = self.boids[i].velocity + v1 + v2 + v3
			self.boids[i].update()
			self.boids[i].draw()
			
	def rule1(self, aBoid):
		t = v2.vector2(0,0)
		for i in range(len(self.boids)):
			if(self.boids[i] is not aBoid):
				t = t + self.boids[i].position
				
		t = t /(len(self.boids)-1)
		return ((t - aBoid.position) / (len(self.boids)*15))
	
	def rule2(self, aBoid):
		t = v2.vector2(0,0)
		for i in range(len(self.boids)):
			if(self.boids[i] is not aBoid):
				d = self.boids[i].position - aBoid.position
				if(d.mag() <= 30):
					t = t - d*2
		return t
	
	def rule3(self, aBoid):
		t = v2.vector2(0,0)
		for i in range(len(self.boids)):
			if(self.boids[i] is not aBoid):
				t = t + self.boids[i].velocity
		t = t / (len(self.boids)-1)
		return (t - aBoid.velocity)
			