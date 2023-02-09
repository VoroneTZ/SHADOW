//cerberi_croman's code (user request topic)
//http://www.coniserver.net/ubb7/ubbthreads.php?ubb=showflat&Number=186382#Post186382

#define gravity skill30
#define zoffset skill31
var running;

#define animate skill32
#define animate2 skill33
#define state skill34
#define currentframe skill35
#define blendframe skill36
ENTITY* enemy;
#define nullframe -2
#define blend -1
#define stand 0
#define run 1
#define walk 2
#define walkSlow 3
#define walkBack 4
#define jump 5
#define fall 6

#define run_animation_speed 7

var slender_see;
VECTOR speed;
var anm_perc;
var move_speed;
var sMove = 1;
var wcount;
var wcounter;
var get_tired;
var regen;

void pl_move();
void pl_camera();
void pl_animate(animation_speed);
var player_live;
SOUND* foot = "toprak.wav";
//player action
var time;
action player1()
{
	player = me;
	
	set(my,UNLIT);
	my.gravity = 6; // needed for
	my.zoffset = 2; // gravity handling
	c_setminmax(me);
	
	while(player_live>1)
	{
		
		pl_animate(1);
		pl_move();
		pl_camera();
	time+= time_step / 16;
		wait(1);
	}

}
var time;

void sprint_fun()
{
	
if(key_w && wcount == 0){while(key_w){wait(1);}wcount = 1;}
	while(wcount == 1 && regen == 0){
		wcounter += 3 * time_step;
		if(key_w && wcounter < 50){
			sMove = 2; 
			}else{
			sMove = 1;
			
		}
		if(wcounter > 30 || sMove == 2){
			wcount = 0;
			wcounter = 0;
		
		}
		wait(1);
	}
}

var camera_run=0;

// player move action
function camera_anim()
{

	
		if (sMove == 2 && camera_run==0){camera_run=1; addBlur();
			while(camera.arc<=70)
{camera.arc=camera.arc+1;
wait(1);}
	}
if (sMove == 1 && camera_run==1){while(camera.arc>=60)
{camera.arc=camera.arc-1;
wait(1);}removeBlur();
	camera_run=0; }

}
void pl_move()
{
camera_anim();
	if(key_w){sprint_fun();}
	if(sMove == 2){get_tired += 3*time_step;}
	if(get_tired > 300){sMove = 1;regen += 3*time_step;
	if(regen > 120){regen = 0;get_tired = 0;}
	}
	
	result = c_trace(my.x, vector(my.x,my.y,my.z-500), IGNORE_ME|IGNORE_PASSENTS|IGNORE_PASSABLE|IGNORE_SPRITES|USE_BOX); 
	speed.z = -(result - my.zoffset);

	if(sMove == 1){
		speed.x = (key_w - key_s) * walk_spd*2 * time_step;//6
		speed.y = (key_a - key_d) * walk_spd * time_step;

	}
	if(sMove == 2 && get_tired <= 300){
		speed.x = (key_w - key_s) * run_spd*2 * time_step;//11
		speed.y = (key_a - key_d) * run_spd * time_step;
	}
	my.pan = camera.pan;

	if(key_w && sMove == 1 && my.state != walk){my.blendframe = walk;}
	if(key_w && sMove == 2 && my.state != run){my.blendframe = run;}
	if(key_s && my.state != walkBack){my.blendframe = walkBack; speed.x += 2 * time_step;}
	if(!key_w && !key_s && !key_a && !key_d && my.state != stand){my.blendframe = stand;}
	
	c_move(me, speed.x, nullvector, IGNORE_PASSABLE | GLIDE);
	

	
}



// player animate function
void pl_animate(animation_speed) 
{
	if (animation_speed <= 0) animation_speed = 1;
	
	if (my.state != blend && my.blendframe != nullframe) 
	{ 
		my.animate2 = 0;
		my.state = blend;
	}
	
	if (my.state == blend)
	{
		if (my.currentframe == stand) ent_animate(my,"stand",my.animate,ANM_CYCLE);
		if (my.currentframe == run) ent_animate(my,"run",my.animate,ANM_CYCLE);
		if (my.currentframe == walk) ent_animate(my,"walk",my.animate,ANM_CYCLE);
		if (my.currentframe == walkBack) ent_animate(my,"walk",my.animate,ANM_CYCLE);
		if (my.currentframe == walkSlow) ent_animate(my,"walk",my.animate,ANM_CYCLE);
		if (my.blendframe == stand) ent_blend("stand",0,my.animate2);
		if (my.blendframe == run) ent_blend("run",0,my.animate2);
		if (my.blendframe == walk) ent_blend("walk",0,my.animate2);
		if (my.blendframe == walkBack) ent_blend("walk",0,my.animate2);
		if (my.blendframe == walkSlow) ent_blend("walk",0,my.animate2);

		my.animate2 += 45 * time_step;
		
		if (my.animate2 >= 100) 
		{
			my.animate = 0;
			my.state = my.blendframe;
			my.blendframe = nullframe;
		}
	}
	
	if (my.state == stand) 
	{
		ent_animate(my,"stand",my.animate,ANM_CYCLE);
		my.animate += 5 * animation_speed * time_step;
		my.animate %= 100;
		my.currentframe = stand;
	}
	
	if (my.state == run) 
	{
		ent_animate(my,"run",my.animate,ANM_CYCLE);
		my.animate += run_animation_speed * animation_speed * time_step;
		my.animate %= 100;
		my.currentframe = run;
	}
	
	if (my.state == walk) 
	{
		ent_animate(my,"walk",my.animate,ANM_CYCLE);
		my.animate += 7 * animation_speed * time_step;
		my.animate %= 100;
		my.currentframe = walk;
		wait(1);
		
	}
	
	if (my.state == walkSlow) 
	{
		ent_animate(my,"walk",my.animate,ANM_CYCLE);
		my.animate += 5 * animation_speed * time_step;
		my.animate %= 100;
		my.currentframe = walkSlow;
	}
	
	if (my.state == walkBack) 
	{
		ent_animate(my,"walk",my.animate,ANM_CYCLE);
		my.animate -= 5 * animation_speed * time_step;
		if(my.animate <= 0){my.animate += 100;}
		my.currentframe = walkBack;
	}
}

var camera_type=1;

// player camera function
void pl_camera()
{

		camera.genius = me;
		camera.pan -= 15 * mouse_force.x * time_step;
		camera.tilt += 15 * mouse_force.y * time_step;

		camera.x = player.x;
		camera.y = player.y;
		camera.z = player.z + 20;
	
}

