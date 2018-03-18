
cbuffer global
{
	matrix W;//���[���h�s��
	matrix WVP; //���[���h����ˉe�܂ł̕ϊ��s��
	float4 LightDir;  //���C�g�̕����x�N�g��
	float4 Ambient = float4(0, 0, 0, 0);//�A���r�G���g��
	float4 Diffuse = float4(1, 0, 0, 0); //�g�U����(�F�j
	float4 Specular = float4(1, 1, 1, 1);//���ʔ���
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