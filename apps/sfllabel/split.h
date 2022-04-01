/* Source file for utility that creates a signed distance field */
#ifndef __R3_SFLLABEL_SPLIT_H__
#define __R3_SFLLABEL_SPLIT_H__



////////////////////////////////////////////////////////////////////////
// NAMESPACE
////////////////////////////////////////////////////////////////////////

namespace gaps {
  


////////////////////////////////////////////////////////////////////////
// FUNCTION DECLARATIONS
////////////////////////////////////////////////////////////////////////

int RasterizeSDF(R2Grid& grid, const R2Polygon& polygon, int end_condition = 0);



}; // end namespace



#endif
