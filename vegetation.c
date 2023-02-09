//section:Variable (Rihgt click for help)
//title:Global
//entry:Maximum Entities
//var max_entities=20000;
//entry:Terrain Chunk
terrain_chunk = 0;
//title:Internal
//entry:Tree&Tree2&Tree3 Number
//Help:If (Unit==300){Tree1=300,Tree2=300,Tree3=300}Total 900 Trees entities
var tree_number=200.0;//500//100
//entry:Rock Number
var rock_number=750.0;//1000
//entry:Bush1 Number
var bush_number=1000.0;//2000//100
//entry:Bush2 + Bush3 Number 
//Help:If (bush 2 number==500){bush3 number=500}Total 1000 entities
var bush2_number=500.0;//500
//entry:Distance
//Help:Vegetation Entities Visible Distance
var distance=lvl2dist;
////entry:Invisible Randomize
////Help:Invisible Vegetation Randomize. If <10 low performance
var invisible_randomize=10;
//entry:Ray Distance
var ray_distance=(lvl2dist/2); 
//entry:Ray Number
var ray_number=2000;//2000
var pages_number=12.0;
var pages;
var time;
var mmhandle;
VECTOR temp;
//section:Models
//title:Entities
//entry:Tree1 model
STRING* tree1 = "1bigtree2.mdl";
//entry:Tree2 model
STRING* tree2 = "1pinetree.mdl";
//entry:Tree3 model
STRING* tree3 = "1Tree5.mdl";

//entry:Rock model
STRING* rock1 = "kaya2.mdl";
//entry:Bush1 model
STRING* bush1 = "bush7.mdl";
//entry:Bush2 model
STRING* bush2 = "bush3.mdl";
//entry:Bush3 model
STRING* bush3 = "weed24.mdl";//weed24
//entry:Ray model
STRING* ray = "rays1.mdl";
function pages_load();
function ray_func();
function rock_load();
function bush_load();
function bush2_load();
function bushsn_load();
function bush2_func();
function mtl_vegetation_init()  //Hillen's code (outdoor demo)
{
	vec_set(mtl.emissive_blue,mat_model.emissive_blue);
	vec_set(mtl.ambient_blue,mat_model.ambient_blue);
	vec_set(mtl.diffuse_blue,mat_model.diffuse_blue);
	vec_set(mtl.specular_blue,mat_model.specular_blue);
	mtl.power=mat_model.power;
	mtl.albedo=mat_model.albedo;

}

MATERIAL* mtl_vegetation = //Hillen's code (outdoor demo)
{
	event=mtl_vegetation_init; 
	effect=
	"
	texture entSkin1;
	

	technique vegetation
	{
		pass p0
		{
			Texture[0]=<entSkin1>;
			ZWriteEnable=True;
			AlphaBlendEnable=True;
			AlphaTestEnable=True;
			AlphaRef=100;
			AlphaFunc=Greater;
			CullMode=None; // CCW or None

			ColorArg1[0]=Texture;
			ColorOp[1]=Add;
			ColorArg2[0]=Diffuse;
		}
	}
technique fallback{pass p0{}}
	";
}

