#include "stdafx.h"
#include "resources.h"

RESOURCES::RESOURCES()
{
}

RESOURCES::~RESOURCES()
{
}

bool RESOURCES::Isharvested()
{
	
	return _nHarvestCount <= _nMaxHarvestCount;
}
