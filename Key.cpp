#include "Key.h"
#include "Player.h"

void Key::OnTriggerEnter(GameObject* other)
{

}

void Key::UnHover()
{

}

void Key::Hover()
{

}

void Key::Interact(GameObject* other)
{
	Player* player = dynamic_cast<Player*>(other);
	player->AddKey(keyId);
	Destroy();
}
