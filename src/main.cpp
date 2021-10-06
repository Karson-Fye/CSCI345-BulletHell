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

class MyGame:public Game{	  
	SDL_Rect src;
	vector<Particle *> particles;
	Particle *man;
	Animation a,b,c;
	Mix_Chunk *sound;
	int jx,jy;
	public:
	MyGame(int w=640,int h=480):Game("Bullet Hell",w,h) {
		int numPart = 2;
	  sound=media->readWav("media/tick.wav");
		c.read(media, "media/main.txt");
		src.x=0; src.y=0;
		SDL_QueryTexture(c.getTexture(), NULL, NULL, &src.w ,&src.h);
		man = new MyParticle(ren,&c,sound,&src,w/2,h/2,0,0,0,0);
		man->setBound(0,0,w,h);
		for (int i=0;i<numPart;i++) { 
			int vx=rand()%500 - 250;
			int vy=rand()%500 - 250;
			a.read(media,"media/stick.txt");
			// SDL_Texture *bitmapTex=media->read("media/obsticle.bmp");
			src.x=0; src.y=0;
			SDL_QueryTexture(a.getTexture(), NULL, NULL, &src.w, &src.h);
			particles.push_back(new MyParticle(ren,&a,sound,&src,w/2,h/2,vx,vy,0,50));
			particles[i]->setBound(0,0,w,h);
		}
		jx=w/2;
		jy=w/2;
		b.read(media,"media/background.txt");
		src.x=0; src.y=0; src.w=640; src.h=480;
	}
	void handleKeyUp(SDL_Event keyEvent) {
		if (keyEvent.key.keysym.sym==SDLK_LEFT || keyEvent.key.keysym.sym==SDLK_RIGHT)
		  man->setVelocityX(0);
		if (keyEvent.key.keysym.sym==SDLK_DOWN || keyEvent.key.keysym.sym==SDLK_UP)
			man->setVelocityY(0);
	}
	void handleKeyDown(SDL_Event keyEvent) {
		if (keyEvent.key.keysym.sym==SDLK_ESCAPE)
			delete this;
		if (keyEvent.key.keysym.sym==SDLK_LEFT)
		  man->setVelocityX(-200);
		else if (keyEvent.key.keysym.sym==SDLK_RIGHT)
			man->setVelocityX(200);
		if (keyEvent.key.keysym.sym==SDLK_UP)
			man->setVelocityY(-200);
		else if (keyEvent.key.keysym.sym==SDLK_DOWN)
			man->setVelocityY(200);
	}
	void handleButtonDown(SDL_Event joyEvent) {
		// if (joyEvent.jbutton.button==0 && joyEvent.jbutton.which==0)
		//   particles[0]->incVelocity(0,-100);
	}
	void handleAxisMovement(SDL_Event joyEvent) {
		// if (joyEvent.jaxis.axis==0 && joyEvent.jaxis.which==0)
		//   jx=((joyEvent.jaxis.value)*100)/32768;
		// if (joyEvent.jaxis.axis==1 && joyEvent.jaxis.which==0)
		//   jy=((joyEvent.jaxis.value)*100)/32768;
		// particles[0]->setAcceleration(jx,jy);
	}
	
	void handleKeyDown(SDL_Event keyEvent) {
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
		
		/*if(keyEvent.key.keysym.sym==SDLK_d & keyEvent.key.keysym.sym==SDLK_w)
		{
			particles[0]->x+=10;
			particles[0]->y-=10;
			cout<< "D works and W work" << endl; 
		}*/
	}
	
	
	
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
