///////////////////////////////////////////////////////////////////////////////////////////
#define PRAGMA_PATH "shade-c"
#define PRAGMA_PATH "stuff"

#include <litec.h>
#include <d3d9.h> // <--- THIS IS IMPORTANT!
#include <acknex.h>
#include <default.c>
var gmover=0;
#include "sc_core.c"

#include "sc_pp.c"
#include "sc_pp.h"
#include "sc_core.h"
#include "rain.c"
#include "water_drops.c"
#include <mtlView.c>
//#include <ppSsao.c>
#include <ackphysx.h>
ENTITY* enemy;
var lvl6shadow_health=10000; 
#include "weapons7.c"

var resolution_sc=12; 
// Screen Resolution 1-12
// 1 320x200 (window only)  
// 2 320x240 (window only)  
// 3 320x400 (window only) 
// 4 400x300 (window only) 
// 5 512x384 (window only) 
// 6  640x480, 640x400, 640x352  
// 7 800x600, 720x480, 848x480 (default) 
// 8 1024x768, 1024x600  
// 9 1280x1024, 1280x800, 1280x720  
// 10  1400x1050, 1440x900  
// 11 1600x1200, 1680x1050  
// 12 1920x1200, 1920x1080 

var windowed_sc=1; 
// 1 - Fullscreen mode. 
// 2 - Window mode (default). 

var fps_mlim=60;
//Limits the frame rate from 10 to 400, or 0 for no limit

var vert_synh=1;
// 1- Enables Vertical Sync

var antialias=9;
// 0 - No antialiasing.
// 1 - Full scene antialiasing in 3D card default mode.
// 4 - Full scene antialiasing with 4 samples per pixel. 
// 9 - Full scene antialiasing with 9 samples per pixel. 

var DOF=1; 
// 1 - Enables Depth of Field Effect

var Reflact=1; 
// 1 - Enables Refraction

var volparts=1;
// 1 - Enables Volumetric Particles

var lightrays=1;
// 1 - Enables Light Rays from sun

var tripplebuffer=1; 
// 0 - Double buffering
// 1 - Triple buffering 

var hdr=1;
// 1- Enables High Dynamic Range Rendering

var shaders=1;
// 1- activate shaders
// 0- disable all shaders. HDR, LightsRays, VolParts, Reflact, DOF- auto turn off

var lvl1treedist=3000;
// Level 1 tree visible distance (2000 default)

var lvl2dist=3000;
// Level 2 vegetation visible distance (2000 default)

var lesson=1;// 0\1

function show_pages();
var lighter_on;
var rndm_i;
var walk_spd=4;
var run_spd=8;
var rndm_c;
var flash_light=2000;
var time;
var player_life=100;
var dist_attack;
var pages=0;
var game_stats=6;



function addsobel();
var frame25;
#include "vegetation.c"

#include <mtlFX.c>
function addBlur();
function removeBlur();

#include "player.c"
SOUND* foot = "toprak.wav";
#include "svegetation.c"
var number_of_bushes=1;
var sMove = 1;
ENTITY* menuhandle;
ENTITY* mqhandle;
ENTITY* noizehandle;
var hiz;
var handles;
var slender_see;
var trigger;
ENTITY* fireww;
BMAP* mouse_pcx = "mouse.png"; 

var pause_active=0;
////////////////////////////////////////////////////////////////////////////////////////////
 
 	

str_cpy(save_dir,"saves");
function continue_game(); 
function see_wh();
function start_lvl4();


