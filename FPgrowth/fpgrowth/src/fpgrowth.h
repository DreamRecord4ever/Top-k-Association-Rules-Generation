/*----------------------------------------------------------------------
  File    : fpgrowth.h
  Contents: fpgrowth algorithm for finding frequent item sets
  Author  : Christian Borgelt
  History : 2011.08.22 file created
            2011.09.21 available variants and modes reorganized
            2012.06.20 function fpg_adjust() added (consistency check)
----------------------------------------------------------------------*/
#ifndef __FPGROWTH__
#define __FPGROWTH__
#include "tract.h"
#ifndef ISR_CLOMAX
#define ISR_CLOMAX
#endif
#include "report.h"

/*----------------------------------------------------------------------
  Preprocessor Definitions
----------------------------------------------------------------------*/
/* --- fpgrowth variants --- */
#define FPG_SIMPLE    0         /* simple  nodes (parent/link) */
#define FPG_COMPLEX   1         /* complex nodes (children/sibling) */
#define FPG_SINGLE    2         /* top-down processing on single tree */
#define FPG_TOPDOWN   3         /* top-down processing of the tree */

/* --- operation modes --- */
#define FPG_FIM16     0x0100    /* use 16 items machine (bit rep.) */
#define FPG_PERFECT   0x0200    /* perfect extension pruning */
#define FPG_REORDER   0x0400    /* reorder items in cond. databases */
#define FPG_TAIL      0x0800    /* head union tail pruning */
#define FPG_DEFAULT   (FPG_FIM16|FPG_PERFECT|FPG_REORDER|FPG_TAIL)
#define FPG_VERBOSE   INT_MIN   /* verbose message output */

/*----------------------------------------------------------------------
  Functions
----------------------------------------------------------------------*/
extern void fpg_adjust (int target, int eval,
                        int *algo, int *mode, int *pack, int *mrep);
extern int  fpgrowth   (TABAG *tabag, int target, int algo, int mode,
                        SUPP supp, int eval, double minval,
                        ISREPORT *report);
#endif
