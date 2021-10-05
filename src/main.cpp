// Example program:
// Using SDL2 to create an application window

#include <iostream>
#include <SDL.h>
#include <vector>
#include <map>
#include "Exception.hpp"
#include "MediaManager.hpp"
#include "Game.hpp"
#include "Particle.hpp"

using namespace std;

class MyGame:public Game{	  
    SDL_Rect src;
    vector<Particle *> particles;
    Animation a,b;
	public:
	MyGame(int w=640,int h=480):Game("The Game",w,h) {
      for (int i=0;i<1;i++) { 
		 int vx=rand()%500 - 250;
		 int vy=rand()%500 - 250;
		 a.read(media,"media/stick.txt");
	//	 SDL_Texture *bitmapTex=media->read("media/obsticle.bmp");
		 src.x=0; src.y=0;
		 SDL_QueryTexture(a.getTexture(), NULL, NULL, &src.w, &src.h);
         particles.push_back(new Particle(ren,&a,&src,w/5,h/2/*,vx,vy,0,50*/));
         particles[i]->setBound(0,0,w,h);
       }
       b.read(media,"media/background.txt");
       src.x=0; src.y=0; src.w=640; src.h=480;
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
