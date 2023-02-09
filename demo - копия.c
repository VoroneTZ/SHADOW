///////////////////////////////////////////////////////////////////////////////////////////
#define PRAGMA_PATH "shade-c"
#define PRAGMA_PATH "stuff"
#include <litec.h>
#include <d3d9.h> // <--- THIS IS IMPORTANT!
#include <acknex.h>
#include <default.c>
var gmover=0;
#include "sc_core.c"
#include "svegetation.c"
#include "sc_core.h"
#include "rain.c"
#include <mtlView.c>

#include <ackphysx.h>


var lighter_on;
var rndm_i;
var rndm_a;
var rndm_b;
var rndm_c;
var level_num;
var time;
var player_life=100;
var dist_attack;
var pages=0;
ENTITY* enemy;
var frame25;
#include "vegetation.c"
function start_lvl2();
#include <mtlFX.c>
#include "player.c"
SOUND* foot = "toprak.wav";
function start_lvl1();
var number_of_bushes=1;
var sMove = 1;
ENTITY* menuhandle;
ENTITY* mqhandle;
var hiz;
var handles;
var slender_see;
ENTITY* fireww;
var pause_active=0;
var resolution_sc=12; /// 1-12
var windowed_sc=2; ///   0-1
var vert_synh=1; //      0-1
var antialias=1;//       0-3
var DOF=1; //0-1
var Reflact=1; //       0-1
var volparts=1; //        0-1
var water=0;       //    0-1
var lightrays=1; //0-1
var tripplebuffer=1; //0-1
var hdr=1;
var time_lvl;
////////////////////////////////////////////////////////////////////////////////////////////

str_cpy(save_dir,"saves");
function continue_game(); 

STRING* temp_str = "Welcome";
function see_wh();
var enemy_z;
FONT* arial_font = "Arial#50";
FONT* digit_font = "Tipbrush Script#50";
FONT* digit_font1 = "Tipbrush Script#80b";
PANEL* pages_pan =
{

 digits (  0, 0, "Spheres %.0f", digit_font, 1,pages); 
 
  // digits (  0, 40, "Health %.0f", digit_font, 1, player_life);
 // digits (  0, 60, "See %.0f", digit_font, 1,  player.pan);
 digits (  0, 80, "Time %.0f", digit_font, 1,  time);
  //flags =  SHOW;
  
}



void addBlurToView()
{
  sc_mtl_pp_radialBlur.skill1 = 10000000000000;
  
  sc_mtl_pp_radialBlur.skill2 = 10000000000000000;
  sc_mtl_pp_radialBlur.skill3 = 200000000000000000000000000000000000;
   
  sc_ppAdd(sc_mtl_pp_radialBlur, camera, 0);
}

void removeBlurFromView()
{
   sc_ppRemove(sc_mtl_pp_radialBlur, camera, 0);
}


function nothing()
{
	// i h8 this fuckin world
}
PANEL* pan25 =
{
	bmap = "options.png";
layer = 90;
 
flags= transparent;
  
}

PANEL* pan251 = 
{
	bmap = "menu.PNG";
  

      digits (  355, 290, "So close...", digit_font1, 3, NULL);
    layer = 99;
	flags = OVERLAY | transparent;;

}
PANEL* pan252 = 
{
	bmap = "menu.PNG";
  
layer = 99;
      digits (  355, 290, "Run...", digit_font1, 3, NULL);
    
	flags = OVERLAY | transparent;;

}



PANEL* tv_pan =
{
	bmap = "tv.png";

 
flags= transparent;
  
}

BMAP* map_envMap = "sky_night.pcx";

function quit_program()
{
	sys_exit("123");
}
////////////////////////////////////////////////////////////////////////////////////////////

function select_lvl();

