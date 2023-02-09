/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var trpg_player_speed = 10; // player's movement speed
var trpg_fwdbk_accel = 4; // player's forward / backward acceleration
var trpg_side_accel = 2; // player's sideway (strafe) acceleration
var trpg_friction = 1.5; // player's friction - this value should always be greater than 1
var trpg_camera_h = 12; // horizontal camera acceleration
var trpg_camera_h_frict = 0.95; // always use a value below 1 here
var trpg_camera_v = 8; // vertical camera acceleration
var trpg_camera_v_frict = 0.8; // always use a value below 1 here

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// default player movement keys used by the rpg template: WSAD, left shift to run
STRING* key_forward = "w";
STRING* key_backward = "s";
STRING* key_left = "a";
STRING* key_right = "d";
STRING* key_run = "shiftl"; // left shift key

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BMAP* cursor_tga = "cursor.tga";
BMAP* inventory_tga = "inventory.tga";
BMAP* shield_pcx = "shield.pcx";
BMAP* mace_pcx = "mace.pcx";
BMAP* armor_pcx = "armor.pcx";
BMAP* ring_pcx = "ring.pcx";
BMAP* blue_pcx = "blue.pcx";
BMAP* red_pcx = "red.pcx";
BMAP* green_pcx = "green.pcx";
BMAP* fire_tga = "fire.tga";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define items skill30
#define armour skill41 // armor, but I can't use the same name twice
#define attack skill42
#define life skill43
#define shield 1
#define mace 2
#define armor 4
#define ring 8

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STRING* shield_mdl = "shield.mdl";
STRING* mace_mdl = "mace.mdl";
STRING* armor_mdl = "armor.mdl";

STRING* ringoffire_tga = "ringoffire.tga";

STRING* trpg_fire_wav = "fire.wav";
STRING* step_wav = "step.wav";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SOUND* gotmace_wav = "gotmace.wav";
SOUND* use_wav = "use.wav";
SOUND* pickedup_wav = "pickedup.wav";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ENTITY* t_mace;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PANEL* inventory_pan = // the main panel for the items in the inventory
{
	bmap = inventory_tga;
	pos_y = -2; // feel free to play with this value
	layer = 10;
	flags = SHOW;
}

PANEL* armour_value_pan = 
{
	bmap = blue_pcx;
	pos_x = 710;
	pos_y = 490;
	layer = 11;
	flags = SHOW;
}

PANEL* attack_pan = 
{
	bmap = green_pcx;
	pos_x = 710;
	pos_y = 520;
	layer = 11;
	flags = SHOW;
}

PANEL* life_pan = 
{
	bmap = red_pcx;
	pos_x = 710;
	pos_y = 550;
	layer = 11;
	flags = SHOW;
}

PANEL* shield_pan = // displays the shield on the panel
{
	bmap = shield_pcx;
	pos_x = 715;
	pos_y = 30;
	layer = 11;
	flags = SHOW | OVERLAY;
	on_click = use_shield;
}

PANEL* mace_pan =  // displays the mace on the panel
{
	bmap = mace_pcx;
	pos_x = 730;
	pos_y = 145;
	layer = 11;
	flags = SHOW | OVERLAY;
	on_click = use_mace;
}

PANEL* armor_pan = // displays the armor on the panel
{
	bmap = armor_pcx;
	pos_x = 710;
	pos_y = 255;
	layer = 11;
	flags = SHOW | OVERLAY;
	on_click = use_armor;
}