var ggg;
var enemy_z;
FONT* arial_font = "Arial#50";
FONT* digit_font = "Tipbrush Script#50";
FONT* digit_font1 = "Tipbrush Script#80b";
PANEL* pages_pan =
{

 //digits (  0, 0, "Spheres %.0f", digit_font, 1,pages); 
 layer=99;
   //digits (  0, 40, "Health %.0f", digit_font, 1, ggg);
 // digits (  0, 60, "See %.0f", digit_font, 1,  slender_see);
  digits (  0, 80, "SHADOW %.0f", digit_font, 1,  lvl6shadow_health);
  flags =  SHOW;
  flags= transparent;
  
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

BMAP* n1 = "Random3D.dds";
BMAP* n2 = "NoiseVolume.dds";

VIEW* tv_view= { layer=999999; flags=PROCESS_TARGET; }

MATERIAL* old_tv_mat =
{
//	skin1 =n2;
	skin2 =n1;

	effect = "old_tv.fx";
}

var tv_check=0;

void tv_film()
{
	if(tv_check==0)
	{
		tv_view.material = old_tv_mat;	
		camera.stage = tv_view;	
		tv_check=1;
	}
	else
	{
		tv_view.material = NULL;	
		camera.stage = NULL;	
		tv_check=0;
	}
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
function settings_show();

PANEL* panel = //„Î‡‚ÌÓÂ ÏÂÌ˛
{
	bmap = "menu.PNG";
  
	button (355, 290, "button.png", "button.png", "button.png", select_lvl, NULL, NULL); 
	button (350, 375, "button.png", "button.png", "button.png", options_show, NULL, NULL); 
	button (365, 407, "button.png", "button.png", "button.png", quit_program, NULL, NULL); 
		button (349, 339, "button.png", "button.png", "button.png", settings_show, NULL, NULL); 
   digits (  320, 0, "Version 0.2.1", digit_font, 3, NULL);
      digits (  355, 290, "Start", digit_font, 3, NULL);
         digits (  349, 339, "Options", digit_font, 3, NULL);
            digits (  350, 375, "Authors", digit_font, 3, NULL);
               digits (  365, 407, "Exit", digit_font, 3, NULL);
                  digits (  330, 200, "Shadow", digit_font1, 3, NULL);
	flags = OVERLAY | visible | transparent;

}
ENTITY* wh;
action whore_intro()
{
	me=wh;
}
PANEL* subtitles1 = //Ò‡·˚
{
   digits (  100, 200, "Use W,A,S,D to move", digit_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles2 = //Ò‡·˚
{ 
   digits (  100, 200, "Use mouse to look around", digit_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles3 = //Ò‡·˚
{ 
   digits (  100, 200, "Press W twice to run", digit_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles4 = //Ò‡·˚
{ 
   digits (  100, 200, "You found the key", digit_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles5 = //Ò‡·˚
{ 
   digits (  100, 200, "Use Left Mouse Button to take a Sphere", digit_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles6 = //Ò‡·˚
{ 
   digits (  100, 200, "SHADOW", digit_font1, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles7 = //Ò‡·˚
{ 
   digits (  100, 200, "Develop by Dima 'VoroneTZ'", digit_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles8 = //Ò‡·˚
{ 
   digits (  100, 200, "Game Studio A8 engine", digit_font, 3, NULL);
	flags = OVERLAY;
}
PANEL* subtitles9 = //Ò‡·˚
{ 
   digits (  100, 200, "Shade-C shader library", digit_font, 3, NULL);
	flags = OVERLAY;
}

PANEL* level_pan = //„Î‡‚ÌÓÂ ÏÂÌ˛
{
	bmap = "menu.PNG";
  
	button (355, 290, "button.png", "button.png", "button.png", intro_city, NULL, NULL); 
	button (355, 325, "button.png", "button.png", "button.png", start_lvl1, NULL, NULL); 
	button (355, 360, "button.png", "button.png", "button.png", start_lvl2, NULL, NULL); 
	button (355, 395, "button.png", "button.png", "button.png", start_lvl3, NULL, NULL); 
	button (355, 430, "button.png", "button.png", "button.png", start_lvl4, NULL, NULL); 
	button (355, 465, "button.png", "button.png", "button.png", start_lvl5, NULL, NULL); 
	button (355, 500, "button.png", "button.png", "button.png", start_lvl6, NULL, NULL); 
	button (365, 535, "button.png", "button.png", "button.png", main_menu_show, NULL, NULL); 

      digits (  355, 290, "Intro", digit_font, 3, NULL);
      digits (  355, 395, "Level 3", digit_font, 3, NULL);
      digits (  355, 360, "Level 2", digit_font, 3, NULL);
      digits (  355, 325, "Level 1", digit_font, 3, NULL);
      digits (  355, 430, "Level 4", digit_font, 3, NULL);
      digits (  355, 465, "Level 5", digit_font, 3, NULL);
      digits (  355, 500, "Level 6", digit_font, 3, NULL);
      digits (  365, 535, "Back", digit_font, 3, NULL);
      digits (  330, 200, "New Game", digit_font1, 3, NULL);
	flags = OVERLAY | transparent;

}


function close_lvl()
{
	player_life=-10;
}
PANEL* pause_p = //Ô‡ÛÁ‡
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
	panel.alpha=100;
		level_pan.alpha=0;
	set(level_pan,SHOW);
	while(panel.alpha>=0)
	{
		panel.alpha-=10*time_step;
			level_pan.alpha+=10*time_step;
		wait(1);
	}
	reset(panel,SHOW);
	panel.alpha=100;
	
}
PANEL* loading =
{
	bmap = "options.png";
  digits (  20, 0, "Loading...", digit_font, 3, NULL);
layer = 99;

flags= transparent;
}

PANEL* black =
{
	bmap = "options.png";
 // digits (  20, 0, "Loading...", digit_font, 3, NULL);
layer = 9;

flags= SHOW | transparent;
}

PANEL* vtzgames =
{
//	bmap = "options_pan.png";
  digits (  0, 0, "VTZ Games presents...", digit_font, 3, NULL);
layer = 99;

flags= transparent;
}

PANEL* engine =
{
//	bmap = "options_pan.png";
  digits (  0, 0, "A8 Engine", digit_font, 3, NULL);
layer = 99;

flags= transparent;
}

PANEL* shadow_panel =
{
	//bmap = "options_pan.png";
  digits (  0, 0, "SHADOW", digit_font1, 8, NULL);
layer = 99;

flags= transparent;
}

PANEL* warning =
{
//	bmap = "warning.dds";
//  digits (  20, 0, "Loading...", digit_font, 3, NULL);
layer = 99;

//flags= SHOW;
}




PANEL* options_pan;

function save_program()
{	reset(options_pan,SHOW);
	set(panel,SHOW);
result = game_save("options",1,SV_ALL);
if (result <= 0) {printf("Save Error!"); } 

	
}
function donate()
{
	exec("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=9Q5347VH2TEX2",NULL);
}
PANEL* options_pan = //Ì‡ÒÚÓÈÍË
{
	digits (  340, 20, "Authors", digit_font1, 3, NULL);
	
	digits (  290, 120, "Develop by Dima 'VoroneTZ'", digit_font, 3, NULL);
 	//digits (  290, 280, "As DanteeZ", digit_font, 3, NULL); 
 	digits (  100, 220, "Vladislava ' Danteez ' , Iliya ' kyjlu4uk ' , Rostislav ' Zed Up '", digit_font, 3, NULL);
 	digits (  320, 180, "Special thanks", digit_font, 3, NULL);
 	digits (355,524,"DONATE",digit_font,3,NULL);

	
	digits (  366, 564, "Back", digit_font, 3, NULL);
 	button (366, 564, "button.png", "button.png", "button.png", main_menu_show, NULL, NULL); 
 	button (366, 524, "button.png", "button.png", "button.png", donate, NULL, NULL); 
	flags = OVERLAY | TRANSLUCENT;
}

function max_graph()
{
var shaders=1;
	result = game_save("save",1,SV_VARS);
if (result <= 0) { error("Save Error!"); }
}
function min_graph()
{
var shaders=0;
	result = game_save("save",1,SV_VARS);
if (result <= 0) { error("Save Error!"); }
}

PANEL* settings_pan = //Ì‡ÒÚÓÈÍË
{
	digits (  340, 20, "Ortions", digit_font1, 3, NULL);
	
	digits (  290, 120, "Graphics", digit_font, 3, NULL);
 	digits (  290, 280, "You need restart to accept the changes", digit_font, 3, NULL); 
 	digits (  320, 220, "Maximum", digit_font, 3, NULL);
 	digits (  320, 180, "Minimum", digit_font, 3, NULL);
 

	
	digits (  366, 564, "Back", digit_font, 3, NULL);
 	button (366, 564, "button.png", "button.png", "button.png", main_menu_show, NULL, NULL); 
 	button (320, 180, "button.png", "button.png", "button.png", min_graph, NULL, NULL); 
 	button (320, 220, "button.png", "button.png", "button.png", max_graph, NULL, NULL); 
	flags = OVERLAY | TRANSLUCENT;
}
function settings_show()
{
		panel.alpha=100;
		settings_pan.alpha=0;
	set(settings_pan,SHOW);
	while(panel.alpha>=0)
	{
		panel.alpha-=10*time_step;
			settings_pan.alpha+=10*time_step;
		wait(1);
	}
	reset(panel,SHOW);
	panel.alpha=100;
}
void addnegative()
{
//mtl_dilate !!mtl_sobel   old_tv_mat
if (shaders==1){
   sc_ppAdd(mtl_negative, camera, 0);
	wait(5);
	sc_ppRemove(mtl_negative, camera, 0);
}
}

void addsobel()
{
//mtl_dilate !!   old_tv_mat
if (shaders==1){
   sc_ppAdd(mtl_sobel, camera, 0);
	wait(5);
	sc_ppRemove(mtl_sobel, camera, 0);
}
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
	
	set(panel,SHOW);
panel.alpha=0;

	set(panel,SHOW);
	while(panel.alpha<=100)
	{
		panel.alpha+=10*time_step;
			options_pan.alpha-=10*time_step;
			level_pan.alpha-=10*time_step;
			settings_pan.alpha-=10*time_step;
		wait(1);
	}
reset(options_pan,SHOW);
		reset(level_pan,SHOW);
	reset(settings_pan,SHOW);
	
}

function options_show()
{
	panel.alpha=100;
		options_pan.alpha=0;
	set(options_pan,SHOW);
	while(panel.alpha>=0)
	{
		panel.alpha-=10*time_step;
			options_pan.alpha+=10*time_step;
		wait(1);
	}
	reset(panel,SHOW);
	panel.alpha=100;
}
var player_live=10;
var trace_dist = 0;



function pause_game()
{
on_esc=nothing;
pause_active=1;
	mouse_mode = 4;
		freeze_mode = 1;
	set(pause_p,SHOW);
	 pause_p.alpha = 0; // Panel 100% transparent
while (pause_p.alpha < 100)
{
  pause_p.alpha += 2*time_step; 
  wait(1);
} 
	on_esc=continue_game;
	

}
void removeminetcka()
{
	if (shaders==1){
    sc_ppRemove(old_tv_mat, camera, 0);
 //    sc_ppRemove(mtl_dilate, camera, 0);
 }
}

function game_over()
{
//	sys_exit(123);
	reset(pause_p,SHOW);
	//	media_stop(noizehandle);
	removeBlur();
	reset(pages_pan,SHOW);
	media_stop(mmhandle);
	media_stop(mqhandle);
number_rock=0;
number_pages=0;
number_bush=0;
removeminetcka();
number_bush2=0;
number_tree=0;
gmover=1;
on_esc=nothing;
	mouse_mode = 4;
		detail_size = 10;
			freeze_mode = 0;
			pages=0;
		sun_light=1;
			fog_color=4;
	d3d_fogcolor4.red=175;
d3d_fogcolor4.green=175;
	d3d_fogcolor4.blue=175;	
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
 tv_pan.alpha -= 2*time_step; 
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
function start_lvl1();
function start_lvl2();
function start_lvl3();
action firew();

ENTITY* ending;
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
	removeminetcka();
	gmover=1;
	if(game_stats==1){game_stats=2;}
	result = game_save("save",1,SV_VARS);
if (result <= 0) { error("Save Error!"); }

start_lvl2();
}
action cutscene2_anim()
{
	wait(-1);
   while(1) 
   {
      my.skill1 += 2*time_step;
      if (my.skill1 > 95) my.skill1 = 95; 
      ent_animate(me,"Frame",my.skill1,ANM_CYCLE);
      wait(1);
   }
  
}
action cutscene3_anim()
{
//	wait(-1);
   while(1) 
   {
      my.skill1 += 2*time_step;
      //if (my.skill1 > 95) my.skill1 = 95; 
      ent_animate(me,"animation",my.skill1,ANM_CYCLE);
      wait(1);
   }
  
}
action cutscene3_animwall()
{
wait(-1);
	media_play ("cut2.wav", NULL, 100);
my.z=10000;
}
action car_y_intro()
{
	wait(-5);
	while(1)
	{
		my.y=my.y+40*time_step;
		wait(1);
	}
}

action car_y2_intro()
{
	wait(-5);
	while(1)
	{
		my.y=my.y-40*time_step;
		wait(1);
	}
}

action car_x_intro()
{
while(1){
	wait(1);
	while(time==1){	
	my.x=my.x-40*time_step;
	if(my.x<=1230)
	{
		time=2; break;
		}
	wait(1);
	}
}
}
function cut_scene_level2()
{
	on_esc=nothing;
player_live=0;
media_play ("scr6.wav", NULL, 100);
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 2*time_step; 
 
  wait(1);
}
		
media_play("cut1.wav", NULL, 100);
	camera.x=-21781;
	camera.y=-14582;
	camera.z=2152;
	camera.pan=226;
	camera.tilt=-8;
	ent_create ("shadow2.mdl", vector(-22823, -15651, 2147), cutscene2_anim);
gmover=1;


while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10*time_step; 
 
  wait(1);
}
wait(-2);
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 2*time_step; 
 
  wait(1);
}
	player_life=100;
	player_live=100;
	removeminetcka();
	 	media_stop(mmhandle);
	media_stop(mqhandle);
	pages=0;
	time=0;
	if(game_stats==2){game_stats=3;}
		result = game_save("save",1,SV_VARS);
if (result <= 0) { error("Save Error!"); }
start_lvl3();
}

function cut_scene_level3()
{
	on_esc=nothing;
player_live=0;
media_play ("scr6.wav", NULL, 100);
	camera.x=4295;
	camera.y=964;
	camera.z=2;
	camera.pan=180;
	
	ent_create ("shadow3l.mdl", vector(3677, 925, -93), cutscene3_anim);

	ent_create ("wall22.mdl", vector(3835, 963, 2), cutscene3_animwall);
	wait(-2);
gmover=1;
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 2*time_step; 
 
  wait(1);
}
		
while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 2*time_step; 
 
  wait(1);
}
	
	media_stop(mmhandle);
	media_stop(mqhandle);
	player_life=100;
	player_live=100;
	removeminetcka();
	if(game_stats=3){game_stats=4;}
	
		result = game_save("save",1,SV_VARS);
if (result <= 0) { error("Save Error!"); }
	
start_lvl4();
}

void addminetcka()
{
	if (shaders==1){
   sc_ppAdd(old_tv_mat, camera, 0);
  // sc_ppAdd(mtl_dilate, camera, 0);
}
} 
void removeBlur()
{
	if (shaders==1){
    sc_ppRemove(sc_mtl_pp_radialBlur, camera, 0);
    }
}

void addBlur()
{
	if (shaders==1){
   sc_ppAdd(sc_mtl_pp_radialBlur, camera, 0); 
   }
} 



function intro_city()
{
set(loading,SHOW);
set(tv_pan,SHOW);	
tv_pan.alpha = 0;
loading.alpha = 0; // Panel 100% transparent
while (loading.alpha < 100)
{
  loading.alpha += 2*time_step; 
  wait(1);
}	
		camera.clip_near=0;
	camera.clip_far=10000;
	camera.fog_start = 0; 
	camera.fog_end = 8000;
reset (level_pan,SHOW);
time=0;
level_load ("intro.wmb");	
//on_esc=skip_intro;
camera.x=916;
camera.y=-448;
camera.z=38;

//camera.roll=5;
camera.pan=270;
	mouse_mode=0;
while (loading.alpha > 0)
{
  loading.alpha -= 2*time_step; 
  wait(1);
} 
while(time==0){
	camera.y=camera.y-10*time_step;
	//8976
if (camera.y<=-600){if (camera.y>=-1700)
{set(subtitles8,SHOW);
	}
	else{reset(subtitles8,SHOW);
	}
}
	if (camera.y<=-2200){if (camera.y>=-3300)
	{set(subtitles9,SHOW);
	}
	else{reset(subtitles9,SHOW);
	}
}
	if (camera.y<=-3800){if (camera.y>=-4900)
	{set(subtitles7,SHOW);
	}else{reset(subtitles7,SHOW);
	}
}
	if (camera.y<=-5400){if (camera.y>=-6500)
	{set(subtitles6,SHOW);
	}else{reset(subtitles6,SHOW);
	}
}
if(camera.y<=-7337){time=1;
	}
	wait(1);
}
while(camera.pan<=359){camera.pan=camera.pan+10*time_step; wait(1);
}
addBlur();
while(time==1){
	camera.arc=camera.arc+1;
	wait(1);
		}
		addnegative();
		wait(1);
		media_stop(menuhandle);
removeBlur();
camera.arc=60;
set(loading,SHOW);
set(tv_pan,SHOW);	
tv_pan.alpha = 0;

  loading.alpha = 100; 
	

level_load ("intro1.wmb");	
camera.x=128;
camera.y=-45;
camera.z=61;
camera.roll=5;
camera.pan=180;
	mouse_mode=0;
while (loading.alpha > 0)
{
  loading.alpha -= 2*time_step; 
  wait(1);
} 
set(subtitles2,SHOW);
media_play("intro1.wav",NULL,100);
wait(-2);

wait(-1);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10*time_step; 
 
  wait(1);
}
reset(subtitles2,SHOW);
camera.x=580;
camera.y=-90;
camera.z=119;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10*time_step; 
 
  wait(1);
}
wait(-1);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10*time_step; 
 
  wait(1);
}
camera.x=128;
camera.y=-45;
camera.z=61;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10*time_step; 
 
  wait(1);
}
wait(-1);
media_play("intro2.wav",NULL,100);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10*time_step; 
 
  wait(1);
}

camera.x=587;
camera.y=281;
camera.z=122;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10*time_step; 
 
  wait(1);
}
wait(-1);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10*time_step; 
 
  wait(1);
}
camera.x=128;
camera.y=-45;
camera.z=61;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10*time_step; 
 
  wait(1);
}

wait(-1);
media_play("intro3.wav",NULL,100);

wait(-2);

wait(-1);
media_play("intro4.wav",NULL,100);

wait(-1);

wait(-1);
media_play("intro5.wav",NULL,100);

wait(-1);

wait(-1);
media_play("intro6.wav",NULL,100);

wait(-2);

wait(-1);
media_play("intro7.wav",NULL,100);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10*time_step; 
 
  wait(1);
}

camera.x=648;
camera.y=766;
camera.z=122;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10*time_step; 
 
  wait(1);
}
wait(-1);

while (tv_pan.alpha < 100)
{
  tv_pan.alpha += 10*time_step; 
 
  wait(1);
}
camera.x=128;
camera.y=-45;
camera.z=61;

while (tv_pan.alpha > 00)
{
  tv_pan.alpha -= 10*time_step; 
 
  wait(1);
}

wait(-1);
media_play("intro8.wav",NULL,100);

wait(-2);

wait(-1);
ent_create ("shadow.mdl", vector(-30,-45,51), NULL); 
wait(-2);
addnegative();
if(game_stats==0){game_stats=1;}
	result = game_save("save",1,SV_VARS);
if (result <= 0) { error("Save Error!"); }
start_lvl1();


}