PANEL* panel = //„Î‡‚ÌÓÂ ÏÂÌ˛
{
	bmap = "menu.PNG";
  
	button (355, 290, "button.png", "button.png", "button.png", select_lvl, NULL, NULL); 
	button (350, 375, "button.png", "button.png", "button.png", options_show, NULL, NULL); 
	button (365, 407, "button.png", "button.png", "button.png", quit_program, NULL, NULL); 
   digits (  320, 0, "Version 0.2.0", digit_font, 3, NULL);
      digits (  355, 290, "Start", digit_font, 3, NULL);
         digits (  340, 339, "Net Play", digit_font, 3, NULL);
            digits (  350, 375, "Authors", digit_font, 3, NULL);
               digits (  365, 407, "Exit", digit_font, 3, NULL);
                  digits (  330, 200, "Shadow", digit_font1, 3, NULL);
	flags = OVERLAY | visible;

}
ENTITY* wh;
ENTITY* ending;
action whore_intro()
{
	me=wh;
}
PANEL* subtitles1 = //hello my dear friend
{
   digits (  0, 0, "hello my dear friend", arial_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles2 = //do you remember?
{ 
   digits (  0, 0, "do you remember?", arial_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles3 = //I dont know why you soul not in hell
{ 
   digits (  0, 0, "I dont know why you soul not in hell", arial_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles4 = //but I dont want give it to you back
{ 
   digits (  0, 0, "but I dont want give it to you back", arial_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles5 = //but you can try
{ 
   digits (  0, 0, "but you can try", arial_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles6 = //get you soul back
{ 
   digits (  0, 0, "get you soul back", arial_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles7 = //but this will be not simple
{ 
   digits (  0, 0, "but this will be not simple", arial_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles8 = //give me 12 spheres of light
{ 
   digits (  0, 0, "give me 12 spheres of light", arial_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles9 = //and i`ll give you your soul back
{ 
   digits (  0, 0, "and i`ll give you your soul back", arial_font, 3, NULL);
	flags = OVERLAY;
}

PANEL* level_pan = //„Î‡‚ÌÓÂ ÏÂÌ˛
{
	bmap = "menu.PNG";
  
	button (355, 290, "button.png", "button.png", "button.png", intro, NULL, NULL); 
	button (355, 325, "button.png", "button.png", "button.png", start_lvl1, NULL, NULL); 
	button (355, 360, "button.png", "button.png", "button.png", start_lvl2, NULL, NULL); 
		button (355, 395, "button.png", "button.png", "button.png", start_lvl3, NULL, NULL); 
	button (365, 407, "button.png", "button.png", "button.png", main_menu_show, NULL, NULL); 
  // digits (  320, 0, "Version 0.1.7", digit_font, 3, NULL);
      digits (  355, 290, "Intro", digit_font, 3, NULL);
      digits (  355, 395, "Level 3", digit_font, 3, NULL);
       digits (  355, 360, "Level 2", digit_font, 3, NULL);
            digits (  355, 325, "Level 1", digit_font, 3, NULL);
               digits (  365, 407, "Back", digit_font, 3, NULL);
                  digits (  330, 200, "New Game", digit_font1, 3, NULL);
	flags = OVERLAY ;

}

function close_lvl()
{
	player_life=-10;
}
PANEL* pause_p = //„Î‡‚ÌÓÂ ÏÂÌ˛
{
	bmap = "menu.PNG";
  
	button (355, 290, "button.png", "button.png", "button.png", continue_game, NULL, NULL); 

	button (365, 339, "button.png", "button.png", "button.png", close_lvl, NULL, NULL); 

      digits (  340, 290, "Continue", digit_font, 3, NULL);
  
               digits (  365, 339, "Exit", digit_font, 3, NULL);
                  digits (  340, 200, "Pause", digit_font1, 3, NULL);
	flags = OVERLAY | transparent;;

}

function select_lvl()
{
	reset(panel,SHOW);
	set(level_pan,SHOW);
		
}
PANEL* loading =
{
	bmap = "options.png";
  digits (  20, 0, "Loading...", digit_font, 3, NULL);
layer = 99;

flags= transparent;
}

PANEL* options_pan;

function save_program()
{	reset(options_pan,SHOW);
	set(panel,SHOW);
result = game_save("options",1,SV_ALL);
if (result <= 0) {printf("Save Error!"); } 

	
}

PANEL* options_pan = //Ì‡ÒÚÓÈÍË
{
	digits (  340, 20, "Authors", digit_font1, 3, NULL);
	
	digits (  280, 120, "Producer: Vorontsov Dmityi", digit_font, 3, NULL);
 	digits (  290, 280, "Designer: Egorova Vladislava", digit_font, 3, NULL); 
 	digits (  310, 220, "Designer: Ilya Kulich", digit_font, 3, NULL);
 	digits (  270, 180, "Programmer: Vorontsov Dmityi", digit_font, 3, NULL);
 	digits (  290, 380, "Music: Smekhovsky Rostislav", digit_font, 3, NULL);
 	digits (  300, 320, "Music: Egorova Vladislava", digit_font, 3, NULL);

	
	digits (  366, 564, "Back", digit_font, 3, NULL);
 	button (366, 564, "button.png", "button.png", "button.png", main_menu_show, NULL, NULL); 
	flags = OVERLAY;
}
function frame_25()
{
	var wind;
	while(gmover==0){
	wind=integer(random(30));
if(wind==1){media_play("wndTREE.wav", NULL, 100);}
if(wind==2){media_play("wndTREE2.wav", NULL, 100);}		
if(wind==3){media_play("wndTREE3.wav", NULL, 100);}
if(wind==4){media_play("wndTREE4.wav", NULL, 100);}
if(wind==5){media_play("wndTREE5.wav", NULL, 100);}
if(wind==6){media_play("wndTREE6.wav", NULL, 100);}
if(wind==7){media_play("wndTREE7.wav", NULL, 100);}	
		
if (vec_dist(player.x,enemy.x) < 1000)
{
frame25=integer(random(30));
if(frame25==1){set(pan25,SHOW);set(pan251,SHOW);wait(3);reset(pan25,SHOW);reset(pan251,SHOW);}
if(frame25==2){set(pan25,SHOW);set(pan252,SHOW);wait(3);reset(pan25,SHOW);reset(pan252,SHOW);}

if(frame25==3){media_play("scr1.wav", NULL, 100);}
if(frame25==4){media_play("scr2.wav", NULL, 100);}
if(frame25==5){media_play("scr3.wav", NULL, 100);}
if(frame25==6){media_play("scr4.wav", NULL, 100);}
if(frame25==7){media_play("scr5.wav", NULL, 100);}
}
wait(-random(20));	
}

}
function main_menu_show()
{
	reset(options_pan,SHOW);
		reset(level_pan,SHOW);
	set(panel,SHOW);

	
}

function options_show()
{
	set(options_pan,SHOW);
	reset(panel,SHOW);
}
var player_live=10;
var trace_dist = 0;



function pause_game()
{
	pause_active=1;
on_esc=nothing;
	mouse_mode = 4;
		freeze_mode = 1;
	set(pause_p,SHOW);
	 pause_p.alpha = 0; // Panel 100% transparent
while (pause_p.alpha < 100)
{
  pause_p.alpha += 2; 
  wait(1);
} 
	on_esc=continue_game;
	

}

function game_over()
{
//	sys_exit(123);
	reset(pause_p,SHOW);
	reset(pages_pan,SHOW);
	media_stop(mmhandle);
	media_stop(mqhandle);
number_rock=0;
number_pages=0;
number_bush=0;
number_bush2=0;
number_tree=0;
gmover=1;
on_esc=nothing;
	mouse_mode = 4;
		detail_size = 10;
			freeze_mode = 0;
			pages=0;
level_load ("menu.wmb");
	menuhandle = media_loop("menu.mp3",NULL,100);
	camera.clip_near=0;
camera.clip_far=3500;
	camera.fog_start = 0; 
	camera.fog_end = 3500;
set(panel,SHOW);
	camera.x=364;
	camera.y=459;
	camera.z=60;
	camera.pan=213;
	camera.tilt=3;	
	player_life=100;
	player_live=100;
	camera.arc=60;
	pause_active=0;
	while (tv_pan.alpha > 0)
{
 tv_pan.alpha -= 2; 
  wait(1);	
}

}

action intro_cam()
{
	while(1){
		camera.genius = me;
		camera.pan -= 15 * mouse_force.x * time_step;
		camera.tilt += 15 * mouse_force.y * time_step;
if (camera.pan<=150){camera.pan=150;}
if (camera.pan>=210){camera.pan=210;}
if (camera.tilt<=-20){camera.tilt=-20;}
if (camera.tilt>=10){camera.tilt=10;}
		wait(1);
	}
}


function intro()
{
set(loading,SHOW);
set(tv_pan,SHOW);	
tv_pan.alpha = 0;
loading.alpha = 0; // Panel 100% transparent
while (loading.alpha < 100)
{
  loading.alpha += 2; 
  wait(1);
}	
reset (level_pan,SHOW);
level_load ("intro1.wmb");	
camera.x=128;
camera.y=-45;
camera.z=61;
camera.roll=5;
camera.pan=180;
	mouse_mode=0;
while (loading.alpha > 0)
{
  loading.alpha -= 2; 
  wait(1);
} 
set(subtitles1,SHOW);
media_play("intro1.wav",NULL,100);
wait(-2);
reset(subtitles1,SHOW);
wait(-1);

set(subtitles2,SHOW);
reset(subtitles2,SHOW);
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10; 
 
  wait(1);
}

camera.x=580;
camera.y=-90;
camera.z=119;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10; 
 
  wait(1);
}
wait(-1);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10; 
 
  wait(1);
}
camera.x=128;
camera.y=-45;
camera.z=61;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10; 
 
  wait(1);
}
wait(-1);
media_play("intro2.wav",NULL,100);
set(subtitles3,SHOW);
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10; 
 
  wait(1);
}

camera.x=587;
camera.y=281;
camera.z=122;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10; 
 
  wait(1);
}
wait(-1);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10; 
 
  wait(1);
}
camera.x=128;
camera.y=-45;
camera.z=61;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10; 
 
  wait(1);
}
reset(subtitles3,SHOW);
wait(-1);
media_play("intro3.wav",NULL,100);
set(subtitles4,SHOW);
wait(-2);
reset(subtitles4,SHOW);
wait(-1);
media_play("intro4.wav",NULL,100);
set(subtitles5,SHOW);
wait(-1);
reset(subtitles5,SHOW);
wait(-1);
media_play("intro5.wav",NULL,100);
set(subtitles6,SHOW);
wait(-1);
reset(subtitles6,SHOW);
wait(-1);
media_play("intro6.wav",NULL,100);
set(subtitles7,SHOW);
wait(-2);
reset(subtitles7,SHOW);
wait(-1);
media_play("intro7.wav",NULL,100);
set(subtitles8,SHOW);
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10; 
 
  wait(1);
}

camera.x=648;
camera.y=766;
camera.z=122;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10; 
 
  wait(1);
}
wait(-1);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10; 
 
  wait(1);
}
camera.x=128;
camera.y=-45;
camera.z=61;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10; 
 
  wait(1);
}
reset(subtitles8,SHOW);
wait(-1);
media_play("intro8.wav",NULL,100);
set(subtitles9,SHOW);
wait(-2);
reset(subtitles9,SHOW);
wait(-1);
ent_create ("shadow.mdl", vector(-30,-45,51), NULL); 
wait(-2);
start_lvl1();


}
SOUND* foot = "toprak.wav";
function footstep()
{
	while(gmover==0){
	// «¬”  ’Œƒ‹¡€
if(key_w==1||key_a==1||key_d==1||key_s==1)
		{
			handles=ent_playsound(player,foot,30);
		}
		if(sMove == 2){wait(5);}
		if(sMove == 1){wait(7);}
}
}
action firew();
action end_lvl()
{
	ending=me;
}
function cut_scene_level1()
{
	on_esc=nothing;
player_live=0;
set(player,INVISIBLE);
player.x=-1204;
player.y=-5108;
player.z=59;
camera.pan=-60;
camera.tilt=0;
while (vec_dist(player.x, camera.x)>=100)
{
if (camera.x<=player.x){camera.x=camera.x+1;}	
if (camera.x>=player.x){camera.x=camera.x-1;}
if (camera.y<=player.y){camera.y=camera.y+1;}	
if (camera.y>=player.y){camera.y=camera.y-1;}

wait(1);
}
ent_create ("shadowph.mdl", vector(-1272, -4926, 58), NULL); 
ent_create ("firew.mdl", vector(-1272, -4926, 58), firew); 
media_play ("scr2.wav", NULL, 100);
while (camera.pan>=-230)
{
camera.pan=camera.pan-8;

wait(1);
}


wait(-2);
reset(pause_p,SHOW);
	reset(pages_pan,SHOW);
	media_stop(mmhandle);
	media_stop(mqhandle);
number_rock=0;
number_pages=0;
number_bush=0;
number_bush2=0;
number_tree=0;
on_esc=nothing;
	mouse_mode = 4;
		detail_size = 10;
			freeze_mode = 0;
			pages=0;

	camera.clip_near=0;
camera.clip_far=3500;
	camera.fog_start = 0; 
	camera.fog_end = 3500;

	player_life=100;
	player_live=100;
	camera.arc=60;
start_lvl2();
}
action cutscene2_anim()
{
	wait(-1);
   while(1) 
   {
      my.skill1 += 2;
      if (my.skill1 > 95) my.skill1 = 95; 
      ent_animate(me,"Frame",my.skill1,ANM_CYCLE);
      wait(1);
   }
}


function cut_scene_level2()
{
	on_esc=nothing;
player_live=0;
media_play ("scr6.wav", NULL, 100);
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 2; 
 
  wait(1);
}
		
media_play("cut1.wav", NULL, 100);
	camera.x=-21781;
	camera.y=-14582;
	camera.z=2152;
	camera.pan=226;
	camera.tilt=-8;
	ent_create ("shadow2.mdl", vector(-22823, -15651, 2147), cutscene2_anim);



while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10; 
 
  wait(1);
}
wait(-2);
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 2; 
 
  wait(1);
}
game_over();
}
function start_lvl1()
{
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
level_num=1;
set(loading,SHOW);
time_lvl=800;
gmover=0;
loading.alpha = 0; // Panel 100% transparent
while (loading.alpha < 100)
{
  loading.alpha += 2; 
 
  wait(1);
}
 
time=0;
detail_size = 100;
//fog_color=1;
	sun_light=1;
		camera.clip_near=0;
	camera.clip_far=8000;
	camera.fog_start = 0; 
	camera.fog_end = 2000;
	level_load ("level1.wmb");

	wait(-1);

///////////////////////////—¬≈“, ¬—≈Ã Õ”∆≈Õ —¬≈“

	d3d_lightres = 25;
	player.lightrange = 2000;   
	set(player,SPOTLIGHT);

///////////////////////////œ–Œ◊¿ﬂ ’–≈Õ‹


		
	reset(level_pan,SHOW);
	mouse_mode=0;
	set(pages_pan,SHOW);
	mqhandle = media_loop("psy.wav",NULL,0);

addBlurToView();
	
loading.alpha = 100; 
while (loading.alpha > 0)
{
  loading.alpha -= 2; 
   media_tune(menuhandle,loading.alpha,0,0);
  wait(1);
} 
	media_stop(menuhandle);
	footstep();
on_esc=pause_game;
frame_25();
see_wh();
	reset(loading,SHOW);
	set(tv_pan,SHOW);
	while(1)
	{
	///////////////////////////’›À—¿ ///////////////////////
sc_mtl_pp_radialBlur.skill1 = 0.3;
  
  sc_mtl_pp_radialBlur.skill2 = 0.5;
  sc_mtl_pp_radialBlur.skill3 = 2;
  
  
if (pages==11){if (vec_dist(player.x,ending.x)<=50)
{cut_scene_level1();
wait(1);
break;
}
}	
media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);	
///////////////////////////  ¿Ã≈–¿
if (camera.tilt>=90){camera.tilt=90;}
if (camera.tilt<=-60){camera.tilt=-60;}
media_tune(mqhandle,100-player_life,0,0);
///////////////////////////¬»ƒ»Ã ƒ≈¡»À¿? ///////////////////////
	
c_scan(player.x,player.pan,vector(60,0,3000),IGNORE_FLAG2|IGNORE_PASSABLE|IGNORE_WORLD);

		if (you == enemy || you == fireww){
			
			slender_see=10;
}
		else
		{
	
			slender_see=-1;
		}
	
		if(slender_see<0)
{
	if(pause_active==0){
if (player_life<100){player_life+=0.5;}
}
}	

 
///////////////////////////◊“Œ Ã≈ÿ¿≈“ ¬»ƒ≈“‹ ƒ≈¡»À¿? ///////////////////////

c_trace (player.x,enemy.x,USE_POLYGON|IGNORE_FLAG2);


	

	if(slender_see>0){
	if (vec_dist(player.x, enemy.x)<1000)
	{ 	if (you == enemy) 
	{
	
	if(pause_active==0){
	dist_attack=(1000-(vec_dist(player.x, enemy.x)))*0.001;
player_life=player_life-dist_attack;}

	}
	else
	{
	//	slender_see=-1;
	if (player_life<100){player_life+=0.5;
	}
}	
}
}



///////////////////////////œŒ¬Œ–Œ“ ƒ»¡»À¿ ///////////////////////


if (player.y>enemy.y)
{
if (player.x>enemy.x)
	{
	enemy.pan=asinv((player.y-enemy.y)/vec_dist(player.x, enemy.x));
	} 
else 
	{
	enemy.pan=90+asinv((enemy.x-player.x)/vec_dist(player.x, enemy.x));
	}
} 


if (player.y<enemy.y)
{ 
if (player.x<enemy.x)
	{
	enemy.pan=180+asinv((enemy.y-player.y)/vec_dist(player.x, enemy.x));
	} 
else 
	{
	enemy.pan=180+90+asinv((player.x-enemy.x)/vec_dist(player.x, enemy.x));
	}
}


/////////////////////// œŒƒ€’¿Õ»≈ ///////////////////////


			if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}
			if (vec_dist(player.x, enemy.x) < 100){camera.arc=120;slender_see=10;	player_live=0;camera.pan=enemy.pan+180; camera.tilt=11;
	while(player_life>1){ 	
				
		media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);
			camera.pan=enemy.pan+180;
			player_life=player_life-1;
	
		wait(1);
			}
			gmover=1;game_over();break;
		}



