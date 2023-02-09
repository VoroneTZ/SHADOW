////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Special thanks go to Loopix for the grass models and to Nifty for the idea
// 1) Include svegetation.wdl in your project
// 2) Place a terrain entity inside the level and attach it the action named my_terrain. Set its skill1 and skill2 values.
// 3) Export the skin of the terrain and paint the areas where the grass and the trees are supposed to appear in green (R G B = 0 255 0)
// 4) Save the resulting file as colormap.tga and copy it inside your game folder. That's it!
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

var skin_size_x; // the size of the skin (and the color map) in pixels
var skin_size_y; // on the x and y axis

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STRING* grass1_mdl = "grass1.mdl";
STRING* grass2_mdl = "grass2.mdl";
STRING* tree1_mdl = "tree1.mdl";

STRING* colormap_tga = "colormap.tga";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BMAP* vegetation_map;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ENTITY* terrain1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function place_grass();
function place_trees();
function color_map();
function weaving_grass();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define grass_area skill1; // the size of the grassy area that surrounds the player, set it in Wed
#define grass_dist skill2; // the distance between two consecutive grass models, set it in Wed

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
var tree_number=200.0;
var number_tree=0;
// uses grass_area, grass_dist
action Terrain1()
{

		my.min_x=-6781;//5295//4081
	//entry:Maximum x
	my.max_x=7300;//4566//3041
	//entry:Minimum y
	my.min_y=9053;//5200//4053
	//entry:Maximum y
	my.max_y=-6300;//4500//3300
	//image:help.bmp
//	place_grass();
//	bush_load();
//	bush2_load();
//	pages_load();
	while(number_tree<tree_number)
	{
		ent_create(grass2_mdl, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), place_grass);
		ent_create(grass1_mdl, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), place_grass);
		ent_create(grass1_mdl, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), place_grass);
		number_tree+=0.1;
		//	wait(1);
		
	}
	
}

function generate_grass()
{
	max_entities = 10000;
	wait (3); // wait until the level is loaded
	VECTOR grass_pos;
	var grass_id = 1;
	VECTOR grass_coords;
	ent_create (colormap_tga, nullvector, color_map); // create the color map entity
	// wait until the player, the terrain and the color map appear in the level
	while ((player == NULL) || (terrain1 == NULL) || (vegetation_map == NULL)) {wait (1);}
	grass_pos.x = player.x - terrain1.skill1; // set the initial position of the grass models
	grass_pos.y = player.y - terrain1.skill1; // surround the player with the grass models
	grass_pos.z = terrain1.max_z + 400; // and place them up high in the sky
	grass_coords.x = grass_pos.x;	
	grass_coords.y = grass_pos.y;
	while (grass_coords.x < player.x + terrain1.skill1)
	{
		grass_pos.y = grass_coords.y + (random(0.2 * terrain1.skill2) - 0.4 * terrain1.skill2);
		grass_pos.x = grass_coords.x + (random(0.2 * terrain1.skill2) - 0.4 * terrain1.skill2);
		if (random (1) > 0.1)
		{
			you = ent_create (grass1_mdl, grass_pos.x, place_grass);
		}
		else
		{
			you = ent_create (grass2_mdl, grass_pos.x, place_grass);
		}
		// we can spread the cpu load over 10 consecutive frames by giving every 10th model a different id (skill1 value)
		you.skill1 = grass_id; // used for further optimizations (not used in this demo)
		grass_id %= 10;
		grass_id += 1;
		grass_coords.y += terrain1.skill2;
		if (grass_coords.y > (player.y + terrain1.skill1))
		{
			grass_coords.x += terrain1.skill2;
			grass_coords.y = player.y - terrain1.skill1;
		}
		if (random (1) > 0.99) // play with 0.99 to adjust the number of trees in the level
		{
			grass_pos.x += 20 - random(40); // don't plant the tree in the same spot with a grass model
			grass_pos.y += 20 - random(40);
		//	ent_create (tree1_mdl, grass_pos.x, place_trees);
		}
	}
}

function color_map()
{
	set(my,PASSABLE);
	//set(my,INVISIBLE);
 	vegetation_map = bmap_for_entity (my, 0);
	skin_size_x = bmap_width (vegetation_map); // get the size of the color map (same with the skin of the terrain)
	skin_size_y = bmap_height (vegetation_map); // on the x and y axis
}
 
function place_grass()
{	set(my,PASSABLE);
  my.material = mtl_animTree;
   mtl_setup(40,40,20,20);
	
	//Section Tree
	//enable:Tree Material?(low performance)
	//my.material=mtl_vegetation;
	
	my.pan=random(360);
//	my.skill9=random(invisible_randomize);
	var lv_speed = 12; 
	var lv_power =12; 
	lv_speed = random(8); 
	lv_power = random(12);
	var lv_sin;
	if(my.skill1==0){my.skill1=4;} 
	if(my.skill2==0){my.skill2=2;}
	my.skill6=random(360); 
	my.skill3=my.x; 
	my.skill4=my.y; 
	my.skill5=my.z; 
	VECTOR temp;
	
	var gg=0;
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;

		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS)+ 3; 
		

		if(trace_hit)
		{
			my.z=my.z+5;
			gg=11;
		}
		wait(1);
	}
		while(1) 
	{ 

	
		if(vec_dist(camera.x,my.x)>1500)
		{
			set(my,INVISIBLE);
		}
		
		else
		{
			reset(my,INVISIBLE);
			
		}
		
		wait(1); 
	} 
	
	}


function place_trees()
{

}

function weaving_grass()
{
	var grass_angles;
	var grass_speed;
	grass_speed = 2 + random(5);
	while (1)
	{
		grass_angles += grass_speed * time_step; // allow the grass to weave
		my.roll += 0.02 * sin(grass_angles);
		wait (1);
	}
}
