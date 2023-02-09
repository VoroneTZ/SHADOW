//----------------------------------------------------------------------------------------
// SSAO v0.6 for Gamestudio A7 & A8
// Copyright (C) 2010, 2011 by Christian Behrenberg
//----------------------------------------------------------------------------------------
// Permission is hereby granted, free of charge, to any person obtaining a copy of this
// software and associated documentation files (the "Software"), to deal in the Software
// without restriction, including without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to per-
// mit persons to whom the Software is furnished to do so, subject to the following con-
// ditions:
// 
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, IN-
// CLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LI-
// ABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
// OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//----------------------------------------------------------------------------------------

#ifndef ppSsao_c
#define ppSsao_c

#include "ppSsao.h"
#include <stdio.h>


// integration into game

	// adds SSAO after last view in the camera-render chain in standalone mode
	void runSsao ()
	{
		runSsao(SSAO_MODE_DEF);
	}

	// adds SSAO after last view in the camera-render chain in an explicit mode
	void runSsao (long mode)
	{
		runSsao(camera, mode);
	}

	// adds SSAO after last view in the render chain, starting on the base view, in
	// standalone mode
	void runSsao (VIEW* base)
	{
		runSsao(base, SSAO_MODE_DEF);
	}

	// adds SSAO after last view in the render chain, starting on the base view, in an
	// explicit mode
	void runSsao (VIEW* base, long mode)
	{
		VIEW* v = base;

		while (v->stage != NULL)
			v = v->stage;

		runSsaoContext(v, NULL, mode);
	}

	// adds SSAO right in the context of an explicit pre- & post view in standalone mode
	void runSsao (VIEW* pre, VIEW* post)
	{
		runSsaoContext(pre, post, SSAO_MODE_DEF);
	}

	// adds SSAO right in the context of an explicit pre- & post view in an explicit mode
	void runSsaoContext (VIEW* pre, VIEW* post, long mode)
	{
		if (pre == NULL)
			return;
			
		// mode check
		if ((mode >= SSAO_MODE_STANDALONE) && (mode <= SSAO_MODE_SOURCE))
			ssaoMode = mode;
		else
			ssaoMode = SSAO_MODE_DEF;
			
		ssaoActive = true;
			
		setSsaoContext(pre, post);

		#ifdef A7
			// store fog information
			ssaoFogNr = fog_color;
			fog_color = 0;
		#endif
		
		// fire activation event
		fireSsaoEvent(on_ssaoActivated);
   }


// building the renderchain

	BOOL hasSsaoChainToBeRecreated ()
	{
		if (bmapSsaoDepthHires == NULL)
			return(true);
		else
			return(hasSsaoBmapToBeRecreated(bmapSsaoDepthHires, SSAO_HD));
	}

	void recreateSsaoChain ()
	{
		BOOL bRecreate = hasSsaoChainToBeRecreated();
	
		if (bRecreate)
		{
			// diffuse
			recreateSsaoRenderTarget(&bmapSsaoDiffuseHires, SSAO_DIFF_HD, SSAO_HD);
			
			// source: depths
			{
				viewSsaoSrcDepth->bmap = recreateSsaoRenderTarget(&bmapSsaoDepthHires, SSAO_DEPTH_HD, SSAO_HD);
				#ifdef SSAO_FULL_DEPTH
					viewSsaoSrcDepth->target1 = recreateSsaoRenderTarget(&bmapSsaoDepthFullHires, SSAO_DEPTH_FULL_HD, SSAO_HD);
				#endif

				viewSsaoSrcDepth->stage = viewSsaoSrcNormalsAlpha;
			}

			// source: normals + alpha
			{
				viewSsaoSrcNormalsAlpha->bmap = recreateSsaoRenderTarget(&bmapSsaoNormalHires, SSAO_NORMAL_HD, SSAO_HD);

				#ifdef SSAO_FULL_NORMALS
					viewSsaoSrcNormalsAlpha->target1 = recreateSsaoRenderTarget(&bmapSsaoNormalFullHires, SSAO_NORMAL_FULL_HD, SSAO_HD);
				#endif

				#ifndef SSAO_NO_SOFTALPHA
				{
					BMAP** t = NULL;

					#ifdef SSAO_FULL_NORMALS
						t = &(viewSsaoSrcNormalsAlpha->target2);
					#else
						t = &(viewSsaoSrcNormalsAlpha->target1);
					#endif
					
					*t = recreateSsaoRenderTarget(&bmapSsaoAlphaHires, SSAO_ALPHA_HD, SSAO_HD);
				}
				#endif

				viewSsaoSrcNormalsAlpha->stage = viewSsaoApproximation;
			}

			// processing
			{
				// downsampling, approximation and blur
				{
					recreateSsaoRenderTarget(&(mtlSsaoBlurPassH->skin1), SSAO_BLUR, SSAO_LD);
					recreateSsaoRenderTarget(&(mtlSsaoBlurPassV->skin1), SSAO_BLUR, SSAO_LD);

					viewSsaoApproximation->bmap = mtlSsaoBlurPassH->skin1;
					viewSsaoApproximation->target1 = recreateSsaoRenderTarget(&(mtlSsaoApproximation->skin1), SSAO_NRMxMASK_LD, SSAO_LD);

					viewSsaoBlurPassH->bmap = mtlSsaoBlurPassV->skin1;
					mtlSsaoBlurPassH->skin2 = mtlSsaoApproximation->skin1;

					viewSsaoBlurPassV->bmap = mtlSsaoBlurPassH->skin1;
					mtlSsaoBlurPassV->skin2 = mtlSsaoApproximation->skin1;

					viewSsaoApproximation->stage = viewSsaoBlurPassH;
					viewSsaoBlurPassH->stage = viewSsaoBlurPassV;
					viewSsaoBlurPassV->stage = viewSsaoUpsampling;
				}

				// upsampling
				{
					viewSsaoUpsampling->bmap = recreateSsaoRenderTarget(&(mtlSsaoUpsampling->skin3), SSAO_UPSAMPLING, SSAO_LD);
					mtlSsaoUpsampling->skin1 = mtlSsaoBlurPassH->skin1;
					mtlSsaoUpsampling->skin2 = mtlSsaoApproximation->skin1;

					viewSsaoUpsampling->stage = viewSsaoCombine;
				}
				
			}
		}
		
		// combine target
		{
			VIEW* lastSsaoView = NULL;
			
			#ifndef SSAO_NO_PARTICLES
			if (num_particles > 0)
			{
				if (viewSsaoParticle == NULL)
					viewSsaoParticle = view_create(0);
			
				lastSsaoView = viewSsaoParticle;
			}
			else
			#endif
				lastSsaoView = viewSsaoCombine;
				
			#ifndef SSAO_NO_COMBINE_TARGET
			if (lastSsaoView != NULL)
				if (ssaoViewPost != NULL)
					if (hasSsaoBmapToBeRecreated(bmapSsaoCombineHires, SSAO_HD))
						lastSsaoView->bmap = recreateSsaoRenderTarget(&bmapSsaoCombineHires, SSAO_COMBINE_HD, SSAO_HD);
			#endif		
		}
		
		updateSsaoChain();
		
		if (bRecreate)
			fireSsaoEvent(on_ssaoTargetRecreated);
	}
	
