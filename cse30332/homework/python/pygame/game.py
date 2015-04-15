#John F. Lake, Jr. 
#pygame primer
#I just made an imitation of the death start destroying the earth


#All we need is pygame and some math: 
import pygame
import math

#Earth class: 
class Earth(pygame.sprite.Sprite):
	def __init__(self,gs=None):

		#Initialize the sprite with the images, the health & explosion frame: 
		pygame.sprite.Sprite.__init__(self)
		self.health = 100
		self.image = pygame.image.load("globe.png")
		self.redImage = pygame.image.load("globe_red100.png")
		self.explodeImages = []
		self.expFrame = 0

		#Boolean to tell if it's alive or not
		self.isAlive = 1

		#load into a list all of the explosion frames: 
		for i in range(0,17):
			if i < 10:
				self.ex = pygame.image.load("explosion/frames00%da.png" % i)
			else:
				self.ex = pygame.image.load("explosion/frames0%da.png" % i)
			self.explodeImages.append(self.ex)
				
		#Calculate the rects of the regular earth, the red earth, and the explosions:
		self.expRect = self.explodeImages[0].get_rect()
		self.expRect = self.expRect.move(400,300)
		self.expRect = self.expRect.inflate(200,0)
		self.rect = self.image.get_rect()
		self.rect = self.rect.move(300,300)
		self.redRect = self.redImage.get_rect()
		self.redRect = self.redRect.move(300,300)


	#Because the earth is mostly static, you just use the ticks for explosions:
	def tick(self):

		#If the earth is dead: 
		if self.health <=0 and self.isAlive:
			self.image = self.explodeImages[self.expFrame]

			#increment the frame of the explosion
			self.expFrame = self.expFrame +1

			#if the frame is outside of the allowed frames, just set the earth to dead: 
			if self.expFrame > 16:
				self.expFrame = 0
				self.isAlive = 0

#Player class: 
class Player(pygame.sprite.Sprite):
	def __init__(self,gs=None):

		#Initialize the sprite, sound, and images:
		pygame.sprite.Sprite.__init__(self)
		self.shootSound = pygame.mixer.Sound("screammachine.wav")
		self.image = pygame.image.load("deathstar.png")
		self.laser = pygame.image.load("laser.png")
		self.rect = self.image.get_rect()
		cent = self.rect.center
		self.laserrect = self.laser.get_rect(center=cent)
		self.laserX = 0
		self.laserY = 0
		self.rect = self.rect.move(20,20)

		#Original image, used for rotation calculation: 
		self.orig_image = self.image

		#Location/velocity of the death star:
		self.location = self.rect
		self.velX = 0
		self.velY = 0

		#Whether the death star is firing or not: 
		self.tofire = False


	#Function to rotate the death start to face the mouse:
	def rotate(self):

		#Get the mouse position: 
		mx,my = pygame.mouse.get_pos()
		y = self.location.y + self.location.width/2
		x = self.location.x + self.location.height/2
		top = my-y
		bottom = mx-x
		if bottom == 0:
			bottom = 0.0001

		#Find the angle: 
		angle = math.degrees(math.atan2(my-y,bottom))+50

		#Rotate the image around its center: 
		oldcenter = self.rect.center
		self.image = pygame.transform.rotate(self.orig_image,angle*-1.0)
		self.rect = self.image.get_rect(center=oldcenter)




	#Tick (alters movement and rotates the player)
	def tick(self):

		#User input: 
		for event in pygame.event.get():

			#If you press a key, move in that direction
			if event.type is pygame.KEYDOWN:
				if event.key == pygame.K_LEFT:
					self.velX = -5
				elif event.key == pygame.K_RIGHT:
					self.velX = 5
				elif event.key == pygame.K_UP:
					self.velY = -5
				elif event.key == pygame.K_DOWN:
					self.velY = 5
			#if you let up on a key in a direction, stop motion in that direction: 
			elif event.type is pygame.KEYUP:
				if event.key == pygame.K_LEFT:
					self.velX = 0
				elif event.key == pygame.K_RIGHT:
					self.velX = 0
				elif event.key == pygame.K_UP:
					self.velY = 0
				elif event.key == pygame.K_DOWN:
					self.velY = 0

			#If you click, fire!
			elif event.type is pygame.MOUSEBUTTONDOWN:
				self.tofire = True
				self.center = self.rect.center 
				self.laserrect = self.laser.get_rect(center=self.center)
				self.laserdestX,self.laserdestY = pygame.mouse.get_pos()
				self.laserX = self.laserrect.x
				self.laserY = self.laserrect.y
				self.laserDX = (self.laserdestX-self.laserX)/20
				self.laserDY = (self.laserdestY-self.laserY)/20

			#If you stop clicking, stop firing.
			elif event.type is pygame.MOUSEBUTTONUP:
				self.tofire = False


		if self.tofire == True:
			#emit laser beam: 
			self.laserrect = self.laserrect.move(self.laserDX,self.laserDY)
			if self.laserrect.x>640:
				self.laserrect.x = 640-self.laserrect.width
			elif self.laserrect.x<0:
				self.laserrect.x = 0
			if self.laserrect.y>480:
				self.laserrect.y = 480-self.laserrect.height
			elif self.laserrect.y<0:
				self.laserrect.y = 0

			#play the sound of shooting the laser: 
			self.shootSound.play()
		else:

			#Rotate the death star
			self.location = self.rect
			if self.location.x <=0:
				self.location.x = 0
			elif self.location.y <=0:
				self.location.y = 0
			elif self.location.y >= 480 - self.rect.height:
				self.location.y = 480-self.rect.height
			elif self.location.x >= 640 -self.rect.width:
				self.location.x = 640-self.rect.width
			self.rotate()

			#Move the death star
			self.rect = self.rect.move(self.velX,self.velY)

			

				

