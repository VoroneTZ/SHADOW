//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// New physics car library
// (c) oP group / jcl 2010
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: Add friction events (crash sound, lose wheels on impact, dents)
// TODO: Add brake lights

#ifndef car_c
#define car_c
#include <acknex.h>
#include <ackphysX.h>
#include <strio.c>
#include <keys.c>

#define PRAGMA_PATH "%EXE_DIR%\\templates\\sounds";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// External files 

STRING* engine_wav = "engine.ogg";
STRING* tires_wav = "tires.wav";
STRING* horn_wav = "horn.wav";
STRING* crash_wav = "crash.ogg";

STRING* steer_anim = "steering";
STRING* frontright_anim = "frontright";
STRING* frontleft_anim = "frontleft";
STRING* rearright_anim = "rearright";
STRING* rearleft_anim = "rearleft";

////////////////////////////////////////////////////////////////////////////////////////////////
// defines

#define CAR_TORQUEFACTOR 20

////////////////////////////////////////////////////////////////////////////////////////////////
// Global car variables
var tcar_gravity = 30;
var tcar_facBrake = 4;	// brake power as multiple of the motor power
var tcar_facSteer = 4;	// steer angle increase in degrees per tick
var tcar_dampSteer = 70;	// steer damping at high speed in percent
var tcar_crashSpeed = 20;	// speed change to play a crash sound

var tcar_maxSpeed = 200; // the speed depends on the radius of the wheels as well
var tcar_maxTorque = 1000;
var tcar_maxSteer = 17;	// steer angle limit

var tcar_spsSpring = 400; 
var tcar_spsDamper = 100; 
var tcar_spsWay = 100; 

var tcar_massFactor = 0;
var tcar_massOffset =	-100;
var tcar_massShape = 50;

var tcar_wheelDrive = 2;	// rear wheel drive 
var tcar_frictionWheel = 300;	// wheel longitudinal friction
var tcar_frictionLatF = 1000;	// front wheel lateral friction
var tcar_frictionLatR =	1000;	// rear wheel lateral friction

var tcar_wheel_fx = 40;
var tcar_wheel_fy = 20;
var tcar_wheel_fz = 1;
var tcar_wheel_rx = -34;
var tcar_wheel_ry = 20;
var tcar_wheel_rz = 1;

var tcar_hover = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//default keys
STRING* key_forward = "w";
STRING* key_backward = "s";
STRING* key_left = "a";
STRING* key_right = "d";

STRING* key_horn = "h";
STRING* key_lift = "l";
STRING* key_brake = "space";

var joy_brake = 0;
var joy_horn =0 ;
var joy_lift = 0;

var tcar_USE_GAMEPAD = 0; // treat the joystick as a digital device

////////////////////////////////////////////////////////////////////////////////////////////////
// car skills
#define car_maxSpeed skill1 // sets the maximum speed for player's car

// negative offset values are set automatically for the right side wheels, so set the offsets only for the left side wheels
#define car_wheel_fx skill2 // offset for the front wheels on the x axis
#define car_wheel_fy skill3 // offset for the front wheels on the y axis
#define car_wheel_fz skill4 // offset for the front wheels on the z axis
#define car_wheel_rx skill5 // offset for the rear wheels on the x axis
#define car_wheel_ry skill6 // offset for the rear wheels on the y axis
#define car_wheel_rz skill7 // offset for the rear wheels on the z axis

#define car_wheelDrive	skill8
#define car_maxTorque	skill9
#define car_maxSteer	skill10

#define car_massFactor	skill11	
#define car_massOffset	skill12
#define car_massShape		skill13

#define car_spsSpring skill14
#define car_spsDamper skill15
#define car_spsWay 		skill16

#define car_frictionWheel skill18
#define car_frictionLatF skill19
#define car_frictionLatR skill20

#define car_hover FLAG1

#define car_torque	skill61
#define car_brake		skill62
#define car_steerangle skill63

#define actor_id		skill66
#define ID_CAR 			1357
#define ID_WHEEL		1358