// Update ssao chain
void updateSsaoChain ()
{
	// pre to sources or to nothing or to post view
	if (ssaoActive)
	{
		ssaoViewPre->stage = viewSsaoSrcDepth;
		ssaoViewPre->bmap = bmapSsaoDiffuseHires;
	}
	else
	{
		if (ssaoMode == SSAO_MODE_STANDALONE)
		{
			ssaoViewPre->stage = ssaoViewPost;
			ssaoViewPre->bmap = NULL;
		}
		else // SSAO_MODE_SOURCE
		{
			if (ssaoViewPost != NULL)
			{
				ssaoViewPre->stage = viewSsaoSrcDepth;
				ssaoViewPre->bmap = bmapSsaoDiffuseHires;
			}
			else
			{
				ssaoViewPre->stage = NULL;
				ssaoViewPre->bmap = NULL;
			}
		}
	}
	
	// sample sources
	viewSsaoSrcDepth->stage = viewSsaoSrcNormalsAlpha;
	
	// calculate ssao
	if (ssaoActive || ((!ssaoActive) && ((ssaoMode == SSAO_MODE_SOURCE) && (ssaoViewPost != NULL))))
		viewSsaoSrcNormalsAlpha->stage = viewSsaoApproximation;
	else
		viewSsaoSrcNormalsAlpha->stage = ssaoViewPost;
		
	// approximation
	copySsaoClippingParams(mtlSsaoApproximation, ssaoViewPre);

	// blur
	copySsaoClippingParams(mtlSsaoBlurPassH, ssaoViewPre);
	copySsaoClippingParams(mtlSsaoBlurPassV, ssaoViewPre);
	
	// upsampling
	copySsaoClippingParams(mtlSsaoUpsampling, ssaoViewPre);	

	// combine, last view linkage
	if (ssaoActive)
	{
		// combine
		copySsaoClippingParams(mtlSsaoCombine, ssaoViewPre);
		mtlSsaoCombine->skin1 = mtlSsaoUpsampling->skin3;
		
		// last view linkage
			
			// get last view
			VIEW* lastSsaoView = viewSsaoCombine;
			#ifndef SSAO_NO_PARTICLES
			if (num_particles > 0)
			{
				if (viewSsaoParticle == NULL)
					viewSsaoParticle = view_create(0);
			
				viewSsaoCombine->stage = viewSsaoParticle;
				lastSsaoView = viewSsaoParticle;
			}
			#endif				
			
			lastSsaoView->stage = ssaoViewPost;
			lastSsaoView->bmap = NULL;
			
			#ifndef SSAO_NO_COMBINE_TARGET
				if (lastSsaoView->stage != NULL)
					lastSsaoView->bmap = bmapSsaoCombineHires;
			#endif
	}
}

