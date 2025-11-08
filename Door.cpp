#include "Door.h"
#include <iostream>

void Door::OnTriggerEnter(GameObject* other)
{
	std::cout << other->name << std::endl;
}

void Door::Unlock()
{

}
