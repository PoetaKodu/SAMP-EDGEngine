// File description:
// Implements class manipulating players and agent used to process certain server events.
#pragma once

// Precompiled header:
#include "../../../stdafx.h"


// Custom includes:
#include <AdvancedGDK/Player/Player.hpp>
#include <AdvancedGDK/Misc/Math.hpp>


namespace agdk
{		

	/// <summary>
	/// Stores every player in game.
	/// </summary>
	class PlayerPool final
	{
	public:
		using PoolType			= std::vector< std::shared_ptr< Player > >;
		using RawPoolType		= std::vector< Player * >;

		/// <summary>
		/// Initializes a new instance of the <see cref="PlayerPool"/> class.
		/// </summary>
		PlayerPool();
		
		/// <summary>
		/// Finalizes an instance of the <see cref="PlayerPool"/> class.
		/// </summary>
		~PlayerPool();

		/// <summary>
		/// Gets the specified player using its index.
		/// </summary>
		/// <param name="playerIndex_">Index of the player.</param>
		/// <returns>Pointer to player with specified index.</returns>
		Player* get(std::size_t const playerIndex_) const;
		
		
		/// <summary>
		/// Finds player with the specified function.
		/// </summary>
		/// <param name="func_">The function.</param>
		/// <returns>Player found with specified function. May be null pointer.</returns>
		template <typename _Func>
		Player* find(_Func func_)
		{
			auto it = std::find_if(m_connectedPlayers.begin(), m_connectedPlayers.end(), func_);
			if (it != m_connectedPlayers.end())
				return *it;
			return nullptr;
		}

		/// <summary>
		/// Finds the everyone in radius from specified location.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="radius_">The radius.</param>
		/// <returns>Vector of players in radius from specified location.</returns>
		RawPoolType findEveryoneInRadius(Vector3 const location_, Meters const radius_);
		
		/// <summary>
		/// Finds the nearest player within the radius from specified location.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="radius_">The radius.</param>
		/// <returns>Nearest player within the radius from specified location. May be null pointer.</returns>
		Player* findNearest(Vector3 const location_, Meters const radius_);

		/// <summary>
		/// Finds the nearest player within the radius from specified player.
		/// </summary>
		/// <param name="player_">The location.</param>
		/// <param name="radius_">The radius.</param>
		/// <returns>Nearest player within the radius from specified location. May be null pointer.</returns>
		Player* findNearest(Player const *const player_, Meters const radius_);

		/// <summary>
		/// Finds the player by name.
		/// </summary>
		/// <param name="name_">Name of the player.</param>
		/// <param name="caseSensitive_">Case sensitive.</param>
		/// <returns>Player found by name. May be null pointer.</returns>
		Player* findByName(std::string_view const name_, bool const caseSensitive_ = true);
	
		/// <summary>
		/// Finds player by name or index stored in string.
		/// </summary>
		/// <param name="nameOrIndex">Name or index stored in string.</param>
		/// <param name="caseSensitive_">Case sensitive.</param>
		/// <returns>Player found by name or index. May be null pointer.</returns>
		Player* findByNameOrIndex(std::string_view const nameOrIndex_, bool const caseSensitive_ = true);

		/// <summary>
		/// Finds player by name or index stored in string (picks best match).
		/// </summary>
		/// <param name="nameOrIndex_">Name or index stored in string</param>
		/// <param name="minimalScore_">The minimal score (number of characters in sequence).</param>
		/// <returns>Player found by name or index. May be null pointer.</returns>
		/// <remarks>
		/// <para>
		/// Parameter "minimalScore_" is preventing from picking random players that matches only with few letters.
		///	Case sensitivity is turned off!
		///	This is because this function should be used as easier way to find players.
		///	Be careful though - administrative operations like setting player's rank shouldn't be
		///	implemented using this function.It may cause unwanted players to get
		///	high ranks and is generally dangerous. Can be freely used in f.e. command: /goto [player name / id]
		/// </para>
		/// </remarks>
		Player* findBestMatch(std::string_view const nameOrIndex_, std::size_t const minimalScore_ = 2);

		/// <summary>
		/// Gets the player pool (of raw pointers).
		/// </summary>
		/// <returns>Pool (std::vector) containing every player.</returns>
		auto getPool() const {
			return m_connectedPlayers;
		}

		/// PlayerPoolAgent have access to some private members.
		friend class PlayerPoolAgent;
	private:

		/// <summary>
		/// Called when player connects.
		/// </summary>
		/// <param name="player_">The player.</param>
		/// <remarks>
		/// <para>This is an exclusive function, called before any other and with different arguments.</para>
		/// </remarks>
		void whenPlayerConnectsEx(std::shared_ptr<Player> &&player_);
		
		/// <summary>
		/// Called when player disconnects.
		/// </summary>
		/// <param name="playerIndex_">Index of the player.</param>
		/// <remarks>
		/// <para>This is an exclusive function, called after any other and with different arguments.</para>
		/// </remarks>
		void whenPlayerDisconnectsEx(std::size_t const playerIndex_);

		// Private members
		
		PoolType			m_playerPool;		/// Store players in vector of shared pointers.
		RawPoolType			m_playerRawPool;	/// Store raw pointers in this vector.
		RawPoolType			m_connectedPlayers;	/// Store every connected player in this vector.

	public:
		const std::size_t	maxPlayers;
	};

}

