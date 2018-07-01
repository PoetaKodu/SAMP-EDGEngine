#include "AdvancedGDKPCH.hpp" // PCH

// Custom headers:
#include <AdvancedGDK/Core/Clock.hpp>

namespace agdk
{
/////////////////////////////////////////////////////////////////////////////////////////////
Clock::Clock()
	: m_startPoint{ Clock::now() }
{
		
}

/////////////////////////////////////////////////////////////////////////////////////////////
Clock::Duration Clock::restart()
{
	auto current = this->getElapsedTime();
	m_startPoint = Clock::now();
	return current;
}

/////////////////////////////////////////////////////////////////////////////////////////////
Clock::Duration Clock::getElapsedTime() const
{
	return Clock::now() - m_startPoint;
}

/////////////////////////////////////////////////////////////////////////////////////////////
Clock::TimePoint Clock::now()
{
	return std::chrono::steady_clock::now();
}

/////////////////////////////////////////////////////////////////////////////////////////////
Clock::Duration Clock::sinceEpoch()
{
	return Clock::now().time_since_epoch();
}

}
