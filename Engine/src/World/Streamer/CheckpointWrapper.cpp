#include SAMPCPP_PCH

#include <SAMPCpp/World/Streamer/CheckpointWrapper.hpp>

namespace samp_cpp::default_streamer
{

///////////////////////////////////////////////////////////////////////////
CheckpointWrapper::CheckpointWrapper(Checkpoint& checkpoint_)
	:
	I3DNodePlacementTracker{ checkpoint_.getPlacement() },
	m_checkpoint{ &checkpoint_ }
{
}

///////////////////////////////////////////////////////////////////////////
void CheckpointWrapper::whenPlacementChanges(ActorPlacement const& prevPlacement_, ActorPlacement const& newPlacement_)
{
	// TODO: implement this.
}

}
