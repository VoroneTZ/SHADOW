/////////////////////////////////fog.c/////////////////////////////////
//
//Generated by Parted by Martin Coumont (redphoenix)
//
//LiteC Script file from 28.04.2013 ; 11:33:35:
//
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////header/////////////////////////////////

#ifndef PARTED_VECTOR_DEF
 #define PARTED_VECTOR_DEF
 VECTOR* parted_temp_vec = { x=0;y=0;z=0; }
 VECTOR* parted_temp2_vec = { x=0;y=0;z=0; }
 ANGLE* parted_temp_ang = { pan=0;tilt=0;roll=0; }
#endif

#ifndef dust1_DEF
 #define dust1_DEF
   BMAP* dust1_map = "dust1.tga";
#endif
/////////////////////////////////particle code/////////////////////////////////

function Base_Effect_base_event(PARTICLE* p) {
   if((p.x-camera.x)*cos(camera.pan) + (p.y-camera.y)*sin(camera.pan) + (p.z-camera.z)*sin(camera.tilt) < 0)p.lifespan = 200;
   p.skill_d = (p.skill_d + time_step*(var)1.800)%100;
}

function Base_Effect_base(PARTICLE* p) {
   p.size = random(168.174)+(1.826);
   p.alpha = random(0.619)+(1.381);
   p.red = 53;
   p.green = 80;
   p.blue = 106;
   p.skill_c = 0.5;
   parted_temp_vec.x = random(191.406)+208.594;
   parted_temp_vec.y = random(600.000)+-300.000;
   parted_temp_vec.z = random(0.000)+0.000;
   vec_rotate(parted_temp_vec,camera.pan);
   vec_add(p.x,parted_temp_vec);
   p.vel_x = random(0.799)+(-0.399);
   p.vel_y = random(0.799)+(-0.399);
   p.vel_z = random(2.000)+(-1.000);
   p.lifespan = random(119.922)+80.078;
   p.gravity = 0.000;
   p.bmap = dust1_map;
   p.flags = BRIGHT | STREAK | TRANSLUCENT | MOVE;
   p.skill_x = p.vel_x;
   p.skill_y = p.vel_y;
   p.skill_z = p.vel_z;
   p.event = Base_Effect_base_event;
}

/////////////////////////////////emitter actions/////////////////////////////////

action For_Effect_emitter() {
   var eff_frac; eff_frac = 0;
wait(1);
   while(my) {
      vec_set(parted_temp_vec,nullvector);
      vec_add(parted_temp_vec,camera.x);
         eff_frac += 0.100*time_step*6.25;
         if(eff_frac >= 1){
            effect(Base_Effect_base,integer(eff_frac),parted_temp_vec,nullvector);
             eff_frac -= integer(eff_frac);
         }
      wait(1);
   }
}
/////////////////////////////////creation/////////////////////////////////

function fog_create(VECTOR* position) {
   if(!position)position = nullvector;
   wait(3);
   you = ent_create(NULL,position,Base_Effect_emitter);
   if(you) {
      vec_add(you.x,vector(16.257,16.257,0.000));
      vec_set(you.pan,vector(0.000,0.000,0.000));
      vec_set(you.scale_x,vector(1.000,1.000,10.000));
      set(you,PASSABLE);
      set(you,INVISIBLE);
   }
}

