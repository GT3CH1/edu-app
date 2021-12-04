/**
 * Authors - William Erignac
 * Last Modified - 12/2/2021
 *
 * All the information the VC needs to know
 * about an object to render it.
 */

#ifndef OBJECTRENDERINFORMATION_H
#define OBJECTRENDERINFORMATION_H

#include <QTransform>
#include <QImage>

struct ObjectRenderInformation
{
public:
	const QPointF position;
	const double rotation;
	const QPointF scale;
	const QImage toRender;
};

#endif // OBJECTRENDERINFORMATION_H