wait (1);
		
	}

}

function start_lvl2()
{
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
level_num=2;
set(loading,SHOW);
time_lvl=600;
gmover=0;
loading.alpha = 0; // Panel 100% transparent
while (loading.alpha < 100)
{
  loading.alpha += 2; 
  wait(1);
}
time=0;
//detail_size = 100;
	level_load ("level2.wmb");

	wait(-1);


///////////////////////////œ––◊¿ﬂ ’–≈Õ‹

//	media_loop("back.mp3", NULL, 100);	
//	sc_dofDynFocus(400,50000,1);
	reset(level_pan,SHOW);
	mouse_mode=0;
	frame_25();
	set(pages_pan,SHOW);
	mqhandle = media_loop("psy.wav",NULL,0);
loading.alpha = 100; // Panel 100% transparent
while (loading.alpha > 0)
{
  loading.alpha -= 2; 
  media_tune(menuhandle,loading.alpha,0,0);
  wait(1);
} 
	media_stop(menuhandle);
	reset(loading,SHOW);
	set(tv_pan,SHOW);
	on_esc=pause_game;
	while(1)
	{
	if(camera.z<=-120){player_life=-1;}
///////////////////////////  ¿Ã≈–¿
if (camera.tilt>=90){camera.tilt=90;}
if (camera.tilt<=-60){camera.tilt=-60;}
		media_tune(mqhandle,100-player_life,0,0);

///////////////////////////¬»ƒ»Ã ƒ≈¡»À¿?

if (pages==11)
{cut_scene_level2();
wait(1);
break;
}
c_scan(player.x,player.pan,vector(60,0,3000),IGNORE_FLAG2|IGNORE_PASSABLE|IGNORE_WORLD);

		if (you == enemy || you == fireww){
			
			slender_see=10;
}
		else
		{
	
			slender_see=-1;
		}
	
		if(slender_see<0)
{
		if(pause_active==0){
if (player_life<100){player_life+=0.5;}
}	
}

///////////////////////////◊“Œ Ã≈ÿ¿≈“ ¬»ƒ≈“‹ ƒ≈¡»À¿?

c_trace (player.x,enemy.x,USE_POLYGON|IGNORE_FLAG2);


	

	if(slender_see>0){
	if (vec_dist(player.x, enemy.x)<1000)
	{ 	if (you == enemy) 
	{
	
		if(pause_active==0){
	dist_attack=(1000-(vec_dist(player.x, enemy.x)))*0.001;
	player_life=player_life-dist_attack;
}
	}
	else
	{
	//	slender_see=-1;
	if (player_life<100){player_life+=0.5;
	}
}	
}
}


///////////////////////////œŒ¬Œ–Œ“ ƒ»¡»À¿


if (player.y>enemy.y)
{
if (player.x>enemy.x)
	{
	enemy.pan=asinv((player.y-enemy.y)/vec_dist(player.x, enemy.x));
	} 
else 
	{
	enemy.pan=90+asinv((enemy.x-player.x)/vec_dist(player.x, enemy.x));
	}
} 


if (player.y<enemy.y)
{ 
if (player.x<enemy.x)
	{
	enemy.pan=180+asinv((enemy.y-player.y)/vec_dist(player.x, enemy.x));
	} 
else 
	{
	enemy.pan=180+90+asinv((player.x-enemy.x)/vec_dist(player.x, enemy.x));
	}
}


/////////////////////// œŒƒ€’¿Õ»≈


			if (player_life<0){	game_over();break;}
			if (vec_dist(player.x, enemy.x) < 100){camera.arc=120;slender_see=10;	player_live=0;camera.pan=enemy.pan+180; camera.tilt=10;
			while(player_life>1){ 	
				
		media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);
			camera.pan=enemy.pan+180;
			player_life=player_life-1;
	
		wait(1);
			}
			game_over();break;
		}


///////////////////////////’›À—¿

	
media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);

