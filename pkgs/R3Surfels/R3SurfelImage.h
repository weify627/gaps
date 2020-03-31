/* Include file for the R3 surfel image class */
#ifndef __R3__SURFEL__IMAGE__H__
#define __R3__SURFEL__IMAGE__H__



////////////////////////////////////////////////////////////////////////
// NAMESPACE 
////////////////////////////////////////////////////////////////////////

namespace gaps {



////////////////////////////////////////////////////////////////////////
// CLASS DEFINITION
////////////////////////////////////////////////////////////////////////

class R3SurfelImage {
public:
  //////////////////////////////////////////
  //// CONSTRUCTOR/DESTRUCTOR FUNCTIONS ////
  //////////////////////////////////////////

  // Constructor functions
  R3SurfelImage(const char *name = NULL);
  R3SurfelImage(const R3SurfelImage& image);

  // Destructor function
  virtual ~R3SurfelImage(void);


  ////////////////////////////
  //// PROPERTY FUNCTIONS ////
  ////////////////////////////

  // Channel access functions
  int NChannels(void) const;
  const R2Grid *Channel(int channel_index) const;

  // Camera intrinsics functions
  int ImageWidth(void) const;
  int ImageHeight(void) const;
  const R2Point& ImageCenter(void) const;
  RNLength XFocal(void) const;
  RNLength YFocal(void) const;
  RNAngle XFOV(void) const;
  RNAngle YFOV(void) const;
  
  // Camera extrinsics functions
  const R3CoordSystem& Pose(void) const;
  const R3Point& Viewpoint(void) const;
  R3Vector Towards(void) const;
  const R3Vector& Up(void) const;
  const R3Vector& Right(void) const;

  // Timestamp property functions
  RNScalar Timestamp(void) const;

  // Name property functions
  const char *Name(void) const;

  // User data property functions
  RNFlags Flags(void) const;
  void *Data(void) const;


  //////////////////////////
  //// ACCESS FUNCTIONS ////
  //////////////////////////

  // Scene access functions
  R3SurfelScene *Scene(void) const;
  int SceneIndex(void) const;

  // Scan access functions (can be NULL)
  R3SurfelScan *Scan(void) const;


  /////////////////////////////////////////
  //// PROPERTY MANIPULATION FUNCTIONS ////
  /////////////////////////////////////////

  // Channel manipulation functions
  virtual void InsertChannel(int channel_index, const R2Grid& channel);
  virtual void SetChannel(int channel_index, const R2Grid& channel);
  virtual void RemoveChannel(int channel_index);
  
  // Pose manipulation functions
  virtual void SetPose(const R3CoordSystem& pose);
  virtual void SetViewpoint(const R3Point& viewpoint);
  virtual void SetOrientation(const R3Vector& towards, const R3Vector& up);
  virtual void SetFocalLengths(RNLength focal_length);
  virtual void SetXFocal(RNLength focal_length);
  virtual void SetYFocal(RNLength focal_length);

  // Timestamp manipulation functions
  virtual void SetTimestamp(RNScalar timestamp);

  // Name manipulation functions
  virtual void SetName(const char *name);

  // Image metadata manipulation functions
  virtual void SetImageDimensions(int width, int height);
  virtual void SetImageCenter(const R2Point& center);

  // Set scan (if surfels captured with image)
  virtual void SetScan(R3SurfelScan *scan);
  
  // User data manipulation functions
  virtual void SetFlags(RNFlags flags);
  virtual void SetData(void *data);


  /////////////////////////////////////////////
  //// COORDINATE TRANSFORMATION FUNCTIONS ////
  /////////////////////////////////////////////

  // Transform between coordinate systems
  R3Point TransformFromWorldToCamera(const R3Point& world_position) const;
  R2Point TransformFromWorldToImage(const R3Point& world_position) const;
  R3Point TransformFromCameraToWorld(const R3Point& camera_position) const;
  R2Point TransformFromCameraToImage(const R3Point& camera_position) const;
  R3Point TransformFromImageToWorld(const R2Point& image_position) const;
  R3Point TransformFromImageToCamera(const R2Point& image_position, RNLength depth = -1) const;

  // Check if pixel coordinates are within image bounds
  RNBoolean ContainsImagePosition(const R2Point& image_position) const;

  
  ///////////////////////////
  //// DISPLAY FUNCTIONS ////
  ///////////////////////////

  // Draw function
  virtual void Draw(RNFlags flags = R3_SURFEL_DEFAULT_DRAW_FLAGS) const;

  // Print function
  virtual void Print(FILE *fp = NULL, const char *prefix = NULL, const char *suffix = NULL) const;

