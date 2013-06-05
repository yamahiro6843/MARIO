#pragma once 

#include "ProjecterUtils.h"

namespace Projecter 
{
	class DispImage : public Image
	{
	public:
		DispImage()
		{}

		void DisplayToWindow()
		{
			// プロジェクタに投影
			cvNot( this->spImage.get() , this->spImage.get() ) ;
			cvShowImage( "Projecter Image" , this->spImage.get() ) ;
//			cvWaitKey(3);
		}

	};

}
