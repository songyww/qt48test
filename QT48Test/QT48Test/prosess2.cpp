#include "prosess2.h"
#include"qimage.h"
#include"qt_windows.h"
#include"qmath.h"
#include "ui_qt48test.h"
#include<ArcSDK.h>
#include"picture.h"
prosess2::prosess2(QObject *parent)
	: QObject(parent)
{

}

prosess2::~prosess2()
{

}

#define PI 3.1415926
double pix[2000][2000];//当前分析图像的像素
double feature_color[3][12];//待检索图像的颜色特征
double feature_color_1[3][12]; //当前分析图像的颜色特征
double feature_shape[8];//待检索图像的形状特征
double feature_shape_1[8]; //当前分析图像的形状特征
int counts;//检索库图像计数器
QString* temp[100];//检索库中图像路径
QString temp_1[100];//临时存放检索库中图像路径
QString strfile;//待检索图像的路径
QString m_strPath;//检索库路径	
bool open_pic;//设置待检索图像标志位
bool dir;//设置检索库标志位
bool color;//各种颜色方法是否使用过标志位
bool shape;//形状方法是否使用过标志位
picture image;//基于颜色特征
picture image_color_temp;
picture image_color_1;
picture image_color_2;
picture image_color_3;
picture image_shape;
picture image_shape_temp;
int tempi;//临时的检索库图像计数器
int c_per;//颜色所占百分比
int s_per;//形状所占百分比