wait (1);
		
	}

}

function start_lvl3()
{
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
level_num=1;
set(loading,SHOW);
time_lvl=800;
gmover=0;
loading.alpha = 0; // Panel 100% transparent
while (loading.alpha < 100)
{
  loading.alpha += 2; 
 
  wait(1);
}
 
time=0;
detail_size = 100;
//fog_color=1;
	sun_light=1;
		camera.clip_near=0;
	camera.clip_far=8000;
	camera.fog_start = 0; 
	camera.fog_end = 2000;
	level_load ("level3.wmb");

	wait(-1);

///////////////////////////—¬≈“, ¬—≈Ã Õ”∆≈Õ —¬≈“

//	d3d_lightres = 25;
//	player.lightrange = 2000;   
//	set(player,SPOTLIGHT);

///////////////////////////œ–Œ◊¿ﬂ ’–≈Õ‹


		
	reset(level_pan,SHOW);
	mouse_mode=0;
	set(pages_pan,SHOW);
	mqhandle = media_loop("psy.wav",NULL,0);

addBlurToView();
	
loading.alpha = 100; 
while (loading.alpha > 0)
{
  loading.alpha -= 2; 
   media_tune(menuhandle,loading.alpha,0,0);
  wait(1);
} 
	media_stop(menuhandle);
	footstep();
on_esc=pause_game;
frame_25();
see_wh();
	reset(loading,SHOW);
	set(tv_pan,SHOW);
	while(1)
	{
	///////////////////////////’›À—¿ ///////////////////////
sc_mtl_pp_radialBlur.skill1 = 0.3;
  
  sc_mtl_pp_radialBlur.skill2 = 0.5;
  sc_mtl_pp_radialBlur.skill3 = 2;
  
  
if (pages==9){game_over();
wait(1);
break;
}
	
media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);	
///////////////////////////  ¿Ã≈–¿
if (camera.tilt>=90){camera.tilt=90;}
if (camera.tilt<=-60){camera.tilt=-60;}
media_tune(mqhandle,100-player_life,0,0);
///////////////////////////¬»ƒ»Ã ƒ≈¡»À¿? ///////////////////////
	enemy.z=player.z;
c_scan(player.x,player.pan,vector(60,0,3000),IGNORE_FLAG2|IGNORE_PASSABLE|IGNORE_WORLD);

		if (you == enemy || you == fireww){
			
			slender_see=10;
}
		else
		{
	
			slender_see=-1;
		}
	
		if(slender_see<0)
{
	if(pause_active==0){
if (player_life<100){player_life+=0.5;}
}
}	

 
///////////////////////////◊“Œ Ã≈ÿ¿≈“ ¬»ƒ≈“‹ ƒ≈¡»À¿? ///////////////////////

c_trace (player.x,enemy.x,USE_POLYGON|IGNORE_FLAG2);


	

	if(slender_see>0){
	if (vec_dist(player.x, enemy.x)<1000)
	{ 	if (you == enemy) 
	{
	
	if(pause_active==0){
	dist_attack=(1000-(vec_dist(player.x, enemy.x)))*0.001;
player_life=player_life-dist_attack;}

	}
	else
	{
	//	slender_see=-1;
	if (player_life<100){player_life+=0.5;
	}
}	
}
}



///////////////////////////œŒ¬Œ–Œ“ ƒ»¡»À¿ ///////////////////////


if (player.y>enemy.y)
{
if (player.x>enemy.x)
	{
	enemy.pan=asinv((player.y-enemy.y)/vec_dist(player.x, enemy.x));
	} 
else 
	{
	enemy.pan=90+asinv((enemy.x-player.x)/vec_dist(player.x, enemy.x));
	}
} 


if (player.y<enemy.y)
{ 
if (player.x<enemy.x)
	{
	enemy.pan=180+asinv((enemy.y-player.y)/vec_dist(player.x, enemy.x));
	} 
else 
	{
	enemy.pan=180+90+asinv((player.x-enemy.x)/vec_dist(player.x, enemy.x));
	}
}


/////////////////////// œŒƒ€’¿Õ»≈ ///////////////////////


			if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}
			if (vec_dist(player.x, enemy.x) < 100){camera.arc=120;slender_see=10;	player_live=0;camera.pan=enemy.pan+180; camera.tilt=11;
	while(player_life>1){ 	
				
		media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);
			camera.pan=enemy.pan+180;
			player_life=player_life-1;
	
		wait(1);
			}
			gmover=1;game_over();break;
		}



