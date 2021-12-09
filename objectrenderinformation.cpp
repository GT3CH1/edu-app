/**
 * Authors - William Erignac
 * Last Modified - 12/8/2021
 *
 * A container of all the information needed to render
 * a GameObject. ObjectRenderArea implements comparisons by renderLayer
 * to quickly sort the objects for rendering.
 */

#include "objectrenderinformation.h"
#include <cmath>
#include <QDebug>

bool ObjectRenderInformation::operator==(const ObjectRenderInformation& other) const
{
	return renderLayer == other.renderLayer && id == other.id;
}

bool ObjectRenderInformation::operator>(const ObjectRenderInformation& other) const
{
	if (renderLayer == other.renderLayer)
		return (id > other.id);
	return (renderLayer > other.renderLayer);
}

bool ObjectRenderInformation::operator<(const ObjectRenderInformation& other) const
{
	if (renderLayer == other.renderLayer)
		return (id < other.id);
	return (renderLayer < other.renderLayer);
}
