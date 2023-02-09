#include <acknex.h>
#include <default.c>
#include <mtlView.c>
#include <ackphysx.h>
#include <mtlFX.c>
STRING* level_str = "menu.WMB"; 
STRING* cam = " ";
FONT* digit_font = "font.png";
TEXT* cam_text= 
{
	font = digit_font; 
	layer = 1; 
	string=cam; 
	flags =  center_x,center_y,VISIBLE; 
	pos_x = 512; 
	pos_y = 10; 
	alpha=100; 
	red = 75; 
	green = 128; 
	blue = 223; 
}
STRING* sprint = " ";
TEXT* sprint_text= 
{
	font = digit_font; 
	layer = 1; 
	string=sprint; 
	flags =  center_x,center_y,VISIBLE; 
	pos_x = 512; 
	pos_y = 20; 
	alpha=100; 
	red = 75; 
	green = 128; 
	blue = 223; 
}

ENTITY* skycube =
{
	type = "sky_night.pcx";
	flags2 =  TRANSLUCENT | SKY |DOME | VISIBLE;
	scale_x = 0.7; 
	tilt = 20;
	speed_u = 1; 
	speed_v = 1; 
	layer = 2; 
	alpha = 100; 
}
ENTITY* skycube2 =
{
	type = "clouds.tga";
	flags2 = TRANSLUCENT | SKY |DOME | VISIBLE;
	speed_u = 2; 
	speed_v = 8; 
	scale_x = 1.9; 
	scale_y = 1.9; 
	tilt = -5; 

	layer = 5; 
	alpha = 60; 
}
ENTITY* skycube3 =
{
	type = "clouds.tga";
	flags2 = TRANSLUCENT | SKY | DOME | VISIBLE;
	speed_u = 1; 
	speed_v = 5; 
	scale_y = 1.2; 
	scale_x = 1.2; 
	tilt = -6; 
	layer = 5; 
	alpha = 100; 
}

var resolution_sc; /// 1-12
var windowed_sc; ///   0-1
var vert_synh; //      0-1
var antialias;//       0-3
var DOF; //0-1
var Reflact; //       0-1
var volparts; //        0-1
var water;       //    0-1
var lightrays; //0-1
var tripplebuffer; //0-1
var hdr;

function quit_program()
{
sys_exit("123");
}
function save_program()
{
result = game_save("options",1,SV_ALL);
if (result <= 0) {printf("Save Error!"); } 
	
//	sys_exit("123");
	
}

PANEL* options_pan = //настройки
{
	digits (  0, 0, 6, digit_font, 1,vert_synh); 
  digits (  0, 20, 6, digit_font, 1,resolution_sc);
   digits (  0, 40, 6, digit_font, 1, windowed_sc);
	bmap = "options_pan.PNG";
	hslider(347,145,145,"slider.png",8,12,resolution_sc);
	hslider(347,181,145,"slider.png",1,2,windowed_sc);
	hslider(347,214,145,"slider.png",0,1,tripplebuffer);
	hslider(347,244,145,"slider.png",0,1,vert_synh);
	hslider(347,277,145,"slider.png",0,3,antialias);
	hslider(347,309,145,"slider.png",0,1,water);
	hslider(347,338,145,"slider.png",0,1,DOF);
	hslider(347,376,145,"slider.png",0,1,Reflact);
	hslider(347,407,145,"slider.png",0,1,volparts);
	hslider(347,442,145,"slider.png",0,1,lightrays);
	hslider(347,480,145,"slider.png",0,1,hdr);
 	button (334, 525, "button.png", "button.png", "button.png", save_program, NULL, NULL); 
 	button (366, 564, "button.png", "button.png", "button.png", quit_program, NULL, NULL); 
	flags = OVERLAY | visible;
}


void main()
{
	
	nexus=400;
	max_entities=20000;

	warn_level = 2;

	mouse_mode = 0;
	video_mode=8;
	video_screen=2;
	video_depth=32;
	//////////////////////	level_load(s_level);
	// now load the level
	level_load(level_str);
	wait(3);
	d3d_triplebuffer=1;
	//	ent_create("cbabe.mdl",vector(50,60,700),player1);
	//	ent_create("land.hmp",nullvector,Terrain);
	sun_light=10;
	vec_set(d3d_lodfactor,vector(50,60,70)); 
	sky_clip=50;
	fog_color=4;
	d3d_fogcolor4.red=175;
	d3d_fogcolor4.green=175;
	d3d_fogcolor4.blue=175;
	sky_color.red = d3d_fogcolor4.red; 
	sky_color.green = d3d_fogcolor4.green; 
	sky_color.blue = d3d_fogcolor4.blue; 
	camera.clip_near=0;
	camera.clip_far=3500;
	camera.fog_start = 0; 
	camera.fog_end = 3000;
	mouse_mode = 4;
	camera.x=364;
	camera.y=459;
	camera.z=60;
	camera.pan=213;
	camera.tilt=3;
	video_window(vector(0,0,0),vector(0,0,0),0,"Shadow-Options");
	wait(-1);
	if (game_load("options",1) <= 0) { printf("Load Error!"); } 
}