wait (1);
		
	}

}

function continue_game()
{
	pause_active=0;
	on_esc=nothing;
		mouse_mode = 0;
		freeze_mode = 0;
	pause_p.alpha = 100; // Panel 100% transparent
while (pause_p.alpha > 0)
{
  pause_p.alpha -= 2; 
  wait(1);
} 
	reset(pause_p,SHOW);
	on_esc=pause_game;
	
}



BMAP* mouse_pcx = "mouse.png"; 
function main()
{
		menuhandle = media_loop("menu.mp3",NULL,100);
	detail_size = 10;
//	if (game_load("options",1) <= 0) { printf("Load Error!");} 
	set(loading,SHOW);
	shadow_stencil=4;
	max_entities = 99999;
	var d3d_vsync = vert_synh;
d3d_antialias = 9;
on_esc=nothing;
	mouse_map = mouse_pcx;
	mouse_mode = 4;
	fps_max = 60; // limit the frame rate to 75 fps (not really needed)
	nexus=400;
	video_mode=12;
	video_screen=1;
wait(1);
	level_load ("menu.wmb");
	camera.x=364;
	camera.y=459;
	camera.z=60;
	camera.pan=213;
	camera.tilt=3;

	d3d_triplebuffer=tripplebuffer;



	camera.clip_near=0;
camera.clip_far=3500;
	camera.fog_start = 0; 
	camera.fog_end = 3500;
	
	
	
sc_bHDR = hdr;
	sc_bDOF = DOF;
	sc_bRefract = Reflact;
	sc_bVolParts = volparts;
	
	sc_bReflect = water;
	sc_bWater = water;
	addBlurToView();
	sc_setup();
sc_dofDynFocus(10,500,1);
	//set skycube as non volumetric particle, this is needed. ALWAYS! (well, not always, but most of the time. It doesn't hurt to set this)
//	sc_skill(skycube,sc_myVolPart, 0);

// rendertarget resize-factor. 4 looks good in most cases
var sc_hdrRT = 9; 
// 16/32/64/128 hdr bitdepth
var sc_hdrBits = 32;

var sc_hdrParams[1] = {0.04, 8, 85, 0.08, 0.18, 0.8, 2};
// [0] = blurstrength 1 ("light scattering")
// [1] = blurstrength 2 (blurring)
// [2] = bloomstrength
// [3] = Highpass luminance
// [4] = Highpass middle grey
// [5] = Highpass white cutoff
// [6] = Dynamic Exposure Adaption Speed

//turn HDR on/off
var sc_bHDR = 1;



	//set light ray strength and length. These can be set during runtime to alter the effect in realtime
	sc_lightRayStr = 0.8;
	sc_lightRayLength = 5.5;
	sun_light=10;
	vec_set(d3d_lodfactor,vector(1,2,3)); 
	sky_clip=50;
	fog_color=4;
	d3d_fogcolor4.red=175;
d3d_fogcolor4.green=175;
	d3d_fogcolor4.blue=175;	
	sc_lightRays();
if(lightrays==1){	sc_lightRays();}

	//	set(sc_pan_sunDummy,SHOW);
  panel.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
  panel.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
  options_pan.pos_x = (screen_size.x/2)-300; 
  
  
  level_pan.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
  level_pan.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
  options_pan.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
  options_pan.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
    pause_p.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
  pause_p.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
  
  pan251.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
  pan251.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
  
  pan252.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
  pan252.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;

random_seed(0);
wait(1);

video_window(vector(0,0,0),vector(0,0,0),0,"Shadow");

reset(loading,SHOW);
}