function start_lesson()
{
	wait(-5);
	set(subtitles1,SHOW);
	wait(-5);
	reset(subtitles1,SHOW);
		wait(-5);
	set(subtitles3,SHOW);
	wait(-5);
	reset(subtitles3,SHOW);
		wait(-5);
	set(subtitles5,SHOW);
	wait(-5);
	reset(subtitles5,SHOW);
	lesson=1;
}

function start_lvl1()
{
	if (game_stats>=1){
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
set(loading,SHOW);
on_esc=nothing;

gmover=0;
walk_spd=4;
run_spd=8;
loading.alpha = 0; // Panel 100% transparent
while (loading.alpha < 100)
{
  loading.alpha += 2*time_step; 
 
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
	addminetcka();
	
	wait(-1);
		camera.tilt=0;
///////////////////////////—¬≈“, ¬—≈Ã Õ”∆≈Õ —¬≈“
flash_light=2000;
//	d3d_lightres = 250;
	player.lightrange = flash_light;   
	
	player.flags |= SPOTLIGHT|CAST|LIGHT;

	//vec_set(player.blue,vector(255,100,100));
///////////////////////////œ––◊¿ﬂ ’–≈Õ‹

//	media_loop("back.mp3", NULL, 100);	
	//	sc_dofDynFocus(400,50000,1);
	reset(level_pan,SHOW);
	mouse_mode=0;
//	set(pages_pan,SHOW);
	mqhandle = media_loop("noize.mp3",NULL,0);

//	noizehandle = media_loop("noize.mp3",NULL,0);
	
loading.alpha = 100; // Panel 100% transparent
while (loading.alpha > 0)
{
  loading.alpha -= 2*time_step; 
   media_tune(menuhandle,loading.alpha,0,0);
  wait(1);
} 
	media_stop(menuhandle);
on_esc=pause_game;
frame_25();
on_esc=pause_game;
	reset(loading,SHOW);
	set(tv_pan,SHOW);
	see_wh();
	if (lesson==0){
	start_lesson();
	}
	while(1)
	{
		if (pages==11){if (vec_dist(player.x,ending.x)<=50)
{cut_scene_level1(); reset(subtitles4,SHOW);
wait(1);
break;
}
}	
///////////////////////////  ¿Ã≈–¿
if (camera.tilt>=90){camera.tilt=90;}
if (camera.tilt<=-60){camera.tilt=-60;}
	player.lightrange = flash_light; 
if(flash_light>=10){flash_light=2000-time*2;}

///////////////////////////¬»ƒ»Ã ƒ≈¡»À¿?
		if (pages==11)
{set(subtitles4,SHOW);
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
if (player_life<100){player_life+=0.5*time_step;}
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
player_life=player_life-(dist_attack*time_step);}

	}
	else
	{
	if(pause_active==0){
if (player_life<100){player_life+=0.5*time_step;}
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


			if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}
			if (vec_dist(player.x, enemy.x) < 100){media_play("scr6.wav",NULL,100);camera.arc=120;camera.x=1586; camera.y=1487; camera.z=-318; camera.pan= 181; camera.tilt=29;slender_see=10;	player_live=0; addnegative();
	while(player_life>1){ 	
				
		media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);
			//camera.pan=enemy.pan+180;
			player_life=player_life-1*time_step;
	
		wait(1);
			}
			gmover=1;game_over();break;
		}

///////////////////////////’›À—¿

	
media_tune(mqhandle,100-player_life,0,0);
//media_tune(noizehandle,100-(vec_dist(player.x,enemy.x)/2),0,0);
tv_pan.alpha = 100-((player_life/2)+50);

wait (1);
		
	}

}
}