// switching SSAO on / off

	// enables/disables SSAO
	BOOL toggleSsaoState ()
	{
		// no base defined or sources not established
		if ((!ssaoViewPre) || ((!viewSsaoSrcDepth) || (!viewSsaoSrcNormalsAlpha)))
			return(false);
			
		// activate if it was off and vice versa
		BOOL bSet = setSsaoState(!ssaoActive);
		return(bSet);
	}

	// enables / disables SSAO basing upon a boolean
	BOOL setSsaoState (BOOL active)
	{
		// no base defined or sources aren't established
		if ((!ssaoViewPre) || ((!viewSsaoSrcDepth) || (!viewSsaoSrcNormalsAlpha)))
			return(false);
			
		ssaoActive = active;
		
		if (ssaoActive)
			runSsaoContext(ssaoViewPre, ssaoViewPost, ssaoMode);
		else
		{
			switch (ssaoMode)
			{
				case SSAO_MODE_STANDALONE:
				{
					ssaoViewPre->stage = ssaoViewPost;
					ssaoViewPre->bmap = NULL;
					break;
				}
				
				case SSAO_MODE_SOURCE:
				{
					if (ssaoViewPost != NULL)
						viewSsaoSrcNormalsAlpha->stage = ssaoViewPost;
					else
					{
						ssaoViewPre->stage = NULL;
						ssaoViewPre->bmap = NULL;
					}
					
					break;
				}
			}

			#ifndef SSAO_NO_PARTICLES
				reset(ssaoViewPre, NOPARTICLE);
			#endif

			#ifdef A7
				fog_color = ssaoFogNr;
			#endif

			fireSsaoEvent(on_ssaoDeactivated); // fire external event			
		}
		
		return(true);
	}


// queries

	// returns if SSAO ís currently active or not
	BOOL getSsaoState ()
	{
		return(ssaoActive);
	}

	BMAP* getSsaoClippedDepthMap ()
	{
		if (hasSsaoBmapToBeRecreated(bmapSsaoDepthHires, SSAO_HD))
			recreateSsaoChain();

		return(bmapSsaoDepthHires);
	}

	BMAP* getSsaoFullDepthMap ()
	{
		#ifdef SSAO_FULL_DEPTH
			if (hasSsaoBmapToBeRecreated(bmapSsaoDepthFullHires, SSAO_HD))
				recreateSsaoChain();

			return(bmapSsaoDepthFullHires);
		#else
			return(getSsaoClippedDepthMap());
		#endif
	}

	BMAP* getSsaoClippedNormalMap ()
	{
		if (hasSsaoBmapToBeRecreated(bmapSsaoNormalHires, SSAO_HD))
			recreateSsaoChain();

		return(bmapSsaoNormalHires);
	}

	BMAP* getSsaoFullNormalMap ()
	{
		#ifdef SSAO_FULL_NORMALS
			if (hasSsaoBmapToBeRecreated(bmapSsaoNormalFullHires, SSAO_HD))
				recreateSsaoChain();

			return(bmapSsaoNormalFullHires);
		#else
			return(getSsaoClippedNormalMap());
		#endif
	}

	// returns the screenspace softalpha map
	#ifndef SSAO_NO_SOFTALPHA
	BMAP* getSsaoSoftAlphaMap ()
	{
		if (hasSsaoBmapToBeRecreated(bmapSsaoAlphaHires, SSAO_HD))
			recreateSsaoChain();

		return(bmapSsaoAlphaHires);
	}
	#endif

	BMAP* getSsaoDiffuseMap ()
	{
		if (hasSsaoBmapToBeRecreated(bmapSsaoDiffuseHires, SSAO_HD))
			recreateSsaoChain();

		return(bmapSsaoDiffuseHires);
	}

	#ifndef SSAO_NO_COMBINE_TARGET
	BMAP* getSsaoCombineMap ()
	{
		BMAP* bResult = NULL;
		
		if (ssaoActive)
			bResult = bmapSsaoCombineHires;
		else
			bResult = bmapSsaoDiffuseHires;
				
		if (hasSsaoBmapToBeRecreated(bResult, SSAO_HD))
		{
			recreateSsaoChain();
			bResult = getSsaoCombineMap();
		}
		
		return(bResult);
	}
	#endif


// Removes SSAO from your render chain. All render targets and G-buffer views will be
// removed. The pre view will be staged with the post view, if set before.
void removeSsao ()
{
	// decouple
	setSsaoState(false);

	// remove render targets
	{
		// diffuse
		ssaoFreePtr(&bmapSsaoDiffuseHires);
		
		// depth
		ssaoFreePtr(&bmapSsaoDepthHires);
		#ifdef SSAO_FULL_DEPTH
			ssaoFreePtr(&bmapSsaoDepthFullHires);
		#endif
		
		// normals
		ssaoFreePtr(&bmapSsaoNormalHires);
		#ifdef SSAO_FULL_NORMALS
			ssaoFreePtr(&bmapSsaoNormalFullHires);
		#endif
		
		// blur
		ssaoFreePtr(&(mtlSsaoBlurPassH->skin1));
		ssaoFreePtr(&(mtlSsaoBlurPassV->skin1));
		
		// alpha
		#ifndef SSAO_NO_SOFTALPHA
			ssaoFreePtr(&bmapSsaoAlphaHires);
		#endif
		
		// combine
		#ifndef SSAO_NO_COMBINE_TARGET
			ssaoFreePtr(&bmapSsaoCombineHires);
		#endif
	}

	// remove G-buffer views
	ssaoFreePtr(&viewSsaoSrcDepth);
	ssaoFreePtr(&viewSsaoSrcNormalsAlpha);

	// reset context
	{
		// link pre with post
		ssaoViewPre->stage = ssaoViewPost;
		
		ssaoViewPre = NULL;
		ssaoViewPost = NULL;
	}
}