action whore() // attached to the skeletons in the level
{
random_seed(0);
VECTOR temp;
reset(my,PASSABLE); 
enemy=me;
var current_height;
while(gmover==0)
{
if (pages<=11)
{
if(slender_see<0)
{
if (time>=time_lvl){    
if (vec_dist(player.x, me.x) > 700){
if (my.x>player.x){my.x=my.x-random(600);}
else {my.x=my.x+random(600);}
if (my.y>player.y){my.y=my.y-random(600);}
else {my.y=my.y+random(600);}
vec_set (temp.x, my.x);
temp.z -= 30000;
current_height = c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON);
my.z -= current_height;
my.z=my.z+80;
fireww.x=my.x;
fireww.y=my.y;
fireww.z=my.z;	
wait(-random(4));
}
if (vec_dist(player.x, me.x) < 700){
if (my.x>player.x){my.x=my.x-random(200);}
else {my.x=my.x+random(200);}
if (my.y>player.y){my.y=my.y-random(200);}
else {my.y=my.y+random(200);}
vec_set (temp.x, my.x);
temp.z -= 3000;
current_height = c_trace(my.x, temp.x,IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON);
my.z -= current_height;   my.z=my.z+80;
fireww.x=my.x;
fireww.y=my.y;
fireww.z=my.z;    
wait(-random(2));
}
}
if(time>=200 && time<=time_lvl){	 
if (rndm_i==0){random_seed(0);my.x=player.x+400+(random (900-time));my.y=player.y+400+(random (900-time));rndm_i=integer(random(4)); }
if (rndm_i==1){random_seed(0);my.x=player.x-400-(random (900-time));my.y=player.y+400+(random (900-time));rndm_i=integer(random(4)); }
if (rndm_i==2){random_seed(0);my.x=player.x+400+(random (900-time));my.y=player.y-400-(random (900-time));rndm_i=integer(random(4)); }
if (rndm_i==3){random_seed(0);my.x=player.x-400-(random (900-time));my.y=player.y-400-(random (900-time));rndm_i=integer(random(4)); }
vec_set (temp.x, my.x);
temp.z -= 3000;
current_height = c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON);
my.z -= current_height;
my.z=my.z+80;
fireww.x=my.x;
fireww.y=my.y;
fireww.z=my.z;
wait(-random(10));
}
}
wait(1);	
}
if (pages==11){my.z=-100;fireww.z=-100; wait(-10);}
}
}

