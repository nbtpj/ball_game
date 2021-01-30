#ifndef RENDER_H
#define RENDER_H
//this lib is coded for rendering the major part of the whole program. in the others , I may put the render-main menu function in here
#include"header.h"
#include<time.h>
#include<stdlib.h>
#define FILE_BALL "ballpng.png"
#define FILE_WALL "wall.jpg"
#define FILE_BACKGROUND "background.jpg"
#define FILE_DOT "point.png"
SDL_Color brown={96, 125, 139},impressed_brown={93, 64, 55},deep_orange={255, 87, 34},light_orange={255, 202, 40};
void renderScore(SDL_Renderer*renderer, TTF_Font*F, long& score)
{
    SDL_Rect sc={WIDTH-40,0,40,80};

    SDL_Surface*s=  TTF_RenderText_Solid(F,std::to_string(score).c_str(),light_orange);
    SDL_Texture*SC=SDL_CreateTextureFromSurface(renderer,s);

    SDL_FreeSurface(s);
    SDL_RenderCopy(renderer,SC,NULL,&sc);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(SC);

}
bool renderRaw(SDL_Renderer*renderer,ball&b,SDL_Rect barrier[],const line no[],const int &sz, SDL_Texture*bk,SDL_Texture*BB,SDL_Texture*WALL,bool sound,TTF_Font*F,long&score)
//this function renders the movement of the ball and returns true if the ball still be on the screen or false if the ball got out of the screen
{
    renderScore(renderer,F,score);

     SDL_Event a;SDL_Rect pos;
     bool EXIT=false;


    while(!EXIT)/*&&(quit==false)*/
      {
          int i=stop(b,0.01/*t*/,no,11,sound);
          if(i!=0)
          {
              EXIT=true;
              if(i==2) return false;
          }

          bool qu=false;
          pos={b.P.x-S/2,b.P.y-S/2,S,S};
          while(SDL_PollEvent(&a)!=0)
          {
              if(a.type==SDL_QUIT/*||a.type==SDL_KEYDOWN-> for mod the game :) , but believe me, do not unlock this if you do not get the bug*/) qu=true;
          };
          if(qu) break;
           SDL_RenderClear(renderer);
          SDL_RenderCopy(renderer,bk,NULL,NULL);
          SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
 //       for(int i=0;i<sz;i++) line::renderLine(no[i],renderer); if you want to see the lines, unlock this line
          SDL_RenderCopy(renderer,WALL,NULL,&barrier[0]);
          SDL_RenderCopy(renderer,WALL,NULL,&barrier[1]);
          SDL_RenderCopy(renderer,BB,NULL,&pos);
       // SDL_RenderDrawPoint(renderer,b.P.x,b.P.y); in fact, our ball is just a point, so if you want to see this point, unlock this line
          renderScore(renderer,F,score);
      };
      return true;

};
void update(SDL_Renderer*renderer,ball&b, SDL_Rect barrier[],SDL_Texture*BB,SDL_Texture*bk,SDL_Texture*WALL,TTF_Font*F,long&score)
//update the position of all objects and generate a new barrier
{

    bool increase= false;

    SDL_Rect new_rect={rand()%(WIDTH-W*2),rand()%(HEIGHT*3/4-3*S)+S,W*2,H};
    SDL_Rect pp={int(b.P.x)-S/2,int(b.P.y)-S/2,S,S};bool r_0=false,r_1=false;
    if((b.P.y+S/2<=barrier[0].y) &&( b.P.x>=barrier[0].x )&&( b.P.x<=barrier[0].x+barrier[0].h )&&( b.P.y+2+S/2>=barrier[0].y)) r_0=true;
    if((b.P.y+S/2<=barrier[1].y) &&( b.P.x>=barrier[1].x )&&( b.P.x<=barrier[1].x+barrier[1].h )&&( b.P.y+2+S/2>=barrier[1].y)) r_1=true;
    while(b.P.y<HEIGHT*3/4)
    {
        SDL_RenderClear(renderer);
        b.P.y++;increase=true;
        pp.y++;
        barrier[0].y++;
        barrier[1].y++;
        SDL_RenderCopy(renderer,bk,NULL,NULL);
        if(barrier[0].y<=HEIGHT)  SDL_RenderCopy(renderer,WALL,NULL,&barrier[0]);
        if(barrier[1].y<=HEIGHT)  SDL_RenderCopy(renderer,WALL,NULL,&barrier[1]);
        SDL_RenderCopy(renderer,BB,NULL,&pp);
        SDL_RenderPresent(renderer);
    };
    barrier[1]=barrier[0];barrier[0]=new_rect;


};
bool getInput(SDL_Renderer*renderer,ball&b,SDL_Rect barrier[],SDL_Texture*BB,SDL_Texture*WALL,SDL_Texture*bk,TTF_Font*F,long&score)
{
    renderScore(renderer,F,score);
    SDL_Event e;
    SDL_Rect poz={0,0,7,7};

    SDL_Rect pos={int(b.P.x)-S/2,int(b.P.y)-S/2,S,S};
    while(true)
    {
        int x,y;

        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT) return false;
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {SDL_GetMouseState(&x,&y);
                b.V.x=WIDTH/2-x;
                b.V.y=HEIGHT/2-y;
                return true;
            }

        };SDL_GetMouseState(&x,&y);
        int xx=b.P.x+(WIDTH/2-x)*5,yy=b.P.y+(HEIGHT/2-y)*5;
        double X=b.P.x,Y=b.P.y,Vx=(WIDTH/2-x),Vy=HEIGHT/2-y;;


        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,bk,NULL,NULL);
        SDL_RenderCopy(renderer,BB,NULL,&pos);
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    for(int i=1;i<30;i++)
        {
            X+=Vx*0.3;Vx*=0.999;
            Y+=Vy*0.3;Vy+=G*0.3;Vy*=0.999;
            poz.x=int(X);poz.y=int(Y);
            SDL_RenderDrawRect(renderer,&poz);

        };
    SDL_RenderCopy(renderer,WALL,NULL,&barrier[0]);
    SDL_RenderCopy(renderer,WALL,NULL,&barrier[1]);
    renderScore(renderer,F,score);
 //   SDL_RenderDrawLine(renderer,b.P.x,b.P.y,xx,yy);
 //   SDL_RenderPresent(renderer);

    };


};
bool QuitOrNot (SDL_Renderer*renderer,SDL_Rect barrier[],TTF_Font*F,SDL_Texture *bk,SDL_Texture *WALL,long&score)
//print when the player lose, ask him whether he wants to quit or return the main menu
{
    renderScore(renderer,F,score);


  SDL_Rect restart={WIDTH*3/4,HEIGHT*3/8,WIDTH/4,HEIGHT/8},quit={WIDTH*3/4,HEIGHT/2,WIDTH/4,HEIGHT/8},PP={WIDTH/4,HEIGHT/4+HEIGHT/8,WIDTH/2,HEIGHT/4};
  SDL_Texture *pic[4];
  SDL_Surface *s=TTF_RenderText_Solid(F,"MENU",brown);
  pic[0]=SDL_CreateTextureFromSurface(renderer,s);
  s=TTF_RenderText_Solid(F,"MENU",impressed_brown);
  pic[1]=SDL_CreateTextureFromSurface(renderer,s);
  s=TTF_RenderText_Solid(F,"QUIT",brown);
  pic[2]=SDL_CreateTextureFromSurface(renderer,s);
  s=TTF_RenderText_Solid(F,"QUIT",impressed_brown);
  pic[3]=SDL_CreateTextureFromSurface(renderer,s);
  SDL_Color X={247, 220, 111 };
  s=TTF_RenderText_Solid(F,"you lost:((",X);
  SDL_Texture* poor=SDL_CreateTextureFromSurface(renderer,s);
  s=TTF_RenderText_Solid(F,std::to_string(score).c_str(),X);
  SDL_Rect FINAL_SCORE={WIDTH/2,HEIGHT/2+HEIGHT/8,50,100};
  SDL_Texture*final_score=SDL_CreateTextureFromSurface(renderer,s);
  SDL_FreeSurface(s);
  SDL_Event e;
  SDL_RenderCopy(renderer,poor,NULL,&PP);SDL_RenderCopy(renderer,final_score,NULL,&FINAL_SCORE);
  SDL_RenderPresent(renderer); SDL_Delay(2000);

   while(true)
   {
       bool rt=false,qu=false;
       while(SDL_PollEvent(&e)!=0)
       {
           if(e.type==SDL_QUIT) return true;
           if(e.type==SDL_MOUSEBUTTONDOWN)
           {
                      int x,y;
                      SDL_GetMouseState(&x,&y);

                       if(x>=WIDTH*3/4 && x<=WIDTH)
                          {
                            if(y>=HEIGHT*3/8&&y<=HEIGHT/2) return false;
                            if(y>HEIGHT/2&&y<=5*HEIGHT/8) return true;
                          };

           };
       };
       int x,y;
       SDL_GetMouseState(&x,&y);
       if(x>=WIDTH*3/4 && x<=WIDTH)
       {
                            if(y>=HEIGHT*3/8&&y<=HEIGHT/2) rt=true;
                            if(y>HEIGHT/2&&y<=5*HEIGHT/8) qu=true;

       };

       SDL_RenderClear(renderer);
       SDL_RenderCopy(renderer,bk,NULL,NULL);
       SDL_RenderCopy(renderer,WALL,NULL,&barrier[0]);
       SDL_RenderCopy(renderer,WALL,NULL,&barrier[1]);
       if(rt) {SDL_RenderCopy(renderer,pic[1],NULL,&restart);} else SDL_RenderCopy(renderer,pic[0],NULL,&restart);
       if(qu) {SDL_RenderCopy(renderer,pic[3],NULL,&quit);} else SDL_RenderCopy(renderer,pic[2],NULL,&quit);

       SDL_RenderPresent(renderer);
   };

};










#endif // RENDER_H
