/////////////////////////////////water_drops.c/////////////////////////////////
//
//Generated by Parted by Martin Coumont (redphoenix)
//
//LiteC Script file from 01.05.2013 ; 12:58:21:
//
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////header/////////////////////////////////

#ifndef PARTED_VECTOR_DEF
 #define PARTED_VECTOR_DEF
 VECTOR* parted_temp_vec = { x=0;y=0;z=0; }
 VECTOR* parted_temp2_vec = { x=0;y=0;z=0; }
 ANGLE* parted_temp_ang = { pan=0;tilt=0;roll=0; }
#endif

#ifndef rain1_DEF
 #define rain1_DEF
   BMAP* rain1_map = "rain1.tga";
#endif
/////////////////////////////////particle code/////////////////////////////////

function water_drop_base(PARTICLE* p) {
   p.size = 2.000;
   p.alpha = random(36.870)+(8.130);
   p.red = 128;
   p.green = 128;
   p.blue = 128;
   p.skill_c = 0.5;
   p.vel_x = (0.000);
   p.vel_y = (0.000);
   p.vel_z = (3.000);
   p.lifespan = 100.000;
   p.gravity = random(0.590)+0.000;
   p.bmap = rain1_map;
   p.flags = BRIGHT | TRANSLUCENT | MOVE;
   p.skill_x = p.vel_x;
   p.skill_y = p.vel_y;
   p.skill_z = p.vel_z;
   p.event = NULL;
}

/////////////////////////////////emitter actions/////////////////////////////////

action water_drop_emitter() {
   var eff_frac; eff_frac = 0;
wait(1);
   while(my) {
      parted_temp_vec.x = random(0.000)+0.000;
      parted_temp_vec.y = random(0.000)+0.000;
      parted_temp_vec.z = random(0.000)+0.000;
      vec_add(parted_temp_vec,my.x);
         eff_frac += 0.100*time_step*6.25;
         if(eff_frac >= 1){
            effect(water_drop_base,integer(eff_frac),parted_temp_vec,nullvector);
             eff_frac -= integer(eff_frac);
         }
      wait(1);
   }
}
/////////////////////////////////creation/////////////////////////////////

function water_drops_create(VECTOR* position) {
   if(!position)position = nullvector;
   wait(3);
   you = ent_create(NULL,position,water_drop_emitter);
   if(you) {
      vec_add(you.x,vector(0.000,0.000,194.500));
      vec_set(you.pan,vector(0.000,0.000,0.000));
      vec_set(you.scale_x,vector(1.000,1.000,1.000));
      set(you,PASSABLE);
      set(you,INVISIBLE);
   }
}

