#pragma once
#include<graphics.h>
#include<string>
#include<vector>
class imgLoadCtrl
{
public:
	imgLoadCtrl(std::wstring* path, int num, POINT s, bool Isconvert, bool Iswhite);
	~imgLoadCtrl();
	std::vector<IMAGE*>* getImages();
	int getImagesNum();
	void draw(POINT* loc, int imgNum);
private:
	IMAGE* setConvert(IMAGE* img);
	IMAGE* setWhite(IMAGE* img);
	std::vector<IMAGE*> imgsPoint;
};