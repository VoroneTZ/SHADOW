/////////////////////////////////for.c/////////////////////////////////
//
//Generated by Parted by Martin Coumont (redphoenix)
//
//LiteC Script file from 19.04.2013 ; 18:43:16:
//
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////header/////////////////////////////////

#ifndef PARTED_VECTOR_DEF
 #define PARTED_VECTOR_DEF
 VECTOR* parted_temp_vec = { x=0;y=0;z=0; }
 VECTOR* parted_temp2_vec = { x=0;y=0;z=0; }
 ANGLE* parted_temp_ang = { pan=0;tilt=0;roll=0; }
#endif

#ifndef PARTED_RANGEFUNC_DEF
 #define PARTED_RANGEFUNC_DEF
 function range(x,y,z) {
   z+=y;
   if(x >= y && x <= z) return(1);
   return(0);
 }
#endif

#ifndef dust1_DEF
 #define dust1_DEF
   BMAP* dust1_map = "dust1.tga";
#endif
/////////////////////////////////particle code/////////////////////////////////

function fog_base_event(PARTICLE* p) {
   if((p.x-camera.x)*cos(camera.pan) + (p.y-camera.y)*sin(camera.pan) + (p.z-camera.z)*sin(camera.tilt) < 0)p.lifespan = 0;
   p.skill_d = (p.skill_d + time_step*(var)1.000)%100;
}

function fog_base(PARTICLE* p) {
   p.size = random(45.820)+(184.180);
   p.alpha = random(10.000)+(0.000);
   p.red = 50;
   p.green = 61;
   p.blue = 83;
   p.skill_c = 0.5;
   parted_temp_vec.x = random(191.406)+208.594;
   parted_temp_vec.y = random(600.000)+-300.000;
   parted_temp_vec.z = 0.000;
   vec_rotate(parted_temp_vec,camera.pan);
   vec_add(p.x,parted_temp_vec);
   p.vel_x = random(0.799)+(-0.399);
   p.vel_y = random(0.799)+(-0.399);
   p.vel_z = (0.000);
   p.lifespan = 9.000;
   p.gravity = 0.000;
   p.bmap = dust1_map;
   p.flags = BRIGHT | TRANSLUCENT | MOVE;
   p.skill_x = p.vel_x;
   p.skill_y = p.vel_y;
   p.skill_z = p.vel_z;
   p.event = fog_base_event;
}

/////////////////////////////////timetableemitter actions/////////////////////////////////

action fog_emitter() {
   var my_time;my_time = 0;
   var timetable_num;timetable_num = 0;
   var eff_frac; eff_frac = 0;
   wait(1);
   while(my) {
      my_time += time_step/16;
      if(my_time >= 0.000)my_time = 0;
      timetable_num = 1;
      vec_set(parted_temp_vec,nullvector);
      vec_add(parted_temp_vec,camera.x);
      if(!(total_frames % 8) && timetable_num) {
         eff_frac += 1.000*timetable_num*time_step*6.25;
         if(eff_frac >= 1){
            effect(fog_base,integer(eff_frac),parted_temp_vec,nullvector);
            eff_frac -= integer(eff_frac);
         }
      }
      wait(1);
   }
}
/////////////////////////////////creation/////////////////////////////////

function for_create(VECTOR* position) {
   if(!position)position = nullvector;
   wait(3);
   you = ent_create(NULL,position,fog_emitter);
   if(you) {
      vec_add(you.x,vector(2.771,8.961,0.877));
      vec_set(you.pan,vector(0.000,0.000,0.000));
      vec_set(you.scale_x,vector(1.000,1.000,1.000));
      set(you,PASSABLE);
      set(you,INVISIBLE);
   }
}

