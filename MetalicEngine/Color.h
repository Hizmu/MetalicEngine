


enum class COLOR
{
	BLACK = 0x000000,
	SILVER = 0xC0C0C0,
	GRAY = 0x808080,
	WHITE = 0xffffff,
	MARRON = 0x800000,
	RED = 0xff0000,
	PURPLE = 0x800080,
	FUCHSIA = 0xff00ff,
	GREEN = 0x008000,
	LIME = 0x00ff00,
	OLIVE = 0x808000,
	YELLOW = 0xffff00,
	NAVY = 0x000080,
	BLUE = 0x0000ff,
	TEAL = 0x008080,
	AQUA = 0x00FFFF,


};

	struct Color
	{
		Color() {};
		Color(float red, float green, float blue, float alpha):red(red),green(green),blue(blue),alpha(alpha){}
		Color(COLOR col){ }
		float red, green, blue, alpha;

	};
