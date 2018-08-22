/**
 * \file
 * \brief DisplayPlaneOperation class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_DISPLAY_DISPLAYPLANEOPERATION_HPP_
#define INCLUDE_DISTORTOS_DEVICES_DISPLAY_DISPLAYPLANEOPERATION_HPP_

namespace distortos
{

namespace devices
{

class Plane;

/**
 * DisplayPlaneOperation class is a single operation on Plane that can be executed by Display Driver as part of
 * a transaction.
 *
 * \ingroup devices
 */

class DisplayPlaneOperation
{
public:

	/**
	 * \brief DisplayPlaneOperation's constructor with operation on Plane
	 *
	 * \param [in] plane is the Plane to transfer operation that will be executed
	 *
	 * \note non-explicit on purpose
	 */

	constexpr DisplayPlaneOperation(Plane& plane) :
			plane_{plane}
	{

	}

	/**
	 * \return reference to contained Plane
	 */

	Plane& getPlane() const
	{
		return plane_;
	}

private:

	/// single transfer operation
	Plane& plane_;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_DISPLAY_DISPLAYPLANEOPERATION_HPP_