  // Render image by projecting surfels into image
  int RenderImage(R2Image *color_image = NULL, R2Grid *depth_image = NULL,
    R2Grid *xnormal_image = NULL, R2Grid *ynormal_image = NULL, R2Grid *znormal_image = NULL,
    R2Grid *label_image = NULL, R2Grid *object_image = NULL,
    R2Grid *node_image = NULL, R2Grid *block_image = NULL) const;

  
  ////////////////////////////////////////////////////////////////////////
  // INTERNAL STUFF BELOW HERE
  ////////////////////////////////////////////////////////////////////////

  // For backward compatibility
  R2Point ImagePosition(const R3Point& world_position) const;

protected:
  // Internal data
  friend class R3SurfelScene;
  friend class R3SurfelScan;
  R3SurfelScene *scene;
  int scene_index;
  R3SurfelScan *scan;
  RNArray<R2Grid *> channels;
  R3CoordSystem pose;
  RNScalar timestamp;
  int image_width, image_height;
  R2Point image_center;
  RNLength xfocal, yfocal;
  char *name;
  RNFlags flags;
  void *data;
};



////////////////////////////////////////////////////////////////////////
// Channel indices
////////////////////////////////////////////////////////////////////////

enum {
  R3_SURFEL_DEPTH_CHANNEL,
  R3_SURFEL_USER_CHANNELS,
  R3_SURFEL_NUM_CHANNELS
};


  
////////////////////////////////////////////////////////////////////////
// INLINE FUNCTION DEFINITIONS
////////////////////////////////////////////////////////////////////////

inline int R3SurfelImage::
NChannels(void) const
{
  // Return the number of channels (including NULL pointers)
  return channels.NEntries();
}

  

inline const R2Grid *R3SurfelImage::
Channel(int channel_index) const
{
  // Return the channel (may be NULL)
  return channels[channel_index];
}

  

inline RNLength R3SurfelImage::
XFocal(void) const
{
  // Return horizontal focal length in pixels
  return xfocal;
}



inline RNLength R3SurfelImage::
YFocal(void) const
{
  // Return vertical focal length in pixels
  return yfocal;
}



inline RNLength R3SurfelImage::
XFOV(void) const
{
  // Return half-angle for horizontal field of view
  if (xfocal <= 0) return 0.0;
  return atan(0.5*image_width/xfocal);
}



inline RNLength R3SurfelImage::
YFOV(void) const
{
  // Return half-angle for vertical field of view
  if (yfocal <= 0) return 0.0;
  return atan(0.5*image_height/yfocal);
}



inline int R3SurfelImage::
ImageWidth(void) const
{
  // Return image width
  return image_width;
}



inline int R3SurfelImage::
ImageHeight(void) const
{
  // Return image height
  return image_height;
}



inline const R2Point& R3SurfelImage::
ImageCenter(void) const
{
  // Return image center
  return image_center;
}



inline const R3CoordSystem& R3SurfelImage::
Pose(void) const
{
  // Return pose 
  return pose;
}



inline const R3Point& R3SurfelImage::
Viewpoint(void) const
{
  // Return pose viewpoint
  return pose.Origin();
}



inline R3Vector R3SurfelImage::
Towards(void) const
{
  // Return pose towards vector
  return -(pose.Axes().Axis(RN_Z));
}



inline const R3Vector& R3SurfelImage::
Up(void) const
{
  // Return pose up vector
  return pose.Axes().Axis(RN_Y);
}



inline const R3Vector& R3SurfelImage::
Right(void) const
{
  // Return pose right vector
  return pose.Axes().Axis(RN_X);
}



inline RNScalar R3SurfelImage::
Timestamp(void) const
{
  // Return timestamp
  return timestamp;
}



inline const char *R3SurfelImage::
Name(void) const
{
  // Return name
  return name;
}



inline RNFlags R3SurfelImage::
Flags(void) const
{
  // Return flags
  return flags;
}



inline void *R3SurfelImage::
Data(void) const
{
  // Return user data
  return data;
}



inline R3SurfelScene *R3SurfelImage::
Scene(void) const
{
  // Return scene this image is in
  return scene;
}



inline int R3SurfelImage::
SceneIndex(void) const
{
  // Return index in list of images associated with scene
  return scene_index;
}



inline R3SurfelScan *R3SurfelImage::
Scan(void) const
{
  // Return scan this image is associated (NULL if none)
  return scan;
}



inline void R3SurfelImage::
InsertChannel(int channel_index, const R2Grid& channel)
{
  // Insert a new channel
  SetChannel(channel_index, channel);
}


  
inline R2Point R3SurfelImage::
ImagePosition(const R3Point& world_position) const
{
  // DO NOT USE -- only here for backward compatibility
  // Transform 3D point from world into image coordinate system
  return TransformFromWorldToImage(world_position);
}

  

// End namespace
}


// End include guard
#endif