//
//  actor.cpp
//  PUBG
//
//  Created by wza on 2021/5/26.
//
#include "actor.h"
actor::actor()
{
	canMove = true;
	isInvincible = false;
	delegateSprite = nullptr;
	sActorType = at_null;
}
void actor::bindSprite(cocos2d::Sprite* sprite)
{
	delegateSprite = sprite;
	addChild(delegateSprite);
}
int actor::getHealthPoint()
{
	return sHealthPoint;
}
int actor::getDefencePoint()
{
	return sDefencePoint;
}
bool actor::doDamage(int attackPoint)
{
	int damage = attackPoint - this->getDefencePoint();
	if(damage<0)
	{
		
	}
	else
	{
		this->sHealthPoint -= damage;
		return sHealthPoint > 0;	//maybe he is dead
	}
	return true;
}
bool actor::bindPhysicalBody()
{
	if (this->delegateSprite == nullptr)
	{
		log("failed to bind physical body for no sprite");
		return false;
	}
	else
	{
		PhysicsBody* phyBody = PhysicsBody::createBox(Size(sizeOfContext[sActorType][0], sizeOfContext[sActorType][1]));
		phyBody->setDynamic(true);
		phyBody->setCategoryBitmask(1);
		phyBody->setCollisionBitmask(1);
		phyBody->setContactTestBitmask(1);
		delegateSprite->setPhysicsBody(phyBody);
	}
}