#Main game class: 
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



		#Main game loop;
		while True:
			self.clock.tick(60)
			self.player.tick()
			self.screen.fill(self.black)
			self.screen.blit(self.player.image,self.player.rect)



			#While the player is pressing the mouse button: 
			while self.player.tofire is True:
				#Render the laser: 
				self.screen.blit(self.player.laser,self.player.laserrect)

				#If the earth is alive, render it: 
				if self.earth.isAlive:
					if self.earth.health >= 50:
						self.screen.blit(self.earth.image,self.earth.rect)
					elif self.earth.health >0:
						self.screen.blit(self.earth.redImage,self.earth.redRect)

				#Tick the player (for the laser)
				self.player.tick()

				#if the laser collides with the earth, subtract health
				if self.player.laserrect.colliderect(self.earth.rect) and self.earth.isAlive:
					self.earth.health = self.earth.health -1
				pygame.display.flip()

				#Explosion!
				while self.earth.health <=0 and self.earth.isAlive:
					explodeSound.play()
					self.screen.fill(self.black)
					self.screen.blit(self.player.image,self.player.rect)
					self.screen.blit(self.player.laser,self.player.laserrect)
					self.screen.blit(self.earth.image,self.earth.expRect)
					pygame.display.flip()
					self.earth.tick()

			
			#Render the earth if it's alive: 
			if self.earth.health >= 50:
				self.screen.blit(self.earth.image,self.earth.rect)
			elif self.earth.health >0:
				self.screen.blit(self.earth.redImage,self.earth.redRect)


			#If the user let go of the mouse button, but the earth is still exploding:
			while  self.earth.isAlive and self.earth.health <=0:
				self.screen.fill(self.black)
				self.screen.blit(self.player.image,self.player.rect)
				self.screen.blit(self.player.laser,self.player.laserrect)
				self.screen.blit(self.earth.image,self.earth.expRect)
				pygame.display.flip()
				self.earth.tick()
			pygame.display.flip()



#Run the game 
if __name__ == '__main__':
	gs = GameSpace()
	gs.main()