function start_lvl2()
{
		if (game_stats>=2){
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
set(loading,SHOW);
gmover=0;
walk_spd=4;
run_spd=8;

loading.alpha = 0; // Panel 100% transparent
while (loading.alpha < 100)
{
  loading.alpha += 2*time_step; 
  wait(1);
}
time=0;
//detail_size = 100;
	level_load ("level2.wmb");
	addminetcka();
	wait(-1);
//	noizehandle = media_loop("noize.mp3",NULL,0);
sun_light=1;
///////////////////////////—¬≈“, ¬—≈Ã Õ”∆≈Õ —¬≈“

//	d3d_lightres = 250;
//	player.lightrange = 2000;   
//	set(player,SPOTLIGHT);

///////////////////////////œ––◊¿ﬂ ’–≈Õ‹
		camera.tilt=0;
//	media_loop("back.mp3", NULL, 100);	
//	sc_dofDynFocus(400,50000,1);
	reset(level_pan,SHOW);
	mouse_mode=0;
//	set(pages_pan,SHOW);
	mqhandle = media_loop("noize.mp3",NULL,0);
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
	see_wh();
	while(1)
	{
		if (pages==11)
{cut_scene_level2();
wait(1);
break;
}
if (camera.tilt>=90){camera.tilt=90;}
if (camera.tilt<=-60){camera.tilt=-60;}
//media_tune(noizehandle,ggg,0,0);
///////////////////////////¬»ƒ»Ã ƒ≈¡»À¿?
if (vec_dist(player.x,enemy.x)<=1000){
ggg=100-(vec_dist(player.x,enemy.x)/20);}
else{ggg=1;}
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
if (player_life<100){player_life+=0.5*time_step;}
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
player_life=player_life-(dist_attack*time_step);}

	}
	else
	{
	if(pause_active==0){
if (player_life<100){player_life+=0.5*time_step;}
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

if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}
			if (vec_dist(player.x, enemy.x) < 100){media_play("scr6.wav",NULL,100);camera.arc=120;camera.x=1586; camera.y=1487; camera.z=1470; camera.pan= 181; camera.tilt=29;slender_see=10;	player_live=0; addnegative();
	while(player_life>1){ 	
				
		media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);
			//camera.pan=enemy.pan+180;
			player_life=player_life-1;
	
		wait(1);
			}
			gmover=1;game_over();break;
		}

///////////////////////////’›À—¿

	
media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);

