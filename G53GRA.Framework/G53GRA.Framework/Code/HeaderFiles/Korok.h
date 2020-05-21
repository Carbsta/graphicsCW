#include "DisplayableObject.h"
#include "Animation.h"
#include "../HeaderFiles/KorokWand.h"
#include "../HeaderFiles/KorokMask.h"
#include "../HeaderFiles/KorokBody.h"

class Korok :
	public DisplayableObject,
	public Animation
{
public:
	Korok();
	Korok(GLuint mt, GLuint mbt, GLuint wt);
	Korok(KorokWand* w, KorokMask* m, KorokBody* b);
	~Korok();
	void Display();
	void Update(const double& deltaTime);
	enum class Anim { Sway, Jump };
	void setAnim(Anim _anim);
	void setOffset(float _offset);
private:
	KorokWand* wand;
	KorokMask* mask;
	KorokBody* body;
	Anim anim = Anim::Sway;
	float aT = 0.0f;
	float jumpHeight = 1.f;
	int rotateDistance, headDistance, wandDistance;
	float jumpSpeed, rotateSpeed, headSpeed, wandSpeed;
	float offset = 0.f;
};
