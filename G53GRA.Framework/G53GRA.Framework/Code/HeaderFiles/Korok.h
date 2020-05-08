#include "DisplayableObject.h"
#include "../HeaderFiles/KorokWand.h"
#include "../HeaderFiles/KorokMask.h"
#include "../HeaderFiles/KorokBody.h"

class Korok :
	public DisplayableObject
{
public:
	Korok();
	Korok(GLuint mt);
	Korok(KorokWand* w, KorokMask* m, KorokBody* b);
	~Korok();
	void Display();
private:
	KorokWand* wand;
	KorokMask* mask;
	KorokBody* body;
};
