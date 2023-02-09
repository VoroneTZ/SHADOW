/*******************************************************************************************************************
VARIABLES
*******************************************************************************************************************/

//sets the waterdepth
var sc_waterDepth = 5;

//turn water on/off
var sc_bWater = 1;

// DON'T CHANGE ANYTHING BELOW THIS LINE ---------------------------------------------------------------------------

/*******************************************************************************************************************
BITMAPS
*******************************************************************************************************************/

BMAP* sc_bmap_waterFresnel = "sc_waterFresnel.bmp";

/*******************************************************************************************************************
MATERIAL-EVENTS
*******************************************************************************************************************/

void sc_mtlEvent_water()
{
	mtl.skill1 = floatv(-1.0);
	if(render_view == camera)
	{
		mtl.skill1 = floatv(1.0);
	}
	
}

/*******************************************************************************************************************
MATERIALS
*******************************************************************************************************************/

MATERIAL* sc_mtl_water =
{
	skin4 = sc_bmap_waterFresnel;
	flags = ENABLE_RENDER | TANGENT;
	effect = "sc_water.fx";
	event = sc_mtlEvent_water;
}


