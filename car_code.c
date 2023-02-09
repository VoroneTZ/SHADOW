///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//PhysX car script/////////////////////////////////////////////////////////////
//by Painkiller (2011)/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
var tcamera_dist = 100;
var tcamera_height = 25;
//Camera functions copied from camera.c
function camera_face(ENTITY* ent,var height)
{
	if (!ent) return;
// adjust height
	camera.z = ent.z + height;
// face ent
	vec_to_angle(camera.pan,vec_diff(NULL,ent.x,camera.x));
}
// look at the entity from position that moves with it
function camera_offset(ENTITY* ent,VECTOR* offset)
{
	if (!ent) return;
	vec_set(camera.x,offset);
	vec_add(camera.x,ent.x);
	camera_face(ent,offset.z);
}
// chase the entity with the camera, while keeping distance and height
function camera_chase(ENTITY* ent,var dist,var height)
{	
	if (!ent) return;
// move camera along line to ent	
	VECTOR vLine;
	vec_diff(vLine,ent.x,camera.x);
	vec_normalize(vLine,dist);
	vec_set(camera.x,vec_diff(NULL,ent.x,vLine));
	camera_face(ent,height);
}
// first or third person camera
function camera_person(ENTITY* ent,VECTOR* offset,var factor)
{
	if (!ent) return;
	vec_set(camera.x,offset);
	vec_rotate(camera.x,ent.pan);
	vec_add(camera.x,ent.x);
	vec_set(camera.pan,vector(ent.pan,ent.tilt*factor,ent.roll*factor));
	if (camera.z < ent.z) { // don't move camera in the ground 
		camera.tilt = 0; 
		camera.z = ent.z;
	}
}
// return the speed of a physX actor in km/h in the forward direction 
var pXent_getspeed(ENTITY* ent)
{
	VECTOR vSpeed,vDir;
	pXent_getvelocity(ent,vSpeed,NULL);
	vec_for_angle(vDir,ent.pan);
// speed in km/h, assume 18 quants = 1 m	
	var speed = vec_dot(vDir,vSpeed) * (60.*60.)/(18.*1000.); 
	if (abs(speed) < 1) 
		return 0;
	else 
		return speed;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SOUND* engine_snd = "engine_mondeo.wav";
SOUND* wind_snd = "wind1.wav";
var engine_snd_handle;
var wind_snd_handle;

var camera_mode=1;
var gear=1;
var max_brake=0;
var max_rpm;
var numgears;
var gear1;
var gear2;
var gear3;
var gear4;
var gear5;
var gear6;
var gearr;
var geard;
var rpm=0;
var gear_ratio=0;
var lspeed=0;
var aspeed=0;
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
function handle_keys_startup() //handles gear shifting and changing camera mode
{
	while(!carplayer) wait(1);
	while(carplayer)
	{
		
		if(key_v) //toggle camera mode
		{
			camera_mode+=1;
			if(camera_mode>3) camera_mode=1;
			while(key_v) wait(1);
		}
		
		if(gear==1 && rpm>=3300) //gear up
		{
			gear=2;
		//	rpm=2200;
		//	gear=minv(gear, numgears);
			wait(-1);
		}
		
		
			if(gear==2 && rpm>=3500) //gear up
		{
			gear=3;
		//	rpm=2200;
		//	gear=minv(gear, numgears);
			wait(-1);
		}
		
		
			if(gear==3 && rpm>=3700) //gear up
		{
			gear=4;
		//	rpm=2200;
			//gear=minv(gear, numgears);
			wait(-1);
		}
		
		
			if(gear==4 && rpm>=3900) //gear up
		{
			gear=5;
		//	rpm=2200;
		//	gear=minv(gear, numgears);
			wait(-1);
		}
		
			if(gear==5 && rpm>=4000) //gear up
		{
			gear=6;
		//	rpm=2200;
		//	gear=minv(gear, numgears);
			wait(-1);
		}
		
				if(gear==2 && rpm<=2300) //gear up
		{
			gear=1;
		//	rpm=2200;
		//	gear=minv(gear, numgears);
			wait(-1);
		}
		
		
			if(gear==3 && rpm<=2500) //gear up
		{
			gear=2;
		//	rpm=2200;
		//	gear=minv(gear, numgears);
			wait(-1);
		}
		
		
			if(gear==4 && rpm<=2700) //gear up
		{
			gear=3;
		//	rpm=2200;
			//gear=minv(gear, numgears);
			wait(-1);
		}
		
		
			if(gear==5 && rpm<=2900) //gear up
		{
			gear=4;
		//	rpm=2200;
		//	gear=minv(gear, numgears);
			wait(-1);
		}
		
			if(gear==6 && rpm<=3000) //gear up
		{
			gear=5;
			//rpm=2200;
		//	gear=minv(gear, numgears);
			wait(-1);
		}
		

	wait(1);
	}
}
function EngineTorqueCurve(var c_rpm ) //get engine torque at given rpm
{
	var c_torque=0;
	
	if(c_rpm<1200) c_torque=350;
	if(c_rpm>=1200 && c_rpm<1400) c_torque=420;
	if(c_rpm>=1400 && c_rpm<1600) c_torque=470;
	if(c_rpm>=1600 && c_rpm<2400) c_torque=480;
	if(c_rpm>=2400 && c_rpm<2800) c_torque=470;
	if(c_rpm>=2800 && c_rpm<3000) c_torque=460;
	if(c_rpm>=3000 && c_rpm<3200) c_torque=450;
	if(c_rpm>=3200 && c_rpm<3400) c_torque=440;
	if(c_rpm>=3400 && c_rpm<3600) c_torque=430;
	if(c_rpm>=3600 && c_rpm<3800) c_torque=410;
	if(c_rpm>=3800 && c_rpm<4000) c_torque=390;
	if(c_rpm>=4000) c_torque=380;
	
	return c_torque;
}
var wheel_angle;

function start_car()
{
	//setup car
	ENTITY* car = ent_create("bmw.mdl",vector(-20293.203,-2757.364,355.830),NULL);
	carplayer=car;
	pXent_settype(car,PH_RIGID,PH_BOX);
	pXent_setmassoffset (car, vector(12, 0, -16), NULL); //low gravity center to prevent toppling
	pXent_setdamping (car, 7.79, 0); //air friction, maybe you want to play with this value for other cars
	
	car.skill1=789; //identify me as a car for AI cars
	set(car, FLAG2); //used by AI cars to scan
	
	//Get wheel model filename from car
	STRING* wheel_filename=str_create("#25");
	str_for_entfile(wheel_filename,car);
	str_trunc(wheel_filename, 4); //remove .mdl
	str_cat(wheel_filename, "_wheel.mdl");
	
	//create and setup wheels
	ENTITY* FLwheel = ent_create(wheel_filename,vector(car.x+27.3,car.y+10.9,car.z-6),NULL); //wheel positions taken from bmw model in MED
	ENTITY* FRwheel = ent_create(wheel_filename,vector(car.x+27.3,car.y-10.9,car.z-6),NULL);
	ENTITY* BLwheel = ent_create(wheel_filename,vector(car.x-22.8,car.y+10.9,car.z-6),NULL);
	ENTITY* BRwheel = ent_create(wheel_filename,vector(car.x-22.8,car.y-10.9,car.z-6),NULL);
	set(FLwheel, PASSABLE);
	set(FRwheel, PASSABLE);
	set(BLwheel, PASSABLE);
	set(BRwheel, PASSABLE);
	pXcon_add ( PH_WHEEL, FLwheel, car, 0 ); //add constraints
	pXcon_add ( PH_WHEEL, FRwheel, car, 0 );
	pXcon_add ( PH_WHEEL, BLwheel, car, 0 );
	pXcon_add ( PH_WHEEL, BRwheel, car, 0 ); 
	pXcon_setparams2 (FLwheel, NULL, vector(62, 100, 0), vector(500, 100, 4) ); //set longitudinal friction, lateral friction, suspension spring, susp. damper and susp. way
	pXcon_setparams2 (FRwheel, NULL, vector(62, 100, 0), vector(500, 100, 4) );
	pXcon_setparams2 (BLwheel, NULL, vector(150, 300, 0), vector(500, 100, 4) );
	pXcon_setparams2 (BRwheel, NULL, vector(150, 300, 0), vector(500, 100, 4) );
//	 car.event = player_remove;

 
	//setup car shader
	if (edition >= 3) //only if your GS supports shaders
	{
	//	car.material=mtl_envBump; //skycube reflections
		car.material=MaskedEnvMap; //realtime reflections
		car.skill41=floatv(1);
		car.skill42=floatv(80);
	}

	
	var steer=0;
	var torque=0;
	var brake=0;
	var throttle=0;
	  var skill1_old = 0, skill2_old = 0, skill3_old = 0;
	//setup sounds
	engine_snd_handle=snd_loop(engine_snd, 100, 0); //engine sound
	wind_snd_handle=snd_loop(wind_snd, 100, 0); //wind sound
	
	//setup car parameters
		max_brake=5000;
		numgears=6;
		gear1=3.1;
		gear2=1.78;
		gear3=1.18;
		gear4=0.81;
		gear5=0.57;
		gear6=0.50;
		gearr=-2.90;
		geard=3.95;
		max_rpm=4000;
		
	var pi=3.14159265;

	while(1)
	{

  

		wheel_angle=FRwheel.pan;
		lspeed=pXent_getspeed(car); //car linear speed
		aspeed=lspeed/(3.6*0.33); //wheels angular speed
		
		//change dear ratio depending of current gear
		if(gear==1) gear_ratio=gear1;
		if(gear==2) gear_ratio=gear2;
		if(gear==3) gear_ratio=gear3;
		if(gear==4) gear_ratio=gear4;
		if(gear==5) gear_ratio=gear5;
		if(gear==6) gear_ratio=gear6;
		if(gear==-1) gear_ratio=gearr;
		
		
		//smooth steering with arrow keys
			//smooth steering with arrow keys
		steer+=5*(key_d-key_a)*time_step;
		if(!key_d && !key_a)
		{
			if(abs(steer)<1.5) steer=0;
			if(steer<0) steer+=7*time_step;
			if(steer>0) steer-=7*time_step;
			if(abs(steer)<1.5) steer=0;
		}
		steer=clamp(steer, -40, 40);
		
		//smooth throttle
		throttle+=0.5*key_w*time_step;
		if(!key_w) throttle-=0.5*time_step;
		throttle=clamp(throttle, 0, 1);
		torque = EngineTorqueCurve(rpm) * throttle * gear_ratio * geard * 0.9 *324; //324 converts from kg*m*m*s-2 to kg*quant*quant*s-2
		
		//get rpm from wheel speed
		rpm = aspeed * gear_ratio * geard * 60. / (2*pi);
		if(rpm<1000) rpm=1000;
		if(rpm>max_rpm) torque=0;
		
		brake+=max_brake*0.5*car.skill3*time_step;
		if(!car.skill3) brake-=max_brake*0.5*time_step;
		brake=clamp(brake, 0, max_brake);
	//	if(key_cud) car.skin=1; else car.skin=1;
		
		//set wheels angle, torque and braking torque
		pXcon_setwheel (FLwheel,steer,-torque,brake);
		pXcon_setwheel (FRwheel,steer,-torque,brake);
		pXcon_setwheel (BLwheel,0,0,brake);
		pXcon_setwheel (BRwheel,0,0,brake);
		
		//key l to kick toppled car
		VECTOR temp;
		vec_set(temp, vector(0, 0, 100*time_step));
		vec_rotate(temp, car.pan);
		if(key_l) pXent_addforcecentral(car, temp);
		
		//update camera
		if(camera_mode==1) camera_chase(carplayer,tcamera_dist,tcamera_height); //external back camera
		if(camera_mode==2) camera_offset(carplayer,vector(tcamera_dist,tcamera_dist,tcamera_height)); //external fixed camera
		if(camera_mode==3) camera_person(carplayer, nullvector, 1); //cockpit view, replace nullvector with your desired cockpit position
		
		//tune car sound ddepending of engine rpm
		snd_tune(engine_snd_handle, 100, rpm*0.07, 0);
		//tune wind sound depending of car speed
		snd_tune(wind_snd_handle, 100*(minv( abs(lspeed)/200. , 1) )+1, 0, 0);
		
		wait(1);
	}
}
var abs_speed=0;
PANEL* tachometer =
{
	needle(70, 70, "needle_mondeo.tga", 70, 70, 128, 340, 0, abs_speed);
	bmap="tacho_mondeo.tga";
	flags=  FILTER;
}
FONT* arial_font = "Arial#50";
PANEL* rpm_meter =
{
	  digits (  0, 0, 4, arial_font, 3, wheel_angle);
	needle(70, 70, "needle_mondeo.tga", 70, 70, 128, 7000, 0, rpm);
	bmap="rpm_mondeo.tga";
	flags= FILTER;
}
function place_meters_startup() //Align tachometer and rpm meter
{
	while(1)
	{
		abs_speed=abs(lspeed);
		
		tachometer.pos_x=50;
		tachometer.pos_y=screen_size.y-tachometer.size_x-50;
		rpm_meter.pos_x=screen_size.x-rpm_meter.size_x-50;
		rpm_meter.pos_y=screen_size.y-rpm_meter.size_x-50;
		
	wait(1);
	}
}