// render context

	// attaches a view, while taking care of the SSAO chain, if necessary
	void attachSsaoView (VIEW* predecessor, VIEW* newView)
	{
		if ((predecessor != NULL) && (newView != NULL))
		{
			// New view is inserted between predecessor and deferred view
			if (predecessor->stage == viewSsaoSrcDepth)
			{
				predecessor->stage = newView;
				newView->stage = viewSsaoSrcDepth;
			}
		}
	}

	// detaches a view, while taking care of the SSAO chain, if necessary
	void detachSsaoView (VIEW* disattached)
	{
		VIEW* predecessor = ssaoGetViewPredecessor(disattached);

		if ((disattached != NULL) && (predecessor != NULL))
		{
			// Successor view is deferred view
			if (disattached->stage == viewSsaoSrcDepth)
			{
				predecessor->stage = viewSsaoSrcDepth;
				disattached->stage = NULL;
				ssaoViewPre = predecessor;
			}
			else
				if (disattached == ssaoViewPost)
				{
					ssaoViewPost = disattached->stage;
					disattached->stage = NULL;
				}
		}
	}

	// sets the first view BEFORE and AFTER the SSAO chain as
	// dynamically adapted render context
	void setSsaoContext (VIEW* pre, VIEW* post)
	{
		if (pre != NULL) //&& (pre != ssaoViewPre))
		{
			ssaoViewPre = pre;
			
			#ifndef SSAO_NO_PARTICLES
				set(pre, NOPARTICLE); // deactivate particles
			#endif
			
			// assert source views
			assertSsaoView(&viewSsaoSrcNormalsAlpha, SSAO_VIEW_SRC_FLAGS, objMtlDeferredSwitch, viewSsaoApproximation);
			assertSsaoView(&viewSsaoSrcDepth, SSAO_VIEW_SRC_FLAGS, objMtlDeferredSwitch, viewSsaoSrcNormalsAlpha);
		}
		
		ssaoViewPost = post;
		
		recreateSsaoChain();
	}

	// get the pointers to the pre- and post views
	void getSsaoContext (VIEW** pre, VIEW** post)
	{
		if (pre != NULL)
			*pre = ssaoViewPre;

		if (post != NULL)
			*post = ssaoViewPost;
	}


// surface types

	// sets the surface type of an entity
	void setSsaoSurface (ENTITY* e, int type)
	{
		if (e)
			e->SURFACE |= type;
	}

	// returns if an entity has a specific surface type
	BOOL hasSsaoSurface (ENTITY* e, int type)
	{
		if (e)
			return(e->SURFACE & type);
		else
			return(false);
	}

	// returns the assigned surface type
	int getSsaoSurface (ENTITY* e)
	{
		if (e)
			return(e->SURFACE);
	}

	// recognizes some surfaces types dependent on an entity's type
	void recognizeSsaoSurface (ENTITY* e)
	{
		int entityType = ent_type(e);

		if (entityType >= 2)
		{
			switch (entityType)
			{
				case 2: // ABT-maps have no alpha!
				        e->SURFACE |= SSAO_TYPE_SOLID;
				        break;

				case 3: // BSP-maps have no alpha!
				        e->SURFACE |= SSAO_TYPE_SOLID;
				        break;

				case 4: // Terrains have no alpha!
				        e->SURFACE |= SSAO_TYPE_SOLID;
				        break;

				case 5: // models
				{
				        // assign only binary alpha on overlay flag
				        if (e->flags & (OVERLAY))
				           e->SURFACE |= SSAO_TYPE_BINARY;
				}

				// UNKNOWN - CAN'T MAKE ANY ASSUMPTIONS!

				case 6: // Sprites

				        // if it is a decal, ignore it
				        if (e->flags & (DECAL))
				           e->SURFACE |= SSAO_TYPE_IGNORE;
				        else
				        {
					        #ifndef SSAO_NO_SOFTALPHA
					           e->SURFACE |= SSAO_TYPE_SOFTALPHA;
					        #else // No softalpha allowed -> fallback to binary alpha
					           e->SURFACE |= SSAO_TYPE_BINARY;
					        #endif
					     }

				        break;
			}

			// Don't try to recognize this entity anymore
			e->SURFACE |= (SSAO_TYPE_RECOGNIZED);
		}
	}


