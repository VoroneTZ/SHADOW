typedef struct 
{
	// useful struct for storing position and angle of projection texture
	VECTOR Pos; 
	VECTOR Ang;
	var Fov; 
	VECTOR ePos;
	VECTOR eAng;
} PSystem;
PSystem pSys[8];
var debug_pMatrix = 1; // if == 1 debug projection matrix

function debug_projection (VECTOR* pPos,VECTOR* pAng,var fov,var dist,VECTOR* col)
{
	VECTOR dpos;
	VECTOR aang;
	vec_set(dpos,vector(dist,0,0));
	vec_rotate (dpos,pAng);vec_add(dpos,pPos);vec_rotate (aang,pAng);vec_add(aang,pPos);
	draw_line3d(dpos,NULL,100);
	draw_line3d(pPos,vector(0,255,0),100);
	
	aang.x = fov/2;aang.y = fov/(2+(fov*fov/15000));
	vec_set(dpos,vector(dist,0,0));vec_rotate(dpos,vector(aang.x,aang.y,0));
	vec_rotate(dpos,pAng);vec_add(dpos,pPos);
	draw_line3d(pPos,NULL,100);
	draw_line3d(pPos,col,100);
	draw_line3d(dpos,col,100);
	
	vec_set(dpos,vector(dist,0,0));vec_rotate (dpos,vector(-aang.x,aang.y,0));
	vec_rotate (dpos,pAng);vec_add(dpos,pPos);
	draw_line3d(pPos,NULL,100);
	draw_line3d(dpos,col,100);
	
	vec_set(dpos,vector(dist,0,0));vec_rotate (dpos,vector(aang.x,-aang.y,0));
	vec_rotate (dpos,pAng);vec_add(dpos,pPos);
	draw_line3d(pPos,NULL,100);
	draw_line3d(dpos,col,100);
	
	vec_set(dpos,vector(dist,0,0));vec_rotate (dpos,vector(-aang.x,-aang.y,0));
	vec_rotate (dpos,pAng);vec_add(dpos,pPos);
	draw_line3d(pPos,NULL,100);
	draw_line3d(dpos,col,100);
}

function create_dxmat(D3DXMATRIX* mMain,VECTOR* Ppos,VECTOR* pAng,var fov,BMAP* projBmap)
{
	//create DX projection matrix for camera from given parametrs 
	D3DXMATRIX mAng,mPos,mCAng,mProj;
	D3DXMATRIX mRX,mRY,mRZ;
	float posProj[3];
	float aCam[3];
	float aSelf[3];
	proc_mode = PROC_LATE;
	float fTexAdj[16] =
		{ 0.5, 0.0, 0.0, 0.0,
		  0.0,-0.5,	0.0, 0.0,
		  0.0, 0.0, 1.0, 0.0,
		  0.0, 0.0, 0.0, 1.0 };
	if (projBmap) {
		fTexAdj[12] = 0.5 + (0.5/(float)bmap_width(projBmap));
		fTexAdj[13] = 0.5 + (0.5/(float)bmap_width(projBmap));
	}	

	posProj[0] = -camera.y+Ppos.y;posProj[1] = camera.z-Ppos.z;posProj[2] = camera.x-Ppos.x;
	aCam[0] = -camera.pan*D3DX_PI/180;
	aCam[1] = -camera.tilt*D3DX_PI/180;
	aCam[2] = -camera.roll*D3DX_PI/180;
	aSelf[0] = pAng.x*D3DX_PI/180;
	aSelf[1] = pAng.y*D3DX_PI/180;
	aSelf[2] = pAng.z*D3DX_PI/180;

	//D3DXMatrixOrthoOffCenterLH (mProj,-fov,fov,-fov,fov,0,1);////only for isometric projection count4
	D3DXMatrixPerspectiveFovLH (mProj,fov*D3DX_PI/180,1,0,1); //only for perspective projection count3 
	D3DXMatrixTranslation(mPos,posProj[0],posProj[1],posProj[2]);
	D3DXMatrixRotationYawPitchRoll(mCAng ,aCam[0],aCam[1],aCam[2]);

	D3DXMatrixRotationX(mRX,aSelf[1]);
	D3DXMatrixRotationY(mRY,aSelf[0]);
	D3DXMatrixRotationZ(mRZ,aSelf[2]);
	D3DXMatrixMultiply(mAng,mRY,mRX);
	D3DXMatrixMultiply(mAng,mAng,mRZ);
	//D3DXMatrixRotationYawPitchRoll(mAng ,aSelf[0],aSelf[1],aSelf[2]); //dont work for Eulen angles
	D3DXMatrixMultiply(mProj,mProj,fTexAdj);
	D3DXMatrixMultiply(mProj,mAng,mProj);
	D3DXMatrixMultiply(mProj,mPos,mProj);
	D3DXMatrixMultiply(mMain,mCAng,mProj);
	
	if (debug_pMatrix)
	{
		debug_projection(Ppos,pAng,fov,10000,vector(255,0,0));
		debug_projection(Ppos,pAng,fov,-10000,vector(0,0,255));
	}
}

function debug_pMatrix_switch () {debug_pMatrix = !debug_pMatrix;} //enable,disable 

function proj_fromFile (STRING* name,VECTOR* pos,VECTOR* aang,var* fov,BMAP** pShadow)
{
	//function load projection texture and parametrs from disk
	//load projection texture from name+.png
	//set pos,aang,fov from name+.txt
	STRING* fname = "#20";
	var file_handle ;
	BMAP* bLoad = "#128x128x24";
	str_cpy(fname,name);str_cat(fname,".png");bmap_load(bLoad,fname,1);*pShadow = bLoad;
	str_cpy(fname,name);str_cat(fname,".txt");
	file_handle = file_open_read (fname);
	pos.x = file_var_read(file_handle);pos.y = file_var_read(file_handle);
	pos.z = file_var_read(file_handle);
	aang.x = file_var_read(file_handle);aang.y = file_var_read(file_handle);
	aang.z = file_var_read(file_handle);
	*fov = file_var_read(file_handle);
	
	file_close (file_handle);
}