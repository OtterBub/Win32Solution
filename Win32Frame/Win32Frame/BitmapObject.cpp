#include "BitmapObject.h"
#include "Win32Frame.h"

#ifdef UNICODE
#define LoadImage  LoadImageW
#else
#define LoadImage  LoadImageA
#endif // !UNICODE

BitmapObject::BitmapObject()
{
	mBitmap = NULL;
	mDrawMode = SRCCOPY;
	mDestScale = OtterVector2f( 1, 1 );
	mIsTransparent = false;
}
#ifdef UNICODE
BitmapObject::BitmapObject( std::wstring filename )
{
	mBitmap = (HBITMAP)LoadImage( WIN32FRAME.GetHInstance(), filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	CreateBitmapInfo();
	mDestSize = OtterVector2f( mBitmapInfo.bmWidth, mBitmapInfo.bmHeight );
	mDestScale = OtterVector2f( 1, 1 );
	mSrcRect = OtterRect2f( 0, 0, mDestSize.x, mDestSize.y );
	mDrawMode = SRCCOPY;
	mIsTransparent = false;
}
bool BitmapObject::FileLoad( std::wstring filename )
{
	if( mBitmap != NULL )
		DeleteObject( mBitmap );
	mBitmap = (HBITMAP)LoadImage( WIN32FRAME.GetHInstance(), filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	CreateBitmapInfo();
	mDestSize = OtterVector2f( mBitmapInfo.bmWidth, mBitmapInfo.bmHeight );
	//mDestScale = OtterVector2f( 1, 1 );
	mSrcRect = OtterRect2f( 0, 0, mDestSize.x, mDestSize.y );
	return true;
}
#else
BitmapObject::BitmapObject( std::string filename )
{
	mBitmap = (HBITMAP)LoadImage( WIN32FRAME.GetHInstance(), filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	CreateBitmapInfo();
	mDestSize = OtterVector2f( mBitmapInfo.bmWidth, mBitmapInfo.bmHeight );
}
bool BitmapObject::FileLoad( std::string filename )
{
	if( mBitmap != NULL )
		DeleteObject( mBitmap );
	mBitmap = (HBITMAP)LoadImage( WIN32FRAME.GetHInstance(), filename.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	CreateBitmapInfo();
	mDestSize = OtterVector2f( mBitmapInfo.bmWidth, mBitmapInfo.bmHeight );
	return true;
}
#endif
BitmapObject::~BitmapObject()
{
	if( mBitmap != NULL )
		DeleteObject( mBitmap );
}

void BitmapObject::Update( float dt )
{
}

void BitmapObject::Draw( HDC hdc )
{
	HDC BitmapDC;
	BitmapDC = CreateCompatibleDC( hdc );
	SelectObject( BitmapDC, mBitmap );
	/*BitBlt( hdc, 
			mPosition.x - ( mBitmapInfo.bmWidth / 2 ), mPosition.y - ( mBitmapInfo.bmHeight / 2 ),
			mBitmapInfo.bmWidth, mBitmapInfo.bmHeight, 
			BitmapDC, 0, 0, SRCCOPY );*/
	if( mIsTransparent == false ) {
		StretchBlt( hdc,
					mPosition.x - ( mBitmapInfo.bmWidth / 2 ), mPosition.y - ( mBitmapInfo.bmHeight / 2 ),
					mDestSize.x * mDestScale.x, mDestSize.y * mDestScale.y,
					BitmapDC,
					mSrcPosition.x, mSrcPosition.y,
					mSrcSize.x, mSrcSize.y, mDrawMode );
	} else {
		TransparentBlt( hdc,
					mPosition.x - ( mBitmapInfo.bmWidth / 2 ), mPosition.y - ( mBitmapInfo.bmHeight / 2 ),
					mDestSize.x * mDestScale.x, mDestSize.y * mDestScale.y,
					BitmapDC,
					mSrcPosition.x, mSrcPosition.y,
					mSrcSize.x, mSrcSize.y, mTransparentRGB );
	}
	DeleteDC( BitmapDC );
}

void BitmapObject::Translate( float x, float y )
{
	Object::Translate( x, y );
}
void BitmapObject::Translate( OtterVector2f trans )
{
	Object::Translate( trans );
}
void BitmapObject::SetPosition( float x, float y )
{
	Object::SetPosition( x, y );
}
void BitmapObject::SetPosition( OtterVector2f pos )
{
	Object::SetPosition( pos );
}

void BitmapObject::SetScale( OtterVector2f scale )
{
	mDestScale = scale;
}
void BitmapObject::SetScale( float scaleX, float scaleY )
{
	mDestScale.x = scaleX;
	mDestScale.y = scaleY;
}
void BitmapObject::SetDestSize( OtterVector2f destSize )
{
	mDestSize = destSize;
}
void BitmapObject::SetDestSize( float width, float height )
{
	mDestSize.x = width;
	mDestSize.y = height;
}
void BitmapObject::SetSrcPosition( OtterVector2f pos )
{
	mSrcPosition = pos;
}
void BitmapObject::SetSrcPosition( float x, float y )
{
	mSrcPosition.x = x;
	mSrcPosition.y = y;
}
void BitmapObject::SetSrcSize( OtterVector2f size )
{
	mSrcSize = size;
}
void BitmapObject::SetSrcSize( float width, float height )
{
	mSrcSize.x = width;
	mSrcSize.y = height;
}

void BitmapObject::SetDrawMode( DWORD drawMode )
{
	mDrawMode = drawMode;
}

void BitmapObject::SetTransparent( bool isTransparent, UINT rgb )
{
	mIsTransparent = isTransparent;
	mTransparentRGB = rgb;
}

const BITMAP BitmapObject::GetBitmapInfo()
{
	return mBitmapInfo;
}

bool BitmapObject::CreateBitmapInfo()
{
	GetObject( mBitmap, sizeof(BITMAP), &mBitmapInfo );
	return true;
}