#define car_speed		skill71
#define car_wheelFL	skill74			// wheel pointers
#define car_wheelFR skill75
#define car_wheelRL	skill76
#define car_wheelRR	skill77

#define car_hEngine	skill78
#define car_hTire		skill79

// wheel skills (can be different for every wheel)

#define wheel_speed 	skill1		// individual wheel speed factor (0..1), set by ground
#define wheel_friction skill19	// individual lateral friction

//////////////////////////////////////////////////////////////
// general functions

function car_startup()
{
	physX_open();
	pX_setgravity(vector(0,0,-tcar_gravity));
}

// return the speed of a physX actor in km/h in the forward direction 
var pXent_getspeed(ENTITY* ent)
{
	VECTOR vSpeed,vDir;
	pXent_getvelocity(ent,vSpeed,NULL);
	vec_for_angle(vDir,ent.pan);
// speed in km/h, assume 40 quants = 1 m	
	var speed = vec_dot(vDir,vSpeed) * (60.*60.)/(40.*1000.); 
	if (abs(speed) < 1) 
		return 0;
	else 
		return speed;
}

//////////////////////////////////////////////////////////////
// wheel functions

// create a wheel and attach it to the chassis at the given offset.
ENTITY* car_wheelcreate(ENTITY* car,VECTOR* offset)
{
// generate the wheel model name from the car	model name
	STRING* wheel_name = str_for_entfile(NULL,car);
	str_replace(wheel_name,".","_wheel.");
	if (!file_exists(wheel_name)) // fall back to "wheel.mdl"
		str_cpy(wheel_name,"wheel.mdl");

// create the wheel entity		
	ENTITY* wheel = ent_create (wheel_name,offset,NULL);
	if (!wheel) error("Can't load wheel!");
	vec_set(wheel.scale_x,car.scale_x);
	vec_rotate(wheel.x,car.pan);
	vec_add(wheel.x, car.x);
	vec_set(wheel.pan,car.pan); 
	wheel.parent = car;
	wheel.actor_id = ID_WHEEL;
	wheel.wheel_speed = 1;	
	if (shadow_stencil != 0) // no wheel decal shadows 
		wheel.flags |= (car.flags&(SHADOW|CAST));

// treat wheels differently, depending on their position on the car	
	if (offset.y > 0) 
		wheel.pan += 180; // rotate left wheels so that cap points outwards
	if (offset.x > 0) 
		wheel.wheel_friction = car.car_frictionLatF; // front wheel lateral friction
	else
		wheel.wheel_friction = car.car_frictionLatR; // rear wheel lateral friction

// activate wheel physics		
	pXcon_add(PH_WHEEL,wheel,car,0);
	pXcon_setparams2(wheel,NULL,
		vector(car.car_frictionWheel,wheel.wheel_friction,0),
		vector(car.car_spsSpring,car.car_spsDamper,car.car_spsWay));
	
// hovercraft have invisible wheels		
	if(is(car,car_hover)) {
		set(wheel,INVISIBLE);	
		reset(wheel,SHADOW);
	}
	return wheel;
}

// modify the friction and speed of a wheel or a car by the given percentages
// to be called by a ground detecting script 
function car_wheelset(ENTITY* ent,friction,speed,special)
{
	if (ent.actor_id == ID_WHEEL)	{ // modify 1 wheel only
		friction = clamp(friction/100,0,1);
		ent.wheel_speed = clamp(speed/100,0,1);
		pXcon_setparams2(ent,NULL,
			vector(ent.parent.car_frictionWheel*friction,ent.wheel_friction*friction,0),NULL);
	} 
	else if (ent.actor_id == ID_CAR) { // modify car -> all 4 wheels
		car_wheelset((ENTITY*)ent.car_wheelFL,friction,speed,special); 
		car_wheelset((ENTITY*)ent.car_wheelFR,friction,speed,special); 
		car_wheelset((ENTITY*)ent.car_wheelRL,friction,speed,special); 
		car_wheelset((ENTITY*)ent.car_wheelRR,friction,speed,special); 
	}
	//DEBUG_VAR(friction,30);
	//DEBUG_VAR(speed,50);
}