function listva()
{
	set(my,OVERLAY);
	set(my,PASSABLE);
	set(my,FLAG2);
		while(gmover==0) 
	{ 

		if(vec_dist(camera.x,my.x)>distance&&my.skill9<7)
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

function rock_func()
{
//	set(my,UNLIT);
	set(my,PASSABLE);
	//my.shadow=on;
	//poligon(me);
	set(my,FLAG2);
	
	my.pan=random(360);
	my.skill9=random(invisible_randomize);
	var lv_speed = 12; // not_me's code(fake wind)
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
	var gg=0;
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;

		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS) + 3; 
		

		if(trace_hit)
		{
			my.z=my.z-5;
			gg=11;
		}
		wait(1);
	}

	while(gmover==0) 
	{ 

		if(my.skill9<8)
		{
			lv_sin=0;
			my.tilt=0;
		}
		if(vec_dist(camera.x,my.x)>distance&&my.skill9<7)
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


function tree_func1()
{
//	set(my,UNLIT);
	set(my,PASSABLE);

	
	//Section Tree
	//enable:Tree Material?(low performance)
	//my.material=mtl_vegetation;
	
	my.pan=random(360);
	my.skill9=random(invisible_randomize);
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
	
	
	var gg=0;
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;

		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS)+ 3; 
		

		if(trace_hit)
		{
			my.z=my.z-5;
			gg=11;
		}
		wait(1);
	}
ent_create ("2bigtree2.mdl", vector(my.x,my.y,my.z), listva); 
	//	
	//section:Ray
	//enable:Create ray?(Randomize10/1)
	if(random(1) > 0.9){ent_create(ray, vector(my.x,	my.y,my.z+8300), ray_func);}
	
	//image:help2.bmp
	
	while(gmover==0) 
	{ 

	
		if(vec_dist(camera.x,my.x)>distance&&my.skill9<7)
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





function tree_func2()
{
//	set(my,UNLIT);
	set(my,PASSABLE);
	
	
	//Section Tree
	//enable:Tree Material?(low performance)
	//my.material=mtl_vegetation;
	
	my.pan=random(360);
	my.skill9=random(invisible_randomize);
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
	
	
	var gg=0;
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;

		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS)+ 3; 
		

		if(trace_hit)
		{
			my.z=my.z-5;
			gg=11;
		}
		wait(1);
	}

	//	
	//section:Ray
	//enable:Create ray?(Randomize10/1)
	if(random(1) > 0.9){ent_create(ray, vector(my.x,	my.y,my.z+8300), ray_func);}
	
	//image:help2.bmp
	ent_create ("2pinetree.mdl", vector(my.x,my.y,my.z), listva); 
	while(gmover==0) 
	{ 

		if(vec_dist(camera.x,my.x)>distance&&my.skill9<7)
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

function tree_func3()
{
//	set(my,UNLIT);
	set(my,PASSABLE);
	
	
	//Section Tree
	//enable:Tree Material?(low performance)
	//my.material=mtl_vegetation;
	
	my.pan=random(360);
	my.skill9=random(invisible_randomize);
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

	
	var gg=0;
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;

		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS)+ 3; 
		

		if(trace_hit)
		{
			my.z=my.z-5;
			gg=11;
		}
		wait(1);
	}

	//	
	//section:Ray
	//enable:Create ray?(Randomize10/1)
	if(random(1) > 0.9){ent_create(ray, vector(my.x,	my.y,my.z+8300), ray_func);}
	
	//image:help2.bmp
		ent_create ("2Tree5.mdl", vector(my.x,my.y,my.z), listva); 
	while(gmover==0) 
	{ 

		if(vec_dist(camera.x,my.x)>distance&&my.skill9<7)
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

action fire_page()
{
	
	my.material = sc_mtl_obj_heatHaze;
   sc_skill(my, sc_myTexMov, 3);

   var temp[3];

   while(1)
   {
      //behave like a sprite -> face camera
      vec_set(temp,camera.x); 
      vec_sub(temp,my.x);
      vec_to_angle(my.pan,temp); 
      wait(1);
	if (vec_dist(player.x, my.x) < 250)
	{
	if(key_pressed(280))
{my.z=my.z-1000; wait(1);break; }
      
   }
	
}
}

action page()
{
		var gg=0;
		
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;
	
		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS) + 3; 
		

		if(trace_hit)
		{
			my.z=my.z-5;
			gg=11;
		}
		wait(1);
	}
	my.z=my.z+60;
 ent_create ("fire.mdl", vector(my.x,my.y,my.z), fire_page); 
	while (1){


		wait(1);
	if (vec_dist(player.x, my.x) < 250)
	{
	if(key_pressed(280))
	{	
	addsobel();
	show_pages();
		media_play("BOOKPAG2.wav",NULL,30);pages=pages+1; time=time+60; my.z=my.z-1000; wait(1);
if(pages==1){var mmhandle = media_loop("slender 1.mp3",NULL,100);}
if(pages==3){media_stop(mmhandle);var mmhandle = media_loop("slender 2.mp3",NULL,100);}
if(pages==5){media_stop(mmhandle);var mmhandle = media_loop("slender 3.mp3",NULL,100);}
if(pages==7){media_stop(mmhandle);var mmhandle = media_loop("slender 4.mp3",NULL,100);}
if(pages==9){media_stop(mmhandle);var mmhandle = media_loop("slender 5.mp3",NULL,100);}
if(pages==11){media_stop(mmhandle);var mmhandle = media_loop("slender 6.mp3",NULL,100);}

		break; 
}
}
}
}

