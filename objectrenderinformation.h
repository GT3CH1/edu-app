#ifndef OBJECTRENDERINFORMATION_H
#define OBJECTRENDERINFORMATION_H

#include <QTransform>
#include <QImage>

struct ObjectRenderInformation
{
public:
	const QTransform offset;
	const QImage toRender;
};

#endif // OBJECTRENDERINFORMATION_H
