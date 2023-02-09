/////////////////////////////////////////
//eRender - entities rendering for shadow
//render bitmap for projection texture
//-----------------Xd1vo------------------
//////////////////////////////////////////

VIEW* rView = {layer=1000;material = mtl_black;flags = NOFLAG1 ;}// view for rendering shadows
ENTITY* rEnt[100];// list of entities that render for shadows
STRING* rFile = "rScreen"; // def name for saving projection shadows bmap and parametrs
BMAP* rBmap; //in this bmap render shadow for entities 

void get_points (VECTOR* vset,ENTITY* this,var num)
{
	VECTOR vMin,vMax;
	vec_for_min (vMin,this);vec_for_max (vMax,this);
	if (num==0) vec_set(vset,vector(vMin.x,vMin.y,vMin.z));
	if (num==1) vec_set(vset,vector(vMax.x,vMin.y,vMin.z));
	if (num==2) vec_set(vset,vector(vMax.x,vMax.y,vMin.z));
	if (num==3) vec_set(vset,vector(vMin.x,vMax.y,vMin.z));
	
	if (num==4) vec_set(vset,vector(vMin.x,vMin.y,vMax.z));
	if (num==5) vec_set(vset,vector(vMax.x,vMin.y,vMax.z));
	if (num==6) vec_set(vset,vector(vMax.x,vMax.y,vMax.z));
	if (num==7) vec_set(vset,vector(vMin.x,vMax.y,vMax.z));
	vset.x *= this.scale_x;vset.y *= this.scale_y;vset.z *= this.scale_z;
	vec_rotate(vset,this.pan);vec_add(vset,this.x);
}

function is_points_visible (var num)
{
	var c,cp;VECTOR tmp;
	for (c=0;c<=num;c++)
		for(cp=0;cp<=7;cp++) {
			get_points(tmp,rEnt[c],cp);if (vec_to_screen(tmp,rView)==NULL) return(0);
			}
	return(1);
}

function pixel_blur (BMAP* sor,var dx,var dy,var pas)
{
	VECTOR col,fcol;
	var x1,y1,pixel;
	var count=0;
	var cp = maxv(minv(pas,1),0.1);
	vec_set(fcol,nullvector);
	
	for (y1=dy-pas;y1<=(dy+pas);y1+=cp) for (x1=dx-pas;x1<=(dx+pas);x1+=cp) 
	{
		pixel = pixel_for_bmap(sor,clamp(x1,0,bmap_width(sor)-1),clamp(y1,0,bmap_height(sor)-1));
		pixel_to_vec(col,NULL,888,pixel);
		vec_add(fcol,col);count++;
	}
	fcol.x /= count;fcol.y /= count;fcol.z /= count;
	pixel = pixel_for_vec(fcol,NULL,888);
	return (pixel);
}

function screen_to_1024 (var blur)// this function create 1024x1024 projection texture from screen
{
	var pixel,x1,y1;
	var sy;
	BMAP* dest = bmap_createblack(1024,1024,24);
	BMAP* sor = bmap_createblack(screen_size.x,screen_size.y,24);
	bmap_for_screen(sor,0,1);
	bmap_lock(dest,888);bmap_lock(sor,888);
	sy = bmap_height(sor);
	for (y1=0;y1<1024;y1++) for(x1=0;x1<1024;x1++)
	{
		pixel = pixel_blur(sor,(x1/1024)*sy,(y1/1024)*sy,blur);
		pixel_to_bmap(dest,x1,y1,pixel);	
	}
	bmap_unlock(dest);bmap_unlock(sor);
	return(dest);
}

function screen_render_entities (VECTOR* lPos,VECTOR* aang,var* fov,var cent)
{
	// lPos light position; cent - count of render entities(rEnt[cent]);
	// aang,fov - to be set by this function;
	var c,cp;
	VECTOR tmp;
	VECTOR vMin,vMax;
	VECTOR eMin,eMax;
	you = ent_next(NULL);
	while (you!=NULL) {set(you,FLAG1);you = ent_next(you);} 
	//hide enitities what not in list (rEnt[]) for rView
	for (c=0;c<=cent;c++) 
	{
		//find bounding box and center of all entities what in the list (rEnt[])
		reset(rEnt[c],FLAG1);c_setminmax(rEnt[c]);
		if (c==0) {get_points(tmp,rEnt[c],0);vec_set(vMin,tmp);vec_set(vMax,tmp);}
		for (cp=0;cp<=7;cp++)
		{
			get_points(tmp,rEnt[c],cp);
			if (vMin.x>tmp.x) vMin.x=tmp.x;if (vMin.y>tmp.y) vMin.y=tmp.y;
			if (vMin.z>tmp.z) vMin.z=tmp.z;if (vMax.x<tmp.x) vMax.x=tmp.x;
			if (vMax.y<tmp.y) vMax.y=tmp.y;if (vMax.z<tmp.z) vMax.z=tmp.z;
		}
	}
	vec_lerp(eMin,vMin,vMax,0.5);//find center position of all entities (rEnt[])
	
	draw_box3d(vMin,vMax,vector(0,0,255),100);//debug bounding box
	draw_point3d(eMin,vector(10,200,0),100,5);//debug center
	
	vec_set(rView.x,lPos);vec_set(tmp,rView.x);vec_sub(eMin,rView.x);//set position of rView
	vec_to_angle(tmp,eMin);tmp.z=0;
	
	set(rView,VISIBLE);vec_set(rView.pan,tmp);//now rView look at entity (rEnt[]) 
	rView.size_x = screen_size.y;rView.size_y = screen_size.y; // set symmetrical borders for rView
	rView.arc = 60;wait(1);//render rView
	
	if (is_points_visible(cent)) //find Fov there all entities visible
	while(is_points_visible(cent)&&rView.arc>2) {rView.arc--;wait(1);}
		else while(!is_points_visible(cent)&&rView.arc<175) {rView.arc++;wait(1);}
		

	
	vec_set(sky_color,vector(255,255,255));wait(1);//set background to white
	reset(rView,VISIBLE);vec_set(sky_color,vector(128,0,0));//back background to normal
	
	rBmap = screen_to_1024(0.5);//render shadow for entities, with blur factor
	
	STRING* name = "#20";
	str_cpy(name,rFile);str_cat(name,".png");
	bmap_save(rBmap,name); // save shadow bmap 
	str_cpy(name,rFile);str_cat(name,".txt");
	c=0; c = file_open_write(name);
	file_var_write(c,lPos.x);file_var_write(c,lPos.y);file_var_write(c,lPos.z);
	file_var_write(c,tmp.x);file_var_write(c,tmp.y);file_var_write(c,tmp.z);
	file_var_write(c,rView.arc);file_close(c);// save parametrs for projection texture to file
	
	vec_set(aang,tmp);*fov=rView.arc;//return fov and angle 
}