function bush_func()
{
//	set(my,UNLIT);
	set(my,PASSABLE);
	set(my,OVERLAY);
	set(my,FLAG2);
	//section:Bush1
	//enable:Bush1 Material?(low performance)
	//my.material=mtl_vegetation;
	
	my.pan=random(360);
	my.skill9=random(invisible_randomize);
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
	var gg=0;
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;
	
		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS) + 3; 
		

		if(trace_hit)
		{
			my.z=my.z-5;
			gg=11;
		}
		wait(1);
	}
	
	while(gmover==0) 
	{ 

		lv_sin=(lv_sin+time_step*lv_speed)%360;
		my.tilt=sin(lv_sin)*lv_power;
		
		if(my.skill9<8)
		{
			lv_sin=0;
			my.tilt=0;
		}
		if(vec_dist(camera.x,my.x)>distance&&my.skill9<7)
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
var number_tree=0;
BMAP* tex1 = "rock.bmp"; 		// Texture Layer Red
BMAP* tex4 = "road.bmp"; 		// Texture Layer Green
BMAP* tex5 = "sand.bmp"; 		// Texture Layer Blue
BMAP* tex6 = "detailmap.tga"; 	// DetailMap
function multirgb_roughness() 
{	
	bmap_to_mipmap(mtl.skin1);
	bmap_to_mipmap(mtl.skin2);
	bmap_to_mipmap(mtl.skin3);
	bmap_to_mipmap(mtl.skin4);
	
}
MATERIAL* multirgb =//LOOPIX's Terrain Material
{
	flags = tangent;
	skin1 = tex1;
	skin2 = tex4;
	skin3 = tex5;
	skin4 = tex6;
	
	event=multirgb_roughness;
	
	effect
	"
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Define your needed values
	float4x4 matWorldViewProj;	 
	float4x4 matWorld;	
	float4x4 matWorldInv;	
	float4x4 matWorldView;
	
	float4 vecSunDir;
	float4 vecSunDiffuse = float4(255.f/255.f, 255.f/255.f, 255.f/255.f, 1.f);
	float4 vecLight;
	float4 vecLightPos[8];	 // preset this with light positions (xyz) and ranges (w)
	float4 vecLightColor[8]; // preset this with light colors
	float3 vecFalloff = float3(0.f, 0.f, 1.5f);
	
	float4 vecFog;
	
	// Define your textures
	texture mtlSkin1;					
	texture mtlSkin2;					
	texture mtlSkin3;					
	texture mtlSkin4;					
	texture entSkin1;					
	texture entSkin2;
	texture entSkin3; //entSkin3 contains the shadowmap
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Texture settings
	sampler sTex1 = sampler_state			
	{
		Texture = <entSkin2>;   // RGB Mask
		MipFilter = Linear;
		MinFilter = Linear;
		MagFilter = Linear;
		AddressU = Wrap;	
		AddressV = Wrap;
	};
	sampler sTex2 = sampler_state			
	{
		Texture = <entSkin1>;   // Texture Base
		MipFilter = Linear;
		MinFilter = Linear;
		MagFilter = Linear;
		AddressU = Wrap;	
		AddressV = Wrap;
	};
	sampler sTex3 = sampler_state			
	{
		Texture = <mtlSkin1>;	// Texture Layer Red
		MipFilter = Linear;
		MinFilter = Linear;
		MagFilter = Linear;
		AddressU = Wrap;	
		AddressV = Wrap;
	};
	sampler sTex4 = sampler_state			
	{
		Texture = <mtlSkin2>;	// Texture Layer Green
		MipFilter = Linear;
		MinFilter = Linear;
		MagFilter = Linear;
		AddressU = Wrap;	
		AddressV = Wrap;
	};
	sampler sTex5 = sampler_state			
	{
		Texture = <mtlSkin3>;	// Texture Layer Blue
		MipFilter = Linear;
		MinFilter = Linear;
		MagFilter = Linear;
		AddressU = Wrap;	
		AddressV = Wrap;
	};
	sampler sTex6 = sampler_state			
	{
		Texture = <mtlSkin4>;	// Detailmap for Base Texture
		MipFilter = Linear;
		MinFilter = Linear;
		MagFilter = Linear;
		AddressU = Wrap;	
		AddressV = Wrap;
	};
	
	sampler shadowMap= sampler_state
	{
		Texture = <entSkin3>; // Shadowmap
		MipFilter = Linear;
		MinFilter = Linear;
		MagFilter = Linear;
		AddressU = Wrap;
		AddressV = Wrap;
	};
	
	struct TMULTI_VS_OUT // Output to the pixelshader fragment
	{
		float4 Pos 		: POSITION;
		float  Fog		: FOG;
		float4 Color		: COLOR0; 
		float2 Tex1 	: TEXCOORD0;
		float2 Tex2 	: TEXCOORD1;
		float2 Tex3 	: TEXCOORD2;
		float2 Tex4		: TEXCOORD3;
		float2 Tex5		: TEXCOORD5;
		float2 Tex6		: TEXCOORD6;
	};
	
	
	
	
	float DoFog(float4 Pos)	{
		float3 P = mul(Pos,matWorldView);// apply the linear fog formula   		
		return saturate((vecFog.y-P.z) * vecFog.z);	
	}
	
	
	TMULTI_VS_OUT TMulti_VS(
	float4 inPos : POSITION,
	float3 inNormal : NORMAL,
	float2 inTexCoord0 : TEXCOORD0)
	{
		
		TMULTI_VS_OUT Out;
		
		// transform the vector position to screen coordinates
		Out.Pos = mul(inPos,matWorldViewProj);
		
		// rotate and normalize the normal
		float3 N = normalize(mul(inNormal,matWorldInv));
		
		// Add sun light
		float3 objSunDir = normalize(mul(-vecSunDir.xyz, matWorldInv));
		float  sunDiff   = max(dot(inNormal, objSunDir), 0);
		Out.Color        = float4(vecSunDiffuse.rgb * sunDiff, 1);
		
		// Add point lights
		for(int i = 0; i <= 5; i++)
		{
			// Diffuse lighting
			float4 objLightPos  = mul(float4(vecLightPos[i].xyz, 1), matWorldInv);
			float4 objLightDir  = objLightPos - inPos;
			float4 objLightDirN = normalize(objLightDir);
			float  diffLight    = max(dot(objLightDirN, inNormal), 0);
			
			// Calculate attenuation factor
			float falloffFactor = 0;
			if(vecLightPos[i].w > 0)
			{
				float linearDistance = length(objLightDir)/vecLightPos[i].w;
				if(linearDistance < 1) falloffFactor = 1 - linearDistance;
			}
			diffLight *= falloffFactor;
			
			// Add to final result
			Out.Color.rgb  += vecLightColor[i].rgb * diffLight;
		}

		
		Out.Fog = DoFog(inPos);
		
		// scale the texture coordinates for the masked textures
		Out.Tex1  = inTexCoord0.xy;		// Tile Mask
		Out.Tex2  = inTexCoord0.xy;		// Tile Base Texture
		Out.Tex3  = inTexCoord0.xy*30;	// Tile Texture Layer Red (rock)
		Out.Tex4  = inTexCoord0.xy*100;	// Tile Texture Layer Green (road)
		Out.Tex5  = inTexCoord0.xy*180;	// Tile Texture Layer detailmap
		Out.Tex6  = inTexCoord0.xy*80;	// Tile Texture Layer blue (sand)
		return Out;
	}
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// pixelshader
	float4 ps( TMULTI_VS_OUT In ) : COLOR
	{
		float4 MaskColor = tex2D(sTex1,In.Tex1);
		float4 BaseColor = tex2D(sTex2,In.Tex2);
		float4 RedColor = tex2D(sTex3,In.Tex3);
		float4 GreenColor = tex2D(sTex4,In.Tex4);
		float4 BlueColor = tex2D(sTex5,In.Tex5);
		float4 DetailColor = tex2D(sTex6,In.Tex5);
		
		BaseColor = BaseColor + DetailColor - 0.5;//0.5
		
		float4 BaseRed = lerp(BaseColor,RedColor,MaskColor.r);
		float4 BaseGreen = lerp(BaseRed,GreenColor,MaskColor.g);
		float4 FinalColor = lerp(BaseGreen,BlueColor,MaskColor.b);
		FinalColor *=(In.Color-0.90);//*3;
		
		float4 shadow = tex2D(shadowMap,In.Tex1);
		FinalColor = FinalColor*shadow; // maybe you will want to have it brighter ...*(shadow+0.2)	
		
		FinalColor.a = 1.0f; // prevent transparency
		
		return FinalColor;
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	technique mytechnique
	{
		// Define your passes
		pass p0
		{				
			VertexShader = compile vs_2_0 TMulti_VS();
			PixelShader = compile ps_2_0 ps();
		}
	}
	";
}
action Terrain()
{
	
	my.material=multirgb;
//	set(my,UNLIT);
	//section:Terrain Coordinate

		my.min_x=-4081;//5295//4081
	//entry:Maximum x
	my.max_x=3041;//4566//3041
	//entry:Minimum y
	my.min_y=4053;//5200//4053
	//entry:Maximum y
	my.max_y=-3300;//4500//3300
	//image:help.bmp
	rock_load();
	bush_load();
	bush2_load();
	pages_load();
	while(number_tree<tree_number)
	{
		ent_create(tree1, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), tree_func1);
		ent_create(tree2, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), tree_func2);
		ent_create(tree3, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), tree_func3);
		number_tree+=1;
		//	wait(1);
		
	}
	
}

