#include <acknex.h>
#include <default.c>
#include "vegetation.c"
#include "player.c"
STRING* level_str = "main.WMB"; 
STRING* cam = " ";
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
STRING* sprint = "DOUBLE CLICK KEY_W FOR SPRINT";
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


var hiz;
var handles;
void foot_sound()
{
	while(1)
	{
		if(key_w==1)
		{
			handles=ent_playsound(player,foot,100);
		}
		if(sMove == 2){wait(15);}
		if(sMove == 1){wait(20);}
	}
	
}
void main()
{
	nexus=400;
	max_entities=20000;
	
	warn_level = 2;

	mouse_mode = 0;
	video_mode=12;
	video_screen=1;
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
	media_loop("back.mp3", NULL, 180);
	foot_sound();
	//	def_moveset();


}
