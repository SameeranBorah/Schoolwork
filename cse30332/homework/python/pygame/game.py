#John F. Lake, Jr. 


import pygame
import math

class Earth(pygame.sprite.Sprite):
	def __init__(self,gs=None):
		pygame.sprite.Sprite.__init__(self)
		self.gs = gs
		self.image = pygame.image.load("globe.png")
		self.rect = self.image.get_rect()
		self.rect = self.rect.move(300,300)





class Player(pygame.sprite.Sprite):
	def __init__(self,gs=None):
		pygame.sprite.Sprite.__init__(self)
		self.gs = gs
		self.image = pygame.image.load("deathstar.png")
		self.rect = self.image.get_rect()
		self.rect = self.rect.move(20,20)
		self.orig_image = self.image
		self.location = self.rect
		self.tofire = False

	def rotate(self):
		mx,my = pygame.mouse.get_pos()
		if self.tofire == True:
			print "laser beam here."
		else:
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
					print "LEFT"
					self.rect = self.rect.move(-20,0)
				elif event.key == pygame.K_RIGHT:
					print "RIGHT"
					self.rect = self.rect.move(20,0)
				elif event.key == pygame.K_UP:
					print "UP"
					self.rect = self.rect.move(0,-20)
				elif event.key == pygame.K_DOWN:
					print "DOWN"
					self.rect = self.rect.move(0,20)
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
			

				
class GameSpace:
	def main(self):
		#Initialize everything:
		pygame.init()
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
			self.screen.blit(self.earth.image,self.earth.rect)
			pygame.display.flip()


if __name__ == '__main__':
	gs = GameSpace()
	gs.main()