// apply steer angle, adjusted torque and brake power to a wheel
function car_wheeldrive(ENTITY* wheel,steerangle,torque,brake)
{
	pXcon_setwheel(wheel,steerangle,
		torque*wheel.wheel_speed,
		brake+1000*(1-wheel.wheel_speed));
}

// return true when the wheels are supposed to screech
function car_wheelslip(ENTITY* car)
{
	return ((abs(car.car_speed) > 10 && car.car_brake > 10)
			|| (car.car_speed > 10 && car.car_torque < -10)
			|| (car.car_speed < -10 && car.car_torque > 10));
}

//////////////////////////////////////////////////////////////
// car functions

// handle motor and wheel sounds
function car_noise(ENTITY* car,SOUND* sndEngine,SOUND* sndTire,SOUND* sndCrash)
{
// use skills for the sound handles, to keep them individually per car
	if (!car.car_hEngine) car.car_hEngine = ent_playloop(car,sndEngine,100);
	
// tune engine sound according to speed and acceleration		
	if (car.car_hEngine) {
		var freq = 80 
			+ 200*abs(car.car_speed/car.car_maxSpeed) 
			+ 100*abs(car.car_torque/car.car_maxTorque);
		snd_tune(car.car_hEngine,100,freq,0);  //80% of real frequency
	}
	
// play tire sound when tires are slipping 	
	if (!snd_playing(car.car_hTire)) {
		if (car_wheelslip(car))
			car.car_hTire = ent_playloop(car,sndTire,100);
	} else {
		if (!car_wheelslip(car)) {
			snd_stop(car.car_hTire);
			car.car_hTire = 0;
		}
	}
	
// play crash sound on abrupt speed changes	or when car topples	
	static var last_speed = 0;
	static var last_roll = 0;
	if ((abs(last_speed) > tcar_crashSpeed &&
		abs(last_speed-car.car_speed) > tcar_crashSpeed)
		|| (abs(last_roll) < 90 && abs(car.roll) > 90))
	{
		ent_playsound(car,sndCrash,200);
	}
	last_speed = car.car_speed;
	last_roll = car.roll;
		
} 

// animate the suspensions (if available)
function car_animate(ENTITY* car)
{
	if(!ent_status(car,14)) return; // no bones animation 
	ent_animate(me,NULL,0,0);
// animate steering	
	ent_animate(me,steer_anim,(my.car_steerangle+car.car_maxSteer)*100/(2*car.car_maxSteer),ANM_ADD);
// animate suspensions according to joint positions
	VECTOR position;
	pXcon_getposition((ENTITY*)car.car_wheelFR,position);
	ent_animate(me,frontright_anim,position.z,ANM_ADD);
	pXcon_getposition((ENTITY*)car.car_wheelFL,position);
	ent_animate(me,frontleft_anim,position.z,ANM_ADD);
	pXcon_getposition((ENTITY*)car.car_wheelRR,position);
	ent_animate(me,rearright_anim,position.z,ANM_ADD);
	pXcon_getposition((ENTITY*)car.car_wheelRL,position);
	ent_animate(me,rearleft_anim,position.z,ANM_ADD);
}

// put a toppled car on its wheels
function car_lift(ENTITY* car)
{
	pXent_addforcelocal(car,vector(0,0,300),vector(0,0,40));
}

///////////////////////////////////////////////////////////////////////////////////////

// sound the horn (only one at a time)
function car_horn(ENTITY* car) 
{
	SND_CREATE_STATIC(tcar_horn_wav,horn_wav);
	static var hHorn = 0;
	if (!snd_playing (hHorn)) 
		hHorn = ent_playsound(car,tcar_horn_wav,100);
}

