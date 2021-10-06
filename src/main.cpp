// Example program:
// Using SDL2 to create an application window

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
#include <map>
#include "Exception.hpp"
#include "MediaManager.hpp"
#include "Game.hpp"
#include "Particle.hpp"

using namespace std;

class MyParticle:public Particle {
	Mix_Chunk *sample;
	public:
	MyParticle(SDL_Renderer *ren,Animation *a,Mix_Chunk *newSample,SDL_Rect *src,
	  double x,double y,double vx,double vy,double ax,double ay):
	  Particle(ren,a,src,x,y,vx,vy,ax,ay) {
		  sample=newSample;
	}
	void collision() {
		Mix_PlayChannel(-1,sample,0);
	}
};

class MainCharacter:public MyParticle {
	bool left,right,up,down,boost;
	double speed;
	public:
  MainCharacter(SDL_Renderer *ren,Animation *a,Mix_Chunk *newSample,SDL_Rect *src,
	  double x,double y,double vx=0,double vy=0,double ax=0,double ay=0,double newSpeed=200):
		MyParticle(ren,a,newSample,src,x,y,vx,vy,ax,ay) {
			left=0;right=0;up=0;down=0;boost=0;
			speed=newSpeed;
	}
	double getSpeed() {return speed;}
	bool getBoost() {return boost;}
	bool getLeft() {return left;}
	bool getRight() {return right;}
	bool getUp() {return up;}
	bool getDown() {return down;}
	void setSpeed(double newSpeed) {speed = newSpeed;}
	void setBoost(bool newBoost) {boost = newBoost;}
	void setLeft(bool newLeft) {left = newLeft;}
	void setRight(bool newRight) {right = newRight;}
	void setUp(bool newUp) {up = newUp;}
	void setDown(bool newDown) {down = newDown;}
};

