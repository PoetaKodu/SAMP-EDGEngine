#pragma once

#include ADVANCEDGDK_PCH

// Wrappers:
#include <AdvancedGDK/World/Streamer/GlobalObjectWrapper.hpp>
#include <AdvancedGDK/World/Streamer/PersonalObjectWrapper.hpp>
#include <AdvancedGDK/World/Streamer/UniversalObjectWrapper.hpp>
#include <AdvancedGDK/World/Streamer/VehicleWrapper.hpp>
#include <AdvancedGDK/World/Streamer/PlayerWrapper.hpp>

// Wrappers' underlying object types:
#include <AdvancedGDK/World/Vehicle.hpp>
#include <AdvancedGDK/World/GlobalObject.hpp>

// Additional includes:
#include <AdvancedGDK/Core/BasicInterfaces/NonCopyable.hpp>
#include <AdvancedGDK/Core/Pointers.hpp>
#include <AdvancedGDK/Core/Container/DivisibleGrid3.hpp>
#include <AdvancedGDK/World/GangZone.hpp>

namespace agdk
{

namespace default_streamer
{

/// <summary>
/// A container which collects every player, vehicle, object located inside its area.
/// </summary>
/// <seealso cref="INonCopyable" />
class Chunk
	:
#ifdef ADVANCEDGDK_DEBUG
	public IDivisibleGrid3ElementBase,
#endif
	public INonCopyable
{
public:
	template <typename TType>
	using ActorContainer = std::vector< UniquePtr<TType> >;
	
	/// <summary>
	/// Intercepts the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void intercept(UniquePtr<PlayerWrapper> && player_);
	
	/// <summary>
	/// Intercepts the specified vehicle.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	void intercept(UniquePtr<VehicleWrapper> && vehicle_);
	
	/// <summary>
	/// Intercepts the specified global object.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	void intercept(UniquePtr<GlobalObjectWrapper> && globalObject_);

	/// <summary>
	/// Intercepts the specified universal object.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	void intercept(UniquePtr<UniversalObjectWrapper> && universalObject_);

	/// <summary>
	/// Intercepts the specified personal object.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	void intercept(UniquePtr<PersonalObjectWrapper> && personalObject_);

	
	/// <summary>
	/// Releases the specified player.
	/// </summary>
	/// <param name="player_">The player.</param>
	[[nodiscard]] UniquePtr<PlayerWrapper> release(Player const & player_);
	
	/// <summary>
	/// Releases the specified vehicle.
	/// </summary>
	/// <param name="vehicle_">The vehicle.</param>
	[[nodiscard]] UniquePtr<VehicleWrapper> release(Vehicle const & vehicle_);
	
	/// <summary>
	/// Releases the specified global object.
	/// </summary>
	/// <param name="globalObject_">The global object.</param>
	[[nodiscard]] UniquePtr<GlobalObjectWrapper> release(GlobalObject const & globalObject_);

	/// <summary>
	/// Releases the specified universal object.
	/// </summary>
	/// <param name="universalObject_">The universal object.</param>
	[[nodiscard]] UniquePtr<UniversalObjectWrapper> release(UniversalObject const & universalObject_);

	/// <summary>
	/// Releases the specified personal object.
	/// </summary>
	/// <param name="personalObject_">The personal object.</param>
	[[nodiscard]] UniquePtr<PersonalObjectWrapper> release(PersonalObject const & personalObject_);

	/// <summary>
	/// Adds the score around specified player.
	/// </summary>
	/// <param name="placement_">The player's placement.</param>
	void addScoreAroundPlayer(PlayerPlacement const & placement_);
		
	/// <summary>
	/// Subtracts the score around player.
	/// </summary>
	/// <param name="player_">The player's placement.</param>
	void subtractScoreAroundPlayer(PlayerPlacement const & placement_);
	
	/// <summary>
	/// Applies the global actors visibility.
	/// </summary>
	void applyGlobalActorsVisibility();

	/// <summary>
	/// Returns cref to contained list of the Players.
	/// </summary>
	/// <returns>cref to contained list of the Players.</returns>
	auto const& getPlayers() const {
		return m_players;
	}
	
	/// <summary>
	/// Returns cref to contained list of the vehicles.
	/// </summary>
	/// <returns>cref to contained list of the vehicles.</returns>
	auto const& getVehicles() const {
		return m_vehicles;
	}

	/// <summary>
	/// Returns cref to contained list of the global objects.
	/// </summary>
	/// <returns>cref to contained list of the global objects.</returns>
	auto const& getGlobalObjects() const {
		return m_globalObjects;
	}

	/// <summary>
	/// Returns cref to contained list of the universal objects.
	/// </summary>
	/// <returns>cref to contained list of the universal objects.</returns>
	auto const& getUniversalObjects() const {
		return m_universalObjects;
	}

	/// <summary>
	/// Returns cref to contained list of the personal objects.
	/// </summary>
	/// <returns>cref to contained list of the personal objects.</returns>
	auto const& getPersonalObjects() const {
		return m_personalObjects;
	}
	
	/// <summary>
	/// Determines whether this chunk is empty.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this chunk is empty; otherwise, <c>false</c>.
	/// </returns>
	bool isEmpty() const {
		return m_players.empty() && m_vehicles.empty() && m_globalObjects.empty() && m_universalObjects.empty() && m_personalObjects.empty();
	}

private:

#ifdef ADVANCEDGDK_DEBUG

	void GZThingIntercepted();

	void GZThingReleased();

	Color GZCalculateColor();

	Color GZCalculateFlashingColor();

	GangZone* m_gangZone = nullptr;

#endif

	ActorContainer< PlayerWrapper >				m_players;			// Player wrapper container.
	ActorContainer< VehicleWrapper >			m_vehicles;			// Vehicle wrapper container.
	ActorContainer< GlobalObjectWrapper >		m_globalObjects;	// Global object wrapper container.
	ActorContainer< UniversalObjectWrapper >	m_universalObjects;	// Universal object wrapper container.
	ActorContainer< PersonalObjectWrapper >		m_personalObjects;	// Personal object wrapper container.
};

}

} // namespace agdk