// controls the car by setting torque, brake, steer angle etc. from keyboard and joystick
function car_input(ENTITY* car)
{
// set motor torque
	car.car_torque = key_pressed(key_for_str(key_forward))-key_pressed(key_for_str(key_backward))
		+ mouse_left-mouse_right + 0.5*joy_force.y;
	car.car_torque = clamp(car.car_torque,-1,1) * car.car_maxTorque;		

// set brake
	car.car_brake = 
		(key_pressed(key_for_str(key_brake))+joy_pressed(joy_brake)) 
		* car.car_maxTorque * tcar_facBrake;

// set steer angle
	var steer_digital = key_pressed(key_for_str(key_right))-key_pressed(key_for_str(key_left));
	var steer_analog = 0; //mouse_force.x;
	if(tcar_USE_GAMEPAD)
		steer_digital += joy_force.x;
	else
		steer_analog += 0.5*joy_force.x;

	if(steer_analog)
		car.car_steerangle = steer_analog*car.car_maxSteer;
	else if(steer_digital)
		car.car_steerangle += clamp(steer_digital,-1,1)*tcar_facSteer*time_step;
	else {	
// move angle back to 0 when no steer key is hit
		car.car_steerangle -= minv(4,tcar_facSteer*time_step) * sign(car.car_steerangle);
		if (abs(my.car_steerangle) < 1) { car.car_steerangle = 0; }
	}
	
// jump a little, put toppled cars on wheel again		
	if(key_hit(key_lift) || joy_hit(joy_lift))
		car_lift(car);
		
// play the horn		
	if(key_pressed(key_for_str(key_horn)) || joy_pressed(joy_horn))
		car_horn(car);
}

///////////////////////////////////////////////////////////////////////////////////////

// move the car
function car_move(ENTITY* car)
{
	car.car_speed = pXent_getspeed(my);
	var speedfactor = clamp((car.car_maxSpeed - abs(car.car_speed))/car.car_maxSpeed,0,1);

// reverse direction -> full brake
	if ((car.car_speed > 10 && car.car_torque < -10) ||
		(car.car_speed < -10 && car.car_torque > 10))
		car.car_brake = car.car_maxTorque * tcar_facBrake;
			
// clamp steer angle and reduce it at high speed
	car.car_steerangle = clamp(car.car_steerangle,-car.car_maxSteer,car.car_maxSteer);
	var steer = car.car_steerangle * (1 + tcar_dampSteer/100*(speedfactor*speedfactor-1)); 

// time adjust torque and reduce it at high speed
	car.car_torque = clamp(car.car_torque,-car.car_maxTorque,car.car_maxTorque);
	var torque = car.car_torque * CAR_TORQUEFACTOR * speedfactor;
	var brake = car.car_brake * CAR_TORQUEFACTOR;

// don't brake and accelerate at the same time	
	if (brake) torque = 0;

	if (car.car_wheelDrive & 2) { // front driven?
		car_wheeldrive((ENTITY*)car.car_wheelFL,steer,-torque,brake); // -torque because left wheels are 180° rotated
		car_wheeldrive((ENTITY*)car.car_wheelFR,steer,torque,brake);
	} else {
		car_wheeldrive((ENTITY*)car.car_wheelFL,steer,0,brake);
		car_wheeldrive((ENTITY*)car.car_wheelFR,steer,0,brake);
	}
	if (car.car_wheelDrive & 1) { // rear driven?
		car_wheeldrive((ENTITY*)car.car_wheelRL,0,-torque,brake); 
		car_wheeldrive((ENTITY*)car.car_wheelRR,0,torque,brake);
	} else {
		car_wheeldrive((ENTITY*)car.car_wheelRL,0,0,brake); 
		car_wheeldrive((ENTITY*)car.car_wheelRR,0,0,brake);
	}

	//DEBUG_VAR(player.car_speed,10);
	//DEBUG_VAR(car.car_steerangle,30);
	//DEBUG_VAR(car.car_torque,50);
	//DEBUG_VAR(car.car_brake,70);
}