wait (1);
		
	}

}
}



function start_lvl3()
{
		if (game_stats>=3){
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
set(loading,SHOW);
gmover=0;
walk_spd=4;
run_spd=8;

loading.alpha = 0; // Panel 100% transparent
while (loading.alpha < 100)
{
  loading.alpha += 2*time_step; 
 
  wait(1);
}
 
time=0;
detail_size = 100;
fog_color=1;
	sun_light=1;
		camera.clip_near=0;
	camera.clip_far=8000;
	camera.fog_start = 0; 
	camera.fog_end = 2000;
	pages=0;
		sky_color.red = 1;
	sky_color.green = 0;
	sky_color.blue = 0;
	level_load ("level3.wmb");

		camera.tilt=0;
			addminetcka();
	wait(-1);


///////////////////////////œ––◊¿ﬂ ’–≈Õ‹

//	media_loop("back.mp3", NULL, 100);	
	//	sc_dofDynFocus(400,50000,1);
	reset(level_pan,SHOW);
	mouse_mode=0;
//	set(pages_pan,SHOW);
//	mqhandle = media_loop("PSY.wav",NULL,0);


	
loading.alpha = 100; // Panel 100% transparent
while (loading.alpha > 0)
{
  loading.alpha -= 2*time_step; 
   media_tune(menuhandle,loading.alpha,0,0);
  wait(1);
} 
	media_stop(menuhandle);
on_esc=pause_game;
frame_25();
	reset(loading,SHOW);
	set(tv_pan,SHOW);
	see_wh();
	while(1)
	{
			if (pages==9)
{cut_scene_level3();
wait(1);
reset(pages_pan,SHOW);
break;
}
///////////////////////////  ¿Ã≈–¿
if (camera.tilt>=90){camera.tilt=90;}
if (camera.tilt<=-60){camera.tilt=-60;}
//media_tune(noizehandle,100-(vec_dist(player.x,enemy.x)/2),0,0);
///////////////////////////¬»ƒ»Ã ƒ≈¡»À¿?

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
if (player_life<100){player_life+=0.5*time_step;}
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
player_life=player_life-(dist_attack*time_step);}

	}
	else
	{
	if(pause_active==0){
if (player_life<100){player_life+=0.5*time_step;}
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
if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}
			if (vec_dist(player.x, enemy.x) < 100){media_play("scr6.wav",NULL,100);camera.arc=120;camera.x=1586; camera.y=1487; camera.z=1470; camera.pan= 181; camera.tilt=29;slender_see=10;	player_live=0; addnegative();
	while(player_life>1){ 	
				
		media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);
			//camera.pan=enemy.pan+180;
			player_life=player_life-1;
	
		wait(1);
			}
			gmover=1;game_over();break;
		}

///////////////////////////’›À—¿

	
media_tune(mqhandle,100-player_life,0,0);
tv_pan.alpha = 100-((player_life/2)+50);

wait (1);
		
	}

}
}

var lags=1; 

action teleporter1 ()
{
	while(1)
	{
		wait(2);
		if(vec_dist(player.x,my.x)<100){
			addnegative();
			player.x=-10031;
			player.y=1555;
			player.z=3190;
			camera.pan=90;
			player.tilt=0;
			walk_spd=8;
			lags=0;
run_spd=14;
break;
		}
	}
}

