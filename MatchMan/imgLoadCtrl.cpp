#include"imgLoadCtrl.h"
inline void putimageultra(int x, int y, IMAGE* img)//ͼ����ƺ���
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

imgLoadCtrl::imgLoadCtrl(std::wstring* path, int num, POINT s)
{
	TCHAR plrpath[256];
	img_num = num;
	for (size_t i = 0; i < num; i++)
	{
		std::wstring plrpath = *path + std::to_wstring(i) + L".png";
		IMAGE* img = new IMAGE();
		loadimage(img, plrpath.c_str(), s.x, s.y);
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
void imgLoadCtrl::setConvert()
{
	std::vector<IMAGE*> temp_img_vector;
	for (size_t n = 0; n < img_num; n++)
	{
		IMAGE* img = imgsPoint.at(n);
		int w = img->getwidth();
		int h = img->getheight();
		IMAGE* temp = new IMAGE(w, h);
		DWORD* before = GetImageBuffer(img);
		DWORD* after = GetImageBuffer(temp);
		//��תͼƬ����
		for (size_t i = 0; i < h; i++)
		{
			size_t k = w - 1;
			for (size_t j = 0; j < w; j++, k--)
			{
				after[i * w + j] = before[i * w + k];
			}
		}
		//��ת����ͼƬ���������
		temp_img_vector.push_back(temp);
		delete img;
	}
	imgsPoint = temp_img_vector;
}
void imgLoadCtrl::setWhite()
{
	std::vector<IMAGE*> temp_img_vector;
	for (size_t n = 0; n < img_num; n++)
	{
		IMAGE* img = imgsPoint.at(n);
		DWORD* buffer = GetImageBuffer(img);
		IMAGE* whiteImg = new IMAGE(img->getwidth(), img->getheight());
		DWORD* white_img_buffer = GetImageBuffer(whiteImg);
		//͸���Ȳ�Ϊ0����������Ϊ��ɫ
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
		//��ͼƬ�����µ�����
		temp_img_vector.push_back(whiteImg);
		delete img;
	}
	//��ͼ�ͷ��ڴ沢�������ݼ���
	imgsPoint = temp_img_vector;
}