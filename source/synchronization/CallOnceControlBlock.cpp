/**
 * \file
 * \brief CallOnceControlBlock class implementation
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-07-09
 */

#include "distortos/synchronization/CallOnceControlBlock.hpp"

#include "distortos/architecture/InterruptMaskingLock.hpp"

#include "distortos/scheduler/getScheduler.hpp"
#include "distortos/scheduler/Scheduler.hpp"

namespace distortos
{

namespace synchronization
{

/*---------------------------------------------------------------------------------------------------------------------+
| private functions
+---------------------------------------------------------------------------------------------------------------------*/

void CallOnceControlBlock::callOnceImplementation(const Functor& functor)
{
	architecture::InterruptMaskingLock interruptMaskingLock;

	if (done_ == true)	// function already executed?
		return;

	if (blockedList_ != nullptr)	// function is currently being executed, but not yet done?
	{
		while (done_ == false)
			scheduler::getScheduler().block(*blockedList_);
		return;
	}

	scheduler::ThreadControlBlockList blockedList {scheduler::getScheduler().getThreadControlBlockListAllocator(),
			scheduler::ThreadControlBlock::State::BlockedOnOnceFlag};
	blockedList_ = &blockedList;

	functor();

	done_ = true;
	blockedList_ = nullptr;

	while (blockedList.empty() == false)
		scheduler::getScheduler().unblock(blockedList.begin());
}

}	// namespace synchronization

}	// namespace distortos