action teleporter2 ()
{
	while(1)
	{
		wait(2);
		if(vec_dist(player.x,my.x)<100){
			addnegative();
			player.x=382;
			player.y=-1845;
			player.z=527;
			media_tune(mqhandle,100,0,0);
		media_tune(noizehandle,0,0,0);
			player.tilt=0;
			walk_spd=6;
			lags=0;
			trigger=22;
run_spd=12;
break;
		}
	}
}


action trigger_sh()
{
	set(my,PASSABLE);
	while(1)
	{
	if (vec_dist(player.x,my.x)<=220){trigger+=1;break;}
		wait(1);
	}
}
function start_lvl4()
{
		if (game_stats>=4){
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
	set(loading,SHOW);
	gmover=0;
	walk_spd=2;
	trigger=0;
	run_spd=4;
	loading.alpha = 0; // Panel 100% transparent
	while (loading.alpha < 100)
	{
		loading.alpha += 2*time_step; 
		wait(1);
	} 
	time=0;
	reset(tv_pan,SHOW);
	detail_size = 100;
	fog_color=4;
	d3d_fogcolor4.red=175;
	d3d_fogcolor4.green=175;
	d3d_fogcolor4.blue=175;	
	sun_light=1;
	camera.clip_near=0;
	camera.clip_far=8000;
	camera.fog_start = 0; 
	camera.fog_end = 2000;
	level_load ("level4.wmb");
	//noizehandle = media_loop("slender 6.mp3",NULL,0);
	camera.tilt=0;
	addminetcka();
	wait(-1);
///////////////////////////œ–Œ◊¿ﬂ ’–≈Õ‹
mqhandle=	media_loop("dip.mp3", NULL, 70);	
	sc_dofDynFocus(400,50000,1);
	reset(level_pan,SHOW);
	mouse_mode=0;
	
	loading.alpha = 100; // Panel 100% transparent
	while (loading.alpha > 0)
	{
		loading.alpha -= 2*time_step; 
		media_tune(menuhandle,loading.alpha,0,0);
		wait(1);
	} 
	media_stop(menuhandle);
	on_esc=pause_game;
	reset(loading,SHOW);
	set(tv_pan,SHOW);
	while(1)
	{
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
	if (vec_dist(player.x,enemy.x)<=120){
			player_life=-1;}
				if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}
///////////////////////////  ¿Ã≈–¿
	if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}

		if (camera.tilt>=90){camera.tilt=90;}
		if (camera.tilt<=-60){camera.tilt=-60;}
		if(lags==1)
		{
			rndm_i=integer(random(300));
			if(rndm_i==1){addsobel();}
			if(rndm_i==2){addnegative();}
			if(rndm_i==3){addsobel();}
		}
		media_tune(mqhandle,100-player_life,0,0);
		tv_pan.alpha = 100-((player_life/2)+50);
		if (vec_dist(player.x,ending.x)<=100){
			addnegative();
			player.x=-25781;
			player.y=2383;
			player.z=3901;
			player.pan=339;
			lags=3;
			sun_light=100;
			media_tune(mqhandle,0,0,0);
			media_tune(noizehandle,100,0,0);
		}
		wait (1);		
	}
}
}

function start_lvl6()
{
	if (game_stats>=6){
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
	set(loading,SHOW);
	gmover=0;
walk_spd=4;
run_spd=8;



	loading.alpha = 0; // Panel 100% transparent
	while (loading.alpha < 100)
	{
		loading.alpha += 2*time_step; 
		wait(1);
	} 
	time=0;
	lvl6shadow_health=10000;
	detail_size = 100;
	fog_color=4;
	d3d_fogcolor4.red=175;
	d3d_fogcolor4.green=175;
	d3d_fogcolor4.blue=175;	
	sun_light=80;
	camera.clip_near=0;
	camera.clip_far=8000;
	camera.fog_start = 0; 
	camera.fog_end = 2000;
	level_load ("level6.wmb");
		//noizehandle = media_loop("noize.mp3",NULL,0);
	camera.tilt=0;
	addminetcka();
	wait(-1);
	//	snow(100,NULL);
///////////////////////////œ–Œ◊¿ﬂ ’–≈Õ‹
	media_loop("ki.mp3", NULL, 100);	
	sc_dofDynFocus(400,50000,1);
	reset(level_pan,SHOW);
	mouse_mode=0;
	mqhandle = media_loop("noize.mp3",NULL,0);	
	loading.alpha = 100; // Panel 100% transparent
	while (loading.alpha > 0)
	{
		loading.alpha -= 2*time_step; 
		media_tune(menuhandle,loading.alpha,0,0);
		wait(1);
	} 
	media_stop(menuhandle);
	on_esc=pause_game;
	reset(loading,SHOW);
	set(tv_pan,SHOW);
	while(1)
	{	
///////////////////////////  ¿Ã≈–¿
	if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}

		if (camera.tilt>=90){camera.tilt=90;}
		if (camera.tilt<=-60){camera.tilt=-60;}
		
		media_tune(mqhandle,100-player_life,0,0);
		tv_pan.alpha = 100-((player_life/2)+50);
	
	
		wait (1);		
	}
}
}

function start_lvl5()
{
	if (game_stats>=5){
///////////////////////////√–”«»Ã ”–Œ¬≈Õ‹
	set(loading,SHOW);
	gmover=0;
	walk_spd=4;
	run_spd=8;
	pages=9;


	loading.alpha = 0; // Panel 100% transparent
	while (loading.alpha < 100)
	{
		loading.alpha += 2*time_step; 
		wait(1);
	} 
	time=0;
	detail_size = 100;
	fog_color=4;
	d3d_fogcolor4.red=175;
	d3d_fogcolor4.green=175;
	d3d_fogcolor4.blue=175;	
	sun_light=80;
	camera.clip_near=0;
	camera.clip_far=15000;
	camera.fog_start = 0; 
	camera.fog_end = 2000;
	sun_light=100;
	level_load ("level5.wmb");
		//noizehandle = media_loop("noize.mp3",NULL,0);
	camera.tilt=0;
	addminetcka();
	wait(-1);
	//	snow(100,NULL);
///////////////////////////œ–Œ◊¿ﬂ ’–≈Õ‹
	//media_loop("kfs.mp3", NULL, 100);	
	sc_dofDynFocus(400,50000,1);
	reset(level_pan,SHOW);
	mouse_mode=0;
	mqhandle = media_loop("kfs.mp3",NULL,100);	
	loading.alpha = 100; // Panel 100% transparent
	while (loading.alpha > 0)
	{
		loading.alpha -= 2*time_step; 
		media_tune(menuhandle,loading.alpha,0,0);
		wait(1);
	} 
	media_stop(menuhandle);
	on_esc=pause_game;
	reset(loading,SHOW);
	set(tv_pan,SHOW);
	while(1)
	{	
	
	
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
	if (vec_dist(player.x,enemy.x)<=120){player_live=0;media_play("cut3.wav",NULL,100); wait(-13);media_stop(mqhandle);if(game_stats=5){game_stats=6;}
	
		result = game_save("save",1,SV_VARS);
	if (result <= 0) { error("Save Error!"); }start_lvl6();player_live=100;break;}
///////////////////////////  ¿Ã≈–¿
	//if (player_life<0){gmover=1;tv_pan.alpha=100;game_over();break;}

		if (camera.tilt>=90){camera.tilt=90;}
		if (camera.tilt<=-60){camera.tilt=-60;}
		
		media_tune(mqhandle,100-player_life,0,0);
		tv_pan.alpha = 100-((player_life/2)+50);
	
	
		wait (1);		
	}
	}
}

