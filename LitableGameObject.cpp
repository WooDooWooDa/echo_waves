#include "LitableGameObject.h"
#include "math.h"

void LitableGameObject::Update(Uint64 delta)
{
	GameObject::Update(delta);

	if (litUpTimeLeft > 0) {
		litUpTimeLeft -= delta;
	}
	color.A = lerp(0, 255, litUpTimeLeft / litUpTime);
}

void LitableGameObject::Draw(SDL_Renderer* renderer) const
{
	if (spriteTexture == nullptr) {
		GameObject::Draw(renderer);
		return;
	}

	auto drawRect = GetBounds();
	RGBColor drawColor = DEBUG_MODE ? COLOR_RED : color;
	SDL_SetTextureColorMod(spriteTexture, drawColor.R, drawColor.G, drawColor.B);
	SDL_SetTextureAlphaMod(spriteTexture, color.A);
	//SDL_RenderTexture(renderer, spriteTexture, NULL, &drawRect);
	SDL_RenderTextureRotated(renderer, spriteTexture, NULL, &drawRect, SpriteDirToAngle(), NULL, SDL_FLIP_NONE);

	GameObject::DrawCollider(renderer);
}

void LitableGameObject::OnCollisionEnter(CollisionResult res)
{
	if (res.other->name != "SoundParticle") return;

	ResetLitUpTime();
}