action Terrain3()
{
	
//	my.material=multirgb;
//	set(my,UNLIT);
	//section:Terrain Coordinate

		my.min_x=-5573;//5295//4081
	//entry:Maximum x
	my.max_x=5173;//4566//3041
	//entry:Minimum y
	my.min_y=4900;//5200//4053
	//entry:Maximum y
	my.max_y=-4900;//4500//3300
	//image:help.bmp
//	rock_load();
//	bush_load();
	bushsn_load();
//	pages_load();

	
}


var number_rock=0;
function rock_load()
{

	while(number_rock<rock_number)
	{
		ent_create(rock1, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), rock_func);
		number_rock+=1;
		//	wait(1);
		
	}
	
}
var number_pages=0;
function pages_load()
{
random_seed(0); 
	while(number_pages<pages_number)
	{
		ent_create("earth.mdl", vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), page);
		number_pages+=1;
		//	wait(1);
		
	}
	
}


var number_bush=0;
function bush_load()
{

	while(number_bush<bush_number)
	{
		ent_create(bush1, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), bush_func);
		number_bush+=1;
		//	wait(1);
		
	}
	
}

function bushsn_load()
{

	while(number_bush<666)
	{
		ent_create("bush4.mdl", vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+1000), bush_func);
		number_bush+=1;
		//	wait(1);
		
	}
	
}

