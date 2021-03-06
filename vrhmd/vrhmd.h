/** Abstract VRHMD
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
 */
#pragma once

#include <pthread.h>

#include "../core/core.h"
#include "../display/x/xDisplay.h"


namespace vr_core{

	class VRHMD : public Core{
		VRHMD();
		VRHMD(const VRHMD&);
		void operator=(const VRHMD&);
	public:
	protected:

		using Profile = XDisplay::Profile;

		VRHMD(int fd, const Profile&);
		virtual ~VRHMD();

		/**デバイスファイル取得
		 * デバイスファイルを開いてロックして返す。
		 * OpenDeviceFileはudevでデバイスファイル名が確定していることを前提としている。
		 * ScanDeviceFileは第三引数の後ろに数字を付けてvidとpidと一致するデバイスファイルを探す。
		 */
		static int OpenDeviceFile(const char*);
		static int ScanDeviceFile(const int vid, const int pid, const char* ="/dev/hidraw");

		//画面の大きさなど
		const unsigned width;
		const unsigned height;
		static const float nearDistance;
		static const float farDistance;
		const Profile& params;

		//絶対姿勢設定
		void SetPose(const COMPLEX<4>&); //位置なし(位置アリはPOSEにある)

		//姿勢取得
		virtual void UpdateSensor(){};

	private:
		const bool landscape;

		//マルチパスレンダリング用
		unsigned deDistorShaderProgram;
		unsigned deDistorTexture;

		/////センサ関連
		const int fd;
		// 受信処理
		pthread_t sensorThread;
		static void* _SensorThread(void* initialData);
		void SensorThread();

		/////Core関連
		TB::Framebuffer framebuffer;
		TB::Framebuffer& Framebuffer() final { return framebuffer; };
		void PostDraw() final;

		struct DeDistoreElement{
			float u;
			float v;
		}__attribute__((packed));
		void NewDeDistoreCoords();
		void UpdateDeDistoreCoords();
		void RegisterDeDistoreCoords(const float*);
		void BuildDeDistoreCoords();

		float D2(float, float);
	};

}

