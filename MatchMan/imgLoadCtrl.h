#pragma once
#include<graphics.h>
#include<string>
#include<vector>
class imgLoadCtrl
{
public:
	imgLoadCtrl(std::wstring* path, int num, POINT s);
	~imgLoadCtrl();
	std::vector<IMAGE*>* getImages();
	int getImagesNum();
	void draw(POINT* loc, int imgNum);
	void setWhite();
	void setConvert();
	void setCoverwith(IMAGE* cov_img, float rate);
private:
	size_t img_num;
	std::vector<IMAGE*> imgsPoint;
	POINT image_size;
};