function bush2_func()
{
//	set(my,UNLIT);
	//section:Bush2&3
	//enable:Bush2-3 Material?(low performance)
	//my.material=mtl_vegetation;
		set(my,FLAG2);
		

	set(my,PASSABLE);
	my.pan=random(360);
	my.skill9=random(invisible_randomize);
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
	var gg=0;
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;
	
		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS) + 3; 
		

		if(trace_hit)
		{
			my.z=my.z-5;
			gg=11;
		}
		wait(1);
	}
	
	while(gmover==0) 
	{ 

		lv_sin=(lv_sin+time_step*lv_speed)%360;
		my.tilt=sin(lv_sin)*lv_power;
		
		if(my.skill9<8)
		{
			lv_sin=0;
			my.tilt=0;
		}
		if(vec_dist(camera.x,my.x)>distance&&my.skill9<7)
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
var number_bush2=0;
function bush2_load()
{

	while(number_bush2<bush2_number)
	{
		ent_create(bush2, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), bush2_func);
		ent_create(bush3, vector(my.min_x + random(my.max_x - my.min_x),	my.min_y + random(my.max_y - my.min_y),my.z+8300), bush2_func);
		number_bush2+=1;
		//	wait(1);
		
	}
	
}


FONT* digit_font = "Arial#13";