// utility functions

	// Returns true, if a bitmap with the aspect ratio of the screen and a given ratio of
	// the  screensize has to be recreated or not (because resolution changed). E.g. if
	// you pass a lodRatio of 2 and the BMAP* has a size of (512,384) and the screensize
	// is 1280x1024, true is returned, because the BMAP* should have (640,512). Returns
	// always true, if BMAP* is NULL or lodRatio is invalid (<0)
	
	BOOL hasSsaoBmapToBeRecreated (BMAP* bmap, int lodRatio)
	{
		// always recreate, e.g. on invalid parameters
		BOOL bRecreate = true;
		
		// check recreation only when a filled bmap is passed and lodRatio is valid
		if ((bmap != NULL) && (lodRatio > 0))
		{
			BOOL bWidthDiff = (bmap->width != screen_size.x / lodRatio);
			BOOL bHeightDiff = (bmap->height != screen_size.y / lodRatio);
			
			// must be recreated, when either the width or the height is different
			bRecreate = (bWidthDiff || bHeightDiff);
		}
		
		return(bRecreate);
	}

	BMAP* recreateSsaoRenderTarget (BMAP** bmap, int format, int lodRatio)
	{
		if ((bmap == NULL) || (lodRatio <= 0))
			return(NULL);
			
		if (*bmap != NULL)
			ptr_remove(*bmap);

		*bmap = bmap_createblack(screen_size.x / lodRatio, screen_size.y / lodRatio, format);

		return(*bmap);
	}

	void loadSsaoShaders ()
	{
		// objects
		{
			compileSsaoShader(&objMtlDeferredSwitch, "\n#define OBJ_SOLID\n", "ao_pp_obj.fx");
			
			#ifndef SSAO_NO_SKY
				createSsaoObjMtl(&ssaoObjMtlSky, "\n#define OBJ_SKY\n", "ao_pp_obj.fx");
			#endif
			
			createSsaoObjMtl(&ssaoObjMtlSolid, "\n#define OBJ_SOLID\n", "ao_pp_obj.fx");
			createSsaoObjMtl(&ssaoObjMtlBinary, "\n#define OBJ_BINARY\n", "ao_pp_obj.fx");

			#ifndef SSAO_NO_SOFTALPHA
				createSsaoObjMtl(&ssaoObjMtlSoftalpha, "\n#define OBJ_SOFTALPHA\n", "ao_pp_obj.fx");
			#endif
		}

		// postprocessing chain
		{
			compileSsaoShader(&mtlSsaoApproximation, NULL, "ao_pp_ssao.fx");
			compileSsaoShader(&mtlSsaoBlurPassH, "\n#define STEP_X 1\n#define STEP_Y 0\n", "ao_pp_blur.fx");
			compileSsaoShader(&mtlSsaoBlurPassV, "\n#define STEP_X 0\n#define STEP_Y 1\n", "ao_pp_blur.fx");
			compileSsaoShader(&mtlSsaoUpsampling, NULL, "ao_pp_upsample.fx");
			compileSsaoShader(&mtlSsaoCombine, NULL, "ao_pp_combine.fx");
		}
	}

	BOOL compileSsaoShader (MATERIAL** mtlRef, char* customPreamble, char* filename)
	{
		if ((mtlRef == NULL) || (filename == NULL)) return(false);
		if (strlen(filename) < 5) return(false);

      // create material if not there
		if (*mtlRef == NULL) *mtlRef = mtl_create();

		int size = 0;

		// load shader content into buffer
		void* code = file_load(filename, NULL, &size);

		if (size != 0) // successfully loaded
		{
			// global preamble + custom preamble + code = final shader

			STRING* finalShader = str_create(getSsaoShaderPreamble());

			if (customPreamble != NULL)
				str_cat(finalShader, customPreamble);

			str_cat(finalShader, code);
			
			effect_load(*mtlRef, finalShader);

			// unload resources
			file_load(NULL, code, NULL);
			ptr_remove(finalShader);

			return(true);
		}
		else
		{
			return(false);
		}
	}

		STRING* getSsaoShaderPreamble ()
		{
			if (ssaoShaderPreamble == NULL) // singleton
			{
				char str [256];

				ssaoShaderPreamble = str_create("#512");
				str_cpy(ssaoShaderPreamble, "");

				// statics
				{
					// quality
					sprintf(str, "#define SSAO_HD %d\n#define SSAO_LD %d\n", (int)SSAO_HD, (int)SSAO_LD);
					str_cat(ssaoShaderPreamble, str);
				}

				// values
				{
					#ifdef SSAO_SOFTALPHA_QUALITY
						sprintf(str, "#define SSAO_SOFTALPHA_QUALITY %d\n", (int)SSAO_SOFTALPHA_QUALITY);
						str_cat(ssaoShaderPreamble, str);
					#endif

					#ifdef SSAO_UPSAMPLE_DEPTH_T
						sprintf(str, "#define SSAO_UPSAMPLE_DEPTH_T %f\n", (double)SSAO_UPSAMPLE_DEPTH_T);
						str_cat(ssaoShaderPreamble, str);
					#endif

					#ifdef SSAO_SAMPLES
						sprintf(str, "#define SSAO_SAMPLES %d\n", (int)SSAO_SAMPLES);
						str_cat(ssaoShaderPreamble, str);
					#endif
					
					#ifdef SSAO_SAMPLE_SCALE_STEP
						sprintf(str, "#define SSAO_SAMPLE_SCALE_STEP %f\n", (double)SSAO_SAMPLE_SCALE_STEP);
						str_cat(ssaoShaderPreamble, str);
					#endif
					
					#ifdef SSAO_BLUR_SAMPLES
						sprintf(str, "#define SSAO_BLUR_SAMPLES %d\n", (int)SSAO_BLUR_SAMPLES);
						str_cat(ssaoShaderPreamble, str);
					#endif

					#ifdef SSAO_UPSAMPLE_NORMAL_POW
						sprintf(str, "#define SSAO_UPSAMPLE_NORMAL_POW %d\n", (int)SSAO_UPSAMPLE_NORMAL_POW);
						str_cat(ssaoShaderPreamble, str);
					#endif

					#ifndef SSAO_NO_CONTRASTING
						#ifdef SSAO_STATIC_CONTRASTING
							#ifdef SSAO_CONVEX_HIGHLIGHT
							#ifdef SSAO_CONCAVE_DARKNESS
								sprintf(str, "#define SSAO_CONVEX_HIGHLIGHT %f\n#define SSAO_CONCAVE_DARKNESS %f\n", (double)SSAO_CONVEX_HIGHLIGHT, (double)SSAO_CONCAVE_DARKNESS);
								str_cat(ssaoShaderPreamble, str);
							#endif
							#endif
						#endif
					#endif
				}

				// defines
				{
					#ifdef A8
						str_cat(ssaoShaderPreamble, "#define A8\n");
					#endif
					
					#ifdef A7
						str_cat(ssaoShaderPreamble, "#define A7\n");
					#endif
					
					#ifdef SSAO_SHADER_DEBUG
						str_cat(ssaoShaderPreamble, "#define SSAO_SHADER_DEBUG\n");
					#endif
					
					#ifdef SSAO_NO_SOFTALPHA
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_SOFTALPHA\n");
					#endif
					
					#ifdef SSAO_NO_CONTRASTING
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_CONTRASTING\n");
					#else
						#ifdef SSAO_STATIC_CONTRASTING
							str_cat(ssaoShaderPreamble, "#define SSAO_STATIC_CONTRASTING\n");
						#endif
					#endif
					
					#ifdef SSAO_NO_BLUR_NORMAL_T
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_BLUR_NORMAL_T\n");
					#endif
					
					#ifdef SSAO_NO_BLUR_DEPTH_T
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_BLUR_DEPTH_T\n");
					#endif
					
					#ifdef SSAO_NO_BLUR_T
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_BLUR_T\n");
					#endif
					
					#ifdef SSAO_NO_PARTICLES
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_PARTICLES\n");
					#endif
					
					#ifdef SSAO_NO_FOG
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_FOG\n");
					#endif
					
					#ifdef SSAO_NO_SKY
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_SKY\n");
					#endif
					
					#ifdef SSAO_GPU_BONES
						str_cat(ssaoShaderPreamble, "#define SSAO_GPU_BONES\n");
					#endif
					
					#ifdef SSAO_FULL_MAPS
						str_cat(ssaoShaderPreamble, "#define SSAO_FULL_MAPS\n");
					#endif
					
					#ifdef SSAO_FULL_DEPTH
						str_cat(ssaoShaderPreamble, "#define SSAO_FULL_DEPTH\n");
					#endif
					
					#ifdef SSAO_FULL_NORMALS
						str_cat(ssaoShaderPreamble, "#define SSAO_FULL_NORMALS\n");
					#endif
					
					#ifdef SSAO_NO_COMBINE_TARGET
						str_cat(ssaoShaderPreamble, "#define SSAO_NO_COMBINE_TARGET\n");
					#endif
				}
			}

			return(ssaoShaderPreamble);
		}

	void assertSsaoView (VIEW** view, long flags, MATERIAL* mat, VIEW* stage)
	{
		if (view == NULL)
			return;
		else
			if (*view == NULL)
			{
				*view = view_create(0);
				(*view)->flags |= flags;

				if (mat)
					(*view)->material = mat;

				if (stage)
					(*view)->stage = stage;
			}
	}

	// removes an engine object and sets the pointer to NULL
	void ssaoFreePtr (void** ptrRef)
	{
		if (ptrRef)
			if (*ptrRef)
			{
				ptr_remove(*ptrRef);
				*ptrRef = NULL;
			}
	}

	VIEW* ssaoGetViewPredecessor (VIEW* successor)
	{
		if (!successor)
			return(NULL);

		VIEW* result = NULL;
		VIEW* v = ptr_first(camera);

		while (v)
		{
			if (v->stage == successor)
			{
				result = v;
				break;
			}

			v = (VIEW*)(v->link.next);
		}

		return(result);
	}

	void ssaoSyncView (VIEW* src, VIEW* dst)
	{
		if ((!src) || (!dst))
			return;

		vec_set(dst->x,   src->x);
		vec_set(dst->pan, src->pan);
		
		dst->arc = src->arc;

		dst->clip_near = src->clip_near;
		dst->clip_far  = src->clip_far;
	}


