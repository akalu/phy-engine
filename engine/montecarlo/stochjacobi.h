/* stochjacobi.h: generic stochastic Jacobi iteration implementation */

#ifndef _STOCHJACOBI_H_
#define _STOCHJACOBI_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Generic routine for Stochastic Jacobi iterations:
 * - nr_rays: nr of rays to use
 * - GetRadiance: routine returning radiance (total or unshot) to be 
 * propagated for a given element, or NULL if not radiance propagation is
 * required.
 * - GetImportance: same, but for importance.
 * - Update: routine updating total, unshot and source radiance and/or
 * importance based on result received during the iteration. 
 *
 * The operation of this routine is further controlled by global parameters
 * - mcr.do_control_radiosity: perform constant control variate variance reduction
 * - mcr.bidirectional_transfers: for using lines bidirectionally
 * - mcr.importance_driven: importance-driven radiance propagation
 * - mcr.radiance_driven: radiance-driven importance propagation
 * - hierarchy.do_h_meshing, hierarchy.clustering: hierarchical refinement/clustering
 *
 * This routine updates global ray counts and total/unshot power/importance statistics.
 *
 * CAVEAT: propagate either radiance or importance alone. Simultaneous
 * propagation of importance and radiance does not work yet.
 */
extern void DoStochasticJacobiIteration(long nr_rays,
					COLOR *(*GetRadiance)(ELEMENT *),
					float (*GetImportance)(ELEMENT *),
					void Update(ELEMENT *elem, double w));

#ifdef __cplusplus
}
#endif

#endif /* _STOCHJACOBI_H_ */
