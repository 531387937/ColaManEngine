﻿#pragma once

#include <string>
#include <thread>

namespace ColaMan {

	class Thread
	{
	public:
		Thread() = default;
		Thread(const std::string& name)
			: m_Name(name) {}

		template<typename Fn, typename... Args>
		void Dispatch(Fn&& func, Args&&... args)
		{
			m_Thread = std::thread(func, std::forward<Args>(args)...);
			SetName(m_Name);
		}

		void SetName(const std::string& name) { m_Name = name; }

		void Join() { m_Thread.join(); }
	private:
		std::string m_Name;
		std::thread m_Thread;
	};

	class ThreadSignal
	{
	public:
		ThreadSignal(const std::string& name, bool manualReset = false);

		void Wait();
		void Signal();
		void Reset();
	private:
		void* m_SignalHandle = nullptr;
	};
}