// object shaders

	SsaoObjMtl* createSsaoObjMtl ()
	{
		SsaoObjMtl* o = (SsaoObjMtl*)sys_malloc(sizeof(SsaoObjMtl));

		o->m = (MATERIAL***)sys_malloc(sizeof(MATERIAL**) * SSAO_OBJ_ANIM_CNT);

		int i, j;
		for (i = 0; i < SSAO_OBJ_ANIM_CNT; i++)
		{
			(o->m)[i] = (MATERIAL**)sys_malloc(sizeof(MATERIAL*) * SSAO_SRC_CNT);
			
			for (j = 0; j < SSAO_SRC_CNT; j++)
			{
				((o->m)[i])[j] = mtl_create();
			}
		}
	}

	// LOADS EFFECT FILES INTO THE GIVEN SSAO OBJECT MATERIAL
	//
	// loads effect files into the given material, once for cpu- and once for gpu-
	// animation (only A8)
	//
	SsaoObjMtl* createSsaoObjMtl (SsaoObjMtl** ref, char* preamble, char* fxFile)
	{
		if (ref == NULL) return(NULL);

		// given material not existent -> create it
		if (*ref == NULL)
		{
			SsaoObjMtl* o = (SsaoObjMtl*)sys_malloc(sizeof(SsaoObjMtl));

			o->m = (MATERIAL***)sys_malloc(sizeof(MATERIAL**) * SSAO_OBJ_ANIM_CNT);

			int i, j;
			for (i = 0; i < SSAO_OBJ_ANIM_CNT; i++)
			{
				(o->m)[i] = (MATERIAL**)sys_malloc(sizeof(MATERIAL*) * SSAO_SRC_CNT);

				for (j = 0; j < SSAO_SRC_CNT; j++)
					((o->m)[i])[j] = mtl_create();
			}
			
			*ref = o;
		}
		else // otherwise assume, that is already created (wtf)
			return(*ref);

		SsaoObjMtl* m = *ref; // here it is

		static char pre [512];

		int i, j;
		for (i = 0; i < SSAO_OBJ_ANIM_CNT; i++)
			for (j = 0; j < SSAO_SRC_CNT; j++)
			{
				strcpy(pre, "");
				if (preamble) strcat(pre, preamble);

				strcat(pre, "\n"); strcat(pre, ssaoObjAnimDefine[i]);
				strcat(pre, "\n"); strcat(pre, ssaoSrcDefine[j]);
				strcat(pre, "\n");
				
				compileSsaoShader(&(((m->m)[i])[j]), pre, fxFile);
			}
	}


