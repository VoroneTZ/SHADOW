/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Template shooter player code
// Written by George Pirvu - v1.2 July 2010
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var tshooter_player_speed = 6; // player's movement speed
var tshooter_fwdbk_accel = 7; // player's forward / backward acceleration
var tshooter_side_accel = 3; // player's sideway (strafe) acceleration
var tshooter_friction = 1.5; // player's friction - this value should always be greater than 1
var tshooter_fallspeed = 1; // player's fall down speed
var tshooter_jump = 0; // player's jumping force
var tshooter_resilience = 4; // pushes the player upwards a bit if it sinks too much in the floor
var tshooter_disttoground = 64; // distance between the origin of player's model and the ground (used by the camera as well)
var tshooter_camera_h = 12; // horizontal camera acceleration
var tshooter_camera_h_frict = 0.95; // always use a value below 1 here
var tshooter_camera_v = 8; // vertical camera acceleration
var tshooter_camera_v_frict = 0.8; // always use a value below 1 here
var t_shooter_players_health = 100; // the player starts with 100 health points
var angle_slender;
var slender_see;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
var sMove;
// default player movement keys used by the shooter template: WSAD, space to jump and left shift to run
STRING* key_forward = "w";
STRING* key_backward = "s";
STRING* key_left = "a";
STRING* key_right = "d";
STRING* key_jump = "space";
STRING* key_run = "shiftl"; // left shift key

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STRING* tshooter_jump_wav = "tshooter_jump.wav";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

