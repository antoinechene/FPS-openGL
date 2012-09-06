private:
inline uint8_t	__Alpha(uint8_t src, uint8_t dst, uint8_t a)
{
	return (src * a + (256 - a) * dst) >> 8;
}

inline void	__Rect(int16_t x, int16_t y,
		       int16_t w, int16_t h,
		       bool f)
{
	int16_t		minX;
	int16_t		minY;
	int16_t		maxX;
	int16_t		maxY;
	uint8_t*	minP;
	uint8_t*	maxP;
	uint8_t*	tmp_saver; // This var avoid 1 + Y mul
	int32_t		bpp;

	if (0 <= w)
	{
		minX = x;
		maxX = x + w;
	}
	else
	{
		minX = x + w + 1;
		maxX = x + 1;
	}
	if (0 <= h)
	{
		minY = y;
		maxY = y + h;
	}
	else
	{
		minY = y + h + 1;
		maxY = y + 1;
	}
//	bpp = this->__target->__surface->format->BytesPerPixel;
	bpp = 4;
	x = minX;
	--maxY;
	minP = (uint8_t*)this->__target->pixels +
	       minY * this->__target->pitch +
	       minX * bpp;

	tmp_saver = minP;
	maxP = (uint8_t*)minP + (maxY - minY) * this->__target->pitch;
	while (x < maxX)
	{
		*(uint32_t*)minP = this->__color;
/*		minP[0] = this->__Alpha(this->__color & 0xFF,
					minP[0],
					this->__color >> 24 & 0xFF);
		minP[1] = this->__Alpha(this->__color >> 8 & 0xFF,
					minP[1],
					this->__color >> 24 & 0xFF);
		minP[2] = this->__Alpha(this->__color >> 16 & 0xFF,
					minP[2],
					this->__color >> 24 & 0xFF);
*/
		*(uint32_t*)maxP = this->__color;
/*		maxP[0] = this->__Alpha(this->__color & 0xFF,
					minP[0],
					this->__color >> 24 & 0xFF);
		maxP[1] = this->__Alpha(this->__color >> 8 & 0xFF,
					minP[1],
					this->__color >> 24 & 0xFF);
		maxP[2] = this->__Alpha(this->__color >> 16 & 0xFF,
					minP[2],
					this->__color >> 24 & 0xFF);
*/
		minP = minP + bpp;
		maxP = maxP + bpp;
		++x;
	}
	maxP = (uint8_t*)minP + this->__target->pitch - bpp;
	minP = tmp_saver + this->__target->pitch;
	++minY;
	--maxY;
	--maxX;
	while (minY <= maxY)
	{
		*(uint32_t*)minP = this->__color;
/*		minP[0] = this->__Alpha(this->__color & 0xFF,
					minP[0],
					this->__color >> 24 & 0xFF);
		minP[1] = this->__Alpha(this->__color >> 8 & 0xFF,
					minP[1],
					this->__color >> 24 & 0xFF);
		minP[2] = this->__Alpha(this->__color >> 16 & 0xFF,
					minP[2],
					this->__color >> 24 & 0xFF);
*/		*(uint32_t*)maxP = this->__color;
/*		maxP[0] = this->__Alpha(this->__color & 0xFF,
					minP[0],
					this->__color >> 24 & 0xFF);
		maxP[1] = this->__Alpha(this->__color >> 8 & 0xFF,
					minP[1],
					this->__color >> 24 & 0xFF);
		maxP[2] = this->__Alpha(this->__color >> 16 & 0xFF,
					minP[2],
					this->__color >> 24 & 0xFF);
*/		maxP = maxP + this->__target->pitch;
		if (f == false)
		{
			minP = minP + this->__target->pitch;
			++minY;
			continue ;
		}
		tmp_saver = minP;
		x = minX + 1;
		minP = (uint8_t*)minP + bpp;
		while (x < maxX)
		{
			//*(uint32_t*)minP = this->__color;
			minP[0] = this->__Alpha(this->__color & 0xFF,
						minP[0],
						this->__color >> 24 & 0xFF);
			minP[1] = this->__Alpha(this->__color >> 8 & 0xFF,
						minP[1],
						this->__color >> 24 & 0xFF);
			minP[2] = this->__Alpha(this->__color >> 16 & 0xFF,
						minP[2],
						this->__color >> 24 & 0xFF);
			minP = minP + bpp;
			++x;
		}
		++minY;
		minP = tmp_saver + this->__target->pitch;
	}
}

