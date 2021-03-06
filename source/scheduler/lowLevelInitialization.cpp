/**
 * \file
 * \brief internal::lowLevelInitialization() definition
 *
 * \author Copyright (C) 2014-2017 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "distortos/internal/scheduler/lowLevelInitialization.hpp"

#include "distortos/StaticThread.hpp"

#include "distortos/internal/scheduler/getScheduler.hpp"
#include "distortos/internal/scheduler/Scheduler.hpp"
#include "distortos/internal/scheduler/idleThreadFunction.hpp"
#include "distortos/internal/scheduler/MainThread.hpp"
#include "distortos/internal/scheduler/ThreadGroupControlBlock.hpp"

#if __GNUC_PREREQ(5, 1) != 1
// GCC 4.x doesn't fully support constexpr constructors
#error "GCC 5.1 is the minimum version supported by distortos"
#endif

namespace distortos
{

namespace internal
{

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/// size of idle thread's stack, bytes
#ifdef CONFIG_THREAD_DETACH_ENABLE
constexpr size_t idleThreadStackSize {256};
#else	// !def CONFIG_THREAD_DETACH_ENABLE
constexpr size_t idleThreadStackSize {128};
#endif	// !def CONFIG_THREAD_DETACH_ENABLE

/// type of idle thread
using IdleThread = decltype(makeStaticThread<idleThreadStackSize>(0, idleThreadFunction));

/// storage for idle thread instance
std::aligned_storage<sizeof(IdleThread), alignof(IdleThread)>::type idleThreadStorage;

/// storage for main thread instance
std::aligned_storage<sizeof(MainThread), alignof(MainThread)>::type mainThreadStorage;

/// main thread group
ThreadGroupControlBlock mainThreadGroupControlBlock;

#ifdef CONFIG_MAIN_THREAD_CAN_RECEIVE_SIGNALS

/// type of StaticSignalsReceiver for main thread
using MainThreadStaticSignalsReceiver =
		StaticSignalsReceiver<CONFIG_MAIN_THREAD_QUEUED_SIGNALS, CONFIG_MAIN_THREAD_SIGNAL_ACTIONS>;

/// storage for instance of MainThreadStaticSignalsReceiver for main thread
std::aligned_storage<sizeof(MainThreadStaticSignalsReceiver), alignof(MainThreadStaticSignalsReceiver)>::type
		mainThreadStaticSignalsReceiverStorage;

#endif	// def CONFIG_MAIN_THREAD_CAN_RECEIVE_SIGNALS

}	// namespace

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void lowLevelInitialization()
{
#ifdef CONFIG_MAIN_THREAD_CAN_RECEIVE_SIGNALS

	auto& mainThreadStaticSignalsReceiver =
			*new (&mainThreadStaticSignalsReceiverStorage) MainThreadStaticSignalsReceiver;
	const auto mainThreadStaticSignalsReceiverPointer = &static_cast<SignalsReceiver&>(mainThreadStaticSignalsReceiver);

#else	// !def CONFIG_MAIN_THREAD_CAN_RECEIVE_SIGNALS

	// nullptr - reception of signals is disabled for main thread
	constexpr auto mainThreadStaticSignalsReceiverPointer = nullptr;

#endif	// !def CONFIG_MAIN_THREAD_CAN_RECEIVE_SIGNALS

	auto& mainThread = *new (&mainThreadStorage) MainThread {CONFIG_MAIN_THREAD_PRIORITY, mainThreadGroupControlBlock,
			mainThreadStaticSignalsReceiverPointer};
	getScheduler().initialize(mainThread);	/// \todo error handling?
	mainThread.getThreadControlBlock().switchedToHook();

	auto& idleThread = *new (&idleThreadStorage) IdleThread {0, idleThreadFunction};
	idleThread.start();
}

}	// namespace internal

}	// namespace distortos