action t_shooter_player()
{
	camera.tilt=0;
	player = my;
	set (my, INVISIBLE); // using a 1st person player
	set (my, FLAG2); // will be used by enemies' c_scan instructions to detect the player
	var forward_on, backward_on, right_on, left_on, jump_on, run_on;
	var camera_h_speed = 0, camera_v_speed = 0, current_height = 0, jump_handle;
	VECTOR horizontal_speed, vertical_speed, temp;
	vec_set(horizontal_speed.x, nullvector); // initialize this vector
	vec_set(vertical_speed.x, nullvector); // initialize this vector
	while(t_shooter_players_health > 0)
	{
		// key input start

		if (camera.tilt>80){camera.tilt=80;
		}
		if (camera.tilt<-80){camera.tilt=-80;
		}
		forward_on = 0; // reset all the key values at the beginning of each frame
		backward_on = 0;
		right_on = 0;
		left_on = 0;
		jump_on = 0;
		run_on = 0;
		// set the proper variables if their corresponding keys are pressed
		if(key_pressed(key_for_str(key_forward)))
			forward_on = 1;
		if(key_pressed(key_for_str(key_backward)))
			backward_on = 1;  
		if(key_pressed(key_for_str(key_left)))
			left_on = 1;
		if(key_pressed(key_for_str(key_right)))
			right_on = 1;  
		if(key_pressed(key_for_str(key_jump)))
			jump_on = 1;     
		if(key_pressed(key_for_str(key_run)))
			run_on = 1;   
		// key input end
 if (run_on){sMove = 2; } else{sMove = 1;}
		// camera code
		vec_set(camera.x, my.x);
		// accelerate camera's pan and tilt angles depending on mouse_force.x and mouse_force.y in order to create a smooth camera
		camera.pan -= accelerate (camera_h_speed, tshooter_camera_h * (mouse_force.x), tshooter_camera_h_frict);
		camera.tilt += accelerate (camera_v_speed, tshooter_camera_v * (mouse_force.y), tshooter_camera_v_frict);
		my.pan = camera.pan;
		// camera code end

		// player movement start
		// player's horizontal speed (forward / backward / sideways) movement uses acceleration and friction as well
		horizontal_speed.x = (horizontal_speed.x > 0) * maxv(horizontal_speed.x - time_step * tshooter_friction, 0) + (horizontal_speed.x < 0) * minv(horizontal_speed.x + time_step * tshooter_friction, 0);
		if(forward_on)
		{
			horizontal_speed.x += time_step * tshooter_fwdbk_accel;
			horizontal_speed.x = minv(horizontal_speed.x, time_step * tshooter_player_speed  * (1 + run_on));
		}    
		if(backward_on)
		{
			horizontal_speed.x -= time_step * tshooter_fwdbk_accel;
			horizontal_speed.x = maxv(horizontal_speed.x, -(time_step * tshooter_player_speed * (1 + run_on)));
		}    
		horizontal_speed.y = (horizontal_speed.y > 0) * maxv(horizontal_speed.y - time_step * tshooter_friction, 0) + (horizontal_speed.y < 0) * minv(horizontal_speed.y + time_step * tshooter_friction, 0);
		if(left_on)
		{
			horizontal_speed.y += time_step * tshooter_side_accel;
			horizontal_speed.y = minv(horizontal_speed.y, time_step * tshooter_player_speed * (1 + run_on));
		}
		if(right_on)
		{
			horizontal_speed.y -= time_step * tshooter_side_accel;
			horizontal_speed.y = maxv(horizontal_speed.y, -(time_step * tshooter_player_speed * (1 + run_on)));
		}    	
		// disable the friction, allow smooth gliding along the surfaces
		move_friction = 0;
		vec_set(temp.x, my.x);
		temp.z -= 10000;
		current_height = c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_BOX | GLIDE); // compute the distance between player's origin and the floor below its feet 
		if(current_height < (tshooter_disttoground * 0.97)) // if it is smaller than the default value (64 quants) push the player upwards a bit (resilience) - 0.97 gives the hysteresis
		{
			vertical_speed.z = tshooter_resilience * time_step;
		}
		else
		{
			if(current_height > tshooter_disttoground) // if it is bigger than the default value (64 quants), move the player downwards
			{
				vertical_speed.z -= tshooter_fallspeed * time_step;
			}
			else // sitting properly on the floor?
			{
				vertical_speed.z = 0; // then don't do anything on the z axis
			}
		}    
		if((jump_on) && (current_height < tshooter_disttoground)) // jumping while player's feet are placed on the floor?
		{
			if (!snd_playing (jump_handle)) // if no jumping sound is playing, play the jumping sound now
			{
				SND_CREATE_STATIC(shooter_jump, tshooter_jump_wav);
				snd_play(shooter_jump, 70, 0);
			}
			vertical_speed.z = tshooter_jump * time_step; // push the player upwards
		}
		// this c_move instruction does all the job, moving the player in the direction given by horizontal_speed (forward, backward, sideways) and vertical_speed (on the z axis)
		c_move (my, horizontal_speed.x , vertical_speed.x, IGNORE_PASSABLE | USE_BOX | GLIDE); 
		// player movement end
		wait(1);
	
		angle_slender=player.pan-enemy.pan;
	
		if (vec_dist(player.x, enemy.x) < 2000){

		if (angle_slender>=150 && angle_slender<=210){
			
			slender_see=10;
}
		if (angle_slender<150 || angle_slender>210)
		{
	
			slender_see=-1;
		}
	}
	else
	{
		slender_see=-1;
	}
		if(slender_see<0)
{
if (player_life<100){player_life+=0.5;}
}	if (player.y>enemy.y)
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
		if (player_life<0){printf("ÏÎÒÐÀ×ÅÍÎ");sys_exit("123");}
			if (vec_dist(player.x, enemy.x) < 100){camera.pan=enemy.pan+180; camera.arc=120; wait(-2); printf("ÏÎÒÐÀ×ÅÍÎ");sys_exit("123");}
	}
	camera.z -= 30; // bring the camera closer to the floor
	camera.roll = 40; // and rotate its view (the player is dead here)
}

var pages;

action page()
{

	while (1){


		wait(1);
	if (vec_dist(player.x, my.x) < 250)
	{
	if(key_pressed(280))
	{media_play("BOOKPAG2.wav",NULL,100);pages=pages+1;my.z=-1000; reset(my,SHOW); wait(1);return; 
}
}
}
}



