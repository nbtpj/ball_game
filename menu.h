/*
**written by Nguyen Minh Quang
**you are free to make change or reuse my code, but please keep these lines
*/


//my idea when I wrote this file is for rendering whenever I need to call a list for selecting, but it may not be important. You can mod it by your own ideas
#ifndef MENU_H
#define MENU_H
#include "header.h"
#include<SDL.h>
#include<SDL_ttf.h>
#include<string>
#include<SDL_mixer.h>
#define WM 200
#define HM 70
#define fontsize 10

using namespace std;

SDL_Rect R[4];

void InitRect()
//initialize four rectangles on the screen for player to select
{
    R[0].x=WIDTH-WM;R[0].w=WM;R[0].y=HEIGHT/2-2*HM;R[0].h=HM;
    R[1].x=WIDTH-WM;R[1].w=WM;R[1].y=HEIGHT/2-HM;R[1].h=HM;
    R[2].x=WIDTH-WM;R[2].w=WM;R[2].y=HEIGHT/2;R[2].h=HM;
    R[3].x=WIDTH-WM;R[3].w=WM;R[3].y=HEIGHT/2+HM;R[3].h=HM;

};

int get_started(SDL_Renderer*renderer,bool&sound, SDL_Texture*bk,TTF_Font*F)
//render the main menu to the screen
{
    InitRect();
    if(!sound)
        {Mix_PauseMusic();}
        else {Mix_ResumeMusic();};//check whether the music is playing and change it by the value of the "sound" var
    SDL_Color impressed={100,100,100},white ={255,255,255};//initialize 2 colors of font



    if(F==NULL) cout<<"error loading font"<<endl;
    SDL_Texture *PIC[11];
    SDL_Surface*s=NULL;
    s=TTF_RenderText_Solid(F,"START",white);PIC[0]=SDL_CreateTextureFromSurface(renderer,s);//start

    s=TTF_RenderText_Solid(F,"SOUND ON",white);PIC[1]=SDL_CreateTextureFromSurface(renderer,s);s=TTF_RenderText_Solid(F,"SOUND OFF",white);PIC[2]=SDL_CreateTextureFromSurface(renderer,s);//sound

    s=TTF_RenderText_Solid(F,"ABOUT",white);PIC[3]=SDL_CreateTextureFromSurface(renderer,s);//about

    s=TTF_RenderText_Solid(F,"QUIT",white);PIC[4]=SDL_CreateTextureFromSurface(renderer,s);//quit

    s=TTF_RenderText_Solid(F,"START",impressed);PIC[5]=SDL_CreateTextureFromSurface(renderer,s);//start

    s=TTF_RenderText_Solid(F,"SOUND ON",impressed);PIC[6]=SDL_CreateTextureFromSurface(renderer,s); s=TTF_RenderText_Solid(F,"SOUND OFF",impressed);PIC[7]=SDL_CreateTextureFromSurface(renderer,s);//sound

    s=TTF_RenderText_Solid(F,"ABOUT",impressed);PIC[8]=SDL_CreateTextureFromSurface(renderer,s);//about

    s=TTF_RenderText_Solid(F,"QUIT",impressed);PIC[9]=SDL_CreateTextureFromSurface(renderer,s);//quit

    PIC[10]=IMG_LoadTexture(renderer,"about.jpg");
    SDL_Rect aa={int(WIDTH/20),int(HEIGHT/4),int(WIDTH/2),int(HEIGHT/2)};
    SDL_FreeSurface(s);
    SDL_Event e;
    bool quit=false;
    while(!quit)
    {

      bool start=false,sod=false,about=false,q=false;
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT){return 4;}
            if(e.type==SDL_MOUSEBUTTONDOWN)
              {
            int x,y;
            SDL_GetMouseState(&x,&y);
            if((x>=WIDTH-WM)&&(x<=WIDTH))
            {
                if(y>=HEIGHT/2+HM){return 4;}
                else if(y>=HEIGHT/2){about=true;}
                else if(y>=HEIGHT/2-HM)
                    {sod=true;if(sound) {sound=false;Mix_PauseMusic();}
                                else {sound=true;Mix_ResumeMusic();};}
                else return 1;

            }
              };
        };

        if(e.type==SDL_MOUSEMOTION)
        {
            int x,y;
            SDL_GetMouseState(&x,&y);
            if((x>=WIDTH-WM)&&(x<=WIDTH))
            {
                if(y>=HEIGHT/2+HM){q=true;}
                else if(y>=HEIGHT/2){about=true;}
                else if(y>=HEIGHT/2-HM){sod=true;}
                else {start=true;}
            };
        };
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,bk,NULL,NULL);
      if(!start)
        { SDL_RenderCopy(renderer,PIC[0],NULL,&R[0]);}
        else SDL_RenderCopy(renderer,PIC[5],NULL,&R[0]);
      if(!sod)
      {
          if(sound==true){SDL_RenderCopy(renderer,PIC[1],NULL,&R[1]);}
             else SDL_RenderCopy(renderer,PIC[2],NULL,&R[1]);
      } else
        {
            if(sound==true){SDL_RenderCopy(renderer,PIC[6],NULL,&R[1]);}
             else SDL_RenderCopy(renderer,PIC[7],NULL,&R[1]);
        };
      if(!about)
        { SDL_RenderCopy(renderer,PIC[3],NULL,&R[2]);}
         else
            {
                SDL_RenderCopy(renderer,PIC[8],NULL,&R[2]);
                SDL_RenderCopy(renderer,PIC[10],NULL,&aa);
            };
      if(!q)
        { SDL_RenderCopy(renderer,PIC[4],NULL,&R[3]);}
        else SDL_RenderCopy(renderer,PIC[9],NULL,&R[3]);


    SDL_RenderPresent(renderer);

    };
//return 1 if the player click on "start"
//return 4 if the player click on "quit"


    return 0;
}


















#endif // MENU_H
