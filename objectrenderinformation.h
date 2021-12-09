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
	QPointF position;
	double rotation;
	QPointF scale;
	QImage toRender;
	int renderLayer;
	int id;

	bool operator==(const ObjectRenderInformation& other) const;
	bool operator>(const ObjectRenderInformation& other) const;
	bool operator<(const ObjectRenderInformation& other) const;
};

#endif // OBJECTRENDERINFORMATION_H