// material events & functions

	// copies the clipping parameters from a view v into skill1 & 2 of a material m
	void copySsaoClippingParams (MATERIAL* m, VIEW* v)
	{
		m->skill1 = floatv(v->clip_near);
		m->skill2 = floatv(v->clip_far);		
	}

	// GETS THE SURFACE DEPENDENT SHADER OF AN ENTITY
	//
	// Sets *mat to the material for entity e, depending on it's surface type and
	// activated CPU/GPU-bone animation. If entity shall not be rendered, false is
	// returned, otherwise true.
	//
	BOOL getSsaoObjShader (ENTITY* e, MATERIAL** mat, int src)
	{
		if ((e == NULL) || (mat == NULL))
			return(false);

		BOOL render = true; // always render if not stated otherwise
		SsaoObjMtl* mtlSurface = ssaoObjMtlSolid; // solid = default
		
		// select surface material
		{
			#ifndef SSAO_NO_SKY
				if (e->flags2 & (SKY)) // sky
					mtlSurface = ssaoObjMtlSky;
				else // mesh
			#endif
				{
					// recognize surface type, if possible
					if (!(e->SURFACE & SSAO_TYPE_RECOGNIZED))
						recognizeSsaoSurface(e);

					// get material
					if (e->SURFACE & SSAO_TYPE_IGNORE) // skip if ignore
						render = false;
					else
						if (!(e->SURFACE & SSAO_TYPE_SOLID)) // solid, if explicitely set
							if (e->SURFACE & SSAO_TYPE_BINARY) // binary alpha > softalpha
								mtlSurface = ssaoObjMtlBinary;
						#ifndef SSAO_NO_SOFTALPHA
							else
								if (e->SURFACE & SSAO_TYPE_SOFTALPHA) // soft alpha
									mtlSurface = ssaoObjMtlSoftalpha;
						#endif
				}
		}
		
		// select animation type
		int objAnim = SSAO_OBJ_ANIM_CPU;
		{
			// use gpu bones if available and active
			#ifdef SSAO_GPU_BONES
				if (e->material->maxbones > 0)
					objAnim = SSAO_OBJ_ANIM_GPU;
			#endif
		}
		
		// source type is given by <src>

		// fetch shader
		*mat = ((mtlSurface->m)[objAnim])[src];

		return(render);
	}


	// DEFFERED OBJECT SHADER SWITCH
	function objMtlDeferredSwitch_ev ()
	{
		// determine src view
		int src = SSAO_SRC_DEPTH;
		{
			if (render_view == viewSsaoSrcNormalsAlpha)
				src = SSAO_SRC_NRMALPHA;
		}

		// get object shader and rendering flag
		MATERIAL* objMtl = NULL;
		BOOL render = getSsaoObjShader(my, &objMtl, src);

		if ((render == true) && (objMtl != NULL))
		{
			mtl = objMtl; // set shader

			// set clipping parameters
			copySsaoClippingParams(mtl, render_view);

			return(0);
		}
		else
			return(1); // don't render!
	}

	void mtlSsaoSrc_ev ()
	{
		// don't work with diffuse view unless all source views are established
		if (!viewSsaoSrcDepth) return;
		if (!viewSsaoSrcNormalsAlpha) return;

		// hooked event for diffuse view
		if (render_view->stage == viewSsaoSrcDepth)
		{
			// sync clipping parameters
			viewSsaoSrcDepth->clip_near = viewSsaoSrcNormalsAlpha->clip_near = render_view->clip_near;
			viewSsaoSrcDepth->clip_far  = viewSsaoSrcNormalsAlpha->clip_far  = render_view->clip_far;

			// This is the VERY FIRST event which is fired in the whole SSAO chain. If the
			// diffuse render target has to be recreated, we recreate all render targets!
			//if (hasSsaoBmapToBeRecreated(bmapSsaoDiffuseHires, SSAO_HD))
			recreateSsaoChain();
				
			//updateSsaoChain();

			#ifdef A7
				fog_color = 0; // reset A7 fog, if overwritten
			#endif
		}
	}

	// SSAO
	void mtlSsaoApproximation_ev ()
	{
		// update shader parameters

			// Fog usage
			var fogColor;

			#ifdef A7
				fogColor = ssaoFogNr;
			#else
				fogColor = fog_color;
			#endif

			#ifndef SSAO_NO_FOG
				mtl->skill3 = floatv(fogColor != 0); // is fog in use?
				mtl->skill4 = floatv(1.0 - (fogColor != 0)); // is fog NOT in use?
			#endif
			
			// clipping parameters
			mtl->skill1 = floatv(viewSsaoSrcDepth->clip_near);
			mtl->skill2 = floatv(viewSsaoSrcDepth->clip_far);
			
			// clipping parameters
			mtlSsaoBlurPassH->skill1 = floatv(viewSsaoSrcDepth->clip_near);
			mtlSsaoBlurPassH->skill2 = floatv(viewSsaoSrcDepth->clip_far);
			mtlSsaoBlurPassV->skill1 = floatv(viewSsaoSrcDepth->clip_near);
			mtlSsaoBlurPassV->skill2 = floatv(viewSsaoSrcDepth->clip_far);
	}

	function mtlSsaoCombine_ev ()
	{
		#ifdef A7
		if (ssaoFogNr != 0)
		{
			mtl->skill1 = floatv(ssaoViewPre->clip_far);

			COLOR* color = NULL;
			
			switch ((int)ssaoFogNr)
			{
				case 1: color = &d3d_fogcolor1; break;
				case 2: color = &d3d_fogcolor2; break;
				case 3: color = &d3d_fogcolor3; break;
				case 4: color = &d3d_fogcolor4; break;
			}
			
			if (color)
			{
				mtl->skill2 = floatv(color->red   / 255.0);
				mtl->skill3 = floatv(color->green / 255.0);
				mtl->skill4 = floatv(color->blue  / 255.0);
			}
		}
		#endif
		
		// concatenate first post-SSAO view after last SSAO view

		VIEW* lastView = render_view;

		// insert particle pass inbetween last and post-SSAO view if and only if
		// particles are possibly visible

		#ifndef SSAO_NO_PARTICLES
			if (num_particles > 0)
			{
				if (viewSsaoParticle == NULL)
					viewSsaoParticle = view_create(0);
					
				viewSsaoParticle->flags |= SSAO_VIEW_PARTICLE_FLAGS;
				
				#ifdef SSAO_VIEW_PARTICLE_USE_DUMMY_MTL
					viewSsaoParticle->material = mtlSsaoParticle;
				#endif
				
				render_view->stage = viewSsaoParticle;
				ssaoSyncView(render_view, render_view->stage);
				
				//viewSsaoParticle->stage = ssaoViewPost;
				lastView = viewSsaoParticle;
			}
		#endif

		// if the post-SSAO view really exists, render the combined
		// image into a render target, otherwise, render to screen
		
		// default: render to screen
		lastView->stage = NULL;

		// otherwise: staged view
		if (ssaoViewPost != NULL)
			lastView->stage = ssaoViewPost;
	}


