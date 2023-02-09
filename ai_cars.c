///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//AI traffic cars script///////////////////////////////////////////////////////
//by Painkiller (2011)/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

action ai_car()
{
	
	my.skill1=789; //identify me as a car for AI cars
	set(my, FLAG2); //used by AI cars to scan
	
	//Get wheel model filename from car
	STRING* wheel_filename=str_create("#25");
	str_for_entfile(wheel_filename,me);
	str_trunc(wheel_filename, 4); //remove .mdl
	str_cat(wheel_filename, "_wheel.mdl");
	
	//create and setup wheels
	ENTITY* FLwheel = ent_create(wheel_filename,nullvector,NULL); //wheel positions taken from bmw model in MED
	ENTITY* FRwheel = ent_create(wheel_filename,nullvector,NULL);
	ENTITY* BLwheel = ent_create(wheel_filename,nullvector,NULL);
	ENTITY* BRwheel = ent_create(wheel_filename,nullvector,NULL);
	set(FLwheel, PASSABLE);
	set(FRwheel, PASSABLE);
	set(BLwheel, PASSABLE);
	set(BRwheel, PASSABLE);
	
	//set environmet mapping material
	if (edition >= 3) //only if your GS supports shaders
	{
		my.material=mtl_envBump;
		my.skill41=floatv(1);
		my.skill42=floatv(80);
	}
	
	//finds his path
	var node=path_scan(me, my.x, my.pan, vector(360, 0, 130));
	var dist=0;
	VECTOR node_pos;
	VECTOR move_vec;
	ANGLE node_angle;
	
	ENTITY* pointer_signal;
	
	//set 15 (aprox. 50 kmh) as default speed
	var my_speed=15;
	my.skill2=15;
	
	while(me)
	{
		
		//move and rotate the car
		path_getnode(me, node, node_pos, NULL);
		vec_diff(move_vec, node_pos, my.x);
		vec_normalize(move_vec, my_speed*time_step); //set speed
		vec_add(my.x, move_vec); //move the car
		//place and align with floor
		c_trace(my.x, vector(my.x, my.y, my.z-1000), IGNORE_PASSABLE | USE_POLYGON | IGNORE_FLAG2);
		var pan_old=my.pan;
		vec_to_angle(my.pan, normal.x);
		my.tilt-=90;
		my.pan=pan_old;
		my.z=target.z+15; //15 is the value from origin to ground in bmw model
		vec_to_angle(node_angle, move_vec);
		my.pan += ang(node_angle.pan - my.pan) * 0.4 * time_step; // smooth rotation code
		
		if(vec_dist(my.x, node_pos)<40) node=path_nextnode(me,node,1); //switch to next node
		
		//Update wheels position (taken from bmw model in MED)
		vec_set(FLwheel.x, vector(27.3, 10.9, -6-4));
		vec_set(FRwheel.x, vector(27.3, -10.9, -6-4));
		vec_set(BLwheel.x, vector(-22.8, 10.9, -6-4));
		vec_set(BRwheel.x, vector(-22.8, -10.9, -6-4));
		vec_rotate(FLwheel.x, my.pan);
		vec_rotate(FRwheel.x, my.pan);
		vec_rotate(BLwheel.x, my.pan);
		vec_rotate(BRwheel.x, my.pan);
		vec_add(FLwheel.x, my.x);
		vec_add(FRwheel.x, my.x);
		vec_add(BLwheel.x, my.x);
		vec_add(BRwheel.x, my.x);
		FLwheel.pan=0;
		FRwheel.pan=0;
		BLwheel.pan=0;
		BRwheel.pan=0;
		FLwheel.tilt-=my_speed*5*time_step*sign(my_speed);
		FRwheel.tilt-=my_speed*5*time_step*sign(my_speed);
		BLwheel.tilt-=my_speed*5*time_step*sign(my_speed);
		BRwheel.tilt-=my_speed*5*time_step*sign(my_speed);
		FLwheel.pan=my.pan;
		FRwheel.pan=my.pan;
		BLwheel.pan=my.pan;
		BRwheel.pan=my.pan;
		var distance=0;
		//scan for cars in the front, traffic signals or traffic lights
		distance=c_scan(my.x, my.pan, vector(15, 90, 250), SCAN_ENTS | IGNORE_ME | SCAN_FLAG2);
		if(you)
		{
			if(you.skill1==789) //traffic car found
			{
				my.skin=3;
				if(distance<150) my_speed-=1*time_step;
				else my_speed-=0.5*time_step;
				my_speed=maxv(0, my_speed);
			}
			if(you.skill1==456) //stop sign found
			{
				my.skin=3;
				if(distance<150) my_speed-=7*time_step;
				else my_speed-=3*time_step;
				my_speed=maxv(0, my_speed);
				if(my_speed==0) //once we are stopped wait until there is no other cars
				{
					pointer_signal=you; //save the signal pointer and reset flag2 so we won't detect it while scanning for other cars
					reset(pointer_signal, FLAG2);
					wait(-1);
					while(1)
					{
						c_scan(my.x, my.pan, vector(90, 90, 200), SCAN_ENTS | IGNORE_ME | SCAN_FLAG2);//search for other cars
						if(you)
						{
							if(you.skill1!=789) break; //not a traffic car? then get out of here
						}else{
							break; //get out of this loop
						}
						
					wait(1);
					}
					set(pointer_signal, FLAG2); //set again signal flag
				}
			}
			if(you.skill1==123) //traffic light in red found
			{
				my.skin=3;
				if(distance<150) my_speed-=1*time_step;
				else my_speed-=0.5*time_step;
				my_speed=maxv(0, my_speed);
			}
		}else{
			my.skin=1;
			if(my_speed<my.skill2)
			{
				my_speed+=0.3*time_step; //accelerate to max speed
				my_speed=minv(my.skill2, my_speed);
			}
			if(my_speed>my.skill2)
			{
				my_speed-=0.3*time_step; //brake if we are exceeding max speed
				my_speed=maxv(my.skill2, my_speed);
			}
		}
		
		
	wait(1);
	}
}