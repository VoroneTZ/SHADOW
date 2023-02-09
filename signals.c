///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//Traffic Signals script///////////////////////////////////////////////////////
//by Painkiller (2011)/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
action s_90() //90 kmh speed limit signal
{
	pXent_settype(me,PH_STATIC,PH_POLY);
	
	while(1)
	{
		c_scan(my.x, my.pan, vector(60, 90, 150), SCAN_ENTS | IGNORE_ME | SCAN_FLAG2); //search for AI cars and change their max speed (stored in skill2)
		if(you)
		{
			if(you.skill1==789) //found a car
			{
				you.skill2=27-random(3); //27 is aprox. 90 kmh in AI cars and add also a random value
			}
		}
		
	wait(1);
	}
}
action s_50() //90 kmh speed limit signal
{
	pXent_settype(me,PH_STATIC,PH_POLY);
	
	while(1)
	{
		c_scan(my.x, my.pan, vector(60, 90, 150), SCAN_ENTS | IGNORE_ME | SCAN_FLAG2); //search for AI cars and change their max speed (stored in skill2)
		if(you)
		{
			if(you.skill1==789) //found a car
			{
				you.skill2=15-random(3); //15 is aprox. 50 kmh in AI cars and add also a random value
			}
		}
		
	wait(1);
	}
}
action s_stop() //stop signal
{
	pXent_settype(me,PH_STATIC,PH_POLY);
	
	my.skill1=456; //identify me as a stop sign for AI cars
	set(my, FLAG2); //used by AI cars to scan
}
action green_1() //green light
{
	my.pan=you.pan;
	vec_scale(my.scale_x, 0.01);
	
	while(1)
	{
		reset(my, BRIGHT);
		my.ambient=-50;
		wait(-20);
		set(my, BRIGHT);
		my.ambient=0;
		wait(-17);
		reset(my, BRIGHT);
		my.ambient=-50;
		wait(-3);
	
		wait(1);
	}

}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
action amber_1() //amber light
{
	my.pan=you.pan;
	vec_scale(my.scale_x, 0.01);
	
	while(1)
	{
		reset(my, BRIGHT);
		my.ambient=-50;
		wait(-37);
		set(my, BRIGHT);
		my.ambient=0;
		wait(-3);
		reset(my, BRIGHT);
		my.ambient=-50;
		
		wait(1);
	}

}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
action red_1() //red light
{
	my.pan=you.pan;
	vec_scale(my.scale_x, 0.01);
	my.skill1=123; //identify me as a red light for AI cars
	set(my, FLAG2); //used by AI cars to scan
	while(1)
	{
		set(my, FLAG2);
		set(my, BRIGHT);
		my.ambient=0;
		wait(-20);
		reset(my, FLAG2);
		reset(my, BRIGHT);
		my.ambient=-50;
		wait(-20);
		set(my, FLAG2);
		set(my, BRIGHT);
		my.ambient=0;
		
		wait(1);
	}
	
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
action t_light() //first traffic light
{
	pXent_settype(me,PH_STATIC,PH_POLY);
	
	VECTOR pos_1;
	vec_set(pos_1, vector(2.6, -30.7, 49.7));
	vec_for_ent(pos_1, me);
	ent_create("green.tga", pos_1, green_1);
	pos_1.z+=2.6;
	ent_create("amber.tga", pos_1, amber_1);
	pos_1.z+=2.6;
	ent_create("red.tga", pos_1, red_1);
	vec_set(pos_1, vector(2.8, 0, 25.2));
	vec_for_ent(pos_1, me);
	ent_create("green.tga", pos_1, green_1);
	pos_1.z+=2.6;
	ent_create("amber.tga", pos_1, amber_1);
	pos_1.z+=2.6;
	ent_create("red.tga", pos_1, red_1);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
action green_2() //green light
{
	my.pan=you.pan;
	vec_scale(my.scale_x, 0.01);
	
	while(1)
	{
		set(my, BRIGHT);
		my.ambient=0;
		wait(-17);
		reset(my, BRIGHT);
		my.ambient=-50;
		wait(-3);
		wait(-20);
		set(my, BRIGHT);
		my.ambient=0;
	
		wait(1);
	}

}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
action amber_2() //amber light
{
	my.pan=you.pan;
	vec_scale(my.scale_x, 0.01);
	
	while(1)
	{
		reset(my, BRIGHT);
		my.ambient=-50;
		wait(-17);
		set(my, BRIGHT);
		my.ambient=0;
		wait(-3);
		reset(my, BRIGHT);
		my.ambient=-50;
		wait(-20);
		
		wait(1);
	}

}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
action red_2() //red light
{
	my.pan=you.pan;
	vec_scale(my.scale_x, 0.01);
	my.skill1=123; //identify me as a red light for AI cars
	set(my, FLAG2); //used by AI cars to scan
	
	while(1)
	{
		reset(my, FLAG2);
		reset(my, BRIGHT);
		my.ambient=-50;
		wait(-20);
		set(my, FLAG2);
		set(my, BRIGHT);
		my.ambient=0;
		wait(-20);
		reset(my, FLAG2);
		reset(my, BRIGHT);
		my.ambient=-50;
		
		wait(1);
	}
	
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
action t_light_2() //second traffic light
{
	pXent_settype(me,PH_STATIC,PH_POLY);
	
	VECTOR pos_1;
	vec_set(pos_1, vector(2.6, -30.7, 49.7));
	vec_for_ent(pos_1, me);
	ent_create("green.tga", pos_1, green_2);
	pos_1.z+=2.6;
	ent_create("amber.tga", pos_1, amber_2);
	pos_1.z+=2.6;
	ent_create("red.tga", pos_1, red_2);
	vec_set(pos_1, vector(2.8, 0, 25.2));
	vec_for_ent(pos_1, me);
	ent_create("green.tga", pos_1, green_2);
	pos_1.z+=2.6;
	ent_create("amber.tga", pos_1, amber_2);
	pos_1.z+=2.6;
	ent_create("red.tga", pos_1, red_2);
}