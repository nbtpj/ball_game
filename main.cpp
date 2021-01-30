/*
**written by Nguyen Minh Quang
**you are free to make change or reuse my code, but please keep these lines
*/

#include "render.h"
#include "menu.h"

#include <iostream>;`
using namespace std;

SDL_Renderer*renderer=NULL;
SDL_Window*window=NULL;


int main(int argc, char*argv[])
{

   SDL_Init(SDL_INIT_EVERYTHING);
   IMG_Init(IMG_INIT_JPG);
   TTF_Init();
   TTF_Font*F=TTF_OpenFont("blocked.ttf",10);
   Mix_OpenAudio(16000,MIX_DEFAULT_FORMAT,2,2048);
   Mix_Music *Sound=NULL;
    Sound=Mix_LoadMUS("ahihi.wav");
    if(Sound==NULL) cout<<"cant load music"<<endl;
    Mix_PlayMusic(Sound,-1);
    SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_MOUSE_FOCUS,&window,&renderer);
    SDL_Texture*bk=IMG_LoadTexture(renderer,"background.jpg");
    SDL_RenderCopy(renderer,bk,NULL,NULL);
    SDL_Texture *WALL=IMG_LoadTexture(renderer,"wall.jpg");
    SDL_Texture *BB=IMG_LoadTexture(renderer,"ball.png");
    bool sound=false,continue_=true;
    long score=0;

    while(continue_){
            score=0;
      int i=get_started(renderer,sound,bk,F);
      if(i==1) cout<<"you 've started playing game"<<endl;
      if(i==1){
 ball b(S/2+1,HEIGHT*3/4-1,0,0);


 SDL_Rect barrier[2];
 barrier[1]={0,HEIGHT*3/4+S/2,W*2,H};
 barrier[0]={400,HEIGHT-300,W*2,H};
 bool lost=false;
 do{
if(!getInput(renderer,b,barrier,BB,WALL,bk,F,score)){continue_=false;break;};//get input velocity here and check whether the player click at quit

 line l[11];
  int co=-1;//these lines below help to create lines form rectangles
   for(int i=0;i<2;i++)
   {
       co++;
       l[co]={barrier[i].x-S/2-1,barrier[i].y-S/2,barrier[i].x+barrier[i].w+S/2+1,barrier[i].y-S/2};
       co++;
       l[co]={barrier[i].x-S/2,barrier[i].y-S/2,barrier[i].x-S/2,barrier[i].y+barrier[i].h+S/2};
       co++;
       l[co]={barrier[i].x-S/2-1,barrier[i].y+barrier[i].h+S/2,barrier[i].x+barrier[i].w+S/2+1,barrier[i].y+barrier[i].h+S/2};
       co++;
       l[co]={barrier[i].x+barrier[i].w+S/2,barrier[i].y-S/2,barrier[i].x+barrier[i].w+S/2,barrier[i].y+barrier[i].h+S/2};

   };
   co++;
   l[co]={S/2,0,S/2,HEIGHT};
   co++;
   l[co]={WIDTH-S/2,0,WIDTH-S/2,HEIGHT};
   co++;
   l[co]={0,S/2,WIDTH,S/2};
   double now_pos=b.P.y;

  if (renderRaw(renderer,b,barrier,l,11,bk,BB,WALL,sound,F,score)==false) {cout<<"you 've lost"<<endl;if(QuitOrNot(renderer,barrier,F,bk,WALL,score)) continue_=false;lost=true;}
  else if(b.P.y+2<now_pos){score++; update(renderer,b,barrier,BB,bk,WALL,F,score);};} while(!lost);

};
  if(i==4) {continue_=false;cout<<"you quited the game"<<endl;};
};

   TTF_Quit();
   IMG_Quit();
   SDL_Quit();
    return 0;
}