function continue_game()
{
	on_esc=nothing;
	mouse_mode = 0;
	freeze_mode = 0;
	pause_active=0;
	pause_p.alpha = 100; // Panel 100% transparent
	while (pause_p.alpha > 0)
	{
 		pause_p.alpha -= 2*time_step; 
 		wait(1);
	} 
	reset(pause_p,SHOW);
	on_esc=pause_game;	
}




function main()
{
	panel.alpha=100;
	menuhandle = media_loop("menu.mp3",NULL,100);
	detail_size = 10;
	set(black,SHOW);	
	max_entities = 99999;
	if (game_load("save",1) <= 0) { printf("Load Error! Reset to default settings"); } 
	var d3d_vsync = vert_synh;
	d3d_antialias = antialias;
	d3d_triplebuffer=tripplebuffer;
	mouse_map = mouse_pcx;	
	fps_max = fps_mlim; // limit the frame rate to 75 fps (not really needed)
	nexus=400;
	video_mode=resolution_sc;
	video_screen=windowed_sc;
// physX_open();
	wait(1);	
	level_load ("menu.wmb");
	sky_color.red = 1;
	sky_color.green = 0;
	sky_color.blue = 0;
	camera.x=364;
	camera.y=459;
	camera.z=60;
	camera.pan=213;
	camera.tilt=3;	
	camera.clip_near=0;
	camera.clip_far=3500;
	camera.fog_start = 0; 
	camera.fog_end = 3500;		
	sc_bHDR = hdr;
	sc_bDOF = DOF;
	sc_bRefract = Reflact;
	sc_bVolParts = volparts;	
	sc_bReflect =1;
	sc_bWater = 1;
	if (shaders==1)
	{	
		sc_setup();
		sc_lightRayStr = 0.8;
		sc_lightRayLength = 5.5;
	}
	sun_light=10;	
	vec_set(d3d_lodfactor,vector(1,2,3)); 
	sky_clip=50;
	fog_color=4;
	d3d_fogcolor4.red=175;
	d3d_fogcolor4.green=175;
	d3d_fogcolor4.blue=175;	
	if (lightrays==1)
	{
		sc_lightRays();
	}
	options_pan.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
	options_pan.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;	
	settings_pan.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
	settings_pan.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;	
	panel.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
	panel.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
	level_pan.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
	level_pan.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
	pause_p.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
	pause_p.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
  	warning.pos_x = (screen_size.x/2)-512; 
	warning.pos_y = (screen_size.y/2)-200; 
   vtzgames.pos_x = (screen_size.x/2)-70; 
	vtzgames.pos_y = (screen_size.y/2)-100;
	engine.pos_x = (screen_size.x/2)-40; 
	engine.pos_y = (screen_size.y/2)-100;
	shadow_panel.pos_x = (screen_size.x/2)-60; 
	shadow_panel.pos_y = (screen_size.y/2)-100;
	pan251.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
	pan251.pos_y = (screen_size.y - bmap_height(panel.bmap))/2; 
	pan252.pos_x = (screen_size.x - bmap_width(panel.bmap))/2; 
	pan252.pos_y = (screen_size.y - bmap_height(panel.bmap))/2;
	video_window(vector(0,0,0),vector(0,0,0),0,"SHADOW");	
	vtzgames.alpha=0;
	set(vtzgames,SHOW);
	while(vtzgames.alpha<=100)
	{
		vtzgames.alpha+=10*time_step;
		wait(1);	
	}
	wait(-2);
	while(vtzgames.alpha>=0)
	{
		vtzgames.alpha-=10*time_step;
		wait(1);
	}
	reset(vtzgames,SHOW);
	engine.alpha=0;
	set(engine,SHOW);
	while(engine.alpha<=100)
	{
		engine.alpha+=10*time_step;
		wait(1);
	}
	wait(-2);
	while(engine.alpha>=0)
	{
		engine.alpha-=10*time_step;
		wait(1);
	}
	reset(engine,SHOW);
	shadow_panel.alpha=0;
	set(shadow_panel,SHOW);
	while(shadow_panel.alpha<=100)
	{
		shadow_panel.alpha+=10*time_step;
		wait(1);
	}
	wait(-2);
	while(shadow_panel.alpha>=0)
	{
		shadow_panel.alpha-=10*time_step;
		wait(1);
	}
	mouse_mode = 4;
	reset(shadow_panel,SHOW);
	while(black.alpha>=0)
	{
		black.alpha-=10*time_step;
		wait(1);
	}
	reset(black,SHOW);
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
		if(slender_see<0)
			{
				if (time>=600)
					{    
						if (vec_dist(player.x, me.x) > 700)
							{
								if (my.x>player.x)
									{
										my.x=my.x-random(600);
									}
								else 
									{
										my.x=my.x+random(600);
									}
								if (my.y>player.y)
									{
										my.y=my.y-random(600);
									}
								else 
									{
									my.y=my.y+random(600);
									}
  								vec_set (temp.x, my.x);
   							temp.z -= 30000;
   							current_height = c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON);
   							my.z -= current_height;
								my.z=my.z+80;
								fireww.x=my.x;
  								fireww.y=my.y;
  								fireww.z=my.z;	
								wait(-random(4)*time_step);
							}
						if (vec_dist(player.x, me.x) < 700)
							{		
								if (my.x>player.x)
									{
										my.x=my.x-random(200);
									}
								else 
									{
										my.x=my.x+random(200);
									}
								if (my.y>player.y)
									{
										my.y=my.y-random(200);
									}
								else 
									{
										my.y=my.y+random(200);
									}
								vec_set (temp.x, my.x);
   							temp.z -= 3000;
   							current_height = c_trace(my.x, temp.x,IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON);
   							my.z -= current_height;   my.z=my.z+80;
   							fireww.x=my.x;
   							fireww.y=my.y;
   							fireww.z=my.z; 
								wait(-random(2)*time_step);
							}
					}
				if(time>=200 && time<=600)
					{	
						if (rndm_i==0)
							{
								random_seed(0);
								my.x=player.x+400+(random (900-time));
								my.y=player.y+400+(random (900-time));
								rndm_i=integer(random(4)*time_step); 
							}
						if (rndm_i==1)
							{
								random_seed(0);
								my.x=player.x-400-(random (900-time));
								my.y=player.y+400+(random (900-time));
								rndm_i=integer(random(4)*time_step); 
							}
						if (rndm_i==2)
							{
								random_seed(0)
								;my.x=player.x+400+(random (900-time));
								my.y=player.y-400-(random (900-time));
								rndm_i=integer(random(4)*time_step); 
							}
						if (rndm_i==3)
							{
								random_seed(0);
								my.x=player.x-400-(random (900-time));
								my.y=player.y-400-(random (900-time));
								rndm_i=integer(random(4)*time_step); 
							}
						vec_set (temp.x, my.x);
						temp.z -= 3000;
						current_height = c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON);
						my.z -= current_height;
						my.z=my.z+80;
						fireww.x=my.x;
						fireww.y=my.y;
						fireww.z=my.z;
						wait(-random(10)*time_step);
					}
		}
	wait(1);	
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
	temp.z -= 3000;
	current_height = c_trace(my.x, temp.x, IGNORE_MODELS | IGNORE_PASSABLE)+40;
	my.z -= current_height;
	while(gmover==0)
	{
		wait(10);
		if (vec_dist(player.x, me.x) > lvl1treedist)
			{
				set(my,INVISIBLE);	
			}
		else
			{
				reset(my,INVISIBLE);
			}
	}
}

