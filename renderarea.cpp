/**
 * Authors - Jonathan Vielstich
 * Last Modified - 12/01/2021
 */
#include "renderarea.h"

/**
 * Draws the various game objects
 *
 * @brief Displays a clickable QPixmap and provides a simple
 * method to update that image. To add a RenderArea to an
 * existing form, either add a QLabel to the form and promote
 * it to a RenderArea, or use the addWidget method to add a
 * RenderArea to an existing layout.
 */

/**
 * @brief Constructs a new RenderArea widget
 *
 * @param parent
 */
RenderArea::RenderArea(QWidget *parent, [[maybe_unused]] Qt::WindowFlags f) : QLabel(parent)
{
	QPixmap blank(this->width(), this->height());
	blank.fill();
}

/**
 * Sets the image to display on the RenderArea
 *
 * @param toRender - image to display
 */
void RenderArea::setImage(QPixmap &toRender)
{
	setPixmap(toRender.scaled(this->width(), this->height(), Qt::KeepAspectRatioByExpanding));
	update();
}

/**
 * Triggered when the mouse moves, and emits the
 * mouse location if the left mouse button is pressed.
 * @param e
 */
void RenderArea::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() == Qt::LeftButton) {
		emit mouseLocation(e->pos());
	}
}

/**
 * Triggered when a mouse button is pressed, and emits
 * the mouse location if the left button was pressed.
 *
 * @param e - mouse event
 */
void RenderArea::mousePressEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		emit mousePressed(e->pos());
	}
}

/**
 * Triggered when a mouse button is released, and emits
 * the mouse location if the left button was released.
 *
 * @param e - mouse event
 */
void RenderArea::mouseReleaseEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton) {
		emit mouseReleased(e->pos());
	}
}

/**
 * Triggered when a mouse button is double clicked.
 *
 * @param e - mouse event
 */
void RenderArea::mouseDoubleClickEvent(QMouseEvent *e)
{
	// do nothing
}
