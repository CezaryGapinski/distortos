/**
 * \file
 * \brief SignalsCatcherControlBlock class header
 *
 * \author Copyright (C) 2015 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2015-04-16
 */

#ifndef INCLUDE_DISTORTOS_SYNCHRONIZATION_SIGNALSCATCHERCONTROLBLOCK_HPP_
#define INCLUDE_DISTORTOS_SYNCHRONIZATION_SIGNALSCATCHERCONTROLBLOCK_HPP_

#include "distortos/SignalAction.hpp"

namespace distortos
{

namespace synchronization
{

/// SignalsCatcherControlBlock class is a structure required by threads for "catching" and "handling" of signals
class SignalsCatcherControlBlock
{
public:

	/// association of signal number with SignalAction
	using Association = std::pair<uint8_t, SignalAction>;

	/// type of uninitialized storage for Association objects
	using Storage = std::aligned_storage<sizeof(Association), alignof(Association)>::type;

	/**
	 * \brief SignalsCatcherControlBlock's constructor
	 */

	constexpr SignalsCatcherControlBlock()
	{

	}
};

}	// namespace synchronization

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_SYNCHRONIZATION_SIGNALSCATCHERCONTROLBLOCK_HPP_
