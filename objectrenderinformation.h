#ifndef OBJECTRENDERINFORMATION_H
#define OBJECTRENDERINFORMATION_H

#include <QPoint>
#include <QImage>

struct ObjectRenderInformation
{
public:
	const QPoint position;
	const double rotation;
	const QImage toRender;
};

#endif // OBJECTRENDERINFORMATION_H