// initalize the car chassis
action car_init() 
{
	my.actor_id = ID_CAR; // uniquely identify a car

// initialize the skills to default values when zero
	SKILL_DEFAULT(car_maxSpeed,tcar_maxSpeed);
	SKILL_DEFAULT(car_maxTorque,tcar_maxTorque);
	SKILL_DEFAULT(car_maxSteer,tcar_maxSteer);
	SKILL_DEFAULT(car_wheel_fx,tcar_wheel_fx); // default offset for the front wheels on the x axis
	SKILL_DEFAULT(car_wheel_fy,tcar_wheel_fy); // default offset for the front wheels on the y axis
	SKILL_DEFAULT(car_wheel_fz,tcar_wheel_fz); // default offset for the front wheels on the z axis
	SKILL_DEFAULT(car_wheel_rx,tcar_wheel_rx); // default offset for the rear wheels on the x axis
	SKILL_DEFAULT(car_wheel_ry,tcar_wheel_ry); // default offset for the rear wheels on the y axis
	SKILL_DEFAULT(car_wheel_rz,tcar_wheel_rz); // default offset for the rear wheels on the z axis
	SKILL_DEFAULT(car_spsSpring,tcar_spsSpring);
	SKILL_DEFAULT(car_spsDamper,tcar_spsDamper);
	SKILL_DEFAULT(car_spsWay,tcar_spsWay);
	SKILL_DEFAULT(car_massFactor,tcar_massFactor);
	SKILL_DEFAULT(car_massOffset,tcar_massOffset);
	SKILL_DEFAULT(car_massShape,tcar_massShape);
	SKILL_DEFAULT(car_frictionWheel,tcar_frictionWheel);
	SKILL_DEFAULT(car_frictionLatF,tcar_frictionLatF);
	SKILL_DEFAULT(car_frictionLatR,tcar_frictionLatR);
	SKILL_DEFAULT(car_wheelDrive,tcar_wheelDrive);
	
	if(tcar_hover) set(my,car_hover);

// init physics
	my.scale_z *= 0.9;	// reduce z size by 10% to prevent the chassis from dragging over the ground
	pXent_settype(my, PH_RIGID, PH_BOX);
	my.scale_z /= 0.9;

// add 4 wheels	
	vec_mul(my.car_wheel_fx,my.scale_x);
	vec_mul(my.car_wheel_rx,my.scale_x);
	my.car_wheelFL = car_wheelcreate(my,vector(my.car_wheel_fx,-my.car_wheel_fy,90));
	my.car_wheelFR = car_wheelcreate(my,vector(my.car_wheel_fx,my.car_wheel_fy,90));
	my.car_wheelRL = car_wheelcreate(my,vector(my.car_wheel_rx,-my.car_wheel_ry,90));
	my.car_wheelRR = car_wheelcreate(my,vector(my.car_wheel_rx,my.car_wheel_ry,90));

	pXent_setmass(my,my.car_massFactor/100*pXent_getmass(my));
// set a low center of mass, and set symmetric inertia for reducing the trend to topple in curves
	pXent_setmassoffset(my,
		vector(0,0,my.car_massOffset/200*(my.max_z-my.min_z)),
		vector(my.car_massShape/100,1,1));
	pXent_setdamping (my,10,30);
	pXent_setiterations(my,16);

	// set the event handler if we hit something (not used yet)
	 //my.event = EventImpact; 
	// my.emask = ENABLE_FRICTION;
}

///////////////////////////////////////////////////////////////////////////////////////
// main car action - assign this action to your car body model
// uses: car_maxSpeed, car_wheel_fx, car_wheel_fy, car_wheel_fz, car_wheel_rx, car_wheel_ry, car_wheel_rz, car_maxTorque, car_maxTorqBrake, car_spsSpring, car_spsDamper, car_spsWay, car_frictionWheel, car_frictionLatF, car_frictionLatR
// uses: car_hover
action car_player() 
{
	player = me;
	SND_CREATE_STATIC(sndEngine,engine_wav);
	SND_CREATE_STATIC(sndTires,tires_wav);
	SND_CREATE_STATIC(sndCrash,crash_wav);
	
	car_init();			// initialize chassis, add 4 wheels
//	my.material=mtl_car;

	while(1) {
		car_input(me);	// control the car with keyboard & joystick
		car_move(me);		// drive the car
		car_animate(me); // animate steering & suspension
		car_noise(me,sndEngine,sndTires,sndCrash); // handle car sounds 
		 
		wait(1);
	}
}

#endif //car_c
