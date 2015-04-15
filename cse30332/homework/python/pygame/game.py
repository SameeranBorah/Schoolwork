#John F. Lake, Jr. 


import pygame
import math

class Earth(pygame.sprite.Sprite):
	def __init__(self,gs=None):
		pygame.sprite.Sprite.__init__(self)
		self.gs = gs
		self.health = 100
		self.image = pygame.image.load("globe.png")
		self.redImage = pygame.image.load("globe_red100.png")
		self.explodeImages = []
		self.expFrame = 0
		self.isAlive = 1
		for i in range(0,17):
			if i < 10:
				self.ex = pygame.image.load("explosion/frames00%da.png" % i)
			else:
				self.ex = pygame.image.load("explosion/frames0%da.png" % i)

			self.explodeImages.append(self.ex)
				
		self.expRect = self.explodeImages[0].get_rect()
		self.expRect = self.expRect.move(400,300)
		self.rect = self.image.get_rect()
		self.rect = self.rect.move(300,300)
		self.redRect = self.redImage.get_rect()
		self.redRect = self.redRect.move(300,300)

	def tick(self):
		if self.health <=0:
			self.image = self.explodeImages[self.expFrame]
			self.expFrame = self.expFrame +1
			if self.expFrame > 15:
				self.expFrame = 0
				self.isAlive = 0
		
	
			










class Player(pygame.sprite.Sprite):
	def __init__(self,gs=None):
		pygame.sprite.Sprite.__init__(self)
		self.shootSound = pygame.mixer.Sound("screammachine.wav")
		self.gs = gs
		self.image = pygame.image.load("deathstar.png")
		self.rect = self.image.get_rect()
		cent = self.rect.center
		self.laser = pygame.image.load("laser.png")
		self.laserrect = self.laser.get_rect(center=cent)
		self.rect = self.rect.move(20,20)
		self.orig_image = self.image
		self.location = self.rect
		self.tofire = False
		self.laserX = 0
		self.laserY = 0
		self.velX = 0
		self.velY = 0

	def rotate(self):
		mx,my = pygame.mouse.get_pos()
		y = self.location.y + self.location.width/2
		x = self.location.x + self.location.height/2
		top = my-y
		bottom = mx-x
		if bottom == 0:
			bottom = 0.0001
		angle = math.degrees(math.atan2(top,bottom))+50
		oldcenter = self.rect.center
		self.image = pygame.transform.rotate(self.orig_image,angle*-1.0)
		self.rect = self.image.get_rect(center=oldcenter)



	def tick(self):
		for event in pygame.event.get():
			if event.type is pygame.KEYDOWN:
				if event.key == pygame.K_LEFT:
					self.velX = -5
				elif event.key == pygame.K_RIGHT:
					self.velX = 5
				elif event.key == pygame.K_UP:
					self.velY = -5
				elif event.key == pygame.K_DOWN:
					self.velY = 5
			elif event.type is pygame.KEYUP:
				if event.key == pygame.K_LEFT:
					self.velX = 0
				elif event.key == pygame.K_RIGHT:
					self.velX = 0
				elif event.key == pygame.K_UP:
					self.velY = 0
				elif event.key == pygame.K_DOWN:
					self.velY = 0
			elif event.type is pygame.MOUSEBUTTONDOWN:
				self.tofire = True
				self.center = self.rect.center 
				self.laserrect = self.laser.get_rect(center=self.center)
				self.laserdestX,self.laserdestY = pygame.mouse.get_pos()
				self.laserX = self.laserrect.x
				self.laserY = self.laserrect.y
				self.laserDX = (self.laserdestX-self.laserX)/20
				self.laserDY = (self.laserdestY-self.laserY)/20

			elif event.type is pygame.MOUSEBUTTONUP:
				self.tofire = False


		if self.tofire == True:
			#emit laser beam: 
			self.laserrect = self.laserrect.move(self.laserDX,self.laserDY)
			if self.laserrect.x>640:
				self.laserrect.x = 640
			elif self.laserrect.x<0:
				self.laserrect.x = 0
			if self.laserrect.y>480:
				self.laserrect.y = 480
			elif self.laserrect.y<0:
				self.laserrect.y = 0

			self.shootSound.play()
		else:

			#Rotate the death start
			self.location = self.rect
			if self.location.x <=0:
				self.location.x = 0
			elif self.location.y <=0:
				self.location.y = 0
			elif self.location.y >= 480 - self.location.height:
				self.location.y = 480-self.location.height
			elif self.location.x >= 640 -self.location.width:
				self.location.x = 640-self.location.width
			self.rotate()

			#Move the death star
			self.rect = self.rect.move(self.velX,self.velY)

			

				
class GameSpace:
	def main(self):
		#Initialize everything:
		pygame.init()
		pygame.mixer.init()
		explodeSound = pygame.mixer.Sound("explode.wav")
		self.size = self.width,self.height=640,480
		self.black = 0,0,0
		self.screen = pygame.display.set_mode(self.size)
		self.clock = pygame.time.Clock()
		self.player = Player(self)
		self.earth = Earth(self)


		while True:
			self.clock.tick(60)
			self.player.tick()
			self.screen.fill(self.black)
			self.screen.blit(self.player.image,self.player.rect)


			while self.player.tofire is True:
				self.screen.blit(self.player.laser,self.player.laserrect)
				if self.earth.health >= 50:
					self.screen.blit(self.earth.image,self.earth.rect)
				elif self.earth.health >=0:
					self.screen.blit(self.earth.redImage,self.earth.redRect)
				self.player.tick()
				if self.player.laserrect.colliderect(self.earth.rect):
					self.earth.health = self.earth.health -1
				pygame.display.flip()
				if self.earth.health <=0 and self.earth.isAlive:
					explodeSound.play()
					self.screen.fill(self.black)
					self.screen.blit(self.player.image,self.player.rect)
					self.screen.blit(self.player.laser,self.player.laserrect)
					self.screen.blit(self.earth.image,self.earth.expRect)
					pygame.display.flip()
					self.earth.tick()

			
			if self.earth.health >= 50:
				self.screen.blit(self.earth.image,self.earth.rect)
			elif self.earth.health >=0:
				self.screen.blit(self.earth.redImage,self.earth.redRect)
			elif self.earth.isAlive:
				self.screen.blit(self.earth.image,self.earth.expRect)
			self.earth.tick()
			pygame.display.flip()


if __name__ == '__main__':
	gs = GameSpace()
	gs.main()
