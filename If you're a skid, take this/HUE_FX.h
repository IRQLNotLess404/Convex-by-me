typedef struct _HSV {
  float h;
  float s;
  float v;
} HSV, *PHSV, *LPHSV;

HSV rgbQuadToHSV(RGBQUAD rgbQuad) {
	HSV hsl;
	
	BYTE r = rgbQuad.rgbRed, g = rgbQuad.rgbGreen, b = rgbQuad.rgbBlue;
	float fr = (float)r/255.f;
	float fg = (float)g/255.f;
	float fb = (float)b/255.f;
	
	float minr = fmin(fmin(fr, fg), fb), maxr = fmax(fmax(fr, fg), fb); // I fixed this part since that's what made the HSL so opaque!
	float delta = maxr-minr;
	float delr, delg, delb;
	
	float h = 0.f, s = 0.f, l = (float)((maxr+minr)/2.f);
	
	if (delta != 0.f) {
		s = l < 0.5f ? (float)(delta / (maxr + minr)) : (float)(delta / (2.f - maxr - minr));
		delr = (float)(((maxr - fr) / 6.f + (delta / 2.f)) / delta);
		delg = (float)(((maxr - fg) / 6.f + (delta / 2.f)) / delta);
		delb = (float)(((maxr - fb) / 6.f + (delta / 2.f)) / delta);
		
		if (fr == maxr) h = delb-delg;
		else if (fg == maxr) h = (1.f / 3.f) + delr - delb;
		else if (fb == maxr) h = (2.f / 3.f) + delg - delr;
		if (h < 0.f) h += 1.f;
		if (h > 1.f) h -= 1.f;
	}
	
	hsl.h = h;
	hsl.s = s;
	hsl.v = l;
	return hsl;
}

RGBQUAD hsvToRGB(HSV hsl) {
	RGBQUAD rgbq;
	float r = hsl.v, g = hsl.v, b = hsl.v;
	float h = hsl.h, s2 = hsl.s, l = hsl.v;
	float vh = (l <= 0.5f) ? (l*(1.f + s2)) : (l+s2-l*s2);
	
	float m, sv, frac, vsf, mid, mid2;
	int st;
	
	if (vh > 0.f) {
		m = l + l - vh;
		sv = (vh - m) / vh;
		h *= 6.f;
		st = (int)h;
		frac = h-st;
		vsf = vh*sv*frac;
		mid = m+vsf;
		mid2 = vh-vsf;
		switch(st) {
			case 0:
				r = vh;
				g = mid;
				b = m;
				break;
			case 1:
				r = mid2;
				g = vh;
				b = m;
				break;
			case 2:
				r = m;
				g = vh;
				b = mid;
				break;
			case 3:
				r = m;
				g = mid2;
				b = vh;
				break;
			case 4:
				r = mid;
				g = m;
				b = vh;
				break;
			case 5:
				r = vh;
				g = m;
				b = mid2;
				break;
        }
	}
	
	rgbq.rgbRed = (BYTE)(r*255.f);
	rgbq.rgbGreen = (BYTE)(g*255.f);
	rgbq.rgbBlue = (BYTE)(b*255.f);
	return rgbq;
}

INT z = 0;

COLORREF HSL(VOID) {
	DOUBLE HUE = fmod(z, 360),
	SAT = 1,
	VIB = 0.5f,
	C = (1 - fabs(2 * VIB - 1)) * SAT,
	X = C * (1 - fabs(fmod(HUE / 60, 2) - 1)),
	M = VIB - C / 2;
	
	DOUBLE R, G, B;
	if (HUE < 60) {
		R = C; G = X; B = 0;
	}
	else if (HUE < 120) {
		R = X; G = C; B = 0;
	}
	else if (HUE < 180) {
		R = 0; G = C; B = X;
	}
	else if (HUE < 240) {
		R = 0; G = X; B = C;
	}
	else if (HUE < 300) {
		R = X; G = 0; B = C;
	}
	else {
		R = C; G = 0; B = X;
	}
	INT RED = (INT)((R + M) * 255),
	GREEN = (INT)((G + M) * 255),
	BLUE = (INT)((B + M) * 255);
	z++;
	return RGB(RED, GREEN, BLUE);
}