PANEL* ring_pan = // displays the ring on the panel
{
	bmap = ring_pcx;
	pos_x = 710;
	pos_y = 365;
	layer = 11;
	flags = SHOW | OVERLAY;
	on_click = use_ring;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function fade_fire(PARTICLE *p)
{
	p.alpha -= 1000 * time_step; // fade out the fire particles
	if (p.alpha < 0) 
		p.lifespan = 0;
}

function fire_effect(PARTICLE *p)
{
	p->vel_x = 1 - random(2);
	p->vel_y = 1 - random(2);
	p->vel_z = 2 + random(2);
	p.lifespan = 3; // particle lifespan
	p.alpha = 5 + random(70);
	p.bmap = fire_tga;
	p.size = 10 + random(10);
	p.flags |= (BRIGHT | MOVE);
	p.event = fade_fire;
}

function t_attach_mace() // keep in sync the player and its mace / staff
{
	proc_mode = PROC_LATE;
	set (my, PASSABLE);
	while (player)
	{
		vec_set(my.x, player.x);
	   vec_set(my.pan, player.pan);
   	my.frame = player.frame;
	   my.next_frame = player.next_frame;					
   	wait(1);
	}
}

function fire_init_startup()
{
	VECTOR temp, fire_coords;
	var fire_playing, i;
	while (!player) {wait (1);}
	while (1)
	{
		if ((t_mace != NULL) && (player.life > 0) && (mouse_mode == 0))
		{
			SND_CREATE_STATIC(fire_sound_effect, trpg_fire_wav);
			while (mouse_left) // this loop will run for as long as the player is alive
			{	
				// only generate fire while the player is standing still		
				if((key_pressed(key_for_str(key_forward))) + (key_pressed(key_for_str(key_backward))) + (key_pressed(key_for_str(key_left))) + (key_pressed(key_for_str(key_right))) == 0)
				{
					vec_for_vertex (temp, t_mace, 44); // get the origin of the fire vector - it's the 44th mace vertex
					for (i = 0; i <= 1000; i += 10) // create a mace fire source every 10 quants (for a total of 100 fire sources)
					{
						vec_set (fire_coords.x, vector(i, 0, 0));
		  	     		vec_rotate (fire_coords, camera.pan); // allow the player to fire at will, at any angle, regardless of player's model (fixed) tilt angle
		      		vec_add (fire_coords, temp.x);
						effect(fire_effect, 5, fire_coords.x, nullvector);
					}        	
					c_trace (temp.x, fire_coords.x, IGNORE_ME | IGNORE_FLAG2 | ACTIVATE_SHOOT); // trace along the fire line
					if (!snd_playing(fire_playing))
 						fire_playing = snd_play(fire_sound_effect, 100, 0);
					if (player.life <= 0) // the player has died while firing?
						break; // then get out of this loop
				}
				wait (1);
			}
		}
		wait (1);
	}
}	

function check_inventory()
{
	while(1)
	{
		if(player.items > 0)
		{
			if(player.items == 1) // 1 + 0 + 0 + 0
			{
				set(shield_pan, SHOW);
				reset(mace_pan, SHOW);
				reset(armor_pan, SHOW);
				reset(ring_pan, SHOW);
			}
			if(player.items == 2) // 0 + 2 + 0 + 0
			{
				set(mace_pan, SHOW);
				reset(shield_pan, SHOW);
				reset(armor_pan, SHOW);
				reset(ring_pan, SHOW);
			}
			if(player.items == 3) // 1 + 2 + 0 + 0
			{
				set(shield_pan, SHOW);
				set(mace_pan, SHOW);
				reset(armor_pan, SHOW);
				reset(ring_pan, SHOW);
			}
			if(player.items == 4) // 0 + 0 + 4 + 0
			{
				set(armor_pan, SHOW);
				reset(shield_pan, SHOW);
				reset(mace_pan, SHOW);
				reset(ring_pan, SHOW);
			}
			if(player.items == 5) // 1 + 0 + 4 + 0
			{
				set(armor_pan, SHOW);
				set(shield_pan, SHOW);
				reset(mace_pan, SHOW);
				reset(ring_pan, SHOW);
			}
			if(player.items == 6) // 0 + 2 + 4 + 0
			{
				set(armor_pan, SHOW);
				set(mace_pan, SHOW);
				reset(shield_pan, SHOW);
				reset(ring_pan, SHOW);
			}
			if(player.items == 7) // 1 + 2 + 4 + 0
			{
				set(shield_pan, SHOW);
				set(mace_pan, SHOW);
				set(armor_pan, SHOW);
				reset(ring_pan, SHOW);
			}
			if(player.items == 8) // 0 + 0 + 0 + 8
			{
				reset(shield_pan, SHOW);
				reset(mace_pan, SHOW);
				reset(armor_pan, SHOW);
				set(ring_pan, SHOW);
			}
			if(player.items == 9) // 1 + 0 + 0 + 8
			{
				set(shield_pan, SHOW);
				reset(mace_pan, SHOW);
				reset(armor_pan, SHOW);
				set(ring_pan, SHOW);
			}
			if(player.items == 10) // 0 + 2 + 0 + 8
			{
				reset(shield_pan, SHOW);
				set(mace_pan, SHOW);
				reset(armor_pan, SHOW);
				set(ring_pan, SHOW);
			}
			if(player.items == 11) // 1 + 2 + 0 + 8
			{
				set(shield_pan, SHOW);
				set(mace_pan, SHOW);
				reset(armor_pan, SHOW);
				set(ring_pan, SHOW);
			}
			if(player.items == 12) // 0 + 0 + 4 + 8
			{
				reset(shield_pan, SHOW);
				reset(mace_pan, SHOW);
				set(armor_pan, SHOW);
				set(ring_pan, SHOW);
			}
			if(player.items == 13) // 1 + 0 + 4 + 8
			{
				set(shield_pan, SHOW);
				reset(mace_pan, SHOW);
				set(armor_pan, SHOW);
				set(ring_pan, SHOW);
			}
			if(player.items == 14) // 0 + 2 + 4 + 8
			{
				reset(shield_pan, SHOW);
				set(mace_pan, SHOW);
				set(armor_pan, SHOW);
				set(ring_pan, SHOW);
			}
			if(player.items == 15) // 1 + 2 + 4 + 8
			{
				set(shield_pan, SHOW);
				set(mace_pan, SHOW);
				set(armor_pan, SHOW);
				set(ring_pan, SHOW);
			}				
		}
		else
		{
			reset(shield_pan, SHOW);
			reset(mace_pan, SHOW);
			reset(armor_pan, SHOW);
			reset(ring_pan, SHOW);
		}
		mouse_map = cursor_tga;
		vec_set(mouse_pos,mouse_cursor);
		if((player.life > 0) && (mouse_right)) // only use the inventory if the player is alive
		{
			mouse_mode = (mouse_mode + 2) % 4;
			while(mouse_right == 1){wait(1);}
		}		
		wait(1);
	}
}

function inventory_startup()
{
	while (!player) {wait (1);}
	check_inventory();
}

function player_was_hit()
{
	wait (1); // for further use	
}

action t_rpg_player() // attached to the player
{
	VECTOR player_speed;
	player = my; // I'm the player
	my.items = 0;
	my.armour = 20;
	my.attack = 5;
	my.life = 35;
	my.ambient = 50;
	set (my, FLAG2); // will be used by enemies' c_scan instructions to detect the player
	var forward_on, backward_on, right_on, left_on, run_on, anim_percentage, attack_percentage;
	var camera_h_speed = 0, camera_v_speed = 0;
	VECTOR horizontal_speed, vertical_speed, temp;
	vec_set(horizontal_speed.x, nullvector); // initialize this vector
	vec_set(vertical_speed.x, nullvector); // initialize this vector
	my.emask |= (ENABLE_IMPACT | ENABLE_ENTITY);
	my.event = player_was_hit;
	while(player.life > 0)
	{
		armour_value_pan.scale_x = maxv(0.01, player.armour / 100);
		attack_pan.scale_x = maxv(0.01, player.attack / 100);
		life_pan.scale_x = maxv(0.01, player.life / 100);

		// key input start
		forward_on = 0; // reset all the key values at the beginning of each frame
		backward_on = 0;
		right_on = 0;
		left_on = 0;
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
		if(key_pressed(key_for_str(key_run)))
			run_on = 1;     
		// key input end

		// camera code
		vec_set (camera.x, vector(-100, 0, 75));
		vec_rotate (camera.x, player.pan);
		vec_add (camera.x, player.x);
		// accelerate camera's pan and tilt angles depending on mouse_force.x and mouse_force.y in order to create a smooth camera
		camera.pan -= accelerate (camera_h_speed, trpg_camera_h * (mouse_force.x), trpg_camera_h_frict);
		camera.tilt += accelerate (camera_v_speed, trpg_camera_v * (mouse_force.y), trpg_camera_v_frict);
		my.pan = camera.pan;
		// camera code end

		// player movement start
		// player's horizontal speed (forward / backward / sideways) movement uses acceleration and friction as well
		horizontal_speed.x = (horizontal_speed.x > 0) * maxv(horizontal_speed.x - time_step * trpg_friction, 0) + (horizontal_speed.x < 0) * minv(horizontal_speed.x + time_step * trpg_friction, 0);
		if(forward_on)
		{
			horizontal_speed.x += time_step * trpg_fwdbk_accel;
			horizontal_speed.x = minv(horizontal_speed.x, time_step * trpg_player_speed  * (1 + run_on));
		}    
		if(backward_on)
		{
			horizontal_speed.x -= time_step * trpg_fwdbk_accel;
			horizontal_speed.x = maxv(horizontal_speed.x, -(time_step * trpg_player_speed * (1 + run_on)));
		}    
		horizontal_speed.y = (horizontal_speed.y > 0) * maxv(horizontal_speed.y - time_step * trpg_friction, 0) + (horizontal_speed.y < 0) * minv(horizontal_speed.y + time_step * trpg_friction, 0);
		if(left_on)
		{
			horizontal_speed.y += time_step * trpg_side_accel;
			horizontal_speed.y = minv(horizontal_speed.y, time_step * trpg_player_speed * (1 + run_on));
		}
		if(right_on)
		{
			horizontal_speed.y -= time_step * trpg_side_accel;
			horizontal_speed.y = maxv(horizontal_speed.y, -(time_step * trpg_player_speed * (1 + run_on)));
		}    	
		// disable the friction, allow smooth gliding along the surfaces
		move_friction = 0;
		vec_set(temp.x, my.x);
		temp.z -= 10000;
		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_BOX) - 30; // place player's feet on the ground - play with 30
		if((forward_on) + (backward_on) + (left_on) + (right_on)) // at least one of the movement keys is being pressed?
		{
			anim_percentage += 0.5 * (1 + run_on) * trpg_player_speed * time_step;
	      ent_animate(my, "walk", anim_percentage, ANM_CYCLE); // play the "stand" aka idle animation
      }
      else
      {
			if ((mouse_left) && (mouse_mode == 0)) // the player has pressed the left mouse button?
			{
				attack_percentage += 20 * time_step;
	      	ent_animate(my, "attack", attack_percentage, ANM_CYCLE); // play the "attack" animation					
	      	attack_percentage = minv(62, attack_percentage);
			}
			else
			{
				attack_percentage = 0;
				anim_percentage += 1 * time_step;
	      	ent_animate(my, "stand", anim_percentage, ANM_CYCLE); // play the "stand" aka idle animation
      	}
      }
		// this c_move instruction does all the job, moving the player in the direction given by horizontal_speed (forward, backward, sideways) and vertical_speed (on the z axis)
		my.skill80 += c_move (my, horizontal_speed.x , vertical_speed.x, IGNORE_PASSABLE | GLIDE);
      if (my.skill80 > 105) // play with this value
		{
			SND_CREATE_STATIC(rpg_step, step_wav);
			snd_play(rpg_step, 20, 0);
         my.skill80 = 0;
		}		
		// player movement end
		wait(1);
	}
	reset (life_pan, SHOW);	
   my.skill80 = 0; // skill40 controls the "death" animation
	camera.z -= 30; // bring the camera closer to the floor
	camera.roll = 40; // and rotate its view (the player is dead here)
	while (my.skill80 < 96) // don't play all the animation frames because the result doesn't always look good
	{ 
		ent_animate(my, "death", my.skill80, NULL); // play the "death" animation
		my.skill80 += 2 * time_step; // "death" animation speed
		wait (1); 
	} 
	set (my, PASSABLE); // the corpse will be passable from now on
}