action obj_invis()
{
	while(gmover==0)
	{
		wait(10);
		if (vec_dist(player.x, me.x) > lvl1treedist)
			{
				set(my,INVISIBLE);	
			}
		else
			{
				reset(my,INVISIBLE);
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
	if (see_whore==0)
	{
		if (slender_see==10)
			{
			c_trace (player.x,enemy.x,USE_POLYGON|IGNORE_FLAG2);
			if (you == enemy)
				{
				if (vec_dist(player.x, enemy.x) < 700)
					{
					media_play("scr6.wav",NULL,100);
					see_whore=1;
					addnegative();
					wait(-10*time_step);
					}
				if (vec_dist(player.x, enemy.x) > 700)
					{
					see_whore=1;
					wait(-10*time_step);
					}
				}			
			}		
		}
	}	
}

function show_pages()
{
	set(pages_pan,SHOW);
	pages_pan.alpha = 0; // Panel 100% transparent
	while (pages_pan.alpha < 100)
	{
 		 pages_pan.alpha += 2*time_step; 
 		 wait(1);
	}
	wait(-2);
	while (pages_pan.alpha > 0)
	{
 		 pages_pan.alpha -= 2*time_step; 
 		 wait(1);
	}
	reset(pages_pan,SHOW); 
}

action platform()
{
	while(1)
	{
		wait(1);
	if(vec_dist(my.x,player.x)<70)
	{
		wait(-2);
		while(my.x>=679)
		{
			my.x-=6;
		wait(1);
		}
	}
}
}

action platform_crash()
{
	while(1)
	{
		ent_animate(my,"Crash",1,ANM_CYCLE);
		wait(1);
	if(vec_dist(my.x,player.x)<=70)
	{
		wait(-1);
		set(my,PASSABLE);
		while(my.animate<=90){
			ent_animate(my,"Crash",my.animate,ANM_CYCLE);
		my.animate += 1 * time_step;
		my.z=my.z-10;
		wait(1);
		}
		my.z=-1000;
	}
}
}

action shadow_lvl4 ()
{
	set(my,UNLIT);
	enemy=me;
	while(player_life>=0)
	{
		wait(-1);
		if(trigger==1){my.x=-10010;my.y=718;my.z=3137;}
		if(trigger==2){my.x=-9698;my.y=-8;my.z=3064;}
		if(trigger==3){my.x=-9044;my.y=-217;my.z=2975;}
		if(trigger==4){my.x=-8305;my.y=-453;my.z=2945;}
		if(trigger==5){my.x=-7927;my.y=-931;my.z=3509;}
		if(trigger==6){my.x=-9205;my.y=-1539;my.z=2817;}
		if(trigger==7){my.x=-25200;my.y=2144;my.z=3879;}
		if(trigger==8){my.x=-24534;my.y=1934;my.z=3845;}
		if(trigger==9){my.x=-23163;my.y=1612;my.z=3676;}
		if(trigger==10){my.x=-23491;my.y=855;my.z=3583;}
		if(trigger==11){my.x=-24209;my.y=230;my.z=3481;}
		if(trigger==12){my.x=-25005;my.y=-552;my.z=3137;}
		if(trigger==13){my.x=-24856;my.y=-1415;my.z=2377;}
		if(trigger==14){my.x=-24239;my.y=-1267;my.z=2305;}
		if(trigger==15){my.x=-23750;my.y=-1598;my.z=2305;}
		if(trigger==16){my.x=-23001;my.y=-1807;my.z=2199;}
		if(trigger==17){my.x=-21593;my.y=-2351;my.z=2169;}
		if(trigger==18){my.x=-22261;my.y=-3266;my.z=2097;}
		if(trigger==19){my.x=-22869;my.y=-3904;my.z=2071;}
		if(trigger==20){my.x=-24215;my.y=-4811;my.z=2241;}
		if(trigger==21){my.x=-24780;my.y=-4981;my.z=2241;}
		if(trigger==22){my.x=-27796;my.y=-4445;my.z=2062;}
		if(trigger==23){if(game_stats=4){game_stats=5;}	
		result = game_save("save",1,SV_VARS);
		if (result <= 0) { 
			error("Save Error!"); 
			}
		start_lvl5(); media_stop(mqhandle);
		}
	}
}

action shadow_lvl6()
{
	enemy=me;
	while (lvl6shadow_health>=0)
	{
		wait(1);
		
		if (player.y>my.y)
		{
		if (player.x>my.x)
			{
			my.pan=asinv((player.y-my.y)/vec_dist(player.x, my.x));
			} 
		else 
			{
			my.pan=90+asinv((my.x-player.x)/vec_dist(player.x, my.x));
			}
		} 
		
		
		if (player.y<my.y)
		{ 
		if (player.x<my.x)
			{
			my.pan=180+asinv((my.y-player.y)/vec_dist(player.x, my.x));
			} 
		else 
			{
			my.pan=180+90+asinv((player.x-my.x)/vec_dist(player.x, my.x));
			}
		}
	}
}