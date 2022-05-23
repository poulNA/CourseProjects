#include "Image.h"
#include <math.h>

using cs225::PNG;
using cs225::HSLAPixel;

void Image::darken(){
    for(unsigned x=0;x<PNG::width(); ++x){
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.l-=0.1;
            if(pixel.l<0){
                pixel.l =0;
            }
        }
    }
}

void Image::darken(double amount){
    for(unsigned x=0;x<PNG::width(); ++x){
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.l-=amount;
            if(pixel.l<0){
                pixel.l =0;
            }
        }
    }
}

void Image::desaturate(){
    for(unsigned x=0;x<PNG::width(); ++x){
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.s-=0.1;
            if(pixel.s<0){
                pixel.s=0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned x=0;x<PNG::width(); ++x){
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.s-=amount;
            if(pixel.s<0){
                pixel.s=0;
            }
        }
    }
}

void Image::grayscale(){
    for (unsigned x = 0; x < PNG::width(); x++) {
    for (unsigned y = 0; y < PNG::height(); y++) {
      HSLAPixel & pixel = PNG::getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::illinify(){
    for(unsigned x=0;x<PNG::width();++x){
        for (unsigned y =0;y<PNG::height();++y){
            HSLAPixel & pixel= PNG::getPixel(x,y);
            double diff_blue = pixel.h - 216;
            if(diff_blue<0){
                diff_blue=-diff_blue;
            }
            double diff_orange = pixel.h - 11;
            if(diff_orange<0){
                diff_orange=-diff_orange;
            }
            double diff2 = 371-pixel.h;
            if(diff_orange>diff2){
                diff_orange = diff2;
            }      
            
            if(diff_blue<diff_orange){
                pixel.h=216;
            }else{
                pixel.h=11;
            }
        }
    }
}

void Image::lighten(){
    for(unsigned x=0;x<PNG::width(); ++x){
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.l+=0.1;
            if(pixel.l>1){
                pixel.l =1;
            }
        }
    }
}

void Image::lighten(double amount){
    for(unsigned x=0;x<PNG::width(); ++x){
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.l+=amount;
            if(pixel.l>1){
                pixel.l =1;
            }
        }
    }
}

void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < PNG::width(); x++)
    {
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            /* code */
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.h= fmod(pixel.h+degrees,360);
            if(pixel.h<0){
                pixel.h = 360+pixel.h;
            }

        }
        
    }
    
}

void Image::saturate(){
    for (unsigned x = 0; x < PNG::width(); x++)
    {
        /* code */
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.s+=0.1;
            if(pixel.s>1){
                pixel.s=1;
            }
        }
        
    }
    
}

void Image::saturate(double amount){
    for (unsigned x = 0; x < PNG::width(); x++)
    {
        /* code */
        for (unsigned y = 0; y < PNG::height(); y++)
        {
            HSLAPixel & pixel = PNG::getPixel(x,y);
            pixel.s+=amount;
            if(pixel.s>1){
                pixel.s=1;
            }
        }
        
    }
}

void Image::scale(double factor){
    unsigned int new_width = round(PNG::width()*factor);
    unsigned int new_height= round(PNG::height()*factor);
    PNG * new_image= new PNG(new_width,new_height);

    for(unsigned x=0;x<new_width;++x){
        for(unsigned y=0; y<new_height;++y){
            HSLAPixel &  new_pixel = new_image->getPixel(x,y);
            unsigned int nearest_x = int(x/factor);
            unsigned int nearest_y = int(y/factor);
            HSLAPixel & old_pixel = PNG::getPixel(nearest_x,nearest_y);
            new_pixel.h = old_pixel.h;
            new_pixel.l = old_pixel.l;
            new_pixel.s=old_pixel.s;
            new_pixel.a = old_pixel.a;
        }
    }

    PNG::operator=(*new_image);

    delete new_image;
}

void Image::scale(unsigned 	w,unsigned 	h){
    double factor;
    double height = PNG::height();
    double width = PNG::width();
    double temp1 = w/width;
    double temp2 = h/height;
    if(height*temp1 <= h && width*temp1 <=w){
        factor = temp1;
    }else{
        factor = temp2;
    }
    unsigned int new_width = round(width*factor);
    unsigned int new_height= round(height*factor);
    PNG * new_image= new PNG(new_width,new_height);

    for(unsigned x=0;x<new_width;++x){
        for(unsigned y=0; y<new_height;++y){
            HSLAPixel &  new_pixel = new_image->getPixel(x,y);
            unsigned int nearest_x = int(x/factor);
            unsigned int nearest_y = int(y/factor);
            HSLAPixel & old_pixel = PNG::getPixel(nearest_x,nearest_y);
            new_pixel.h = old_pixel.h;
            new_pixel.l = old_pixel.l;
            new_pixel.s=old_pixel.s;
            new_pixel.a = old_pixel.a;
        }
    }

    PNG::operator=(*new_image);

    delete new_image;
}


