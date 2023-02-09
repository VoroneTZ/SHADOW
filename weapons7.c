////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var anim_factor = 0;
var launcher_firing = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BMAP* trail_tga = "trail.tga";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ENTITY* nuke_weapon;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SOUND* gotweapon_wav = "gotweapon.wav";
SOUND* nukefired_wav = "nukefired.wav";
SOUND* exploded_wav = "exploded.wav";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STRING* nukebomb_mdl = "nukebomb.mdl";
STRING* explo13_tga = "explo+13.tga";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function remove_nuke();
function fire_nukes();
function move_nukebomb();
function explode_nuke();
function fade_trail(PARTICLE *p);
function nuke_trail(PARTICLE *p);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

action nuke_launcher() // attach this action to your nuke weapon model
{
	set (my, PASSABLE);
	while (!player) {wait (1);}
	while (vec_dist(player.x, my.x) > 50) // wait until the player has come close to the nuclear weapon model
	{
		my.pan += 3 * time_step; // rotate until the player picks up the nuke weapon
		wait (1);
	}
	snd_play(gotweapon_wav, 80, 0); // play the "got the weapon" sound
	nuke_weapon = ent_createlayer("nuke.mdl", 0, 20); // create the nuke entity on the 20th view layer
	nuke_weapon.flags2 |= SHOW; // show the nuke weapon entity
	nuke_weapon.x = 60; // 60 quants ahead of the view, play with this value
	nuke_weapon.y = -35; // 35 quants towards the right side of the screen, play with this value
	nuke_weapon.z = -25; // 25 quants below, play with this value
	nuke_weapon.tilt = 0;
	wait (1);
	ent_remove (my); // remove the nume model from the ground
}

function explode_nuke()
{
	set(my, BRIGHT | PASSABLE);
	VECTOR temp;
	my.frame = 0;
	wait (1);
	while (my.frame < 13) // go through all the animation frames
	{
		my.frame += 2 * time_step;		
		vec_set (temp.x, camera.x);
		vec_sub (temp.x, my.x);
		vec_to_angle (my.pan, temp); // turn towards the player to make sure that the explo looks great
		wait (1);
	}
	set (my, INVISIBLE); // hide the explosion sprite, keep the sound playing
	wait (-4); // for 4 more seconds
	ent_remove(me); // now remove the explosion sprite
}

function remove_nuke()
{
   my.event = NULL;
	set(my, PASSABLE | INVISIBLE);
	if (you)
		lvl6shadow_health-=100;  // kill the enemies from the first shot
   my.skill20 = 5000; // stop the nuke for good
	wait (1);
   ent_playsound (my, exploded_wav, 1000); // play the explosion sound
   ent_create (explo13_tga, my.x, explode_nuke);
	wait (-1);
	ent_remove(my); // now remove it
}
 
function move_nukebomb()
{
	VECTOR nuke_speed, nuke_pos;
	var tempo_pos, vertical_speed = 0;
	set (my, PASSABLE); // don't collide with the player
	wait (1);
	my.pan = camera.pan + 5;
	my.tilt = camera.tilt;
	my.emask |= (ENABLE_ENTITY | ENABLE_IMPACT | ENABLE_BLOCK);
	my.event = remove_nuke;
   my.skill40 = 1235; // I'm a nuke
   my.skill20 = 0;
   while (my.skill20 < 5000)
   {
    	vec_for_vertex (nuke_pos, my, 13);   	
		effect (nuke_trail, 2, nuke_pos.x, normal); // generate a particle trail
   	if (my.skill20 > 2) // the nuke has moved away from the player? Then let's reset its passable flag
   		reset (my, PASSABLE);
      nuke_speed.x = 60 * time_step;
      nuke_speed.y = 0;
      nuke_speed.z = 0;
      my.skill20 += 1 * time_step;
      c_move (my, nuke_speed, nullvector, IGNORE_PASSABLE);
		c_scan(my.x, my.pan, vector(360, 180, 200), IGNORE_ME | SCAN_ENTS); // play with 200, it gives the nuke destruction range
      wait (1);
      
	}
	remove_nuke();
}

function fire_nukes() // this function is triggered by any left mouse button push
{
	wait (1);
	var firing_once = 1;
	var init_nuke_pos;
	VECTOR nuke_origin;
	if (!nuke_weapon) return; // don't fire bullets if the player didn't pick up the nuke gun yet
	vec_set(nuke_origin.x, vector(50, -12, -7)); // the origin of the nuke is offset by 50, -12 and 7 quants in relation to camera.x
	vec_rotate(nuke_origin.x, camera.pan);
	vec_add(nuke_origin.x, camera.x);
	ent_create(nukebomb_mdl, nuke_origin, move_nukebomb);
	init_nuke_pos = nuke_weapon.x;
	while (nuke_weapon.x > (init_nuke_pos - 5)) // give the gun a recoil movement and move the player backwards a bit
	{
		nuke_weapon.x -= 15 * time_step;
		c_move (player, vector (-30 * time_step, 0, 0), nullvector, IGNORE_PASSABLE | USE_BOX | GLIDE); 
		wait (1);
	}
	while (nuke_weapon.x < init_nuke_pos)
	{
		nuke_weapon.x += 10 * time_step;
		wait (1);	
	}
	nuke_weapon.x = init_nuke_pos;
}

function gun_startup()
{
	on_mouse_left = fire_nukes; // call this function when the left mouse button is pressed	
}

function fade_trail(PARTICLE *p)
{
	p.alpha -= 25 * time_step;
	if (p.alpha < 0) {p.lifespan = 0;}
}

function nuke_trail(PARTICLE *p)
{
	p->vel_x = 0;
	p->vel_y = 0;
	p->vel_z = 0.1 *  random(3);
	p.alpha = 10 + random(40);
	p.bmap = trail_tga;
	p.size = 30 + random(60);
	p.flags |= (BRIGHT | MOVE);
	p.event = fade_trail;
}