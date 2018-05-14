#include "Clickable.h"

bool Clickable::m_bClicked(Vector2f sfVmouseClick)
{
	


	if (sfVmouseClick.x >= m_sfVTopLeftPos.x && sfVmouseClick.x <= m_sfVTopLeftPos.x + m_sfVSize.x)
	{
		
		if(sfVmouseClick.y >= m_sfVTopLeftPos.y && sfVmouseClick.y <= m_sfVTopLeftPos.y + m_sfVSize.y)
		{
			//get the volume settings
			Profile *player;
			player = Profile::getInstance();

			//get the sound
			SoundObject *m_soundObject;
			m_soundObject = SoundObject::getInstance();

			//play the sound
			
		
			m_soundObject->m_vInterfaceSounds[0].setBuffer(m_soundObject->m_vBufferInterfaceSounds[0]);
			m_soundObject->m_vInterfaceSounds[0].setVolume(player->m_iInterfaceAudioVolume);
			m_soundObject->m_vInterfaceSounds[0].play();


			return true;
		}
	}

	return false;
}
