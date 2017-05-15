#ifndef PROSESS2_H
#define PROSESS2_H

#include <QObject>

class prosess2 : public QObject
{
	Q_OBJECT

public:
	prosess2(QObject *parent);
	~prosess2();

private:
public:
	void torque(QString pathfile,int mode);
	void general(QString pathfile,int mode);
	void prosess2::Color_SeekImage();
	void prosess2::Shape_SeekImage();
	void prosess2::sort();
private slots:
	void jiansuo();
};

#endif // PROSESS2_H
