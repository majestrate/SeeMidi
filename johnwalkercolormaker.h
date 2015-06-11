#ifndef JOHNWALKERCOLORMAKER_H
#define JOHNWALKERCOLORMAKER_H

#include <stdio.h>
#include <math.h>



    /* White point chromaticities. */

#define IlluminantC     0.3101, 0.3162	    	/* For NTSC television */
#define IlluminantD65   0.3127, 0.3291	    	/* For EBU and SMPTE */
#define IlluminantE 	0.33333333, 0.33333333  /* CIE equal-energy illuminant */

    /*  Gamma of nonlinear correction.

    See Charles Poynton's ColorFAQ Item 45 and GammaFAQ Item 6 at:

       http://www.poynton.com/ColorFAQ.html
       http://www.poynton.com/GammaFAQ.html

*/

#define GAMMA_REC709	0		/* Rec. 709 */
class JohnWalkerColorMaker{
    public:
        double bbTemp = 5000;
        JohnWalkerColorMaker(int it, double &ir,double &ig,double &ib);
        double bb_spectrum(double wavelength);
        void spectrum_to_xyz(double *x, double *y, double *z);
        void norm_rgb(double *r, double *g, double *b);

        void gamma_correct_rgb(const struct colourSystem *cs, double *r, double *g, double *b);
        void gamma_correct(const struct colourSystem *cs, double *c);
        int constrain_rgb(double *r, double *g, double *b);
        int inside_gamut(double r, double g, double b);
        void xyz_to_rgb(struct colourSystem *cs,
                        double xc, double yc, double zc,
                        double *r, double *g, double *b);
        void xy_to_upvp(double xc, double yc, double *up, double *vp);
        void upvp_to_xy(double up, double vp, double *xc, double *yc);
        static void run(int it, double &ir,double &ig,double &ib);


};
#endif // JOHNWALKERCOLORMAKER_H


