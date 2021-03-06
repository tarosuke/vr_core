/** Scenery
 * Copyright (C) 2017,2019 tarosuke<webmaster@tarosuke.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * スカイスフィアやスカイボックスなどの抽象
 */
#pragma once

#include <toolbox/factory/factory.h>
#include <toolbox/prefs.h>
#include <toolbox/string.h>
#include <toolbox/image.h>

#include <model.h>



namespace vr_core{

	class Scenery : public Model_C{
		Scenery();
		Scenery(const Scenery&);
		void operator=(const Scenery&);
	public:
		using Factory = FACTORY<Scenery, const TB::Image&>;

		Scenery(const Params&, const TB::Image&);

	protected:

	private:

		static FACTORY<Module> factory;
		static TB::Prefs<TB::String> path;

		static Module* New();
	};

}