action firew()
{
	fireww=me;	
	my.material = sc_mtl_obj_heatHaze;
   sc_skill(my, sc_myTexMov, 3);

   var temp[3];

   while(gmover==0)
   {
   
      //behave like a sprite -> face camera
      vec_set(temp,camera.x); 
      vec_sub(temp,my.x);
      vec_to_angle(my.pan,temp); 
      wait(1);
}
}
action tree()
{
	var current_height;

	VECTOR temp;
set(my,PASSABLE);
//my.pan= random(360);	
temp.z -= 3000;
       current_height = c_trace(my.x, temp.x, IGNORE_MODELS | IGNORE_PASSABLE)+40;
       my.z -= current_height;
       while(gmover==0){
       	wait(10);
		if (vec_dist(player.x, me.x) > 2000){set(my,INVISIBLE);
			
		}
		else
		{reset(my,INVISIBLE);
		}
}
}

function see_wh()
{
	var see_whore=0;
	while (player_live>1)
{
	wait(1);
	if (slender_see==-1)
		{
			see_whore=0;
		}
	if (see_whore==0){
		if (slender_see==10){
			c_trace (player.x,enemy.x,USE_POLYGON|IGNORE_FLAG2);
			if (you == enemy){
				if (vec_dist(player.x, enemy.x) < 700)
				{
					media_play("scr6.wav",NULL,100);
					see_whore=1;
					wait(-10);
				}
				if (vec_dist(player.x, enemy.x) > 700)
				{
					see_whore=1;
					wait(-10);
				}
			}
			
		}
		
	}
}	
}