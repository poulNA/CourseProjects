#include "StickerSheet.h"
#include "Image.h"
using cs225::HSLAPixel;
using cs225::PNG;


StickerSheet::StickerSheet(Image& picture, unsigned max){
    size_=max;
    base_ = &picture;
    base_->x=picture.x;
    base_->y=picture.y;
    

}

StickerSheet::~StickerSheet(){
    for(Image* image : stickers_){
        delete image;
    }
    delete base_;
}

StickerSheet::StickerSheet(const StickerSheet& other){
    base_ = new Image(*(other.base_));
    for(Image* image: other.stickers_){
        Image* to_add = new Image(*image);
        to_add->x = image->x;
        to_add->y = to_add->y;
        stickers_.push_back(to_add);
    }
    size_=other.size_;
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y){
    if(stickers_.size() == size_){
        return -1;
    }
    Image* new_image = new Image(sticker);
    new_image->x = x;
    new_image->y=y;
    stickers_.push_back(new_image);
    return stickers_.size()-1;
}

void StickerSheet::changeMaxStickers(unsigned max){
    
    if(max<stickers_.size()){

        for(size_t i = max; i<stickers_.size();++i){
            delete stickers_.at(i);
        }
        stickers_.erase(stickers_.begin()+max,stickers_.end());
    }

    size_=max;
}

Image* StickerSheet::getSticker(unsigned index){
    if(index>=size_||stickers_.size()<=index){
        return NULL;
    }
    return stickers_.at(index);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
    if (this == &other){
        return other;
    }
    for (size_t i = 0; i < stickers_.size(); i++)
    {
        delete stickers_.at(i);
    }
    delete base_;  

    base_ = new Image(*(other.base_));
    for(Image* image: other.stickers_){
        Image* to_add = new Image(*image);
        to_add->x = image->x;
        to_add->y = to_add->y;
        stickers_.push_back(to_add);
    }
    size_=other.size_;  
    return *this;
}

void StickerSheet::removeSticker(unsigned index){
    // Image* sticker = stickers_.at(index);
    // unsigned new_height = base_->height();
    // unsigned new_width = base_width();

    for (size_t i = 0; i < stickers_.size(); i++)
    {
        if(i==index){
            delete stickers_.at(i);
            break;
        }

    }
    stickers_.erase(stickers_.begin()+index);

}

Image StickerSheet::render() const{

    
    Image to_return = *base_;
    to_return.x = base_->x;
    to_return.y = base_->y;

    unsigned height = base_->height();
    unsigned width = base_->width();
    for(Image* image: stickers_){
        if(image->y > height){
            height = image->y + image->height();
        }
        else if(image->y+image->height() > height){
            height = image->y + image->height();
        }
        if(image->x > width){
            width = image->x+image->width();
        }
        else if(image->x+image->width()>width){
            width = image->x+image->width();
        }
    }
    to_return.resize(width,height);

    for (Image* image: stickers_){
        for(unsigned x =0; x<width;++x){
            for (unsigned y=0; y<height; ++y){
                if(x>=image->x && x<image->x+image->width() && y>=image->y && y<image->y+image->height()){
                    HSLAPixel & pixel_sticker = image->getPixel(x-image->x,y-image->y);
                    HSLAPixel & base_pixel = to_return.getPixel(x,y);
                    if(pixel_sticker.a == 0){
                        continue;
                    }
                    base_pixel.h = pixel_sticker.h;
                    base_pixel.s = pixel_sticker.s;
                    base_pixel.l = pixel_sticker.l;
                }
            }
        }
    }
    return to_return;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index<0 || index >stickers_.size()){
        return false;
    }
    Image* image = stickers_.at(index);
    image->x=x;
    image->y=y;
    return true;
}


