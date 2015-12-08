/**
 * \file
 * \brief SoftwareTimerCommon class implementation
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-12-08
 */

#include "distortos/SoftwareTimerCommon.hpp"

namespace distortos
{

/*---------------------------------------------------------------------------------------------------------------------+
| public functions
+---------------------------------------------------------------------------------------------------------------------*/

SoftwareTimerCommon::~SoftwareTimerCommon()
{

}

bool SoftwareTimerCommon::isRunning() const
{
	return softwareTimerControlBlock_.isRunning();
}

int SoftwareTimerCommon::start(const TickClock::time_point timePoint)
{
	softwareTimerControlBlock_.start(timePoint);
	return 0;
}

int SoftwareTimerCommon::stop()
{
	softwareTimerControlBlock_.stop();
	return 0;
}

}	// namespace distortos
