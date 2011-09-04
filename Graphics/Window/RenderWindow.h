#ifndef _RENDER_WINDOW_H_
#define _RENDER_WINDOW_H_

namespace GLESGAE
{

	class RenderContext;
	class RenderWindow
	{
		public:
			RenderWindow()
			: mContext(0)
			, mWidth(0U)
			, mHeight(0U)
			{

			}

			virtual ~RenderWindow() {}

			/// Open this window with the given name, width and height
			virtual void open(const char* windowName, const unsigned int width, const unsigned int height) = 0;

			/// Set this Window's Render Context
			virtual void setContext(RenderContext* const context) = 0;

			/// Get this Window's Render Context - returning the specified type
			template<typename T_Context> const T_Context* getContext() const { return reinterpret_cast<T_Context*>(mContext); }

			/// Get this Window's Render Context
			const RenderContext* getContext() const { return mContext; }

			/// Get the Width of this Window
			unsigned int getWidth() const { return mWidth; }

			/// Get the Height of this Window
			unsigned int getHeight() const { return mHeight; }

			/// Refresh the Window
			virtual void refresh() = 0;

			/// Close this window
			virtual void close() = 0;

		protected:
			RenderContext* mContext;
			unsigned int mWidth;
			unsigned int mHeight;
			
		private:
			// No copying
			RenderWindow(const RenderWindow&);
			RenderWindow& operator=(const RenderWindow&);
	};

}

#endif

