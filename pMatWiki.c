D3DXMATRIX mMatrices[8];// 8 matrices for FFP
function set_mat_pointer (float** mMat,float** pointer) {*pointer = mMat;}
function set_material_matrices ()
{
	set_mat_pointer(mMatrices[0],mat_effect1);
	set_mat_pointer(mMatrices[1],mat_effect2);
	set_mat_pointer(mMatrices[2],mat_effect3);
	set_mat_pointer(mMatrices[3],mat_effect4);
	set_mat_pointer(mMatrices[4],mat_effect5);
}
//1 projected texture + diffuse light
MATERIAL* mtl_pTex1 = {effect = "
float4x4 matEffect1;

texture mtlSkin1;
texture entSkin1;
technique proj_tex
{
	pass p0
	{
		
		Texture[0] = <entSkin1>;
		Texture[1] = <mtlSkin1>; // projected
		
		ColorArg1[0] = Texture;
		ResultArg[0] = Temp;
		
		ColorArg2[1] = Texture;
		ColorArg1[1] = Diffuse;
		ColorOp[1] = AddSigned2x;
		
		ColorArg1[2] = Current;
		ColorArg2[2] = Temp;
		ColorOp[2] = Modulate;
		
		
		TexCoordIndex[0] = 1;
		AddressU[1] = BORDER;
		AddressV[1] = BORDER;
		BorderColor[1] = 0xffffff;  
		
		texcoordindex[1] = cameraspaceposition ; 
		TextureTransformFlags[1] = count3 | projected;
		TextureTransform[1] = <matEffect1>;
		
	}
}";}
//2 projected textures + diffuse light
MATERIAL* mtl_pTex2 = {effect = "
float4x4 matEffect1;
float4x4 matEffect2;

texture mtlSkin1;
texture mtlSkin2;
texture entSkin1;

technique proj_tex
{

	pass p0
	{
		Texture[0] = <entSkin1>;
		Texture[1] = <mtlSkin1>; // projected texture
		Texture[2] = <mtlSkin2>; // projected texture
		
		ColorArg1[0] = Texture;
		ColorArg2[0] = Diffuse;
		ColorOp[0] = Modulate2x;
		ResultArg[0] = Temp;
		
		ColorArg1[1] = Texture;
		ColorOp[1] = SelectArg1;
		
		ColorArg1[2] = Texture;
		ColorArg2[2] = Current;
		ColorOp[2] = Modulate;
		
		ColorArg2[3] = Current;
		ColorArg1[3] = Diffuse;
		ColorOp[3] = AddSigned2x;
		
		ColorArg1[4] = Current;
		ColorArg2[4] = Temp;
		ColorOp[4] = Modulate;
		
		texcoordindex[0] = 1;
		
		AddressU[1] = BORDER;
		AddressV[1] = BORDER;
		BorderColor[1] = 0xffffff;  
		
		texcoordindex[1] = cameraspaceposition ; 
		TextureTransformFlags[1] = count3 | projected;
		TextureTransform[1] = <matEffect1>;
		
		AddressU[2] = BORDER;
		AddressV[2] = BORDER;
		BorderColor[2] = 0xffffff;  
		
		texcoordindex[2] = cameraspaceposition ; 
		TextureTransformFlags[2] = count3 | projected;
		TextureTransform[2] = <matEffect2>;
		
	}
	
}";}
//3 projected textures, 2 shadow 1 light
MATERIAL* mtl_pTex3 = {effect = "
float4x4 matEffect1;
float4x4 matEffect2;
float4x4 matEffect3;

texture mtlSkin1;
texture mtlSkin2;
texture mtlSkin3;
texture entSkin1;
technique proj_tex
{

	pass p0
	{
		Texture[0] = <entSkin1>;
		Texture[1] = <mtlSkin1>; // projected shadow
		Texture[2] = <mtlSkin2>; // projected shadow
		Texture[3] = <mtlSkin3>; // projected spotlight
		
		ColorArg1[0] = Texture;
		ColorArg2[0] = Diffuse;
		ColorOp[0] = Modulate2x;
		ResultArg[0] = Temp;
		
		ColorArg1[1] = Texture;
		ColorOp[1] = SelectArg1;
		
		ColorArg1[2] = Texture;
		ColorArg2[2] = Current;
		ColorOp[2] = Modulate;
		
		ColorArg1[3] = Current;
		ColorArg2[3] = Texture;
		ColorOp[3] = Add;
		
		ColorArg1[4] = Current;
		ColorArg2[4] = Temp;
		ColorOp[4] = Modulate2x;
		
		texcoordindex[0] = 1;
		
		AddressU[1] = BORDER;
		AddressV[1] = BORDER;
		BorderColor[1] = 0xffffff;  
		
		texcoordindex[1] = cameraspaceposition ; 
		TextureTransformFlags[1] = count3 | projected;
		TextureTransform[1] = <matEffect1>;
		
		AddressU[2] = BORDER;
		AddressV[2] = BORDER;
		BorderColor[2] = 0xffffff;  
		
		texcoordindex[2] = cameraspaceposition ; 
		TextureTransformFlags[2] = count3 | projected;
		TextureTransform[2] = <matEffect2>;
		
		AddressU[3] = BORDER;
		AddressV[3] = BORDER;
		BorderColor[3] = 0x000001;  
		
		texcoordindex[3] = cameraspaceposition ; 
		TextureTransformFlags[3] = count3 | projected;
		TextureTransform[3] = <matEffect3>;
		
	}
}";}


// material using for creating shadow
MATERIAL* mtl_black = {effect = "texture entSkin1;

technique black
{
	pass p0
	{
		AlphaBlendEnable=True;  
		Zenable = True;
		ZwriteEnable = True;
		BlendOp=Add;
		Lighting=False;
		
		FogEnable = True;
		FogColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
		FogStart = 60000;
		FogEnd = 50000;
		
		
		ShadeMode = Flat;
		Texture[0] = <entSkin1>;
		ColorArg1[0] = Diffuse;
		ColorOp[0] = SelectArg1;
	}
}
";}


