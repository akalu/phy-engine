/* xxdf.h : General definitions for edf,brdf,btdf, ... */

#ifndef _XXDF_H_
#define _XXDF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "vector.h"

/* Contributions to outgoing radiance are divided
   into three components : */

#define DIFFUSE_COMPONENT 1
#define GLOSSY_COMPONENT 2
#define SPECULAR_COMPONENT 4

#define DIFFUSE_INDEX 0
#define GLOSSY_INDEX 1
#define SPECULAR_INDEX 2  // log2 of COMPONENTS

/* Convert index to component value */

#define XXDF_INDEXTOCOMP(i) (1<<(i))


#define XXDFCOMPONENTS 3  /* There are three components */

#define NO_COMPONENTS 0
#define ALL_COMPONENTS (DIFFUSE_COMPONENT|GLOSSY_COMPONENT|SPECULAR_COMPONENT)

typedef char XXDFFLAGS;



/* Bsdf's have 6 components : 3 for reflection, 3 for transmission */

#define BRDF_DIFFUSE_COMPONENT 0x01
#define BRDF_GLOSSY_COMPONENT 0x02
#define BRDF_SPECULAR_COMPONENT 0x04
#define BTDF_DIFFUSE_COMPONENT 0x08
#define BTDF_GLOSSY_COMPONENT 0x10
#define BTDF_SPECULAR_COMPONENT 0x20

#define BSDF_DIFFUSE_COMPONENT (BTDF_DIFFUSE_COMPONENT|BRDF_DIFFUSE_COMPONENT)
#define BSDF_GLOSSY_COMPONENT (BTDF_GLOSSY_COMPONENT|BRDF_GLOSSY_COMPONENT)
#define BSDF_SPECULAR_COMPONENT (BTDF_SPECULAR_COMPONENT|BRDF_SPECULAR_COMPONENT)


#define BRDF_DIFFUSE_INDEX 0
#define BRDF_GLOSSY_INDEX 1
#define BRDF_SPECULAR_INDEX 2  // log2 of COMPONENTS
#define BTDF_DIFFUSE_INDEX 3
#define BTDF_GLOSSY_INDEX 4
#define BTDF_SPECULAR_INDEX 5  // log2 of COMPONENTS

/* Convert index to component value */

#define BSDF_INDEXTOCOMP(i) (1<<(i))


#define BSDFCOMPONENTS 6  /* There are six components */

#define NO_COMPONENTS 0
#define BSDF_ALL_COMPONENTS (BRDF_DIFFUSE_COMPONENT|BRDF_GLOSSY_COMPONENT|BRDF_SPECULAR_COMPONENT|BTDF_DIFFUSE_COMPONENT|BTDF_GLOSSY_COMPONENT|BTDF_SPECULAR_COMPONENT)


/* converts BSDFFLAGS to XXDFFLAGS */
#define GETBRDFFLAGS(bsflags) (bsflags & ALL_COMPONENTS)
#define GETBTDFFLAGS(bsflags) ((bsflags >> XXDFCOMPONENTS) & ALL_COMPONENTS)

/* converts XXDFFLAGS to BSDFFLAGS */
#define SETBRDFFLAGS(xxflags) (xxflags & ALL_COMPONENTS)
#define SETBTDFFLAGS(xxflags) ((xxflags & ALL_COMPONENTS) << XXDFCOMPONENTS)

typedef char BSDFFLAGS;

  /* Refraction index */

typedef struct REFRACTIONINDEX
{
  float nr, ni;
} REFRACTIONINDEX;

/* Compute an approximate Geometric IOR from a complex IOR (cfr. Gr.Gems II, p289) */
float ComplexToGeometricRefractionIndex(REFRACTIONINDEX nc);

/* Calculate the ideal reflected ray direction (independent of the brdf) */
extern VECTOR IdealReflectedDirection(VECTOR *in, VECTOR *normal);
extern DVECTOR DIdealReflectedDirection(DVECTOR *in, DVECTOR *normal);


/* Calculate the perfect refracted ray direction.
 * Sets totalInternalReflection to TRUE or FALSE accordingly.
 */

extern VECTOR IdealRefractedDirection(VECTOR *in, VECTOR *normal, 
				      REFRACTIONINDEX inIndex, 
				      REFRACTIONINDEX outIndex, 
				      int *totalInternalReflection);

extern DVECTOR DIdealRefractedDirection(DVECTOR *in, DVECTOR *normal, 
					REFRACTIONINDEX inIndex, 
					REFRACTIONINDEX outIndex, 
					int *totalInternalReflection);

#ifdef __cplusplus
}
#endif

#endif /* _XXDF_H_ */