function attach_item()
{
	proc_mode = PROC_LATE;
	set(my,PASSABLE);
	while(player != NULL)
	{
		vec_set(my.x, player.x);
		vec_set(my.pan, player.pan);
		my.frame = player.frame;
		my.next_frame = player.next_frame;
		wait(1);
	}
}

action shield_init()
{
	set(my,PASSABLE);
	my.ambient = 80;
	while(player == NULL){wait(1);}
	while(vec_dist(my.x,player.x) > 50)
	{
		ent_animate(my,"idle", my.skill20,ANM_CYCLE); // play stand frames animation
		my.pan += 1 * time_step;
		my.skill20 += 3 * time_step; // "idle" animation speed
		wait(1);
	}
	snd_play(pickedup_wav, 80, 0);
	player.items += shield;
	ent_remove(me);		
}

action mace_init()
{
	set(my,PASSABLE);
	my.ambient = 80;	
	while(player == NULL){wait(1);}
	while(vec_dist(my.x,player.x) > 50)
	{
		ent_animate(my,"idle", my.skill20,ANM_CYCLE); // play stand frames animation
		my.pan += 1 * time_step;
		my.skill20 += 3 * time_step; // "idle" animation speed
		wait(1);
	}
	snd_play(pickedup_wav, 80, 0);
	player.items += mace;
	ent_remove(me);
}	