// particles
#ifdef A7
#ifndef SSAO_NO_PARTICLES
	function mtlSsaoParticle_ev ()
	{
		return(1);
	}
#endif
#endif


// external events
void fireSsaoEvent (EVENT ev)
{
	if (ev == NULL)
		return;

	void fnc (void); // function pointer

	fnc = ev; // load event
	fnc(); // fire it
}


// fog (only A7)
//
// Remarks: the term "safely" in the descriptions is used due to the fact that
// for A7 the fog_color is always supressed to 0 to avoid fog plane artifacts
// in the deferred view -and- that the (original) fog_color is saved in another
// variable. So, when you use these function, everything is allright!

	// activates -safely- a fog color
	void activateSsaoFog (var colorNr)
	{
		#ifdef A7
			if (getSsaoState())
			{
				ssaoFogNr = colorNr;
				fog_color = 0;
			}
			else
		#endif
				fog_color = colorNr; // A8
	}

	// disables -safely- the fog
	void disableSsaoFog ()
	{
		#ifdef A7
			if (getSsaoState())
				ssaoFogNr = 0;
			else
		#endif
				fog_color = 0; // A8
	}

	// returns -safely- the fog color
	var getSsaoFogColor ()
	{
		#ifdef A7
			if (getSsaoState())
				return ssaoFogNr;
			else
		#endif
				return fog_color; // A8
	}
	
	
// startup
void ssao_startup ()
{
	// strings

	int i;

	for (i = 0; i < SSAO_OBJ_ANIM_CNT; i++)
		ssaoObjAnimDefine[i] = (char*)sys_malloc(sizeof(char)*128);

	strcpy(ssaoObjAnimDefine[SSAO_OBJ_ANIM_CPU], "#define SKIP_BONES");

	#ifdef SSAO_GPU_BONES
		strcpy(ssaoObjAnimDefine[SSAO_OBJ_ANIM_GPU], "#define SKIP_T");
	#endif

	for (i = 0; i < SSAO_SRC_CNT; i++)
		ssaoSrcDefine[i] = (char*)sys_malloc(sizeof(char)*128);
		
	strcpy(ssaoSrcDefine[SSAO_SRC_DEPTH], "#define SSAO_SRC_DEPTH");
	strcpy(ssaoSrcDefine[SSAO_SRC_NRMALPHA], "#define SSAO_SRC_NRMALPHA");

	// shaders
	loadSsaoShaders();
}

#endif /* ssao_c */