void prosess2::torque(QString pathfile,int mode)
{	
	
   /* CBitmap hbmp;
	HBITMAP hbitmap; 
	int R,G,B;
	//装载资源
    hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),pathfile,IMAGE_BITMAP,
		           0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	hbmp.Attach(hbitmap);	
	//获取图像格式
	BITMAP bm;  
	hbmp.GetBitmap(&bm);    
	//创建临时的内存DC对象
	CDC dcMem;	
	dcMem.CreateCompatibleDC(GetDC());	
	dcMem.SelectObject(hbmp);*/

	QImage bm;
	int width=bm.width();
	int height=bm.height();
	QRgb clr;
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			//该函数检索指定坐标点的像素的RGB颜色值
			clr=bm.pixel(x,y);
			int R=qRed(clr);
			int G=qGreen(clr);
			int B=qBlue(clr);
			pix[x][y]=0.299*R+0.587*G+0.114*B;
		}
	}
	//大津法求阈值
	int index_max;//最佳阈值
	double g_max;
	g_max=0;
	for(int index=0;index<256;index++)
	{
		double c0,c1,sum_0,sum_1;
		double w0,w1,u0,u1,g;
		c0=c1=sum_0=sum_1=w0=w1=u0=u1=g=0;
		for(int x=0;x<width;x++)
		{
			for(int y=0;y<height;y++)
			{
				if(pix[x][y]<index)
				{
				sum_0=sum_0+pix[x][y];//统计背景灰度值
				c0++;                               //统计背景像素值
				}
				else
				{
				sum_1=sum_1+pix[x][y];//统计前景灰度值
				c1++;                               //统计前景像素值
				}
			}
		}
		w0=c0/(c0+c1);//背景像素所占比例
		w1=c1/(c0+c1);//前景像素所占比例
		if(c0==0)
			u0=0;
		else
			u0=sum_0/c0;//背景平均灰度值
		if(c1==0)
			u1=0;
		else
			u1=sum_1/c1;//前景平均灰度值
		g=w0*w1*(u0-u1)*(u0-u1);
		if(g>g_max)//保存最佳阈值
		{
			g_max=g;
			index_max=index;
		}
	}
	//根据所求阈值进行阈值分割
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			if(pix[x][y]<index_max)
				pix[x][y]=0;
			else
				pix[x][y]=1;
		}
	}

	//0+0阶矩
	double m00=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m00+=pix[x][y];
	//1+0阶矩
	double m10=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m10+=(x+1)*pix[x][y];
    //0+1阶矩
	double m01=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m01+=(y+1)*pix[x][y];
	//1+1阶矩
	double m11=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m11+=(y+1)*(x+1)*pix[x][y];
	//2+0阶矩
	double m20=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m20+=(x+1)*(x+1)*pix[x][y];
	//0+2阶矩
	double m02=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m02+=(y+1)*(y+1)*pix[x][y];
	//3+0阶矩
	double m30=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m30+=(x+1)*(x+1)*(x+1)*pix[x][y];
	//0+3阶矩
	double m03=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m03+=(y+1)*(y+1)*(y+1)*pix[x][y];
	//1+2阶矩
	double m12=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m12+=(x+1)*(y+1)*(y+1)*pix[x][y];
	//2+1阶矩
	double m21=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m21+=(x+1)*(x+1)*(y+1)*pix[x][y];

	//求图像的区域重心
	double xbar,ybar;
	xbar=(double)m10/m00;
	ybar=(double)m01/m00;

	//求中心矩
	double eta11,eta20,eta02,eta30,eta03,eta21,eta12;
	eta11=(m11-ybar*m10)/(m00*m00);
	eta20=(m20-xbar*m10)/(m00*m00);
	eta02=(m02-ybar*m01)/(m00*m00);
	eta30=(m30-3*xbar*m20+2*xbar*xbar*m10)/(m00*m00*sqrt(m00));
	eta03=(m03-3*ybar*m02+2*ybar*ybar*m01)/(m00*m00*sqrt(m00));
	eta21=(m21-2*xbar*m11-ybar*m20+2*xbar*xbar*m01)/(m00*m00*sqrt(m00));
	eta12=(m12-2*ybar*m11-xbar*m02+2*ybar*ybar*m10)/(m00*m00*sqrt(m00));

    //HU不变矩
	double phi[8];
	phi[0]=eta20+eta02;
	phi[1]=(eta20-eta02)*(eta20-eta02)+(4*eta11*eta11);
	phi[2]=((eta30-3*eta12)*(eta30-3*eta12))+((3*eta21-eta03)*(3*eta21-eta03));
	phi[3]=((eta30+eta12)*(eta30+eta12))+((eta21+eta03)*(eta21+eta03));
	phi[4]=(eta30-3*eta12)*(eta30+eta12)*((eta30+eta12)*(eta30+eta12)-3*(eta21+eta03)*(eta21+eta03)+
		        (3*eta21-eta03)*(eta21+eta03)*(3*(eta30+eta12)*(eta30+eta12)-(eta21+eta03)*(eta21+eta03)));
	phi[5]=(eta20-eta02)*((eta30+eta12)*(eta30+eta12)-(eta21+eta03)*(eta21+eta03))+
		        4*eta11*(eta30+eta12)*(eta21+eta03);
	phi[6]=(3*eta21-eta03)*(eta30+eta12)*((eta30+eta12)*(eta30+eta12)-3*(eta21+eta03)*(eta21+eta03))+
		        (3*eta12-eta30)*(eta21+eta03)*(3*(eta30+eta12)*(eta30+eta12)-(eta21+eta03)*(eta21+eta03)); 
	//图像离心率
	phi[7]=((eta20-eta02)*(eta20-eta02)+4*eta11*eta11)/((eta20+eta02)*(eta20+eta02));
if(mode==1)
	for(int i=0;i<8;i++)
	{
		phi[i]=fabs(log(fabs(phi[i])));
		feature_shape[i]=phi[i];
	}
else
	for(int i=0;i<8;i++)
	{
		phi[i]=fabs(log(fabs(phi[i])));
		feature_shape_1[i]=phi[i];
	}
}

int mymax(int a,int b,int c)//寻找最大
{
	int m;
	if(a>b)
		m=a;
	else
		m=b;
	if(m<c)
		m=c;
	return m;
}

int mymin(int a,int b,int c)//寻找最小
{
	int m;
	if(a<b)
		m=a;
	else 
		m=b;
	if(m>c)
		m=c;
	return m;
}


void RGBToHSV(int r,int g,int b,double *h,double *s,double *v)
{
	*h=acos((r-g+r-b)/(2.0*sqrtf((float)(r-g)*(r-g)+(float)(r-b)*(g-b))));
	if(b>g)
		*h=2*PI-*h;
    *s=(mymax(r,g,b)-mymin(r,g,b))/(float)mymax(r,g,b);
	*v=mymax(r,g,b)/255.0;
}