class MyGame:public Game{	  
	SDL_Rect src;
	vector<Particle *> particles;
	MainCharacter *man;
	Animation a,b,c;
	Mix_Chunk *sound;
	int jx,jy;
	public:
	MyGame(int w=640,int h=480):Game("Bullet Hell",w,h) {
		int numPart = 2;

	  sound=media->readWav("media/tick.wav");
		a.read(media,"media/stick.txt");
		b.read(media,"media/background.txt");
		c.read(media, "media/main.txt");
		
		src.x=0; src.y=0;
		SDL_QueryTexture(c.getTexture(), NULL, NULL, &src.w ,&src.h);
		man = new MainCharacter(ren,&c,sound,&src,w/2,h/2,0,0,0,0,200);
		man->setBound(0,0,w,h);
		for (int i=0;i<numPart;i++) { 
			int vx=rand()%600 - 300;
			int vy=rand()%600 - 300;
			SDL_QueryTexture(a.getTexture(), NULL, NULL, &src.w, &src.h);
			particles.push_back(new MyParticle(ren,&a,sound,&src,w/2,h/2,vx,vy,0,100));
			particles[i]->setBound(0,0,w,h);
		}
		jx=w/2; jy=w/2;
		src.w=640; src.h=480;
	}
	void handleKeyUp(SDL_Event keyEvent) {
		if (keyEvent.key.keysym.sym==SDLK_a) {
			man->setLeft(false);
			if (man->getRight()) man->setVelocityX(man->getSpeed());
		}
		else if (keyEvent.key.keysym.sym==SDLK_d) {
			man->setRight(false);
			if (man->getLeft()) man->setVelocityX(-man->getSpeed());
		}
		else if (keyEvent.key.keysym.sym==SDLK_w) {
			man->setUp(false);
			if (man->getDown()) man->setVelocityX(man->getSpeed());
		}
		else if (keyEvent.key.keysym.sym==SDLK_s) {
			man->setDown(false);
			if (man->getUp()) man->setVelocityX(-man->getSpeed());
		}
		else if (keyEvent.key.keysym.sym==SDLK_LSHIFT) {
			man->setBoost(false);
			man->setSpeed(200);
			if (man->getLeft()) man->setVelocityX(-man->getSpeed());
			if (man->getRight()) man->setVelocityX(man->getSpeed());
			if (man->getUp()) man->setVelocityY(-man->getSpeed());
			if (man->getDown()) man->setVelocityY(man->getSpeed());
		}
		if (!man->getLeft() && !man->getRight())
		  man->setVelocityX(0);
		if (!man->getDown() && !man->getUp())
			man->setVelocityY(0);
	}
	void handleKeyDown(SDL_Event keyEvent) {
		if (keyEvent.key.keysym.sym==SDLK_LSHIFT)
			man->setBoost(true);
		else if (keyEvent.key.keysym.sym==SDLK_ESCAPE)
			delete this;
		else if (keyEvent.key.keysym.sym==SDLK_a) {
			man->setLeft(true);
		  man->setVelocityX(-man->getSpeed());
		}
		else if (keyEvent.key.keysym.sym==SDLK_d) {
			man->setRight(true);
			man->setVelocityX(man->getSpeed());
		}
		else if (keyEvent.key.keysym.sym==SDLK_w) {
			man->setUp(true);
			man->setVelocityY(-man->getSpeed());
		}
		else if (keyEvent.key.keysym.sym==SDLK_s) {
			man->setDown(true);
			man->setVelocityY(man->getSpeed());
		}
		if (man->getBoost()) {
			man->setSpeed(400);
			if (man->getLeft()) man->setVelocityX(-man->getSpeed());
			if (man->getRight()) man->setVelocityX(man->getSpeed());
			if (man->getUp()) man->setVelocityY(-man->getSpeed());
			if (man->getDown()) man->setVelocityY(man->getSpeed());
		}
	}
	/* void handleButtonDown(SDL_Event joyEvent) {
		if (joyEvent.jbutton.button==0 && joyEvent.jbutton.which==0)
		  particles[0]->incVelocity(0,-100);
	}
	void handleAxisMovement(SDL_Event joyEvent) {
		if (joyEvent.jaxis.axis==0 && joyEvent.jaxis.which==0)
		  jx=((joyEvent.jaxis.value)*100)/32768;
		if (joyEvent.jaxis.axis==1 && joyEvent.jaxis.which==0)
		  jy=((joyEvent.jaxis.value)*100)/32768;
		particles[0]->setAcceleration(jx,jy);
	} */
	
	/*void handleKeyDown(SDL_Event keyEvent) {
		if(keyEvent.key.keysym.sym==SDLK_w)
		{
			particles[0]->y-=10;
			cout<< "W works" << endl; 
		}
		if(keyEvent.key.keysym.sym==SDLK_a)
		{
			particles[0]->x-=10;
			cout<< "A works" << endl; 
		}
		if(keyEvent.key.keysym.sym==SDLK_s)
		{
			particles[0]->y+=10;
			cout<< "S works" << endl; 
		}
		if(keyEvent.key.keysym.sym==SDLK_d)
		{
			particles[0]->x+=10;
			cout<< "D works" << endl; 
		}
		
		if(keyEvent.key.keysym.sym==SDLK_d & keyEvent.key.keysym.sym==SDLK_w)
		{
			particles[0]->x+=10;
			particles[0]->y-=10;
			cout<< "D works and W work" << endl; 
		}
	}*/
	
	void update(double dt) {
		SDL_RenderClear(ren);
		b.update(dt);
		
		SDL_RenderCopy(ren, b.getTexture(), &src, &src);
		for (unsigned i=0;i<particles.size();i++) 
			particles[i]->update(dt);
			man->update(dt);
		SDL_RenderPresent(ren);
	}
	~MyGame() {
	}
};

int main(int argc, char* argv[]) {
	try {
		MyGame g;
		g.run();
	} catch (Exception e) {
		cerr << e ;
	}
	return 0;
}
