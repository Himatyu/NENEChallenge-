
cbuffer global
{
	matrix W;//ワールド行列
	matrix WVP; //ワールドから射影までの変換行列
	float4 LightDir;  //ライトの方向ベクトル
	float4 Ambient = float4(0, 0, 0, 0);//アンビエント光
	float4 Diffuse = float4(1, 0, 0, 0); //拡散反射(色）
	float4 Specular = float4(1, 1, 1, 1);//鏡面反射
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Normal : NORMAL;
	float4 Light : TEXCOORD0;
};

VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL)
{
	VS_OUTPUT vo;
	vo.Pos = mul(Pos, WVP);
	vo.Normal = mul(Normal, W);
	vo.Light = LightDir;
	return vo;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 Normal = normalize(input.Normal);
	float4 Light = normalize(input.Light);
	float4 Lambert = saturate(dot(Normal, Light));
	return Diffuse *Lambert;
}