action armor_init()
{
	set(my,PASSABLE);
	my.ambient = 80;	
	while(player == NULL){wait(1);}
	while(vec_dist(my.x,player.x) > 50)
	{
		ent_animate(my,"idle", my.skill20,ANM_CYCLE); // play stand frames animation
		my.pan += 1 * time_step;
		my.skill20 += 3 * time_step; // "idle" animation speed
		wait(1);
	}
	snd_play(pickedup_wav, 80, 0);	
	player.items += armor;
	ent_remove(me);
}	

action ring_init()
{
	set(my,PASSABLE);
	my.ambient = 80;	
	while(player == NULL){wait(1);}
	while(vec_dist(my.x,player.x) > 50)
	{
		ent_animate(my,"idle", my.skill20,ANM_CYCLE); // play stand frames animation
		my.pan += 1 * time_step;
		my.skill20 += 3 * time_step; // "idle" animation speed
		wait(1);
	}
	snd_play(pickedup_wav, 80, 0);	
	player.items += ring;
	ent_remove(me);
}	

function use_shield()
{
	while (mouse_left) {wait (1);}
	snd_play(use_wav, 100, 0);
	player.items -= shield; // remove the shield from the panel
	ent_create(shield_mdl, player.x, attach_item);
	player.life += 30; // bigger hbar
}

