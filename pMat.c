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
MATERIAL* mtl_pTex1 = {effect = "projT1.fx";}
//2 projected textures + diffuse light
MATERIAL* mtl_pTex2 = {effect = "projT2.fx";}
//3 projected textures 
MATERIAL* mtl_pTex3 = {effect = "projT3.fx";}

MATERIAL* mtl_black = {effect = "blackTex.fx";}


