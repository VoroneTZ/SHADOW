//////////////////////////////////////////////////////////////////
//  This effect will take a texture and bumpmap it.
//  Then it will display the cubicenv map based
//  on a mask that is in the A channel of skintex.
//
//  By: Eric Hendrickson-Lambert (Steempipe)
//  Modified by Painkiller for car scripts (2011)
//////////////////////////////////////////////////////////////////

var cubemap_resolution = 512; //set the resolution of the rendered cubemap (power of two!) - the render file in this case must have x=6*256 (=1536) and y=256
										/* 128 =  x=768 y=128
											256 =  x=1536 y=256
											512 =  x=3072 y=512
											1024 =  x=6144 y=1024
										256 or 512 should be fine
										IMPORTANT: SET THE SAME NUMBER FOR THIS |
																							 v */
														 BMAP* render = "render_map512+6.tga";




BMAP* maskedenvmap_cube=  "skycube+6.tga";	// CubicEnvMap

MATERIAL* mtl1;

function mtl_copy(mtl_source)
{
	mtl1 = mtl_source;
	vec_set(mtl.ambient_blue,mtl1.ambient_blue);
	vec_set(mtl.specular_blue,mtl1.specular_blue);
	vec_set(mtl.diffuse_blue,mtl1.diffuse_blue);
	vec_set(mtl.emissive_blue,mtl1.emissive_blue);
	mtl.power = mtl1.power;

//	set a lighting vector for DOT3 bumpmapping
//	mtl.Skill4 = pixel_for_vec(vector(200,200,200),100,8888);
}

function MaskedEnvMap_view()
{
	mat_set(mtl.matrix,matViewInv);
	mtl.matrix41=0;
	mtl.matrix42=0;
	mtl.matrix43=0;
}

function MaskedEnvMap_init()
{
	mtl_copy(mat_model);
	bmap_to_cubemap(bmap_to_mipmap(mtl.skin1));
	
	mtl.event=MaskedEnvMap_view;
	set(mtl,ENABLE_VIEW);
}

MATERIAL* MaskedEnvMap =
{
	skin1=render;

	event=MaskedEnvMap_init;

	effect = "EnvBump.fx";
}


//////////////////////////
//DYNAMIC CUBEMAP
//////////////////////////

VIEW* rendered_view = //
{
     pos_x = 0;
     pos_y = 0;
     size_x = cubemap_resolution; // size of the view on x and y
     size_y = cubemap_resolution; // must be the same as one sixth of the cubemap
     arc = 90; //makes it seamless
     flags = SHOW;
}

function update_view()
{
	while(!carplayer) wait(1); //wait until car is created
	while(1)
	{
		rendered_view.x = carplayer.x; //keeps the position of the cubemap up to date
   	rendered_view.y = carplayer.y;
   	rendered_view.z = carplayer.z;
		
	wait(1);
	}
}

function render_cubemap() //renders the cubemap (order: back, right, front, left, down, up)
{
	update_view();
	rendered_view.bmap = render; //put in render for cubemap
	while(1)
	{	
	rendered_view.pos_x = 0;
	rendered_view.tilt= 0;
	rendered_view.pan = 180;
	wait(1);
	rendered_view.pos_x = cubemap_resolution; //changes the position of the current frame on the cubemap
	rendered_view.pan = 90;
	wait(1);
	rendered_view.pos_x = cubemap_resolution*2;
	rendered_view.pan = 0;
	wait(1);
	rendered_view.pos_x = cubemap_resolution*3;
	rendered_view.pan = -90;
	wait(1);
	rendered_view.pos_x = cubemap_resolution*4;
	rendered_view.pan = 90;
	rendered_view.tilt= -90;
	wait(1);
	rendered_view.pos_x = cubemap_resolution*5;
	rendered_view.pan = 90;
	rendered_view.tilt= 90;
	wait(1);
	}
}

////////////////////////////////////////////
//END