/*******************************************************************************
结果处理及显示
*********************************************************************************/
void prosess2::sort()
{
	int  picnum=1009;//图像显示控件的ID号
		QString tp;//图像路径
		double  num;//图像与待检索图像的距离
		//图像相似度排序
		for(int i=0;i<counts;i++)//综合特征相似度
		{
			image.num[i]=(c_per*image_color_temp.num[i]+s_per*image_shape_temp.num[i])/100;
			image.tp[i]=image_color_temp.tp[i];
		}
		for(int i=0;i<counts;i++)
		{
			for(int j=i+1;j<counts;j++)
			{
				if(image.num[i]>image.num[j])
				{
					tp=image.tp[i];
					num=image.num[i];
					image.tp[i]=image.tp[j];
					image.num[i]=image.num[j];
					image.tp[j]=tp;
					image.num[j]=num;
				}}}
		//显示前十个相似度最高的图像
		for(int i=0;i<10&&picnum<=1018;i++)
		{
			//ShowPic(image.tp[i],picnum);
			picnum++;
		}
	
}

/***********************************************************************************
计算颜色直方图
pathfile为图像的路径，mode为模式状态位，为1时，表示计算的是待检索图像，
为2时，表示计算的是检索库中的图像
************************************************************************************/
void prosess2::general(QString pathfile,int mode)
{	
    //CBitmap hbmp;
	//HBITMAP hbitmap; 
	//装载资源
  //  hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),pathfile,IMAGE_BITMAP,
		        //   0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	//hbmp.Attach(hbitmap);	
	//获取图像格式
	//BITMAP bm;  
	//hbmp.GetBitmap(&bm);    
	QImage bm;
	bm.load( pathfile,0);
	//创建临时的内存DC对象
	//CDC dcMem;	
	//dcMem.CreateCompatibleDC(GetDC());	
	//dcMem.SelectObject(hbmp);
	int width=bm.width();
	int height=bm.height();
	int totalnum= height*width;
	//初始化
	long m_graph[3][12];
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
		{
		   m_graph[i][j]=0;
		   if(mode==1)
			   feature_color[i][j]=0.0;
		   else
			   feature_color_1[i][j]=0.0;
		}
	COLORREF color;
	double h=0,s=0,v=0;
	//计算颜色直方图
	for(long y=0;y<height;y++)
	{	
		for(long x=0;x<width;x++)
		{			
			//color=dcMem.GetPixel(x,y);//
			color=bm.pixel(x,y);
			//颜色空间转换
			RGBToHSV(GetRValue(color),GetGValue(color),GetBValue(color),&h,&s,&v);
		    int result_h=(int)(6*h/PI);
			if( result_h ==12)
				m_graph[0][11]++;
			else
        	    m_graph[0][result_h]++;
            int result_s=(int)(s*12);
			if( result_s ==12)
				m_graph[1][11]++;
			else
			    m_graph[1][result_s]++;
            int result_v=(int)(v*12);
			if( result_v ==12)
				m_graph[2][11]++;
			else
			    m_graph[2][result_v]++;
		}
	}
	//保存颜色直方图
	if(mode==1)
	{
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
			feature_color[i][j]=((float)m_graph[i][j])/((float)totalnum);
	}
	else
	{
	for(int i=0;i<3;i++)
		for(int j=0;j<12;j++)
			feature_color_1[i][j]=((float)m_graph[i][j])/((float)totalnum);
	}
}

