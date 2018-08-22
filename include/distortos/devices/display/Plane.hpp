/**
 * \file
 * \brief Plane class header
 *
 * \author Copyright (C) 2018 Cezary Gapinski cezary.gapinski@gmail.com
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef INCLUDE_DISTORTOS_DEVICES_DISPLAY_PLANE_HPP_
#define INCLUDE_DISTORTOS_DEVICES_DISPLAY_PLANE_HPP_

#include <cstdint>
#include <utility>

namespace distortos
{

namespace devices
{

class Framebuffer;

/**
 * Plane class is a class with plane for display
 *
 * \ingroup devices
 */

class Plane
{
public:

	enum class Type : uint8_t
	{
		primary,
		overlay,
	};

	/**
	 * \brief Plane's constructor
	 *
	 * \param [in] framebuffer is a reference to Framebuffer associated with this plane
	 * \param [in] type is a Type of this plane
	 */

	explicit Plane(Framebuffer& framebuffer, Type type) :
		type_{type},
		xDisplay_{},
		yDisplay_{},
		enabled_{},
		framebuffer_{framebuffer},
		newFramebuffer_{true}
	{

	}

	/**
	 * \brief Plane's destructor
	 */

	~Plane();

	/**
	 * \brief Changes framebuffer associated with this plane
	 *
	 * \warning previous framebuffer must be hold in memory untill the next vsync event if it used in Display Driver
	 * in synchronous mode
	 */

	void swapFramebuffer(const Framebuffer& framebuffer);

	/**
	 * \brief Positions plane object on display
	 *
	 * \param [in] xDisplay is the x offset of plane on display
	 * \param [in] yDisplay is the y offset of plane on display
	 *
	 */
	void position(int16_t xDisplay, int16_t yDisplay);

	/**
	 * \brief Disables plane object on display
	 *
	 */

	void disable()
	{
		enabled_ = false;
	}

	/**
	 * \brief Enables plane object on display
	 *
	 */

	void enable()
	{
		enabled_ = true;
		newFramebuffer_ = true;
	}

	/**
	 * return true if plane is enabled, false otherwise
	 */

	bool isEnabled() const
	{
		return enabled_;
	}

	/**
	 * return true if is the new Framebuffer, false otherwise
	 */

	bool isNewFramebuffer() const
	{
		return newFramebuffer_;
	}

	/**
	 * return this plane Type
	 */

	Type getType() const
	{
		return type_;
	}

	/**
	 * return pair with left and upper position of visible portion of plane on display
	 */

	std::pair<int16_t, int16_t> getCoordinatesOnDisplay() const
	{
		return {xDisplay_, yDisplay_};
	}

	/**
	 * return currently bound Framebuffer
	 */

	const Framebuffer& getFramebuffer() const
	{
		return framebuffer_;
	}

	/**
	 * \brief Notify correct update plane to device
	 *
	 */

	void notifyUpdate()
	{
		newFramebuffer_ = false;
	}

private:

	Type type_;

	/// left position of visible portion of plane on display, signed value allows it to be partially off screen
	int16_t xDisplay_;

	/// upper position of visible portion of plane on display, signed value allows it to be partially off screen
	int16_t yDisplay_;

	/// enable status of the plane
	bool enabled_;

	/// currently bound Framebuffer
	Framebuffer& framebuffer_;

	/// new Framebuffer in the plane
	bool newFramebuffer_;
};

}	// namespace devices

}	// namespace distortos

#endif	// INCLUDE_DISTORTOS_DEVICES_DISPLAY_PLANE_HPP_
