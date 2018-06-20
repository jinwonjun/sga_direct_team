//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// ShadowMapping
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// ApplyShadow
//--------------------------------------------------------------//
string ShadowMapping_ApplyShadow_Model : ModelData = "..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Torus.3ds";

float4x4 gWorldMatrix : World;
float4x4 gLightViewMatrix
<
   string UIName = "gLightViewMatrix";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
> = float4x4( 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00, 0.00, 0.00, 0.00, 0.00, 1.00 );
float4x4 gLightProjMatrix : Projection;

float4x4 gViewProjMatrix : ViewProjection;

float4 gWorldLightPos
<
   string UIName = "gWorldLightPos";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 500.00, 500.00, -500.00, 1.00 );

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float3 Normal : NORMAL;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float4 ClipPosition : TEXCOORD1;
   float Diffuse : TEXCOORD2;
};

VS_OUTPUT ShadowMapping_ApplyShadow_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   
   float4 worldPos = mul( Input.Position, gWorldMatrix);
   Output.Position = mul(worldPos, gViewProjMatrix);
    
   Output.ClipPosition = mul(worldPos, gLightViewMatrix);
   Output.ClipPosition = mul( Output.ClipPosition, gLightProjMatrix);
   
   float3 lightDir = normalize(worldPos.xyz - gWorldLightPos.xyz);
   float3 worldNormal = normalize(
      mul(Input.Normal, (float3x3)gWorldMatrix));
   
   Output.Diffuse = dot(-lightDir, worldNormal);
   
   return( Output );
   
}




texture ShadowMap_Tex
<
   string ResourceName = ".\\";
>;
sampler2D ShadowSampler = sampler_state
{
   Texture = (ShadowMap_Tex);
};
float4 gColor
<
   string UIName = "gColor";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 1.00, 0.00, 0.00, 1.00 );

struct PS_INPUT 
{
   float4 ClipPosition : TEXCOORD1;
   float Diffuse : TEXCOORD2;
};

float4 ShadowMapping_ApplyShadow_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{   
   float3 rgb = saturate(Input.Diffuse) * gColor;
   
   float currentDepth = Input.ClipPosition.z / Input.ClipPosition.w;
   float2 uv = Input.ClipPosition.xy / Input.ClipPosition.w;
   uv.y = -uv.y;
   uv = uv * 0.5 + 0.5;
   
   float shadowDepth = tex2D(ShadowSampler, uv).r;
   
   if ( currentDepth > shadowDepth + 0.0000125f )
   {
      rgb *= 0.5f;
   }
   return( float4( rgb, 1 ) );
}




//--------------------------------------------------------------//
// Technique Section for ShadowMapping
//--------------------------------------------------------------//
technique ShadowMapping
{
   pass ApplyShadow
   {
      VertexShader = compile vs_2_0 ShadowMapping_ApplyShadow_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 ShadowMapping_ApplyShadow_Pixel_Shader_ps_main();
   }

}