void prosess2::Shape_SeekImage()
{
	for(int count=0; count<counts; count++)
		temp_1[count] = *temp[count];
	if(image_shape_temp.strfile_old==strfile&&image_shape_temp.m_strPath_old==m_strPath)
			shape=1;//此检索库下的此检索图像已经用此方法计算过
	else
			shape=0;
	for(int pic=0; pic<counts; pic++)//逐个分析检索库中图像
	{
		if(shape==0)
		{
		torque(temp_1[pic],2);//提取检索的第N幅图的不变矩
		double dis=0;//第N幅图与待检索图像的距离
		double dis_temp=0;
		//显示正在检索的第N幅图与待检索图像的距离
    	for(int i=0;i<8;i++)
			dis+=fabs((feature_shape_1[i]-feature_shape[i])/fabs(feature_shape[i]));
		image_shape_temp.tp[pic]=temp_1[pic];//保存第N幅图路径
		image_shape_temp.num[pic]=dis;//保存第N幅图与待检索图像的距离
		}
		//ShowPic(temp_1[pic],IDC_VIEW1);
	}
	if(shape==0)//若本方法为第一次计算，则保存相似度计算结果
		image_shape=image_shape_temp;
	else//若本方法已经计算过，则读取相似度计算结果
		image_shape_temp=image_shape;
	//检索过的待检索图像及检索库路径更新
	image_shape_temp.m_strPath_old=m_strPath;
	image_shape_temp.strfile_old=strfile;
}
/**************************************************************************************
基于颜色特征的相似度计算函数
***************************************************************************************/
void prosess2::Color_SeekImage()
{
	for(int count=0; count<counts; count++)
		temp_1[count] = *temp[count];
	//switch(c_method)
	//{
	//case 1:
		if(image_color_1.strfile_old==strfile&&image_color_1.m_strPath_old==m_strPath)
			color=1;//此检索库下的此检索图像已经用此方法计算过
		else
			color=0;
	//case 2:
		//if(image_color_2.strfile_old==strfile&&image_color_2.m_strPath_old==m_strPath)
		//	color=1;//此检索库下的此检索图像已经用此方法计算过
		//else
		//	color=0;
		//break;
	//case 3:
	//	if(image_color_3.strfile_old==strfile&&image_color_3.m_strPath_old==m_strPath)
		//	color=1;//此检索库下的此检索图像已经用此方法计算过已经用此方法计算过
	//	else
		//	color=0;
		//break;
	//}
	for(int pic=0; pic<counts; pic++)//逐个分析检索库中图像
	{
		if(color==0)
		{
			//switch(c_method)
			//{
			//case 1:
			general(temp_1[pic],2);//提取检索的第N幅图的颜色直方图
			break;
			/*case 2:
			succession(temp_1[pic],2);//提取检索的第N幅图的累计直方图
			break;
			case 3:
			centerM(temp_1[pic],2);//提取检索的第N幅图的颜色矩
			break;
			}*/
			double dis=0;//第N幅图与待检索图像的距离
			double dis_temp=0;
			//计算正在检索的第N幅图与待检索图像的距离
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<12;j++)
					dis_temp+=(feature_color_1[i][j]-feature_color[i][j])*(feature_color_1[i][j]-feature_color[i][j]);
				dis+=sqrt((double)dis_temp);
				dis_temp=0;
			}
			image_color_temp.tp[pic]=temp_1[pic];//保存第N幅图路径
			image_color_temp.num[pic]=dis;//保存第N幅图与待检索图像的距离
		}
		//ShowPic(temp_1[pic],IDC_VIEW1);
	}
	/*switch(c_method)
	{
	case 1:*/
		if(color==0)//若本方法为第一次计算，则保存相似度计算结果
		{
			image_color_1=image_color_temp;
			sort();			
		}
		else//若本方法已经计算过，则读取相似度计算结果
		{
			image_color_temp=image_color_1;
			sort();
		}
		//检索过的待检索图像及检索库路径更新
		image_color_1.m_strPath_old=image_color_temp.m_strPath_old=m_strPath;
		image_color_1.strfile_old=image_color_temp.strfile_old=strfile;
	/*case 2:
		if(color==0)
		{
			image_color_2=image_color_temp;
			sort();
		}
		else
		{
			image_color_temp=image_color_2;
			sort();
		}
		image_color_2.m_strPath_old=image_color_temp.m_strPath_old=m_strPath;
		image_color_2.strfile_old=image_color_temp.strfile_old=strfile;
		break;
	case 3:
		if(color==0)
		{
			image_color_3=image_color_temp;
			sort();
		}
		else
		{
			image_color_temp=image_color_3;
			sort();
		}
		image_color_3.m_strPath_old=image_color_temp.m_strPath_old=m_strPath;
		image_color_3.strfile_old=image_color_temp.m_strPath_old=strfile;
		break;
	}*/
}

void prosess2 ::jiansuo()
{

	QString strfile("E:\\fen1");
	torque(strfile,1);
	Shape_SeekImage();
	general(strfile,1);
	Color_SeekImage();
	

}
