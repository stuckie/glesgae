#ifndef _COLOR_H_
#define _COLOR_H_

namespace GLESGAE
{
	class Color
	{
		public:
			explicit Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
			{
				mRGBA.r = r;
				mRGBA.g = g;
				mRGBA.b = b;
				mRGBA.a = a;
			}
			
			explicit Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
			{
				mRGBA.r = static_cast<unsigned char>(r);
				mRGBA.g = static_cast<unsigned char>(g);
				mRGBA.b = static_cast<unsigned char>(b);
				mRGBA.a = static_cast<unsigned char>(a);
			}
			
			explicit Color(float r, float g, float b, float a)
			{
				mRGBA.r = static_cast<unsigned char>(r * 255.0F);
				mRGBA.g = static_cast<unsigned char>(g * 255.0F);
				mRGBA.b = static_cast<unsigned char>(b * 255.0F);
				mRGBA.a = static_cast<unsigned char>(a * 255.0F);
			}
			
			explicit Color(unsigned int hex)
			{
				mHex = hex;
			}
			
			float fR() const { return static_cast<float>(mRGBA.r) / 255.0F; }
			float fG() const { return static_cast<float>(mRGBA.g) / 255.0F; }
			float fB() const { return static_cast<float>(mRGBA.b) / 255.0F; }
			float fA() const { return static_cast<float>(mRGBA.a) / 255.0F; }
			
			unsigned char bR() const { return mRGBA.r; }
			unsigned char bG() const { return mRGBA.g; }
			unsigned char bB() const { return mRGBA.b; }
			unsigned char bA() const { return mRGBA.a; }
			
			unsigned int iR() const { return static_cast<unsigned int>(mRGBA.r); }
			unsigned int iG() const { return static_cast<unsigned int>(mRGBA.g); }
			unsigned int iB() const { return static_cast<unsigned int>(mRGBA.b); }
			unsigned int iA() const { return static_cast<unsigned int>(mRGBA.a); }
			
		private:
			union { 
					struct { 
						unsigned char r, g, b, a;
					} mRGBA;
					unsigned char mComponents[4];
					unsigned int mHex;
				};
	};
}

#endif
