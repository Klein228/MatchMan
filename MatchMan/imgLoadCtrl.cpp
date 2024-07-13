#include"imgLoadCtrl.h"
inline void putimageultra(int x, int y, IMAGE* img)//图像绘制函数
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

imgLoadCtrl::imgLoadCtrl(std::wstring* path, int num, POINT s, bool Isconvert,bool Iswhite)
{
	TCHAR plrpath[256];
	for (size_t i = 0; i < num; i++)
	{
		std::wstring plrpath = *path + std::to_wstring(i) + L".png";
		IMAGE* img = new IMAGE();
		loadimage(img, plrpath.c_str(), s.x, s.y);
		if (Isconvert)
		{
			IMAGE* newcvtimg = setConvert(img);
			delete	img;
			img = newcvtimg;
		}
		if (Iswhite)
		{
			IMAGE* newcvtimg = setWhite(img);
			delete	img;
			img = newcvtimg;
		}
		imgsPoint.push_back(img);
	}
}
imgLoadCtrl::~imgLoadCtrl()
{
	for (size_t i = 0; i < imgsPoint.size(); i++)
	{
		delete imgsPoint[i];
	}
}
std::vector<IMAGE*>* imgLoadCtrl::getImages()
{
	return &imgsPoint;
}
int imgLoadCtrl::getImagesNum()
{
	return imgsPoint.size();
}
void imgLoadCtrl::draw(POINT* loc, int imgNum)
{
	putimageultra(loc->x, loc->y, imgsPoint.at(imgNum));
}
IMAGE* imgLoadCtrl::setConvert(IMAGE* img)
{
	IMAGE* temp = new IMAGE(img->getwidth(), img->getheight());
	DWORD* before = GetImageBuffer(img);
	DWORD* after = GetImageBuffer(temp);
	for (size_t i = 0; i < img->getheight(); i++)
	{
		size_t k = img->getwidth() - 1;
		for (size_t j = 0; j < img->getwidth(); j++, k--)
		{
			after[i * img->getwidth() + j] = before[i * img->getwidth() + k];
		}
	}
	return temp;
}
IMAGE* imgLoadCtrl::setWhite(IMAGE* img)
{
	DWORD* buffer = GetImageBuffer(img);
	IMAGE* whiteImg = new IMAGE(img->getwidth(), img->getheight());
	DWORD* white_img_buffer = GetImageBuffer(whiteImg);
	//透明度不为0的像素设置为白色
	for (size_t i = 0; i < img->getheight(); i++)
	{
		for (size_t j = 0; j < img->getwidth(); j++)
		{
			DWORD pixel = buffer[i * img->getwidth() + j];
			BYTE r = GetBValue(pixel);
			BYTE g = GetGValue(pixel);
			BYTE b = GetRValue(pixel);
			BYTE alpha = (pixel & 0xFF000000) >> 24;
			//changeWhite
			if (alpha)
			{
				white_img_buffer[i * img->getwidth() + j] = BGR(RGB(255, 255, 255)) | (((DWORD)(BYTE)(255)) << 24);
			}
		}
	}
	return whiteImg;


}