PANEL* info_panel =
{
	red = 75; 
	green = 128; 
	blue = 223; 
	layer=20;
	digits(10,10,"INFO PANEL",digit_font,1,0);
	digits(10,20,"--------------------------------------------",digit_font,1,0);
	digits(10,30,"Shader Version: %.1f ",digit_font,1,d3d_shaderversion);
	digits(10,50,"D3D TexFree: %.1f ",digit_font,1,d3d_texfree);
	digits(10,60,"D3D AntiAlias: %.1f ",digit_font,1,d3d_antialias);
	digits(10,70,"D3D Anisotropy: %.1f ",digit_font,1,d3d_anisotropy);
	digits(10,80,"D3D Caps: %.1f ",digit_font,1,d3d_caps);
	digits(10,90,"D3D VBuffer: %.1f ",digit_font,1,d3d_vbuffersize);
	digits(10,100,"Number Entities: %.1f ",digit_font,1,num_entities);
	digits(10,110,"Number Actions: %.1f ",digit_font,1,num_actions);
	digits(10,120,"Number Particles: %.1f ",digit_font,1,num_particles);
	digits(10,130,"Number Visible Entities: %.1f ",digit_font,1,num_visents);
	digits(10,140,"Number Visible Entities Render Polys: %.1f ",digit_font,1,num_visentpolys);
	digits(10,150,"Number Visible Entities Render Triangles: %.1f ",digit_font,1,num_vistriangles);
	digits(10,160,"Camera X Position: %.1f ",digit_font,1,camera.x);
	digits(10,170,"Camera Y Position: %.1f ",digit_font,1,camera.y);
	digits(10,180,"Camera Z Position: %.1f ",digit_font,1,camera.z);
	digits(10,190,"Camera Pan: %.1f ",digit_font,1,camera.pan);
	digits(10,200,"Camera Tilt: %.1f ",digit_font,1,camera.tilt);
	digits(10,210,"Screen Size X: %.1f ",digit_font,1,screen_size.x);
	digits(10,220,"Screen Size Y: %.1f ",digit_font,1,screen_size.y);
	digits(10,230,"Nexus: %.1f ",digit_font,1,nexus);
	digits(10,240,"time_step Factor: %.1f ",digit_font,1,time_step_factor);
	digits(10,250,"Camera Clip Near: %.1f ",digit_font,1,camera.clip_near);
	digits(10,260,"Camera Clip Far: %.1f ",digit_font,1,camera.clip_far);
	digits(10,270,"D3D Triplebuffer: %.1f ",digit_font,1,d3d_triplebuffer);
	
	//Section:Debug
	//enable:Info Panel
//	flags = visible;
}



function ray_func()
{
	
	set(my,FLAG2);
	set(my,PASSABLE);
	my.pan=random(360);
	set(my,BRIGHT);
	var gg=0;
	while(gg<10)
	{

		vec_set(temp,my.x);
		temp.z -= 10000;
		my.z -= c_trace(my.x, temp.x, IGNORE_ME | IGNORE_PASSABLE | USE_POLYGON | IGNORE_MODELS) + 3; 
		

		if(trace_hit)
		{
			my.z=my.z-5;
			gg=11;
		}
		wait(1);
	}
	
	while(1) 
	{ 

		my.pan+=0.3*time_step;
		if(vec_dist(camera.x,my.x)>ray_distance)
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













