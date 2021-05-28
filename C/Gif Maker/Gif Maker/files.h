#ifndef FILESH
#define FILESH


//Headers:
#include "linkedList.h" 

//Constsnts:

//The supported picture's endings. (supported by openCv library):
#define PICTURE_ENDING1 ".PNG"
#define PICTURE_ENDING2 ".png"

#define PICTURE_ENDING3 ".bmp"
#define PICTURE_ENDING4 ".BMP"

#define PICTURE_ENDING5 ".pbm"
#define PICTURE_ENDING6 ".PBM"

#define PICTURE_ENDING7 ".pgm"
#define PICTURE_ENDING8 ".PGM"

#define PICTURE_ENDING9 ".ppm"
#define PICTURE_ENDING10 ".PPM"

#define PICTURE_ENDING11 ".sr"
#define PICTURE_ENDING12 ".SR"

#define PICTURE_ENDING13 ".ras"
#define PICTURE_ENDING14 ".RAS"

#define PICTURE_ENDING15 ".jpeg"
#define PICTURE_ENDING16 ".JPEG"

#define PICTURE_ENDING17 ".jpe"
#define PICTURE_ENDING18 ".JPE"

#define PICTURE_ENDING19 ".jp2"
#define PICTURE_ENDING20 ".JP2"

#define PICTURE_ENDING21 ".tiff"
#define PICTURE_ENDING22 ".TIFF"

#define PICTURE_ENDING23 ".tif"
#define PICTURE_ENDING24 ".TIF"

#define PICTURE_ENDING25 ".jpg"
#define PICTURE_ENDING26 ".JPG"


//The signatureof of the gif maker file file.
#define GIF_MAKER_FILE_SIGNATURE "Gif maker's signature" //The gif maker file's signature of the saved file.
#define SIGNATURE_LEN 22 //The len of the gif maker' file.


//Functions:
int isPicturePath(char* path);
void saveGif(gif* pGif);
void loadGifProject(gif* pGif);
void mainGifProjectLoading(FILE* file, gif* pGif);


#endif