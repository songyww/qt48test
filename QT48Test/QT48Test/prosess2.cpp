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
double pix[2000][2000];//��ǰ����ͼ�������
double feature_color[3][12];//������ͼ�����ɫ����
double feature_color_1[3][12]; //��ǰ����ͼ�����ɫ����
double feature_shape[8];//������ͼ�����״����
double feature_shape_1[8]; //��ǰ����ͼ�����״����
int counts;//������ͼ�������
QString* temp[100];//��������ͼ��·��
QString temp_1[100];//��ʱ��ż�������ͼ��·��
QString strfile;//������ͼ���·��
QString m_strPath;//������·��	
bool open_pic;//���ô�����ͼ���־λ
bool dir;//���ü������־λ
bool color;//������ɫ�����Ƿ�ʹ�ù���־λ
bool shape;//��״�����Ƿ�ʹ�ù���־λ
picture image;//������ɫ����
picture image_color_temp;
picture image_color_1;
picture image_color_2;
picture image_color_3;
picture image_shape;
picture image_shape_temp;
int tempi;//��ʱ�ļ�����ͼ�������
int c_per;//��ɫ��ռ�ٷֱ�
int s_per;//��״��ռ�ٷֱ�

void prosess2::torque(QString pathfile,int mode)
{	
	
   /* CBitmap hbmp;
	HBITMAP hbitmap; 
	int R,G,B;
	//װ����Դ
    hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),pathfile,IMAGE_BITMAP,
		           0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	hbmp.Attach(hbitmap);	
	//��ȡͼ���ʽ
	BITMAP bm;  
	hbmp.GetBitmap(&bm);    
	//������ʱ���ڴ�DC����
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
			//�ú�������ָ�����������ص�RGB��ɫֵ
			clr=bm.pixel(x,y);
			int R=qRed(clr);
			int G=qGreen(clr);
			int B=qBlue(clr);
			pix[x][y]=0.299*R+0.587*G+0.114*B;
		}
	}
	//�������ֵ
	int index_max;//�����ֵ
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
				sum_0=sum_0+pix[x][y];//ͳ�Ʊ����Ҷ�ֵ
				c0++;                               //ͳ�Ʊ�������ֵ
				}
				else
				{
				sum_1=sum_1+pix[x][y];//ͳ��ǰ���Ҷ�ֵ
				c1++;                               //ͳ��ǰ������ֵ
				}
			}
		}
		w0=c0/(c0+c1);//����������ռ����
		w1=c1/(c0+c1);//ǰ��������ռ����
		if(c0==0)
			u0=0;
		else
			u0=sum_0/c0;//����ƽ���Ҷ�ֵ
		if(c1==0)
			u1=0;
		else
			u1=sum_1/c1;//ǰ��ƽ���Ҷ�ֵ
		g=w0*w1*(u0-u1)*(u0-u1);
		if(g>g_max)//���������ֵ
		{
			g_max=g;
			index_max=index;
		}
	}
	//����������ֵ������ֵ�ָ�
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

	//0+0�׾�
	double m00=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m00+=pix[x][y];
	//1+0�׾�
	double m10=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m10+=(x+1)*pix[x][y];
    //0+1�׾�
	double m01=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m01+=(y+1)*pix[x][y];
	//1+1�׾�
	double m11=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m11+=(y+1)*(x+1)*pix[x][y];
	//2+0�׾�
	double m20=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m20+=(x+1)*(x+1)*pix[x][y];
	//0+2�׾�
	double m02=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m02+=(y+1)*(y+1)*pix[x][y];
	//3+0�׾�
	double m30=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m30+=(x+1)*(x+1)*(x+1)*pix[x][y];
	//0+3�׾�
	double m03=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m03+=(y+1)*(y+1)*(y+1)*pix[x][y];
	//1+2�׾�
	double m12=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m12+=(x+1)*(y+1)*(y+1)*pix[x][y];
	//2+1�׾�
	double m21=0;
	for(int x=0;x<width;x++)
		for(int y=0;y<height;y++)
			m21+=(x+1)*(x+1)*(y+1)*pix[x][y];

	//��ͼ�����������
	double xbar,ybar;
	xbar=(double)m10/m00;
	ybar=(double)m01/m00;

	//�����ľ�
	double eta11,eta20,eta02,eta30,eta03,eta21,eta12;
	eta11=(m11-ybar*m10)/(m00*m00);
	eta20=(m20-xbar*m10)/(m00*m00);
	eta02=(m02-ybar*m01)/(m00*m00);
	eta30=(m30-3*xbar*m20+2*xbar*xbar*m10)/(m00*m00*sqrt(m00));
	eta03=(m03-3*ybar*m02+2*ybar*ybar*m01)/(m00*m00*sqrt(m00));
	eta21=(m21-2*xbar*m11-ybar*m20+2*xbar*xbar*m01)/(m00*m00*sqrt(m00));
	eta12=(m12-2*ybar*m11-xbar*m02+2*ybar*ybar*m10)/(m00*m00*sqrt(m00));

    //HU�����
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
	//ͼ��������
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

int mymax(int a,int b,int c)//Ѱ�����
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

int mymin(int a,int b,int c)//Ѱ����С
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
���������ʾ
*********************************************************************************/
void prosess2::sort()
{
	int  picnum=1009;//ͼ����ʾ�ؼ���ID��
		QString tp;//ͼ��·��
		double  num;//ͼ���������ͼ��ľ���
		//ͼ�����ƶ�����
		for(int i=0;i<counts;i++)//�ۺ��������ƶ�
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
		//��ʾǰʮ�����ƶ���ߵ�ͼ��
		for(int i=0;i<10&&picnum<=1018;i++)
		{
			//ShowPic(image.tp[i],picnum);
			picnum++;
		}
	
}

/***********************************************************************************
������ɫֱ��ͼ
pathfileΪͼ���·����modeΪģʽ״̬λ��Ϊ1ʱ����ʾ������Ǵ�����ͼ��
Ϊ2ʱ����ʾ������Ǽ������е�ͼ��
************************************************************************************/
void prosess2::general(QString pathfile,int mode)
{	
    //CBitmap hbmp;
	//HBITMAP hbitmap; 
	//װ����Դ
  //  hbitmap=(HBITMAP)::LoadImage (::AfxGetInstanceHandle(),pathfile,IMAGE_BITMAP,
		        //   0,0,LR_LOADFROMFILE|LR_CREATEDIBSECTION);  
	//hbmp.Attach(hbitmap);	
	//��ȡͼ���ʽ
	//BITMAP bm;  
	//hbmp.GetBitmap(&bm);    
	QImage bm;
	bm.load( pathfile,0);
	//������ʱ���ڴ�DC����
	//CDC dcMem;	
	//dcMem.CreateCompatibleDC(GetDC());	
	//dcMem.SelectObject(hbmp);
	int width=bm.width();
	int height=bm.height();
	int totalnum= height*width;
	//��ʼ��
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
	//������ɫֱ��ͼ
	for(long y=0;y<height;y++)
	{	
		for(long x=0;x<width;x++)
		{			
			//color=dcMem.GetPixel(x,y);//
			color=bm.pixel(x,y);
			//��ɫ�ռ�ת��
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
	//������ɫֱ��ͼ
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
			shape=1;//�˼������µĴ˼���ͼ���Ѿ��ô˷��������
	else
			shape=0;
	for(int pic=0; pic<counts; pic++)//���������������ͼ��
	{
		if(shape==0)
		{
		torque(temp_1[pic],2);//��ȡ�����ĵ�N��ͼ�Ĳ����
		double dis=0;//��N��ͼ�������ͼ��ľ���
		double dis_temp=0;
		//��ʾ���ڼ����ĵ�N��ͼ�������ͼ��ľ���
    	for(int i=0;i<8;i++)
			dis+=fabs((feature_shape_1[i]-feature_shape[i])/fabs(feature_shape[i]));
		image_shape_temp.tp[pic]=temp_1[pic];//�����N��ͼ·��
		image_shape_temp.num[pic]=dis;//�����N��ͼ�������ͼ��ľ���
		}
		//ShowPic(temp_1[pic],IDC_VIEW1);
	}
	if(shape==0)//��������Ϊ��һ�μ��㣬�򱣴����ƶȼ�����
		image_shape=image_shape_temp;
	else//���������Ѿ�����������ȡ���ƶȼ�����
		image_shape_temp=image_shape;
	//�������Ĵ�����ͼ�񼰼�����·������
	image_shape_temp.m_strPath_old=m_strPath;
	image_shape_temp.strfile_old=strfile;
}
/**************************************************************************************
������ɫ���������ƶȼ��㺯��
***************************************************************************************/
void prosess2::Color_SeekImage()
{
	for(int count=0; count<counts; count++)
		temp_1[count] = *temp[count];
	//switch(c_method)
	//{
	//case 1:
		if(image_color_1.strfile_old==strfile&&image_color_1.m_strPath_old==m_strPath)
			color=1;//�˼������µĴ˼���ͼ���Ѿ��ô˷��������
		else
			color=0;
	//case 2:
		//if(image_color_2.strfile_old==strfile&&image_color_2.m_strPath_old==m_strPath)
		//	color=1;//�˼������µĴ˼���ͼ���Ѿ��ô˷��������
		//else
		//	color=0;
		//break;
	//case 3:
	//	if(image_color_3.strfile_old==strfile&&image_color_3.m_strPath_old==m_strPath)
		//	color=1;//�˼������µĴ˼���ͼ���Ѿ��ô˷���������Ѿ��ô˷��������
	//	else
		//	color=0;
		//break;
	//}
	for(int pic=0; pic<counts; pic++)//���������������ͼ��
	{
		if(color==0)
		{
			//switch(c_method)
			//{
			//case 1:
			general(temp_1[pic],2);//��ȡ�����ĵ�N��ͼ����ɫֱ��ͼ
			break;
			/*case 2:
			succession(temp_1[pic],2);//��ȡ�����ĵ�N��ͼ���ۼ�ֱ��ͼ
			break;
			case 3:
			centerM(temp_1[pic],2);//��ȡ�����ĵ�N��ͼ����ɫ��
			break;
			}*/
			double dis=0;//��N��ͼ�������ͼ��ľ���
			double dis_temp=0;
			//�������ڼ����ĵ�N��ͼ�������ͼ��ľ���
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<12;j++)
					dis_temp+=(feature_color_1[i][j]-feature_color[i][j])*(feature_color_1[i][j]-feature_color[i][j]);
				dis+=sqrt((double)dis_temp);
				dis_temp=0;
			}
			image_color_temp.tp[pic]=temp_1[pic];//�����N��ͼ·��
			image_color_temp.num[pic]=dis;//�����N��ͼ�������ͼ��ľ���
		}
		//ShowPic(temp_1[pic],IDC_VIEW1);
	}
	/*switch(c_method)
	{
	case 1:*/
		if(color==0)//��������Ϊ��һ�μ��㣬�򱣴����ƶȼ�����
		{
			image_color_1=image_color_temp;
			sort();			
		}
		else//���������Ѿ�����������ȡ���ƶȼ�����
		{
			image_color_temp=image_color_1;
			sort();
		}
		//�������Ĵ�����ͼ�񼰼�����·������
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
