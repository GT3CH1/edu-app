/**
 * Authors - Alex Richins, Gavin Pease
 * Last Modified - 12/12/2021
 */

#include "questswitchfilter.h"
// SwitchFilter
void SwitchFilter::listener(const CallbackOptions &callback)
{
	Filter* waterFilter = (Filter*)callback.getGameObject("waterfilter");
	bool filterOld = waterFilter->getOldFilter();
	if(!filterOld){
		emit Quest::pass();
	} /*else{
		emit Quest::fail();
	}*/
}

void SwitchFilter::reset(const CallbackOptions &callback)
{

}

void SwitchFilter::showText(const CallbackOptions &callback)
{

}