function use_mace()
{
	while (mouse_left) {wait (1);}	
	snd_play(use_wav, 100, 0);	
	player.items -= mace; // remove the mace from the panel
	ent_create(mace_mdl, player.x, attach_item);
	player.attack += 50; // bigger hbar
	t_mace = ent_create(mace_mdl, player.x, t_attach_mace);
}

function use_armor()
{
	while (mouse_left) {wait (1);}	
	snd_play(use_wav, 100, 0);	
	player.items -= armor; // remove the armor from the panel
	ent_create(armor_mdl, player.x, attach_item);
	player.armour += 40; // bigger hbar
}

function fire_action()
{
	set(my, PASSABLE | BRIGHT);
	my.ambient = 100;
	my.pan = random(360);
	while(my.pan < 1500)
	{
		c_scan(my.x, my.pan, vector(360, 90, 70), IGNORE_ME | SCAN_ENTS); // scan 70 quants around each flame
		my.pan += (5 + random(3)) * time_step;
		my.z -= 0.4 * time_step;
		wait(1);
	}
	ent_remove (me);
}

function use_ring()
{
	while (mouse_left) {wait (1);}	
	snd_play(use_wav, 100, 0);
	VECTOR temp;
	var temp_angle = 0; // temporary angle used for the ring of fire	
	if is (ring_pan, SHOW) // the ring can be used only once
	{
		player.items -= ring;
		while (mouse_left) {wait (1);}
		while (!mouse_left) {wait (1);}		
		while(temp_angle < 400) // create a bit more than a full circle of flames around the player
		{
			temp_angle += 2;
			temp.x = player.x + 100 * cos(temp_angle);
			temp.y = player.y + 100 * sin(temp_angle);
			temp.z = player.z;
			ent_create(ringoffire_tga, temp.x, fire_action);
  		}
	}
}

function panels_startup()
{
	while (!player) {wait (1);}
	while (1)
	{
		inventory_pan.pos_x = screen_size.x - bmap_width(inventory_tga);
		
		shield_pan.pos_x = inventory_pan.pos_x + 37; 
		shield_pan.pos_y = inventory_pan.pos_y + 45;
		mace_pan.pos_x = inventory_pan.pos_x + 50; 
		mace_pan.pos_y = inventory_pan.pos_y + 150;
		armor_pan.pos_x = inventory_pan.pos_x + 37;
		armor_pan.pos_y = inventory_pan.pos_y + 250;
		ring_pan.pos_x = inventory_pan.pos_x + 37;
		ring_pan.pos_y = inventory_pan.pos_y + 352;

		armour_value_pan.pos_x = inventory_pan.pos_x + 30; 
		armour_value_pan.pos_y = inventory_pan.pos_y + 468;
		attack_pan.pos_x = inventory_pan.pos_x + 30; 
		attack_pan.pos_y = inventory_pan.pos_y + 493;
		life_pan.pos_x = inventory_pan.pos_x + 30; 
		life_pan.pos_y = inventory_pan.pos_y + 517;

		wait (1);
	}
}

action t_rpg_terrain()
{
	set(my, FLAG2); // we want player's c_trace instructions used by its weapon to ignore the terrain below its feet
}

