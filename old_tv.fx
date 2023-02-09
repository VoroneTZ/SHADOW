//oldtv

const float4 vecSkill1; 
const float4 vecTime;

const float distortionFreq = 0.07f;
const float distortionScale = 0.01f;
const float distortionRoll = 0.009f;
const float interference = 0.5f;
const float frameLimit = 0.50f;
const float frameShape = 0.26f;
const float frameSharpness = 6.0f;

texture TargetMap;
texture mtlSkin1;
texture mtlSkin2;

sampler postTex = sampler_state
{
	texture = <TargetMap>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;  
	AddressU = Clamp;
	AddressV = Clamp;
};

sampler bumpTex = sampler_state
{
	texture = <mtlSkin1>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;  
	AddressU = Wrap;
	AddressV = Wrap;
};

sampler bumpTex2 = sampler_state
{
	texture = <mtlSkin2>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;  
	AddressU = Wrap;
	AddressV = Wrap;
};


float4 main_fp(float2 TexCoords: TEXCOORD0) : COLOR
{
	float2 TransCoords = TexCoords * 2.0 - 1.0;
	
	// Define a frame shape
	float f = (1 - TransCoords.x * TransCoords.x) * (1 - TransCoords.y * TransCoords.y);
	float frame = saturate(frameSharpness * (pow(f, frameShape) - frameLimit));

	// Interference ... just a texture filled with rand()
	float rand = tex3D(bumpTex, float3(1.5 * TransCoords+vecTime.w, vecTime.w)) - 0.2;

	// Some signed noise for the distortion effect
	float noisy = tex3D(bumpTex2, float3(0, 0.5 * TransCoords.y, 0.1 * vecTime.w)) - 0.5;

	// Repeat a 1 - x^2 (0 < x < 1) curve and roll it with sinus.
	float dst = frac(TransCoords.y * distortionFreq + distortionRoll * vecTime.w);
	dst *= (1 - dst);

	// Make sure distortion is highest in the center of the image
	dst /= 1 + distortionScale * abs(TransCoords.y);

	// ... and finally distort
	TexCoords.x += distortionScale * noisy * dst;
	float4 image = tex2D(postTex, TexCoords);

	// Combine frame, distorted image and interference
	float4 Color = frame * (interference * rand + image);
	Color.a = 1.0;
	
	return Color;
}

technique tech_00
{
	pass p0
	{
		PixelShader = compile ps_2_0 main_fp();
	}
}